/**
 *  \file		keytree.h
 *  \brief		二分木構造をマクロで定義するためのライブラリ
 *	\remarks	平衡度の確保は現在、Treapを使っています
 *	\remarks	〇〇以上とか○○未満という感じのあいまい検索に強いはずです
 */
 
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <pthread.h>
#include "./keytree_functions.h"
#include "./private/keylist_implementations.h"
#ifndef	KEYTREE_H_
#define	KEYTREE_H_


//公開マクロ中
//公開マクロ中にて使用する各種マクロ

#define	KEYTREE_INNER_TYPE_S_(basename)			struct keytree_##basename##_s

/**
 *	\struct	keytree_link_basename_t
 *	\brief		構造体において、２分木を構成するキーになるメンバの構造体
 */
#define	KEYTREE_LINK_TYPE_T_(basename)		keytree_link_##basename##_t					//メンバ用リンク構造体
#define	KEYTREE_LINK_TYPE_S_(basename)		struct keytree_link_##basename##_s			//素のメンバ用リンク構造体定義
#define	KEYTREE_INNER_ITERATOR_TYPE_S_(basename)	struct keytree_iterator_##basename##_s				//イテレータ



//プライベート
#ifdef __linux__
	#define	KEYTREE_LOCK_INIT_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_init(&(self)->lock, NULL);\
		}while(0)\

	#define	KEYTREE_LOCK_ACQUIRE_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_lock(&(self)->lock);\
		}while(0)\
		
	#define	KEYTREE_LOCK_RELEASE_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_unlock(&(self)->lock);\
		}while(0)\

	#define	KEYTREE_LOCKER_T	pthread_mutex_t
#else
	#define	KEYTREE_LOCK_INIT_(self)\
		do{\
		}while(0)\

	#define	KEYTREE_LOCK_ACQUIRE_(self)\
		do{\
		}while(0)\
		
	#define	KEYTREE_LOCK_RELEASE_(self)\
		do{\
		}while(0)\

	#define	KEYTREE_LOCKER_T	void*

#endif /* __linux__ */

/**
 *	\def	keytree_define_basetype
 *	\brief	構造体の前に行う最初の宣言。
 */
#define	keytree_define_basetype(basename, nodetype_s)\
	typedef	int		(*KEYTREE_NODE_COMP_T_(basename))(nodetype_s *node_a, nodetype_s *node_b);\
	typedef	void	(*KEYTREE_NODE_VIRT_T_(basename))(nodetype_s *node, void *value, size_t value_len);\
	typedef KEYTREE_LINK_TYPE_S_(basename) {\
		nodetype_s	*ge;	/*「以上」のためのリンク*/\
		nodetype_s	*lt;	/*「未満」のためのリンク*/\
		nodetype_s	*up;	/*「親元」のためのリンク*/\
		void		*tree;	/*所属ツリー*/\
		int			h_pri;	/*Treap用。*/\
		\
		struct{				/*リンクリストメンバ*/\
			nodetype_s	*prev;\
			nodetype_s	*next;\
			void		*list;\
		}list_link;\
	} KEYTREE_LINK_TYPE_T_(basename);\
	\
	KEYTREE_INNER_ITERATOR_TYPE_S_(basename){\
		nodetype_s	*prev;\
		nodetype_s	*curr;\
		nodetype_s	*next;\
		nodetype_s	*head;\
		nodetype_s	*tail;\
		void		*list;\
	};\
	\
	KEYTREE_INNER_TYPE_S_(basename){\
		nodetype_s			*head;		/*イテレーション用。最も値の小さいノード*/\
		nodetype_s			*tail;		/*イテレーション用。最も値の大きいノード*/\
		uint32_t			count;		/*内包ノード数*/\
		int					if_lock;	/*操作中のロックを実施するかどうか*/\
		KEYTREE_LOCKER_T	lock;		/*ロック用メンバ（たいていmutex）*/\
		nodetype_s			*root;		/*ツリーの根ノード*/\
		int					allow_eq;	/*「以上」において、同値の挿入を許すなら1*/\
		int					r_seed;		/*Treap用。乱数の種*/\
		KEYTREE_NODE_COMP_T_(basename)	comp;\
		KEYTREE_NODE_VIRT_T_(basename)	virt;\
	}

/**
 *	\def	keytree_define_prototypes
 *	\param	yourtree		yourtree_t及び関連型や関連関数(yourtree_xxx)が出来上がる。
 *	\param	basename		keytree_define_basetypeで使用したbasetypeをそのまま使う。
 *	\param	nodetype_s		実際に取り扱いたいノード型。struct nodetype_sでやるのが無難。
 *	\param	link_member		今回のリストにおけるリンカとして用いるメンバ変数名
 *	\brief	構造体の後に行う各種宣言。
 *	\brief	yourtree_tとyourtree_iterator_t及び関連関数(yourtree_xxx)が出来上がる。
 */
#define	keytree_define_prototypes(yourtree, basename, nodetype_s, link_member)\
	typedef			KEYTREE_INNER_TYPE_S_(basename) KEYTREE_T_(yourtree);\
	typedef			KEYTREE_INNER_ITERATOR_TYPE_S_(basename) KEYTREE_ITERATOR_T_(yourtree);\
	\
	void			KEYTREE_INIT_(yourtree)(KEYTREE_T_(yourtree) *self, int if_lock, int allow_eq, KEYTREE_NODE_COMP_T_(basename) comp, KEYTREE_NODE_VIRT_T_(basename) find);\
	\
	/*単純な「とる」系。popはツリーからいなくなるので注意*/\
	\
	int				KEYTREE_GET_COUNT_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_REF_FIRST_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_REF_LAST_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	/*nodetype_s*		KEYTREE_POP_FIRST_(yourtree)(KEYTREE_T_(yourtree) *self);*/\
	\
	/*nodetype_s*		KEYTREE_POP_LAST_(yourtree)(KEYTREE_T_(yourtree) *self);*/\
	\
	KEYTREE_T_(yourtree)* KEYTREE_GET_BELONGED_(yourtree)(nodetype_s* node);\
	\
	/*編集系API*/\
	\
	int				KEYTREE_ADD_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	int				KEYTREE_DEL_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	int				KEYTREE_INSERT_BEFORE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYTREE_INSERT_AFTER_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	/*「探す」系*/\
	\
	nodetype_s*		KEYTREE_FIND_EQ_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_EQ_END_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_GE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_LT_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	/*イテレーション関連*/\
	\
	int				KEYTREE_INIT_ITERATOR_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	int				KEYTREE_INIT_ITERATOR_FROM_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator, nodetype_s *node);\
	\
	nodetype_s*		KEYTREE_ITERATE_FORWARD_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	nodetype_s*		KEYTREE_ITERATE_BACKWARD_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	int				KEYTREE_ITERATOR_IS_HEAD_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	int				KEYTREE_ITERATOR_IS_TAIL_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	nodetype_s*		KEYTREE_GET_NEXT_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	nodetype_s*		KEYTREE_GET_PREV_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	int			KEYTREE_DBG_TRAVERSE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *root, int level, int (*dump)(nodetype_s*, char*, int));\
	\
	
/**
 *	\def	keytree_define_implements
 *	\param	yourtree		yourtree_t及び関連型や関連関数(yourtree_xxx)が出来上がる。
 *	\param	basename		keytree_define_basetypeで使用したbasetypeをそのまま使う。
 *	\param	nodetype_s		実際に取り扱いたいノード型。struct nodetype_sでやるのが無難。
 *	\param	link_member		今回のリストにおけるリンカとして用いるメンバ変数名
 *	\brief	構造体の後に行う各種宣言。
 *	\brief	yourtree_tとyourtree_iterator_t及び関連関数(yourtree_xxx)が出来上がる。
 */
#define	keytree_define_implements(yourtree, basename, nodetype_s, link_member)\
	\
	void			KEYTREE_INIT_(yourtree)(KEYTREE_T_(yourtree) *self, int if_lock,int allow_eq, KEYTREE_NODE_COMP_T_(basename) comp, KEYTREE_NODE_VIRT_T_(basename) virt){\
		self->if_lock = (if_lock != 0);\
		KEYTREE_LOCK_INIT_(self);\
		self->head = NULL;\
		self->tail = NULL;\
		self->count = 0;\
		self->comp = comp;\
		self->virt = virt;\
		self->root = NULL;\
		self->r_seed = (int)(&((self)->r_seed));\
		self->allow_eq = allow_eq != 0;\
		\
		/*NULL指定をもらっていた場合は「線形リスト」としての運用しかしないと宣言する*/\
		/*本来これをやるのはリソースの無駄遣いも甚だしいが、それが必要な場面があるので仕方ない（keyhashのおはなし）*/\
		if((self)->comp == NULL  || (self)->virt == NULL){\
			(self)->comp = NULL;\
			(self)->virt = NULL;\
		}\
	}\
	\
	/*単純な「とる」系。popはツリーからいなくなるので注意*/\
	\
	int				KEYTREE_GET_COUNT_(yourtree)(KEYTREE_T_(yourtree) *self){\
		int ret;\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			ret = self->count;\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYTREE_REF_FIRST_(yourtree)(KEYTREE_T_(yourtree) *self){\
		nodetype_s	*ret;\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			ret = self->head;\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYTREE_REF_LAST_(yourtree)(KEYTREE_T_(yourtree) *self){\
		nodetype_s	*ret;\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			ret = self->tail;\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*nodetype_s*		KEYTREE_POP_FIRST_(yourtree)(KEYTREE_T_(yourtree) *self);*/\
	\
	/*nodetype_s*		KEYTREE_POP_LAST_(yourtree)(KEYTREE_T_(yourtree) *self);*/\
	\
	KEYTREE_T_(yourtree)* KEYTREE_GET_BELONGED_(yourtree)(nodetype_s* node){\
		return (node)->link_member.tree;\
	}\
	\
	/*編集系裏API(主だっての使用はしないやつ。static化予定)*/\
	\
	int				KEYTREE_ROTATE_RIGHT_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		nodetype_s	*pivot = (node)->link_member.lt;	/*回転後のnodeの親*/\
		nodetype_s	**up_cursor;						/*nodeを子としていたポインタ*/\
		if(pivot == NULL){\
			/*回転するべき先がいない場合は回転できない*/\
			return -1;\
		}\
		up_cursor = &((self)->root);\
		if((node)->link_member.up != NULL){\
			up_cursor = ((node)->link_member.up->link_member.lt) == node ?\
				&((node)->link_member.up->link_member.lt) :\
				&((node)->link_member.up->link_member.ge) ;\
		}\
		if(*(up_cursor) != node){\
			/*nodeを指しているべきポインタが実際にnodeを指しているかチェック*/\
			return -2;\
		}\
		/*右回転開始*/\
		/*pivotの右をnodeの左の里子へ出す*/\
		node->link_member.lt = pivot->link_member.ge;\
		if(node->link_member.lt != NULL){\
			node->link_member.lt->link_member.up = node;\
		}\
		/*nodeの元親とのリンク相手をpivotへ張り替える*/\
		pivot->link_member.up = node->link_member.up;\
		*up_cursor = pivot;\
		/*最後に、pivotの右の子をnodeとする*/\
		pivot->link_member.ge = node;\
		node->link_member.up = pivot;\
		/*終わり*/\
		return 0;\
	}\
	\
	int				KEYTREE_ROTATE_LEFT_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		nodetype_s	*pivot = (node)->link_member.ge;	/*回転後のnodeの親。nodeの右子を昇格*/\
		nodetype_s	**up_cursor;						/*nodeを子としていたポインタ*/\
		if(pivot == NULL){\
			/*回転するべき先がいない場合は回転できない*/\
			return -1;\
		}\
		up_cursor = &((self)->root);\
		if((node)->link_member.up != NULL){\
			up_cursor = ((node)->link_member.up->link_member.lt) == node ?\
				&((node)->link_member.up->link_member.lt) :\
				&((node)->link_member.up->link_member.ge) ;\
		}\
		if(*(up_cursor) != node){\
			/*nodeを指しているべきポインタが実際にnodeを指しているかチェック*/\
			return -2;\
		}\
		/*左回転開始*/\
		/*pivotの左をnodeの右の里子へ出す*/\
		node->link_member.ge = pivot->link_member.lt;\
		if(node->link_member.ge != NULL){\
			node->link_member.ge->link_member.up = node;\
		}\
		/*nodeの元親とのリンク相手をpivotへ張り替える*/\
		pivot->link_member.up = node->link_member.up;\
		*up_cursor = pivot;\
		/*最後に、pivotの左の子をnodeとする*/\
		pivot->link_member.lt = node;\
		node->link_member.up = pivot;\
		/*終わり*/\
		return 0;\
	}\
	\
	int				KEYTREE_ROTATE_UP_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		if((node)->link_member.up == NULL){\
			/*そもそも上がいないのならこの話はなし*/\
			return -1;\
		}\
		if((node)->link_member.up->link_member.lt == node){\
			/*親から見て左の子なら、親を起点に右回転*/\
			return KEYTREE_ROTATE_RIGHT_(yourtree)(self, (node)->link_member.up);\
		}\
		if((node)->link_member.up->link_member.ge == node){\
			/*親から見て右の子なら、親を起点に左回転*/\
			return KEYTREE_ROTATE_LEFT_(yourtree)(self, (node)->link_member.up);\
		}\
		return -2;\
	}\
	/*編集系API(listと違ってinsert before/afterはない)*/\
	\
	int				KEYTREE_ADD_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		int			ret;\
		/*ルートから比較していく→左右ずれていって末尾にたどり着く→そこで定住＆insert_before/after*/\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			nodetype_s 	**cursor;		/*カーソル。ツリーリンクのポインタを示す*/\
			nodetype_s 	*parent;		/*挿入位置ノードの親ノード*/\
			int			comp_ret = 1;	/*比較結果。*cursor - nodeに相当する演算結果*/\
			/*無所属であることを確認する*/\
			if((node) == NULL || (node)->link_member.tree != NULL){\
				KEYTREE_LOCK_RELEASE_(self);\
				return -1;\
			}\
			if((self)->comp != NULL){\
				/*比較関数が存在する場合に限ってツリーとして動く*/\
				cursor = &((self)->root);\
				parent = NULL;\
				\
				/*葉に落ち着く（＝カーソルが示したリンクポインタがNULLになる）までカーソルを操作する*/\
				while(*cursor != NULL){\
					parent = *cursor;\
					/*nodeが*cursor以上の値を持つかを検査する*/\
					comp_ret = (self)->comp(node, *cursor);\
					/*printf("%s: comp_ret is %d and allow_eq is %d\n", __func__, comp_ret, (self)->allow_eq);*/\
					if((self)->allow_eq == 0 && comp_ret == 0){\
						KEYTREE_LOCK_RELEASE_(self);\
						return -2;\
					}\
					cursor = (comp_ret >= 0) ? &((parent)->link_member.ge) : &((parent)->link_member.lt);\
					\
					\
				}\
				*cursor = node;\
				(node)->link_member.up = parent;\
				(node)->link_member.lt = NULL;\
				(node)->link_member.ge = NULL;\
				/*TODO: 乱数をつけたので、ここでTreapとして昇格ローテーションを繰り返す*/\
				node->link_member.h_pri = rand_r(&((self)->r_seed)) & 0x0000FFFF;\
				while(1){\
					/*仮：親の優先度 <= 子の優先度でヒープを作る*/\
					if((node)->link_member.up == NULL){\
						break;\
					}\
					/*printf("%s: pri parent[%d] vs node[%d]\n", __func__, (node)->link_member.up->link_member.h_pri, (node)->link_member.h_pri);*/\
					if((node)->link_member.up->link_member.h_pri <= (node)->link_member.h_pri){\
						break;\
					}\
					if(KEYTREE_ROTATE_UP_(yourtree)(self, node) < 0){\
						break;\
					}\
					\
				}\
				/*ツリー挿入は終わったので、後は線形リストとしての挿入*/\
				if(comp_ret >= 0){\
					/*parentの後に挿入*/\
					KEYLIST_IMPL_INSERT_AFTER_(self, parent, node, link_member.list_link , ret);\
				}\
				else{\
					/*parentの前に挿入*/\
					KEYLIST_IMPL_INSERT_BEFORE_(self, parent, node, link_member.list_link , ret);\
				}\
			}\
			else{\
				/*比較関数が存在しないときはただの中途挿入がないリスト*/\
				KEYLIST_IMPL_ADD_(self, node, parent, link_member.list_link, ret);\
			}\
			(node)->link_member.tree = self;\
		}KEYTREE_LOCK_RELEASE_(self);\
		\
		return ret;\
	}\
	\
	int				KEYTREE_DEL_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		int ret;\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			if((node) == NULL || (node)->link_member.tree != self){\
				KEYTREE_LOCK_RELEASE_(self);\
				return -1;\
			}\
			if((self)->comp != NULL){\
				int tmp;/*0:左を昇格、1:右を昇格*/\
				while(1){\
					/*葉になるまで回転を続ける*/\
					/*ただし、方向は「小さいほうの子が新しい親になる」もの*/\
					if((node)->link_member.lt != NULL && (node)->link_member.ge != NULL){\
						/*printf("%s: [%p(%d)] left_pri:%d, right_pri:%d\n", __func__, node, \
							(node)->link_member.h_pri, \
							(node)->link_member.lt->link_member.h_pri, \
							(node)->link_member.ge->link_member.h_pri);\
						*/\
						tmp = (node)->link_member.lt->link_member.h_pri > (node)->link_member.ge->link_member.h_pri ;\
					}\
					else if((node)->link_member.lt != NULL && (node)->link_member.ge == NULL){\
						tmp = 0;\
					}\
					else if((node)->link_member.lt == NULL && (node)->link_member.ge != NULL){\
						tmp = 1;\
					}\
					else{\
						break;\
					}\
					if(tmp){\
						KEYTREE_ROTATE_LEFT_(yourtree)(self, node);\
					}\
					else{\
						KEYTREE_ROTATE_RIGHT_(yourtree)(self, node);\
					}\
				}\
				\
				/*どちらかいる方の子ノードを指定する。これをもとに削除後の後始末をつける*/\
				nodetype_s	*child = (node)->link_member.lt == NULL ? (node)->link_member.ge:(node)->link_member.lt;\
				/*指定したノードの子が実質どれだけいるかを把握する*/\
				int			child_num = ((node)->link_member.lt != NULL ? 1:0) + ((node)->link_member.ge != NULL ? 1:0);\
				\
				nodetype_s	*parent = (node)->link_member.up;\
				nodetype_s	**cursor = &((self)->root);\
				nodetype_s	*search;	/*兄弟持ち削除時の代替ノード*/\
				nodetype_s	**search_cursor;/*兄弟持ち削除時の親のlt/geリンク書き換え用カーソル*/\
				nodetype_s	*search_subtree;/*兄弟持ち削除時の代替ノードのサブツリー*/;\
				if(parent != NULL){\
					/*削除対象に親がいるのなら、「親からnodeへたどっていたリンクを書き換える」準備をする*/\
					/*リンクは二又に分かれているので、ひとまず「ltがnodeを指しているかどうか」で判断する*/\
					cursor = ((parent)->link_member.lt == node) ? &((parent)->link_member.lt) : &((parent)->link_member.ge);\
				}\
				if(*(cursor) != node){\
					/*書き換えようと思ったリンクが自分自身じゃない場合はちょっとどうしようもないので取りやめ*/\
					KEYTREE_LOCK_RELEASE_(self);\
					return -2;\
				}\
				/*子持ち検査*/\
				switch(child_num){\
				case 2:	/*兄弟持ち*/\
					/*左部分木の最大ノードを見つけてsearchとする*/\
					search = (node)->link_member.lt;\
					search_cursor = &((search)->link_member.lt);\
					parent = search;\
					while((search)->link_member.ge != NULL){\
						parent = (search);\
						search_cursor = &((search)->link_member.ge);\
						search = (search)->link_member.ge;\
					}\
					search_subtree = (search)->link_member.lt;\
					/*printf("%s: node:%p, search:%p, search_subtree:%p, parent:%p\n", __func__, node, search, search_subtree, parent);\
					printf("%s: node->up:%p, search->up:%p\n", __func__, node->link_member.up, search->link_member.up);\
					printf("%s: node->lt:%p, search->lt:%p\n", __func__, node->link_member.lt, search->link_member.lt);\
					printf("%s: node->ge:%p, search->ge:%p\n", __func__, node->link_member.ge, search->link_member.ge);\
					*/\
					/*searchが削除対象(node)になり替わる*/\
					*cursor = search;	/*nodeの親からのリンクを書き換え*/\
					(search)->link_member.up = (node)->link_member.up;\
					(search)->link_member.lt = (node)->link_member.lt;\
					(search)->link_member.ge = (node)->link_member.ge;\
					\
					/*部分木最大ノードの親子関係を整理する*/\
					*search_cursor = search_subtree;\
					if(search_subtree != NULL){\
						(search_subtree)->link_member.up = parent;\
					}\
					/*全部終わったら、searchが引き取った里子の親リンクを張りなおす*/\
					if((search)->link_member.lt != NULL){\
						(search)->link_member.lt->link_member.up = search;\
					}\
					if((search)->link_member.ge != NULL){\
						(search)->link_member.ge->link_member.up = search;\
					}\
					\
					break;\
				case 1:	/*一人っ子*/\
					/*一人っ子なので、childの親をnodeからnodeの親へとすり替える*/\
					child->link_member.up = node->link_member.up;\
				case 0:	/*子なし（葉ノード）*/\
					/*(*cursor) = child。子なしならchildはNULLとなっている*/\
					*cursor = child;\
					break;\
				}\
			}\
			KEYLIST_IMPL_DEL_(self, node, link_member.list_link, ret);\
			memset(&((node)->link_member), 0, sizeof(KEYTREE_LINK_TYPE_T_(basename)));\
			/*終わったらリストモジュールでのデリートも行う*/\
		}KEYTREE_LOCK_RELEASE_(self);\
		\
		return ret;\
	}\
	\
	int				KEYTREE_INSERT_BEFORE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node){\
		int ret;\
		/*ツリーとしての要件を満たさない場合にのみinsert_beforeとして動く*/\
		if((self)->comp != NULL){\
			return KEYTREE_ADD_(yourtree)(self, node);\
		}\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INSERT_BEFORE_(self, index_node, node, link_member.list_link, ret);\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYTREE_INSERT_AFTER_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node){\
		int ret;\
		/*ツリーとしての要件を満たさない場合にのみinsert_afterとして動く*/\
		if((self)->comp != NULL){\
			return KEYTREE_ADD_(yourtree)(self, node);\
		}\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INSERT_AFTER_(self, index_node, node, link_member.list_link, ret);\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*「探す」系*/\
	\
	nodetype_s*		KEYTREE_FIND_EQ_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s	virt_node;	/*比較処理用仮想ノード*/\
		nodetype_s*	node;		/*探索用ノード*/\
		nodetype_s*	ret;\
		int			comp_ret;\
		/*まずは比較用の仮想ノードを作成。作成方法は初期化時に教わってます*/\
		(self)->virt(&virt_node, value, value_len);\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			/*探索開始。*/\
			node = (self)->root;\
			while(node != NULL){\
				comp_ret = (self)->comp(node, &virt_node);\
				if(comp_ret > 0){\
					/*node > value*/\
					/*比較用valueがnodeのより小さいので、より小さなnodeを求める*/\
					node = (node)->link_member.lt;\
				}\
				else if(comp_ret < 0){\
					/*node < value*/\
					/*比較用valueがnodeのより大きいので、より大きなnodeを求める*/\
					node = (node)->link_member.ge;\
				}\
				else{\
					/*値が一致した場合*/\
					break;\
				}\
			}\
			ret = node;\
			/*node == virtが崩れるまで同値を「値が下がる方向」へたどっていく*/\
			/*→同値の同居を許せる仕様であることと、この関数は同値の「最も小さいもの」を探すため*/\
			if((self)->allow_eq && ret != NULL){\
				do{\
					ret = node;\
					node = KEYTREE_GET_PREV_(yourtree)(self, node);\
				}while(node != NULL && (self)->comp(node, &virt_node) == 0);\
				\
			}\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYTREE_FIND_EQ_END_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s	virt_node;	/*比較処理用仮想ノード*/\
		nodetype_s*	node;		/*探索用ノード*/\
		nodetype_s*	ret;\
		int			comp_ret;\
		/*まずは比較用の仮想ノードを作成。作成方法は初期化時に教わってます*/\
		(self)->virt(&virt_node, value, value_len);\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			/*探索開始。*/\
			node = (self)->root;\
			ret = NULL;\
			while(node != NULL){\
				comp_ret = (self)->comp(node, &virt_node);\
				if(comp_ret > 0){\
					/*node > value*/\
					/*比較用valueがnodeのより小さいので、より小さなnodeを求める*/\
					node = (node)->link_member.lt;\
				}\
				else if(comp_ret < 0){\
					/*node < value*/\
					/*比較用valueがnodeのより大きいので、より大きなnodeを求める*/\
					node = (node)->link_member.ge;\
				}\
				else{\
					/*値が一致した場合*/\
					break;\
				}\
			}\
			ret = node;\
			/*node == virtが崩れるまで同値を「値が上がる方向」へたどっていく*/\
			/*→同値の同居を許せる仕様であることと、この関数は同値の「最も大きいもの」を探すため*/\
			if((self)->allow_eq && ret != NULL){\
				do{\
					ret = node;\
					node = KEYTREE_GET_NEXT_(yourtree)(self, node);\
				}while(node != NULL && (self)->comp(node, &virt_node) == 0);\
				\
			}\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYTREE_FIND_GE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		/*指定した値「以上」のうち、最小のノードを探し出す*/\
		nodetype_s	virt_node;	/*比較処理用仮想ノード*/\
		nodetype_s*	node;		/*探索用ノード*/\
		nodetype_s*	ret;		/*返値*/\
		int			comp_ret;\
		if(self->count <= 0){\
			return NULL;\
		}\
		/*まずは比較用の仮想ノードを作成。作成方法は初期化時に教わってます*/\
		(self)->virt(&virt_node, value, value_len);\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			/*node >= valueを求めて探索開始。*/\
			node = (self)->root;\
			ret = NULL;\
			while(node != NULL){\
				ret = node;\
				comp_ret = (self)->comp(node, &virt_node);\
				/*node >= valueで一番小さな値が欲しいのです*/\
				if(comp_ret > 0){\
					/*node > value*/\
					/*比較用valueがnodeのより小さいので、より小さなnodeを求める*/\
					node = (node)->link_member.lt;\
				}\
				else if(comp_ret < 0){\
					/*node < value*/\
					/*比較用valueがnodeのより大きいので、より大きなnodeを求める*/\
					node = (node)->link_member.ge;\
				}\
				else{\
					/*値が一致した場合：今回の目的は「以上」なので打ち切る*/\
					break;\
				}\
			}\
			/*printf("%s: binsearch_end. ret[%p] with %d\n", __func__, ret, comp_ret);*/\
			/*探索を抜けた鬨のnodeがvalue「以上」なら、「未満」になる直前までnodeを減らす（->prev)*/\
			if(comp_ret >= 0){\
				node = ret;\
				while(ret != NULL){\
					node = KEYTREE_GET_PREV_(yourtree)(self, node);\
					if(node == NULL || (self)->comp(node, &virt_node) < 0){\
						break;\
					}\
					ret = node;\
				}\
			}\
			/*探索を抜けた時のnodeがvalue「未満」なら、「以上」になるまでnodeを増やす（->next)*/\
			else{\
				while(ret != NULL){\
					ret = KEYTREE_GET_NEXT_(yourtree)(self, ret);\
					if(ret == NULL || (self)->comp(ret, &virt_node) >= 0){\
						break;\
					}\
				}\
			}\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYTREE_FIND_LT_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		/*指定した値「未満」のうち、最大のノードを探し出す*/\
		nodetype_s	virt_node;	/*比較処理用仮想ノード*/\
		nodetype_s*	node;		/*探索用ノード*/\
		nodetype_s*	ret;		/*返値*/\
		int			comp_ret;\
		if(self->count <= 0){\
			return NULL;\
		}\
		/*まずは比較用の仮想ノードを作成。作成方法は初期化時に教わってます*/\
		(self)->virt(&virt_node, value, value_len);\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			/*node >= valueを求めて探索開始。*/\
			node = (self)->root;\
			ret = NULL;\
			while(node != NULL){\
				ret = node;\
				comp_ret = (self)->comp(node, &virt_node);\
				if(comp_ret > 0){\
					/*node > value*/\
					/*比較用valueがnode未満なので、より小さなnodeを求める*/\
					node = (node)->link_member.lt;\
				}\
				else if(comp_ret <= 0){\
					/*node < value*/\
					/*比較用valueがnode以上なので、より大きなnodeを求める*/\
					node = (node)->link_member.ge;\
				}\
			}\
			/*printf("%s: binsearch_end. ret[%p] with %d\n", __func__, ret, comp_ret);*/\
			/*探索を抜けた鬨のnodeがvalue「以上」なら、「未満」になるまでnodeを減らす（->prev)*/\
			if(comp_ret >= 0){\
				while(ret != NULL){\
					ret = KEYTREE_GET_PREV_(yourtree)(self, ret);\
					if(ret == NULL || (self)->comp(ret, &virt_node) < 0){\
						break;\
					}\
				}\
			}\
			/*探索を抜けた時のnodeがvalue「未満」なら、「以上」になる直前までnodeを増やす（->next)*/\
			else{\
				node = ret;\
				while(ret != NULL){\
					node = KEYTREE_GET_NEXT_(yourtree)(self, node);\
					if(node == NULL || (self)->comp(node, &virt_node) >= 0){\
						break;\
					}\
					ret = node;\
				}\
			}\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*イテレーション関連*/\
	\
	int				KEYTREE_INIT_ITERATOR_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		(iterator)->prev = (self)->tail;\
		(iterator)->next = (self)->head;\
		(iterator)->curr = NULL;\
		(iterator)->list = self;\
		(iterator)->head = (self)->head;\
		(iterator)->tail = (self)->tail;\
		return 0;\
	}\
	\
	int				KEYTREE_INIT_ITERATOR_FROM_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator, nodetype_s *node){\
		if(node == NULL){\
			return KEYTREE_INIT_ITERATOR_(yourtree)(self, iterator);\
		}\
		if((node)->link_member.list_link.list != self){\
			return -1;\
		}\
		(iterator)->curr = node;\
		(iterator)->next = (node)->link_member.list_link.next;\
		(iterator)->prev = (node)->link_member.list_link.prev;\
		(iterator)->list = self;\
		(iterator)->head = (self)->head;\
		(iterator)->tail = (self)->tail;\
		return 0;\
	}\
	\
	nodetype_s*		KEYTREE_ITERATE_FORWARD_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		nodetype_s *ret = NULL;\
		nodetype_s *next = (iterator)->next;\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATE_FORWARD_(self, iterator, next, link_member.list_link, ret);\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
		\
	}\
	\
	nodetype_s*		KEYTREE_ITERATE_BACKWARD_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		nodetype_s *ret = NULL;\
		nodetype_s *prev = (iterator)->prev;\
		KEYTREE_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATE_BACKWARD_(self, iterator, prev, link_member.list_link, ret);\
		}KEYTREE_LOCK_RELEASE_(self);\
		return ret;\
		\
	}\
	\
	int				KEYTREE_ITERATOR_IS_HEAD_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		return (iterator)->head == (iterator)->curr;\
	}\
	\
	int				KEYTREE_ITERATOR_IS_TAIL_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		return (iterator)->tail == (iterator)->curr;\
	}\
	\
	nodetype_s*		KEYTREE_GET_NEXT_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		if(node == NULL){\
			return self->head;\
		}\
		return self == (node)->link_member.tree ? (node)->link_member.list_link.next : NULL;\
	}\
	\
	nodetype_s*		KEYTREE_GET_PREV_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		if(node == NULL){\
			return (self)->tail;\
		}\
		return (self == (node)->link_member.tree) ? (node)->link_member.list_link.prev : NULL;\
	}\
	\
	int			KEYTREE_DBG_TRAVERSE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *root, int level, int (*dump)(nodetype_s*, char*, int)){\
		char buf[64];\
		buf[0] = '\0';\
		if(root == NULL){\
			root = (self)->root;\
		}\
		\
		if(root == NULL){\
			return 0;\
		}\
		if(dump != NULL){\
			if((*dump)(root, buf, 64) < 0){\
				return -1;\
			}\
			/*printf("%s:[%p(%03d)]:pri->%8d, val->%s, up->%p, lt->%p, ge->%p\n", __func__, root, level, root->link_member.h_pri, buf, root->link_member.up, root->link_member.lt, root->link_member.ge);*/\
		}\
		else{\
		}\
		\
		if(root->link_member.lt != NULL){\
			if(KEYTREE_DBG_TRAVERSE_(yourtree)(self, root->link_member.lt, level + 1, dump) < 0){\
				return -2;\
			}\
		}\
		if(root->link_member.ge != NULL){\
			if(KEYTREE_DBG_TRAVERSE_(yourtree)(self, root->link_member.ge, level + 1, dump) < 0){\
				return -3;\
			}\
		}\
		return 0;\
	}\
	\

#endif	/* !KEYTREE_H_ */

