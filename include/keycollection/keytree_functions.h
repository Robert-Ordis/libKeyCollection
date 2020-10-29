/**
 *  \file   keytree_functions.h
 *  \brief 二分木用の関数定義を集めました
 */

#include <stdint.h>
#ifndef	KEYTREE_FUNCTIONS_H_
#define	KEYTREE_FUNCTIONS_H_

/**
 *	\typedef	yourtree_t
 *	\brief		ユーザーが定義する二分木型の名前
 *	\param		yourtree	実際に生成したい二分木型と関数のベースの名前
 *	\remarks	当該二分木型を操作する関数もyourtree_xxxという命名になります。
 */
#define	KEYTREE_T_(yourtree)			yourtree##_t

/**
 *	\typedef	yourtree_iterator_t
 *	\brief		ユーザーが定義する二分木におけるイテレータ型の名前
 *	\param		yourtree	実際に生成したいイテレータ型のベースの名前
 *	
 */
#define	KEYTREE_ITERATOR_T_(yourtree)	yourtree##_iterator_t

/**
 *	\fn			yourtree_init(*self, allow_eq, comp_node, make_node)
 *	\brief		二分木の初期化
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\param		allow_eq(int)0で同値の挿入不可。1で可能。
 *	\param		comp_node(int(type*, type*)) 2つのノードを比較する型
 *	\param		make_node(void(type*, void*, size_t))与えられた値ポインタから、比較用仮想ノードを作成する
 *	\return			(void)
 */
#define	KEYTREE_INIT_(yourtree)			yourtree##_init

/**
 *	\fn			yourtree_get_count(*self)
 *	\brief		二分木が抱えているノード数を取得
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\return			(int)二分木中の格納数
 */
#define	KEYTREE_GET_COUNT_(yourtree)	yourtree##_get_count

/**
 *	\fn			yourtree_ref_head(*self)
 *	\brief		二分木中の最初のノードを参照する
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL
 */
#define	KEYTREE_REF_HEAD_(yourtree)	yourtree##_ref_head

/**
 *	\fn			yourtree_ref_tail(*self)
 *	\brief		二分木中の最後のノードを参照する
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL
 */
#define	KEYTREE_REF_TAIL_(yourtree)		yourtree##_ref_tail

/**
 *	\fn			yourtree_pop_head(*self)
 *	\brief		二分木中の最初のノードを削除して取得する
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL。このノードは二分木から削除される。
 */
#define	KEYTREE_POP_HEAD_(yourtree)	yourtree##_pop_head

/**
 *	\fn			yourtree_pop_tail(*self)
 *	\brief		二分木中の最後のノードを削除して取得する
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL。このノードは二分木から削除される。
 */
#define	KEYTREE_POP_TAIL_(yourtree)		yourtree##_pop_tail

/**
 *	\fn			yourtree_ref_nth(*self, nth)
 *	\brief		N番目のノードを参照する
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\param		nth		(int)0を基準とした数。0で先頭、増えていってその後ろ。-1だと末尾。減っていってその前
 */

#define	KEYTREE_REF_NTH_(yourtree)		yourtree##_ref_nth

/**
 *	\fn			yourtree_add(*self, *node)
 *	\brief		二分木の末尾にノードを加える
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYTREE_ADD_(yourtree)			yourtree##_add

/**
 *	\fn			yourtree_del(*self, *node)
 *	\brief		二分木から該当するノードを削除する
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYTREE_DEL_(yourtree)			yourtree##_del

/**
 *	\fn			yourtree_insert_before(*self, *index_node, *node)
 *	\brief		二分木に対し、所定のノードの前に挿入する
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)挿入位置指定ノード。NULLで末尾挿入
 *	\param		node		(node_type_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 *	\remarks	これはあくまでリンクリストとして動かしたいときのためのもの
 */
#define	KEYTREE_INSERT_BEFORE_(yourtree)	yourtree##_insert_before

/**
 *	\fn			yourtree_insert_after(*self, *index_node, *node)
 *	\brief		二分木に対し、所定のノードの後に挿入する
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)挿入位置指定ノード。NULLで先頭挿入
 *	\param		node		(node_type_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 *	\remarks	これはあくまでリンクリストとして動かしたいときのためのもの
 */
#define	KEYTREE_INSERT_AFTER_(yourtree)		yourtree##_insert_after

/**
 *	\fn			yourtree_has_node(*self, *node)
 *	\brief		ノードを二分木が持っているかをチェックする
 *	\param		self	(yourtree_t*)取り扱う二分木
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)所属してる場合で1、それ以外で0
 */
#define	KEYTREE_HAS_NODE_(yourtree)	yourtree##_has_node

/**
 *	\fn			yourtree_get_next(*self, *node)
 *	\brief		指定ノードの「次」を取得する
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		node		(node_type_t*)前に扱ったノード。NULLで先頭を返す。
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYTREE_GET_NEXT_(yourtree)	yourtree##_get_next

/**
 *	\fn			yourtree_get_prev(*self, *node)
 *	\brief		指定ノードの「前」を取得する
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		node		(node_type_t*)前に扱ったノード。NULLで末尾を返す。
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYTREE_GET_PREV_(yourtree)	yourtree##_get_prev

/**
 *	\fn			yourtree_get_belong(*node)
 *	\brief		ノードが所属する二分木を参照する
 *	\param		node	(node_type_t*)所属を取りたいノード
 *	\return			(yourtree_t*)所属する二分木のポインタ。ない場合はNULL。
 */
#define	KEYTREE_GET_BELONG_(yourtree)	yourtree##_get_belong

/**
 *	\fn			yourtree_find_eq_node(*self, *node)
 *	\brief		ノードを元手に、同じ値を持つ左端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)参考ノード。所属してもしなくてもOK
 *	\return	該当した値の左端ノード。なければNULL
 */
#define	KEYTREE_FIND_EQ_NODE_(yourtree)			yourtree##_find_eq_node

/**
 *	\fn			yourtree_find_eq_value(*self, *value, value_len)
 *	\brief		指定されたポインタの値と同じ値を持つ左端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		value		(void*)値のポインタ。できればintを直接書くとかの運用はやめてね？
 *	\param		value_len	(size_t)値のポインタのバイト長。
 *	\return	該当した値の左端ノード。なければNULL
 */
#define	KEYTREE_FIND_EQ_VALUE_(yourtree)		yourtree##_find_eq_value

/**
 *	\fn			yourtree_find_eq_node_end(*self, *node)
 *	\brief		ノードを元手に、同じ値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)参考ノード。所属してもしなくてもOK
 *	\return	該当した値の右端ノード。なければNULL
 */
#define	KEYTREE_FIND_EQ_NODE_END_(yourtree)		yourtree##_find_eq_node_end

/**
 *	\fn			yourtree_find_eq_value_end(*self, *value, value_len)
 *	\brief		指定されたポインタの値と同じ値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		value		(void*)値のポインタ。できればintを直接書くとかの運用はやめてね？
 *	\param		value_len	(size_t)値のポインタのバイト長。
 *	\return	該当した値の右端ノード。なければNULL
 */
#define	KEYTREE_FIND_EQ_VALUE_END_(yourtree)	yourtree##_find_eq_value_end

/**
 *	\fn			yourtree_find_lt_node(*self, *node)
 *	\brief		指定したノード「未満」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)参考ノード。所属してもしなくてもOK
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_LT_NODE_(yourtree)			yourtree##_find_lt_node

/**
 *	\fn			yourtree_find_lt_value(*self, *value, value_len)
 *	\brief		指定したポインタの値「未満」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		value		(void*)値のポインタ。できればintを直接書くとかの運用はやめてね？
 *	\param		value_len	(size_t)値のポインタのバイト長。
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_LT_VALUE_(yourtree)		yourtree##_find_lt_value

/**
 *	\fn			yourtree_find_gt_node(*self, *node)
 *	\brief		指定したノード「超過」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)参考ノード。所属してもしなくてもOK
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_GT_NODE_(yourtree)			yourtree##_find_gt_node

/**
 *	\fn			yourtree_find_gt_value(*self, *value, value_len)
 *	\brief		指定したポインタの値「超過」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		value		(void*)値のポインタ。できればintを直接書くとかの運用はやめてね？
 *	\param		value_len	(size_t)値のポインタのバイト長。
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_GT_VALUE_(yourtree)		yourtree##_find_gt_value

/**
 *	\fn			yourtree_find_le_node(*self, *node)
 *	\brief		指定したノード「以下」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)参考ノード。所属してもしなくてもOK
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_LE_NODE_(yourtree)			yourtree##_find_le_node

/**
 *	\fn			yourtree_find_le_value(*self, *value, value_len)
 *	\brief		指定したポインタの値「以下」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		value		(void*)値のポインタ。できればintを直接書くとかの運用はやめてね？
 *	\param		value_len	(size_t)値のポインタのバイト長。
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_LE_VALUE_(yourtree)		yourtree##_find_le_value

/**
 *	\fn			yourtree_find_ge_node(*self, *node)
 *	\brief		指定したノード「以上」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		index_node	(node_type_t*)参考ノード。所属してもしなくてもOK
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_GE_NODE_(yourtree)			yourtree##_find_ge_node

/**
 *	\fn			yourtree_find_ge_value(*self, *value, value_len)
 *	\brief		指定したポインタの値「以上」の値を持つ右端ノードを探す
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		value		(void*)値のポインタ。できればintを直接書くとかの運用はやめてね？
 *	\param		value_len	(size_t)値のポインタのバイト長。
 *	\return	該当した値のノード。なければNULL
 */
#define	KEYTREE_FIND_GE_VALUE_(yourtree)		yourtree##_find_ge_value

/**
 *	\fn			yourtree_init_iterator(*self, *iterator)
 *	\brief		二分木のループを取るためのイテレータを初期化する
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(int)0
 *	\remarks	ここからtype_iterate_forwardを用いることで先頭からループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることで末尾からループを回す
 */
#define	KEYTREE_INIT_ITERATOR_(yourtree)	yourtree##_init_iterator

/**
 *	\fn			yourtree_init_iterator_ranged(*self, *iterator, *head, *tail)
 *	\brief		二分木のループを取るためのイテレータを初期化する。ついでに範囲を指定する
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\param		head		(node_type_t*)先頭ノード。NULLなら二分木の先頭をそのまま。
 *	\param		tail		(node_type_t*)末尾ノード。NULLなら二分木の末尾をそのまま。
 *	\return				(int)0。マイナス値はhead/tailがselfに所属していない場合。
 *	\remarks	ここからtype_iterate_forwardを用いることでheadからループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることでheadからループを回す
 */
#define	KEYTREE_INIT_ITERATOR_(yourtree)	yourtree##_init_iterator

/**
 *	\fn			yourtree_iterator_move(*iterator, *index_node)
 *	\brief		指定されたノードが次の起点になるようイテレータを移動させる
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\param		index_node	(node_type_t*)対象ノード。
 *	\return				(int)0:成功、-2:所属二分木が違う
 *	\remarks	ここからtype_iterator_forward/backwardで指定ノードからループが回る。
 */
#define	KEYTREE_ITERATOR_MOVE_(yourtree)	yourtree##_iterator_move

/**
 *	\fn			yourtree_iterator_forward(*iterator)
 *	\brief		前方向イテレーションを行う
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYTREE_ITERATOR_FORWARD_(yourtree)		yourtree##_iterator_forward

/**
 *	\fn			yourtree_iterator_backward(*iterator)
 *	\brief		後方向イテレーションを行う
 *	\param		self		(yourtree_t*)取り扱う二分木
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYTREE_ITERATOR_BACKWARD_(yourtree)		yourtree##_iterator_backward


#endif	/* !KEYTREE_FUNCTIONS_H_ */
