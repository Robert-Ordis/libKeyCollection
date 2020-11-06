/**
 *  \file   keylist_functions.h
 *  \brief リンクリスト用の関数定義を集めました
 */

#include <stdint.h>
#ifndef	KEYLIST_FUNCTIONS_H_
#define	KEYLIST_FUNCTIONS_H_

/**
 *	\brief		yourlist_t
 *	\brief		ユーザーが定義するリスト型の名前
 *	\param		yourlist	実際に生成したいリスト型と関数のベースの名前
 *	\remarks	当該リスト型を操作する関数もyourlist_xxxという命名になります。
 */
#define	KEYLIST_T_(yourlist)			yourlist##_t

/**
 *	\brief		yourlist_iterator_t
 *	\brief		ユーザーが定義するリストにおけるイテレータ型の名前
 *	\param		yourlist	実際に生成したいイテレータ型のベースの名前
 *	
 */
#define	KEYLIST_ITERATOR_T_(yourlist)	yourlist##_iterator_t

/**
 *	\brief		yourlist_init(*self, if_lock)
 *	\brief		リストの初期化
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		if_lock	(int)リスト自身にロックを持たせる場合1、そうではなく、ロックは外でやる場合0
 *	\return			(void)
 */
#define	KEYLIST_INIT_(yourlist)			yourlist##_init

/**
 *	\brief		yourlist_get_count(*self)
 *	\brief		リストが抱えているノード数を取得
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(int)リスト中の格納数
 */
#define	KEYLIST_GET_COUNT_(yourlist)	yourlist##_get_count

/**
 *	\brief		yourlist_ref_head(*self)
 *	\brief		リスト中の最初のノードを参照する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL
 */
#define	KEYLIST_REF_HEAD_(yourlist)	yourlist##_ref_head

/**
 *	\brief		yourlist_ref_tail(*self)
 *	\brief		リスト中の最後のノードを参照する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL
 */
#define	KEYLIST_REF_TAIL_(yourlist)		yourlist##_ref_tail

/**
 *	\brief		yourlist_pop_head(*self)
 *	\brief		リスト中の最初のノードを削除して取得する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL。このノードはリストから削除される。
 */
#define	KEYLIST_POP_HEAD_(yourlist)	yourlist##_pop_head

/**
 *	\fn			yourlist_pop_tail(*self)
 *	\brief		リスト中の最後のノードを削除して取得する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL。このノードはリストから削除される。
 */
#define	KEYLIST_POP_TAIL_(yourlist)		yourlist##_pop_tail

/**
 *	\brief		yourlist_ref_nth(*self, nth)
 *	\brief		N番目のノードを参照する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		nth		(int)0を基準とした数。0で先頭、増えていってその後ろ。-1だと末尾。減っていってその前
 */

#define	KEYLIST_REF_NTH_(yourlist)		yourlist##_ref_nth

/**
 *	\brief		yourlist_add(*self, *node)
 *	\brief		リストの末尾にノードを加える
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_ADD_(yourlist)			yourlist##_add

/**
 *	\brief		yourlist_add_head(*self, *node)
 *	\brief		リストの先頭にノードを加える
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_ADD_HEAD_(yourlist)			yourlist##_add_head

/**
 *	\brief		yourlist_add_tail(*self, *node)
 *	\brief		リストの末尾にノードを加える
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_ADD_TAIL_(yourlist)			yourlist##_add_tail

/**
 *	\brief		yourlist_del(*self, *node)
 *	\brief		リストから該当するノードを削除する
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_DEL_(yourlist)			yourlist##_del

/**
 *	\brief		yourlist_insert_before(*self, *index_node, *node)
 *	\brief		リストに対し、所定のノードの前に挿入する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		index_node	(nodetype_t*)挿入位置指定ノード。NULLで末尾挿入
 *	\param		node		(nodetype_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_INSERT_BEFORE_(yourlist)	yourlist##_insert_before

/**
 *	\brief		yourlist_insert_after(*self, *index_node, *node)
 *	\brief		リストに対し、所定のノードの後に挿入する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		index_node	(nodetype_t*)挿入位置指定ノード。NULLで先頭挿入
 *	\param		node		(nodetype_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
#define	KEYLIST_INSERT_AFTER_(yourlist)		yourlist##_insert_after
 
/**
 *	\brief		yourlist_init_iterator(*self, *iterator)
 *	\brief		リストのループを取るためのイテレータを初期化する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(int)0
 *	\remarks	ここからtype_iterate_forwardを用いることで先頭からループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることで末尾からループを回す
 */
#define	KEYLIST_INIT_ITERATOR_(yourlist)	yourlist##_init_iterator

/**
 *	\brief		yourlist_iterator_move(*iterator, *index_node)
 *	\brief		指定されたノードが次の起点になるようイテレータを移動させる
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\param		index_node	(nodetype_t*)対象ノード。
 *	\return				(int)0:成功、-2:所属リストが違う
 *	\remarks	ここからtype_iterator_forward/backwardで指定ノードからループが回る。
 */
#define	KEYLIST_ITERATOR_MOVE_(yourlist)	yourlist##_iterator_move

/**
 *	\brief		yourlist_iterator_forward(*iterator)
 *	\brief		前方向イテレーションを行う
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(nodetype_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYLIST_ITERATOR_FORWARD_(yourlist)		yourlist##_iterator_forward

/**
 *	\brief		yourlist_iterator_backward(*iterator)
 *	\brief		後方向イテレーションを行う
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		iterator	(yourlist_iterator_t*)イテレータ
 *	\return				(nodetype_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYLIST_ITERATOR_BACKWARD_(yourlist)		yourlist##_iterator_backward

/**
 *	\brief		yourlist_has_node(*self, *node)
 *	\brief		ノードをリストが持っているかをチェックする
 *	\param		self	(yourlist_t*)取り扱うリスト
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)所属してる場合で1、それ以外で0
 */
#define	KEYLIST_HAS_NODE_(yourlist)	yourlist##_has_node

/**
 *	\brief		yourlist_get_next(*self, *node)
 *	\brief		指定ノードの「次」を取得する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		node		(nodetype_t*)このノードの「次」を取得する。NULLで先頭を返す。
 *	\return				(nodetype_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYLIST_GET_NEXT_(yourlist)	yourlist##_get_next

/**
 *	\brief		yourlist_get_prev(*self, *node)
 *	\brief		指定ノードの「前」を取得する
 *	\param		self		(yourlist_t*)取り扱うリスト
 *	\param		node		(nodetype_t*)このノードの「前」を取得する。NULLで末尾を返す。
 *	\return				(nodetype_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYLIST_GET_PREV_(yourlist)	yourlist##_get_prev

/**
 *	\brief		yourlist_get_belong(*node)
 *	\brief		ノードが所属するリストを参照する
 *	\param		node	(nodetype_t*)前に扱ったノード。NULLで末尾を返す。
 *	\return			(yourlist_t*)所属するリストのポインタ。ない場合はNULL。
 */
#define	KEYLIST_GET_BELONG_(yourlist)	yourlist##_get_belong



#endif	/* !KEYLIST_FUNCTIONS_H_ */
