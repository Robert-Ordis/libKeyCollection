/**
 *  \file		keylist_reference.h
 *  \brief		いわゆる「デフォルト実装」に該当する部分
 *	\remarks	どちらかというとこれは、関数リファレンスのガイド用として作ったものです
 *	\remarks	任意の構造体の頭にkeylist_node_tを付ける使い方はできるけどお勧めしません
 */
#include "keylist.h"
#include "keylist_functions.h"

#ifndef	KEYLIST_REFERENCE_H_
#define	KEYLIST_REFERENCE_H_

/**
 *	\struct	keylist_node_t
 *	\brief		リンクリスト処理におけるデフォルトのノード構造体
 *	\remark	任意の構造体の頭にkeylist_node_tをつけると「何でもリスト」が出来上がります（お勧めしません）
 */
typedef	struct keylist_node_s keylist_node_t;

keylist_define_basetype(keylist_node, struct keylist_node_s);

struct keylist_node_s {
	keylist_link_keylist_node_t	link;
};

keylist_define_prototypes(keylist, keylist_node, struct keylist_node_s, link);


/**
 *	\struct	keylist_t
 *	\brief		リンクリストのコンテナ構造体
 */
 
/**
 *	\struct	keylist_iterator_t
 *	\brief		リンクリストのイテレータ構造体
 */

/**
 *	\fn			keylist_init
 *	\brief		リストの初期化
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\param		if_lock	(int)リスト自身にロックを持たせる場合1、そうではなく、ロックは外でやる場合0
 *	\return			(void)
 */
//#define	KEYLIST_INIT_(keylist)			keylist##_init

/**
 *	\fn			keylist_get_count
 *	\brief		リストが抱えているノード数を取得
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\return			(int)リスト中の格納数
 */
//#define	KEYLIST_GET_COUNT_(keylist)	keylist##_get_count

/**
 *	\fn			keylist_refer_first
 *	\brief		リスト中の最初のノードを参照する
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\return			(keylist_node_t*)先頭ノードのポインタ。ない場合はNULL
 */
//#define	KEYLIST_REF_FIRST_(keylist)	keylist##_refer_first

/**
 *	\fn			keylist_refer_last
 *	\brief		リスト中の最後のノードを参照する
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\return			(keylist_node_t*)末尾ノードのポインタ。ない場合はNULL
 */
//#define	KEYLIST_REF_LAST_(keylist)		keylist##_refer_last

/**
 *	\fn			keylist_pop_first
 *	\brief		リスト中の最初のノードを削除して取得する
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\return			(keylist_node_t*)先頭ノードのポインタ。ない場合はNULL。このノードはリストから削除される。
 */
//#define	KEYLIST_POP_FIRST_(keylist)	keylist##_pop_first

/**
 *	\fn			keylist_pop_last
 *	\brief		リスト中の最後のノードを削除して取得する
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\return			(keylist_node_t*)末尾ノードのポインタ。ない場合はNULL。このノードはリストから削除される。
 */
//#define	KEYLIST_POP_LAST_(keylist)		keylist##_pop_last

/**
 *	\fn			keylist_get_belonged
 *	\brief		ノードが所属するリストを参照する
 *	\param		node	(keylist_node_t*)対象ノード
 *	\return			(keylist_t*)所属するリストのポインタ。ない場合はNULL。
 */
//#define	KEYLIST_GET_BELONGED_(keylist)	keylist##_get_belonged

/**
 *	\fn			keylist_add
 *	\brief		リストの末尾にノードを加える
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\param		node	(keylist_node_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
//#define	KEYLIST_ADD_(keylist)			keylist##_add

/**
 *	\fn			keylist_del
 *	\brief		リストから該当するノードを削除する
 *	\param		self	(keylist_t*)取り扱うリスト
 *	\param		node	(keylist_node_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
//#define	KEYLIST_DEL_(keylist)			keylist##_del

/**
 *	\fn			keylist_insert_before
 *	\brief		リストに対し、所定のノードの前に挿入する
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		index_node	(keylist_node_t*)挿入位置指定ノード。NULLで末尾挿入
 *	\param		node		(keylist_node_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
//#define	KEYLIST_INSERT_BEFORE_(keylist)	keylist##_insert_before

/**
 *	\fn			keylist_insert_after
 *	\brief		リストに対し、所定のノードの後に挿入する
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		index_node	(keylist_node_t*)挿入位置指定ノード。NULLで先頭挿入
 *	\param		node		(keylist_node_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
//#define	KEYLIST_INSERT_AFTER_(keylist)		keylist##_insert_after
 
/**
 *	\fn			keylist_init_iterator
 *	\brief		リストのループを取るためのイテレータを初期化する
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		iterator	(keylist_iterator_t*)イテレータ
 *	\return				(int)0
 *	\remarks	ここからtype_iterate_forwardを用いることで先頭からループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることで末尾からループを回す
 */
//#define	KEYLIST_INIT_ITERATOR_(keylist)	keylist##_init_iterator

/**
 *	\fn			keylist_init_iterator_from
 *	\brief		リストループのイテレータを、ループ開始ノードを指定して初期化する
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		iterator	(keylist_iterator_t*)イテレータ
 *	\param		node_from	(keylist_node_t*)開始位置の指定。
 *	\return				(int)成功で0、失敗でマイナス
 *	\remarks	node_from=NULLでtype_init_iteratorと等価
 *	\remarks	node_fromは必ずselfに所属してなければならない
 */
//#define	KEYLIST_INIT_ITERATOR_FROM_(keylist)	keylist##_init_iterator_from

/**
 *	\fn			keylist_iterate_forward
 *	\brief		前方向イテレーションを行う
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		iterator	(keylist_iterator_t*)イテレータ
 *	\return				(keylist_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYLIST_ITERATE_FORWARD_(keylist)		keylist##_iterate_forward

/**
 *	\fn			keylist_iterate_backward
 *	\brief		後方向イテレーションを行う
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		iterator	(keylist_iterator_t*)イテレータ
 *	\return				(keylist_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYLIST_ITERATE_BACKWARD_(keylist)		keylist##_iterate_backward

/**
 *	\fn			keylist_iterator_is_head
 *	\brief		イテレーションが「初期化時における」先頭かどうかを判定する。
 *	\param		iterator	(keylist_iterator_t*)取り扱うイテレータ
 *	\return				(int)先頭なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYLIST_ITERATOR_IS_HEAD_(keylist)		keylist##_is_head_of_iterator

/**
 *	\fn			keylist_iterator_is_tail
 *	\brief		イテレーションが「初期化時における」末尾かどうかを判定する。
 *	\param		iterator	(keylist_iterator_t*)イテレータ
 *	\return				(int)末尾なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
//#define	KEYLIST_ITERATOR_IS_TAIL_(keylist)		keylist##_is_tail_of_iterator

/**
 *	\fn			keylist_get_next
 *	\brief		指定ノードの「次」を取得する
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		node		(keylist_node_t*)前に扱ったノード。NULLで先頭を返す。
 *	\return				(keylist_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
//#define	KEYLIST_GET_NEXT_(keylist)	keylist##_get_next

/**
 *	\fn			keylist_get_prev
 *	\brief		指定ノードの「前」を取得する
 *	\param		self		(keylist_t*)取り扱うリスト
 *	\param		node		(keylist_node_t*)前に扱ったノード。NULLで末尾を返す。
 *	\return				(keylist_node_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
//#define	KEYLIST_GET_PREV_(keylist)	keylist##_get_prev
#endif	/* KEYLIST_REFERENCE_H_ */
