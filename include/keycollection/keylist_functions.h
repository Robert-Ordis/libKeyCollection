/**
 *  \file   keylist_functions.h
 *  \brief リンクリスト用の関数定義を集めました
 */

#include <stdint.h>
#include <pthread.h>
#ifndef	KEYLIST_FUNCTIONS_H_
#define	KEYLIST_FUNCTIONS_H_

/**
 *	\typedef	yourlist_t
 *	\brief		ユーザーが定義するリスト型の名前
 *	\param		yourlist	実際に生成したいリスト型と関数のベースの名前
 *	\remarks	当該リスト型を操作する関数もyourlist_xxxという命名になります。
 */
#define	KEYLIST_T_(yourlist)			yourlist##_t

/**
 *	\typedef	yourlist_iterator_t
 *	\brief		ユーザーが定義するリストにおけるイテレータ型の名前
 *	\param		yourlist	実際に生成したいイテレータ型のベースの名前
 *	
 */
#define	KEYLIST_ITERATOR_T_(yourlist)	yourlist##_iterator_t

/**
 *	\fn			yourlist_init(*self, if_lock)
 *	\brief		リストの初期化
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		if_lock	(int)リスト自身にロックを持たせる場合1、そうではなく、ロックは外でやる場合0
 *	\return			(void)
 */
#define	KEYLIST_INIT_(yourlist)			yourlist##_init

/**
 *	\fn			yourlist_get_count
 *	\brief		リストが抱えているノード数を取得
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(int)リスト中の格納数
 */
#define	KEYLIST_GET_COUNT_(yourlist)	yourlist##_get_count

/**
 *	\fn			yourlist_refer_first
 *	\brief		リスト中の最初のノードを参照する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL
 */
#define	KEYLIST_REF_FIRST_(yourlist)	yourlist##_refer_first

/**
 *	\fn			yourlist_refer_last
 *	\brief		リスト中の最後のノードを参照する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL
 */
#define	KEYLIST_REF_LAST_(yourlist)		yourlist##_refer_last

/**
 *	\fn			yourlist_pop_first
 *	\brief		リスト中の最初のノードを削除して取得する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL。このノードはリストから削除される。
 */
#define	KEYLIST_POP_FIRST_(yourlist)	yourlist##_pop_first

/**
 *	\fn			yourlist_pop_last
 *	\brief		リスト中の最後のノードを削除して取得する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL。このノードはリストから削除される。
 */
#define	KEYLIST_POP_LAST_(yourlist)		yourlist##_pop_last

/**
 *	\fn			yourlist_get_belonged
 *	\brief		ノードが所属するリストを参照する
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(yourlist_t*)所属するリストのポインタ。ない場合はNULL。
 */
#define	KEYLIST_GET_BELONGED_(yourlist)	yourlist##_get_belonged

/**
 *	\fn			yourlist_add
 *	\brief		リストの末尾にノードを加える
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_ADD_(yourlist)			yourlist##_add

/**
 *	\fn			yourlist_del
 *	\brief		リストから該当するノードを削除する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_DEL_(yourlist)			yourlist##_del

/**
 *	\fn			yourlist_insert_before
 *	\brief		リストに対し、所定のノードの前に挿入する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		index_node	(node_type_t*)挿入位置指定ノード。NULLで末尾挿入
 *	\param		node		(node_type_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_INSERT_BEFORE_(yourlist)	yourlist##_insert_before

/**
 *	\fn			yourlist_insert_after
 *	\brief		リストに対し、所定のノードの後に挿入する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		index_node	(node_type_t*)挿入位置指定ノード。NULLで先頭挿入
 *	\param		node		(node_type_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_INSERT_AFTER_(yourlist)		yourlist##_insert_after
 
/**
 *	\fn			yourlist_init_iterator
 *	\brief		リストのループを取るためのイテレータを初期化する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(int)0
 *	\remarks	ここからtype_iterate_forwardを用いることで先頭からループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることで末尾からループを回す
 */
#define	KEYLIST_INIT_ITERATOR_(yourlist)	yourlist##_init_iterator

/**
 *	\fn			yourlist_init_iterator_from
 *	\brief		リストループのイテレータを、ループ開始ノードを指定して初期化する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\param		node_from	(node_type_t*)開始位置の指定。
 *	\return				(int)成功で0、失敗でマイナス
 *	\remarks	node_from=NULLでtype_init_iteratorと等価
 *	\remarks	node_fromは必ずselfに所属してなければならない
 */
#define	KEYLIST_INIT_ITERATOR_FROM_(yourlist)	yourlist##_init_iterator_from

/**
 *	\fn			yourlist_iterate_forward
 *	\brief		前方向イテレーションを行う
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYLIST_ITERATE_FORWARD_(yourlist)		yourlist##_iterate_forward

/**
 *	\fn			yourlist_iterate_backward
 *	\brief		後方向イテレーションを行う
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYLIST_ITERATE_BACKWARD_(yourlist)		yourlist##_iterate_backward

/**
 *	\fn			yourlist_iterator_is_head
 *	\brief		イテレーションが「初期化時における」先頭かどうかを判定する。
 *	\param		iterator	(yourlist_iterator_t*)取り扱うイテレータ
 *	\return				(int)先頭なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYLIST_ITERATOR_IS_HEAD_(yourlist)		yourlist##_is_head_of_iterator

/**
 *	\fn			yourlist_iterator_is_tail
 *	\brief		イテレーションが「初期化時における」末尾かどうかを判定する。
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(int)末尾なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYLIST_ITERATOR_IS_TAIL_(yourlist)		yourlist##_is_tail_of_iterator

/**
 *	\fn			yourlist_get_next
 *	\brief		指定ノードの「次」を取得する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		node		(node_type_t*)前に扱ったノード。NULLで先頭を返す。
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYLIST_GET_NEXT_(yourlist)	yourlist##_get_next

/**
 *	\fn			yourlist_get_prev
 *	\brief		指定ノードの「前」を取得する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		node		(node_type_t*)前に扱ったノード。NULLで末尾を返す。
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYLIST_GET_PREV_(yourlist)	yourlist##_get_prev

//一応非公開関数。削除処理が大体共通するのでロックなしのものを設置。
#define	KEYLIST_DEL_INLOCK_(yourlist)			yourlist##_del_inlock



#endif	/* !KEYLIST_FUNCTIONS_H_ */
