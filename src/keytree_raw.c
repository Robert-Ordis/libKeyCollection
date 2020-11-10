#include <stdlib.h>
#include <limits.h>

#include "keycollection/keytree.h"
#include "keycollection/keytree_raw.h"
#include "keycollection/keycollection_config.h"

#include "keycollection/private/keylist_inside.h"
#include "keycollection/private/keycollection_lock.h"

/*static関数群。*/

/*rand関数相当*/	
#define kt_rand_macro_(rng)	(int)(rng = (rng * 0x0fdeece66dllu + 0x0bllu) & 0x0000ffffffffffffllu) & 0x7fffffff
inline static int		kt_rand_r_(uint64_t *rng){	
	const static uint64_t rng_mul = 0x0fdeece66dllu;
	const static uint64_t rng_add = 0x0bllu;
	const static uint64_t rng_msk = 0x0000ffffffffffffllu;
	*rng = (*rng * rng_mul + rng_add) & rng_msk;
	return (int)(*rng & 0x7fffffffllu);
}

/*linkを、右方向に下げるように回転する*/
static int		keytree_link_rotate_right_(keytree_t *self, keytree_link_t *link){
	keytree_link_t *pivot = link->lt;		/*回転後のlinkの親。linkが右に降りるので元左子が昇格*/
	keytree_link_t **up_cursor;				/*linkを子としていたポインタ*/
	
	if(pivot == NULL){
		/*後釜のpivotがいないなら回転できません*/
		return -1;
	}
	
	/*まずはlinkを指しているポインタの特定*/
	if(link->up != NULL){
		up_cursor = (link->up->lt == link) ?
			&(link->up->lt) : &(link->up->ge);
	}
	else{
		up_cursor = &(self->root);
	}
	
	if(*(up_cursor) != link){
		/*nodeを指しているべきポインタがnodeを刺していない場合。assertでもするべき？*/
		return -2;
	}
	
	/*右回転開始*/
	/*pivotの右をlinkの左の里子へ出す*/
	link->lt = pivot->ge;
	if(link->lt != NULL){
		link->lt->up = link;
	}
	/*linkの元親とのリンク相手をpivotへ張り替える*/
	pivot->up = link->up;
	*up_cursor = pivot;
	/*最後に、pivotの右の子をnodeとする*/
	pivot->ge = link;
	link->up = pivot;
	/*終わり*/
	return 0;
}

/*linkを、左方向に下げるように回転する*/
static int		keytree_link_rotate_left_(keytree_t *self, keytree_link_t *link){
	keytree_link_t *pivot = link->ge;		/*回転後のlinkの親。linkが左に降りるので元右子が昇格*/
	keytree_link_t **up_cursor;				/*linkを子としていたポインタ*/
	
	if(pivot == NULL){
		/*後釜のpivotがいないなら回転できません*/
		return -1;
	}
	
	/*まずはlinkを指しているポインタの特定*/
	if(link->up != NULL){
		up_cursor = (link->up->lt == link) ?
			&(link->up->lt) : &(link->up->ge);
	}
	else{
		up_cursor = &(self->root);
	}
	
	if(*(up_cursor) != link){
		/*nodeを指しているべきポインタがnodeを刺していない場合。assertでもするべき？*/
		return -2;
	}
	
	/*左回転開始*/
	/*pivotの左をlinkの右の里子へ出す*/
	link->ge = pivot->lt;
	if(link->ge != NULL){
		link->ge->up = link;
	}
	/*linkの元親とのリンク相手をpivotへ張り替える*/
	pivot->up = link->up;
	*up_cursor = pivot;
	/*最後に、pivotの左の子をnodeとする*/
	pivot->lt = link;
	link->up = pivot;
	/*終わり*/
	return 0;
}

/*linkを、上方向に上げるように回転する*/
inline static  int		keytree_link_rotate_up_(keytree_t *self, keytree_link_t *link){
	if(link->up == NULL){
		/*そもそも上がいないのならこの話はなし*/
		return -1;
	}
	
	if(link->up->lt == link){
		/*親から見て左の子なら、親を起点に右回転*/
		return keytree_link_rotate_right_(self, link->up);
	}
	
	if(link->up->ge == link){
		/*親から見て右の子なら、親を起点に左回転*/
		return keytree_link_rotate_left_(self, link->up);
	}
	return -2;
}

static int		keytree_del_inside_(keytree_t *self, keytree_link_t *link){
	/*どちらかいる方の子ノードを指定。これをもとに削除後の後始末をつける*/
	keytree_link_t	*child;
	/*指定したノードの子が実質どれだけいるかを把握*/
	int				child_num;
	
	keytree_link_t	*parent;	/**/
	keytree_link_t	**cursor;
	keytree_link_t	*search;	/*兄弟持ち削除時の代替ノード*/
	keytree_link_t	**search_cursor;	/*兄弟持ち削除時の親のlt/ge書き換えカーソル*/
	keytree_link_t	*search_subtree;	/*兄弟持ち削除時の代替ノードの元サブツリー*/
	
	if(link->coll != self){
		return -1;
	}
	
	if(self->comp_node == NULL){
		/*そもそも比較関数を持たせてもらっていないならこの話は終わり*/
		return 0;
	}
#ifndef	KEYTREE_ROUGHLY_TREAP_DELETION
	{
		int promote_right;
		/*treep実装*/
		while(1){
			/*linkが葉になるまで回転を続ける*/
			/*ただし、方向は「優先度値が小さい＝高い方の子が新しい親になる」もの*/
			if(link->lt != NULL && link->ge != NULL){
				/*右の優先度値が小さい＝高い場合は右を昇格*/
				promote_right = (link->lt->h_pri > link->ge->h_pri);
			}
			else if(link->lt == NULL && link->ge == NULL){
				/*どっちもいない場合、linkは葉ノードなので回転終わり。*/
				break;
			}
			else{
				/*どっちか片方ならば、存在する方を昇格させる*/
				promote_right = (link->ge != NULL);
			}
			if(promote_right){
				/*右を昇格＝自分は左子へ降格*/
				keytree_link_rotate_left_(self, link);
			}
			else{
				/*左を昇格＝自分は右子へ降格*/
				keytree_link_rotate_right_(self, link);
			}
		}
		
		parent = link->up;
		if(parent != NULL){
			cursor = (parent->lt == link) ? &(parent->lt) : &(parent->ge);
		}
		else{
			cursor = &(self->root);
		}
		if(*(cursor) != link){
			/* must assert ? */
			return -3;
		}
		*cursor = NULL;
		link->up = link->lt = link->ge = NULL;
	}
	return 0;
	
#endif	/* !KEYTREE_ROUGHLY_TREAP_DELETION*/
	/*本来、Treap実装ならば要らない部分ではあるが…*/
	/*どちらかいる方の子ノードを指定。削除後の後始末をつけるためのもの*/
	child = (link->lt == NULL) ? link->ge : link->lt;
	/*指定ノードの子供の人数把握。これで処理を決定*/
	child_num = (link->lt != NULL ? 1:0) + (link->ge != NULL ? 1:0);
	
	parent = link->up;
	cursor = &(self->root);
	if(parent != NULL){
		cursor = (parent->lt == link) ? &(parent->lt) : &(parent->ge);
	}
	if(*(cursor) != link){
		/*must assert?*/
		return -3;
	}
	
	/*子供の人数で計算*/
	switch(child_num){
	case 2:	/*兄弟持ち*/
		/*左部分木の最大ノードを見つけてsearchとする*/
		search = link->lt;
		search_cursor = &(search->lt);
		parent = search;
		while(search->ge != NULL){
			parent = search;
			search_cursor = &(search->ge);
			search = search->ge;
		}
		search_subtree = search->lt;
		
		/*searchが削除対象(link)になり替わる*/
		*cursor = search;	/*linkの親からのリンクを書き換える*/
		search->up = link->up;
		search->lt = link->lt;
		search->ge = link->ge;
		search->h_pri = link->h_pri;
		
		/*部分木最大ノードの親子関係整理*/
		*search_cursor = search_subtree;
		if(search_subtree != NULL){
			search_subtree->up = parent;
		}
		/*全部終わったら、searchが引き取った里子のリンクを張り直し*/
		if(search->lt != NULL){
			search->lt->up = search;
		}
		if(search->ge != NULL){
			search->ge->up = search;
		}
		
		break;
	case 1:	/*一人っ子。かわいい一人っ子を、自分の親に引き合わせる*/
		child->up = link->up;
	case 0:	/*子なし（葉ノード）。一人っ子の場合と共通処理*/
		*cursor = child;
	}
	
	link->up = link->lt = link->ge = NULL;
	return 0;
}

inline static keytree_link_t*	keytree_link_get_prev_(keytree_link_t *link){
	return link->prev;
}

inline static keytree_link_t*	keytree_link_get_next_(keytree_link_t *link){
	return link->next;
}
/*
void		keytree_init_raw(size_t offset, keytree_t *self);

int		keytree_get_count_raw(size_t offset, keytree_t *self);

void*		keytree_ref_head_raw(size_t offset, keytree_t *self);

void*		keytree_ref_tail_raw(size_t offset, keytree_t *self);
*/
void*			keytree_pop_head_raw(size_t offset, keytree_t *self){
	keytree_link_t *link = NULL;
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		if(self->head != NULL){
			link = self->head;
			ret = keytree_del_inside_(self, link);
			if(ret >= 0){
				KEYLIST_IMPL_DEL_(self, link, ret);
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	
	return keycollection_get_container_ptr(offset, link);
}

void*			keytree_pop_tail_raw(size_t offset, keytree_t *self){
	keytree_link_t *link = NULL;
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		if(self->tail != NULL){
			link = self->tail;
			ret = keytree_del_inside_(self, link);
			if(ret >= 0){
				KEYLIST_IMPL_DEL_(self, link, ret);
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	
	return keycollection_get_container_ptr(offset, link);
}

void*			keytree_ref_nth_raw(size_t offset, keytree_t *self, int nth){
	keytree_link_t *link = NULL;\
	int i = nth;\
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		/*indexでもつけて効率化するべき？*/
		KEYLIST_IMPL_REF_NTH_(self, link, i);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return keycollection_get_container_ptr(offset, link);
}

int				keytree_add_raw(size_t offset, keytree_t *self, void *node){
	keytree_link_t *link = (keytree_link_t *)keycollection_get_link_ptr(offset, node);
	int ret = 0;
	keytree_link_t		**cursor;		/*親リンクのltまたはgeを指すポインタ。親なしならself->root*/
	keytree_link_t		*parent;		/*nodeの親になるノードのリンク*/
	int comp_ret = 1;					/*比較結果。nodeof(*cursor) - nodeに相当する*/
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		if(link->coll != NULL){
			KEYCOLLECT_LOCK_RELEASE_(self);
			return -1;
		}
		if(self->comp_node != NULL){
			cursor = &(self->root);
			parent = NULL;
			
			while(*cursor != NULL){
				/*葉に落ち着くまでカーソルを操作する*/
				parent = *cursor;
				void *node_c = keycollection_get_container_ptr(offset, parent);
				/*nodeが*cursor以上の値を持つかを検査*/
				comp_ret = self->comp_node(node, node_c);
				if(comp_ret == 0){
					/*同値だった場合→同値NGに引っ掛けるか同値間ソートを動かすか*/
					if(!self->allow_eq){
						KEYCOLLECT_LOCK_RELEASE_(self);
						return -2;
					}
					if(self->comp_equivalent != NULL){
						comp_ret = self->comp_equivalent(node, node_c);
					}
				}
				cursor = (comp_ret >= 0) ? &(parent->ge) : &(parent->lt);
			}
			
			*cursor = link;
			link->up = parent;
			link->lt = link->ge = NULL;
			
			/*ツリー挿入が終わったので、線形リストとしての挿入を実行する*/
			if(comp_ret >= 0){
				KEYLIST_IMPL_INSERT_AFTER_(self, parent, link, ret);
			}
			else{
				KEYLIST_IMPL_INSERT_BEFORE_(self, parent, link, ret);
			}
			
			/*ここからtreap実装*/
			link->h_pri = kt_rand_r_(&self->rng);
			/*
			link->h_pri = kt_rand_r_(&self->rng);
			link->h_pri = kt_rand_macro_(self->rng);
			link->h_pri = nrand48(self->rng);
			*/
			/*printf("%s: h_pri:%ld\n", __func__, link->h_pri);*/
			while(1){
				/*親の優先度 = 子の優先度でヒープを作る*/
				if(link->up == NULL){
					break;
				}
				if(link->up->h_pri <= link->h_pri){
					break;
				}
				if(keytree_link_rotate_up_(self, link) < 0){
					break;
				}
			}
			
		}
		else{
			/*比較関数が存在しないときは、単なる中途挿入がないリスト*/
			KEYLIST_IMPL_ADD_TAIL_(self, link, ret);
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keytree_del_raw(size_t offset, keytree_t *self, void *node){
	keytree_link_t *link = (keytree_link_t *)keycollection_get_link_ptr(offset, node);
	int ret = -3;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		ret = keytree_del_inside_(self, link);
		if(ret >= 0){
			KEYLIST_IMPL_DEL_(self, link, ret);
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keytree_insert_before_raw(size_t offset, keytree_t *self, void *index_node, void *node){
	keytree_link_t *link = (keytree_link_t *)keycollection_get_link_ptr(offset, node);
	keytree_link_t *index_link = (keytree_link_t *)keycollection_get_link_ptr(offset, index_node);
	int ret = -3;
	if(self->comp_node != NULL){
		/*ツリーとしての前提を持っているのなら単純にツリーとして挿入する*/
		return keytree_add_raw(offset, self, node);
	}
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		/*ツリーとしての前提がない場合のみ*/
		KEYLIST_IMPL_INSERT_BEFORE_(self, index_link, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keytree_insert_after_raw(size_t offset, keytree_t *self, void *index_node, void *node){
	keytree_link_t *link = (keytree_link_t *)keycollection_get_link_ptr(offset, node);
	keytree_link_t *index_link = (keytree_link_t *)keycollection_get_link_ptr(offset, index_node);
	int ret = -3;
	if(self->comp_node != NULL){
		/*ツリーとしての前提を持っているのなら単純にツリーとして挿入する*/
		return keytree_add_raw(offset, self, node);
	}
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		/*ツリーとしての前提がない場合のみ*/
		KEYLIST_IMPL_INSERT_AFTER_(self, index_link, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

void*			keytree_find_eq_node_raw(size_t offset, keytree_t *self, void *index_node){
	keytree_link_t	*curr_link;
	void			*curr_node = NULL;
	void			*ret;
	int				comp_ret;
	
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		curr_link = self->root;
		while(curr_link != NULL){
			curr_node = keycollection_get_container_ptr(offset, curr_link);
			comp_ret = self->comp_node(curr_node, index_node);
			if(comp_ret > 0){
				/*current > index: より小さなnodeを求める*/
				curr_link = curr_link->lt;
			}
			else if(comp_ret < 0){
				/*current < index: より大きなnodeを求める*/
				curr_link = curr_link->ge;
			}
			else{
				/*一致したので第1段階終わり*/
				break;
			}
		}
		ret = (curr_link == NULL) ? NULL : curr_node;
		/*curr_node == index_nodeが崩れるまで同値中を「値が下がる方向」へたどる*/
		/*同値の同居を許す仕様であり、同値の「最も小さいもの」を探すため*/
		if(self->allow_eq && ret != NULL){
			do{
				ret = curr_node;
				curr_link = keytree_link_get_prev_(curr_link);
				curr_node = keycollection_get_container_ptr(offset, curr_link);
			}while(curr_link != NULL && self->comp_node(curr_node, index_node) == 0);
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	
	return ret;
}

void*			keytree_find_eq_node_end_raw(size_t offset, keytree_t *self, void *index_node){
	keytree_link_t	*curr_link;
	void			*curr_node = NULL;
	void			*ret;
	int				comp_ret;
	
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		curr_link = self->root;
		while(curr_link != NULL){
			curr_node = keycollection_get_container_ptr(offset, curr_link);
			comp_ret = self->comp_node(curr_node, index_node);
			if(comp_ret > 0){
				/*current > index: より小さなnodeを求める*/
				curr_link = curr_link->lt;
			}
			else if(comp_ret < 0){
				/*current < index: より大きなnodeを求める*/
				curr_link = curr_link->ge;
			}
			else{
				/*一致したので第1段階終わり*/
				break;
			}
		}
		ret = (curr_link == NULL) ? NULL : curr_node;
		/*curr_node == index_nodeが崩れるまで同値中を「値が下がる方向」へたどる*/
		/*同値の同居を許す仕様であり、同値の「最も小さいもの」を探すため*/
		if(self->allow_eq && ret != NULL){
			do{
				ret = curr_node;
				curr_link = keytree_link_get_next_(curr_link);
				curr_node = keycollection_get_container_ptr(offset, curr_link);
			}while(curr_link != NULL && self->comp_node(curr_node, index_node) == 0);
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	
	return ret;
}

void*			keytree_find_le_node_raw(size_t offset, keytree_t *self, void *index_node){
	keytree_link_t	*curr_link;
	void			*curr_node = NULL;
	void			*ret;
	int				comp_ret = 0;
	if(self->size <= 0){
		return NULL;
	}
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		curr_link = self->root;
		//curr_node = keycollection_get_container_ptr(offset, curr_link);
		ret = NULL;
		while(curr_link != NULL){
			/*curr_node >= index_nodeを求めて探索開始*/
			curr_node = keycollection_get_container_ptr(offset, curr_link);
			ret = curr_node;
			comp_ret = self->comp_node(curr_node, index_node);
			if(comp_ret > 0){
				/*current > index: より小さなcurrentを求める*/
				curr_link = curr_link->lt;
			}
			else if(comp_ret < 0){
				/*current < index: より大きなnodeを求める*/
				curr_link = curr_link->ge;
			}
			else{
				/*一致: 「以上」を求めるので第1段階終わり*/
				break;
			}
		}
		
		/*探索を抜けた時のcurrentがindex「以下」なら、「超過」になる直前までcurr_nodeを進めていく*/
		if(comp_ret <= 0){
			curr_link = keycollection_get_link_ptr(offset, curr_node);
			while(ret != NULL){
				curr_link = keytree_link_get_next_(curr_link);
				curr_node = keycollection_get_container_ptr(offset, curr_link);
				if(curr_link == NULL || self->comp_node(curr_node, index_node) > 0){
					break;
				}
				ret = curr_node;
			}
		}
		/*探索を抜けた時のcurrentがindex「超過」なら、「以下」になるまでcurr_nodeを戻していく*/
		else{
			curr_link = keycollection_get_link_ptr(offset, ret);
			while(ret != NULL){
				curr_link = keytree_link_get_prev_(curr_link);
				ret = keycollection_get_container_ptr(offset, curr_link);
				if(ret == NULL || self->comp_node(ret, index_node) <= 0){
					break;
				}
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

void*			keytree_find_ge_node_raw(size_t offset, keytree_t *self, void *index_node){
	keytree_link_t	*curr_link;
	void			*curr_node = NULL;
	void			*ret;
	int				comp_ret = 0;
	if(self->size <= 0){
		return NULL;
	}
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		curr_link = self->root;
		//curr_node = keycollection_get_container_ptr(offset, curr_link);
		ret = NULL;
		while(curr_link != NULL){
			/*curr_node >= index_nodeを求めて探索開始*/
			curr_node = keycollection_get_container_ptr(offset, curr_link);
			ret = curr_node;
			comp_ret = self->comp_node(curr_node, index_node);
			if(comp_ret > 0){
				/*current > index: より小さなcurrentを求める*/
				curr_link = curr_link->lt;
			}
			else if(comp_ret < 0){
				/*current < index: より大きなnodeを求める*/
				curr_link = curr_link->ge;
			}
			else{
				/*一致: 「以上」を求めるので第1段階終わり*/
				break;
			}
		}
		
		/*探索を抜けた時のcurrentがindex「以上」なら、「未満」になる直前までcurr_nodeを戻っていく*/
		if(comp_ret >= 0){
			curr_link = keycollection_get_link_ptr(offset, curr_node);
			while(ret != NULL){
				curr_link = keytree_link_get_prev_(curr_link);
				curr_node = keycollection_get_container_ptr(offset, curr_link);
				if(curr_link == NULL || self->comp_node(curr_node, index_node) < 0){
					break;
				}
				ret = curr_node;
			}
		}
		/*探索を抜けた時のcurrentがindex「未満」なら、「以上」になるまでcurr_nodeを進めていく*/
		else{
			curr_link = keycollection_get_link_ptr(offset, ret);
			while(ret != NULL){
				curr_link = keytree_link_get_next_(curr_link);
				ret = keycollection_get_container_ptr(offset, curr_link);
				if(ret == NULL || self->comp_node(ret, index_node) >= 0){
					break;
				}
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

void*			keytree_find_lt_node_raw(size_t offset, keytree_t *self, void *index_node){
	keytree_link_t	*curr_link;
	void			*curr_node;
	void			*ret;
	int				comp_ret = 0;
	if(self->size <= 0){
		return NULL;
	}
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		curr_link = self->root;
		ret = NULL;
		while(curr_link != NULL){
			/*curr_node >= index_nodeを求めて探索開始*/
			curr_node = keycollection_get_container_ptr(offset, curr_link);
			ret = curr_node;
			comp_ret = self->comp_node(curr_node, index_node);
			if(comp_ret > 0){
				/*current > index: より小さなcurrentを求める*/
				curr_link = curr_link->lt;
			}
			else if(comp_ret <= 0){
				/*current <= index: より大きなnodeを求める*/
				curr_link = curr_link->ge;
			}
		}
		
		/*探索を抜けた時のcurrentがindex「以上」なら、「未満」になるまでcurr_nodeを戻っていく*/
		if(comp_ret >= 0){
			curr_link = keycollection_get_link_ptr(offset, ret);
			while(ret != NULL){
				curr_link = keytree_link_get_prev_(curr_link);
				ret = keycollection_get_container_ptr(offset, curr_link);
				if(ret == NULL || self->comp_node(ret, index_node) < 0){
					break;
				}
			}
		}
		/*探索を抜けた時のcurrentがindex「未満」なら、「以上」になる直前までcurr_nodeを進めていく*/
		else{
			curr_node = ret;
			curr_link = keycollection_get_link_ptr(offset, curr_node);
			while(ret != NULL){
				curr_link = keytree_link_get_next_(curr_link);
				curr_node = keycollection_get_container_ptr(offset, curr_link);
				if(curr_node == NULL || self->comp_node(curr_node, index_node) >= 0){
					break;
				}
				ret = curr_node;
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

void*			keytree_find_gt_node_raw(size_t offset, keytree_t *self, void *index_node){
	keytree_link_t	*curr_link;
	void			*curr_node;
	void			*ret;
	int				comp_ret = 0;
	if(self->size <= 0){
		return NULL;
	}
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		curr_link = self->root;
		ret = NULL;
		while(curr_link != NULL){
			/*curr_node >= index_nodeを求めて探索開始*/
			curr_node = keycollection_get_container_ptr(offset, curr_link);
			ret = curr_node;
			comp_ret = self->comp_node(curr_node, index_node);
			if(comp_ret > 0){
				/*current > index: より小さなcurrentを求める*/
				curr_link = curr_link->lt;
			}
			else if(comp_ret <= 0){
				/*current <= index: より大きなnodeを求める*/
				curr_link = curr_link->ge;
			}
		}
		
		/*探索を抜けた時のcurrentがindex「以下」なら、「超過」になるまでcurr_nodeを進めていく*/
		if(comp_ret <= 0){
			curr_link = keycollection_get_link_ptr(offset, ret);
			while(ret != NULL){
				curr_link = keytree_link_get_next_(curr_link);
				ret = keycollection_get_container_ptr(offset, curr_link);
				if(ret == NULL || self->comp_node(ret, index_node) > 0){
					break;
				}
			}
		}
		/*探索を抜けた時のcurrentがindex「超過」なら、「以下」になる直前までcurr_nodeを戻していく*/
		else{
			curr_node = ret;
			curr_link = keycollection_get_link_ptr(offset, curr_node);
			while(ret != NULL){
				curr_link = keytree_link_get_prev_(curr_link);
				curr_node = keycollection_get_container_ptr(offset, curr_link);
				if(curr_node == NULL || self->comp_node(curr_node, index_node) <= 0){
					break;
				}
				ret = curr_node;
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keytree_init_iterator_raw(size_t offset, keytree_t *self, keytree_iterator_t *iterator){
	iterator->prev = self->tail;
	iterator->next = self->head;
	iterator->curr = NULL;
	iterator->coll = self;
	iterator->head = NULL;
	iterator->tail = NULL;
	return 0;
}

int			keytree_init_iterator_ranged_raw(size_t offset, keytree_t *self, keytree_iterator_t *iterator, void *head, void *tail){
	/*ちょっとした遊び心を搭載してみるテスト*/
	keytree_link_t	*head_link = keycollection_get_link_ptr(offset, head);
	keytree_link_t	*tail_link = keycollection_get_link_ptr(offset, tail);
	
	if(head_link != NULL && head_link->coll != self){
		return -2;
	}
	
	if(tail_link != NULL && tail_link->coll != self){
		return -2;
	}
	
	/*forwardで出てくるのはhead指定したノード。もしくは生来のhead*/
	iterator->next = (head_link != NULL) ? head_link : self->head;
	
	/*backwardで出てくるのはtail指定したノード。もしくは生来のtail*/
	iterator->prev = (tail_link != NULL) ? tail_link : self->tail;
	
	
	iterator->head = head_link;
	iterator->tail = tail_link;
	
	iterator->curr = NULL;
	iterator->coll = self;
	
	return 0;
}

int				keytree_iterator_move_raw(size_t offset, keytree_iterator_t *iterator, void *index_node){
	int ret = 0;
	keytree_link_t *index_link = (keytree_link_t *)keycollection_get_link_ptr(offset, index_node);
	KEYCOLLECT_LOCK_ACQUIRE_(iterator->coll);{
		KEYLIST_IMPL_ITERATOR_MOVE_(iterator, index_link, ret);
		if(iterator->head != NULL){
			iterator->next = iterator->head;
		}
		if(iterator->tail != NULL){
			iterator->prev = iterator->tail;
		}
	}KEYCOLLECT_LOCK_RELEASE_(iterator->coll);
	return ret;
}


void*			keytree_iterator_forward_raw(size_t offset, keytree_iterator_t *iterator){
	keytree_link_t	*tmp_link = iterator->next;
	keytree_link_t	*ret_link;
	KEYCOLLECT_LOCK_ACQUIRE_(iterator->coll);{
		KEYLIST_IMPL_ITERATE_FORWARD_(iterator, tmp_link, ret_link);
		if(iterator->tail != NULL){
			if(ret_link ==iterator->tail){
				/*範囲定義時の終端にぶち当たったらループ終わり*/
				iterator->next = NULL;
			}
			else if(iterator->curr == iterator->coll->tail){
				/*範囲定義時の終端ではないが、コレクションの終端ならばコレクションの始端に移動*/
				iterator->next = iterator->coll->head;
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(iterator->coll);
	return keycollection_get_container_ptr(offset, ret_link);
}

void*			keytree_iterator_backward_raw(size_t offset, keytree_iterator_t *iterator){
	keytree_link_t	*tmp_link = iterator->prev;
	keytree_link_t	*ret_link;
	KEYCOLLECT_LOCK_ACQUIRE_(iterator->coll);{
		KEYLIST_IMPL_ITERATE_BACKWARD_(iterator, tmp_link, ret_link);
		if(iterator->head != NULL){
			if(ret_link == iterator->head){
				/*範囲定義時の終端にぶち当たったらループ終わり*/
				iterator->prev = NULL;
			}
			else if(iterator->curr == iterator->coll->head){
				/*範囲定義時の始端ではないが、コレクションの始端に当たったらコレクションの終端に移動*/
				iterator->prev = iterator->coll->tail;
			}
		}
	}KEYCOLLECT_LOCK_RELEASE_(iterator->coll);
	return keycollection_get_container_ptr(offset, ret_link);
}

/*
keytree_t*	keytree_link_get_belonged_raw(offset, node);
*/

void*			keytree_link_get_next_raw(size_t offset, void* node){
	return keycollection_get_container_ptr(offset,
		keytree_link_get_next_(
			(keytree_link_t *)keycollection_get_link_ptr(offset, node)
		)
	);
}

void*			keytree_link_get_prev_raw(size_t offset, void* node){
	return keycollection_get_container_ptr(offset,
		keytree_link_get_prev_(
			(keytree_link_t *)keycollection_get_link_ptr(offset, node)
		)
	);
}



