/**
 *  \file		keytree_reference.h
 *  \brief		２分木構造のいわゆる「デフォルト実装」に該当する部分
 *	\remarks	どちらかというとこれは、関数リファレンスのガイド用として作ったものです
 *	\remarks	任意の構造体の頭にkeytree_node_tを付ける使い方はできるけどお勧めしません
 */
#include "keytree.h"
#include "keytree_functions.h"

#ifndef	KEYTREE_REFERENCE_H_
#define	KEYTREE_REFERENCE_H_

/**
 *	\struct	keytree_node_t
 *	\brief		２分木処理におけるデフォルトのノード構造体
 *	\remark	任意の構造体の頭にkeytree_node_tをつけると「何でもツリー」が出来上がります（お勧めしません）
 */
typedef	struct keytree_node_s keytree_node_t;

keytree_define_basetype(keytree_node, struct keytree_node_s);

struct keytree_node_s {
	keytree_link_keytree_node_t	link;
};

keytree_define_prototypes(keytree, keytree_node, struct keytree_node_s, link);


/**
 *	\struct	keytree_t
 *	\brief		２分木のコンテナ構造体
 */
 
/**
 *	\struct	keytree_iterator_t
 *	\brief		２分木のイテレータ構造体
 */
 
/**
 *	\typedef	keytree_comp_keytree_node_t
 *	\brief		所定のノード同士を比較するための関数ポインタ型名
 *	\arg		node_a	(keytree_node_t*)比較対象A
 *	\arg		node_b	(keytree_node_t*)比較対象B
 *	\return			(int) node_a - node_bに相当する演算結果。1か-1か0だけでも守っておけばOK
 */
//#define	KEYTREE_NODE_COMP_T_(keytree_node)		keytree_comp_##keytree_node##_t

/**
 *	\typedef	keytree_virt_keytree_node_t
 *	\brief		値からノードを求めるための仮想ノード構築関数ポインタ名
 *	\arg		node		(keytree_node_t*)構築対象の仮想ノード
 *	\arg		value		(void*)キーとする値
 *	\arg		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(void)
 */
//#define	KEYTREE_NODE_VIRT_T_(keytree_node)		keytree_virt_##keytree_node##_t

/**
 *	\fn			keytree_init
 *	\brief		ツリーの初期化
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		if_lock		(int)ツリー自身にロックを持たせる場合1、そうではなく、ロックは外でやる場合0
 *	\param		allow_eq	(int)同値の同居を許すかどうか。0で不許可。それ以外でOK
 *	\param		comp		(keytree_comp_keytree_node_t)ツリー挿入用の比較関数
 *	\param		virt		(keytree_virt_keytree_node_t)ツリー探索用の仮想比較ノード構築関数
 *	\return				(void)
 */
//#define	KEYTREE_INIT_(keytree)			keytree##_init

/**
 *	\fn			keytree_get_count
 *	\brief		ツリーが抱えているノード数を取得
 *	\param		self	(keytree_t*)取り扱うツリー
 *	\return			(int)ツリー中の格納数
 */
//#define	KEYTREE_GET_COUNT_(keytree)	keytree##_get_count

/**
 *	\fn			keytree_refer_first
 *	\brief		ツリー中の先頭のノードを参照する（ルートではなく最小値ノード）
 *	\param		self	(keytree_t*)取り扱うツリー
 *	\return			(keytree_node_t*)先頭ノードのポインタ。ない場合はNULL
 */
//#define	KEYTREE_REF_FIRST_(keytree)	keytree##_refer_first

/**
 *	\fn			keytree_refer_last
 *	\brief		ツリー中の最後のノードを参照する
 *	\param		self	(keytree_t*)取り扱うツリー
 *	\return			(keytree_node_t*)末尾ノードのポインタ。ない場合はNULL
 */
//#define	KEYTREE_REF_LAST_(keytree)		keytree##_refer_last


/**
 *	\fn			keytree_get_belonged
 *	\brief		ノードが所属するツリーを参照する
 *	\param		node	(keytree_node_t*)対象ノード
 *	\return			(keytree_t*)所属するツリーのポインタ。ない場合はNULL。
 */
//#define	KEYTREE_GET_BELONGED_(keytree)	keytree##_get_belonged

/**
 *	\fn			keytree_add
 *	\brief		ツリーにノードを加える。この際、比較はツリー中に定義されたものを使用。
 *	\param		self	(keytree_t*)取り扱うツリー
 *	\param		node	(keytree_node_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
//#define	KEYTREE_ADD_(keytree)			keytree##_add

/**
 *	\fn			keytree_del
 *	\brief		ツリーから該当するノードを削除する
 *	\param		self	(keytree_t*)取り扱うツリー
 *	\param		node	(keytree_node_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
//#define	KEYTREE_DEL_(keytree)			keytree##_del

//listでのinsert_beforeとinsert_afterはツリーでは成立しないので削除。

/**
 *	\fn			keytree_find_eq
 *	\brief		ツリーから該当する値「同等」のノードを探る
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\arg		value		(void*)キーとする値
 *	\arg		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(keytree_node_t*)該当するうち最小に位置するノード。ない場合はNULL
 */
//#define	KEYTREE_FIND_EQ_(keytree)		keytree##_find_eq

/**
 *	\fn			keytree_find_eq_end
 *	\brief		ツリーから該当する値「同等」の最大ノードを探る
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち最小に位置するノード。ない場合はNULL
 */
//#define	KEYTREE_FIND_EQ_END_(yourtree)	keytree##_find_eq_end

/**
 *	\fn			keytree_find_ge
 *	\brief		ツリーから該当する値「以上」のノードを探る
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\arg		value		(void*)キーとする値
 *	\arg		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(keytree_node_t*)該当するうち最小に位置するノード。ない場合はNULL
 *	\brief		まあ、主にイテレーションの末尾を取る用って考えておけばいいです。
 */
//#define	KEYTREE_FIND_GE_(keytree)		keytree##_find_ge

/**
 *	\fn			keytree_find_lt
 *	\brief		ツリーから該当する値「未満」のノードを探る
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\arg		value		(void*)キーとする値
 *	\arg		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(keytree_node_t*)該当するうち最大に位置するノード。ない場合はNULL
 *	\brief		まあ、主にイテレーションの頭を取る用って考えておけばいいです。
 */
//#define	KEYTREE_FIND_LT_(keytree)		keytree##_find_lt

/**
 *	\fn			keytree_init_iterator
 *	\brief		ツリーのループを取るためのイテレータを初期化する
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		iterator	(keytree_iterator_t*)イテレータ
 *	\return				(int)0
 *	\remarks	ここからtype_iterate_forwardを用いることで先頭からループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることで末尾からループを回す
 */
//#define	KEYTREE_INIT_ITERATOR_(keytree)	keytree##_init_iterator

/**
 *	\fn			keytree_init_iterator_from
 *	\brief		ツリーループのイテレータを、ループ開始ノードを指定して初期化する
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		iterator	(keytree_iterator_t*)イテレータ
 *	\param		node_from	(keytree_node_t*)開始位置の指定。
 *	\return				(int)成功で0、失敗でマイナス
 *	\remarks	node_from=NULLでtype_init_iteratorと等価
 *	\remarks	node_fromは必ずselfに所属してなければならない
 */
//#define	KEYTREE_INIT_ITERATOR_FROM_(keytree)	keytree##_init_iterator_from

/**
 *	\fn			keytree_iterate_forward
 *	\brief		前方向イテレーションを行う
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		iterator	(keytree_iterator_t*)イテレータ
 *	\return				(keytree_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYTREE_ITERATE_FORWARD_(keytree)		keytree##_iterate_forward

/**
 *	\fn			keytree_iterate_backward
 *	\brief		後方向イテレーションを行う
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		iterator	(keytree_iterator_t*)イテレータ
 *	\return				(keytree_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYTREE_ITERATE_BACKWARD_(keytree)		keytree##_iterate_backward

/**
 *	\fn			keytree_iterator_is_head
 *	\brief		イテレーションが「初期化時における」先頭かどうかを判定する。
 *	\param		iterator	(keytree_iterator_t*)取り扱うイテレータ
 *	\return				(int)先頭なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYTREE_ITERATOR_IS_HEAD_(keytree)		keytree##_is_head_of_iterator

/**
 *	\fn			keytree_iterator_is_tail
 *	\brief		イテレーションが「初期化時における」末尾かどうかを判定する。
 *	\param		iterator	(keytree_iterator_t*)イテレータ
 *	\return				(int)末尾なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYTREE_ITERATOR_IS_TAIL_(keytree)		keytree##_is_tail_of_iterator

/**
 *	\fn			keytree_get_next
 *	\brief		指定ノードの「次」を取得する
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		node		(keytree_node_t*)前に扱ったノード。NULLで先頭を返す。
 *	\return				(keytree_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
//#define	KEYTREE_GET_NEXT_(keytree)	keytree##_get_next

/**
 *	\fn			keytree_get_prev
 *	\brief		指定ノードの「前」を取得する
 *	\param		self		(keytree_t*)取り扱うツリー
 *	\param		node		(keytree_node_t*)前に扱ったノード。NULLで末尾を返す。
 *	\return				(keytree_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
//#define	KEYTREE_GET_PREV_(keytree)	keytree##_get_prev


#endif	/* KEYTREE_REFERENCE_H_ */
