/**
 *  \file   keyhash_functions.h
 *  \brief ハッシュテーブル用の関数定義を集めました
 */

#include <stdint.h>
#include <pthread.h>
#ifndef	KEYHASH_FUNCTIONS_H_
#define	KEYHASH_FUNCTIONS_H_

/**
 *	\brief		yourhash_t
 *	\brief		ユーザーが定義するハッシュテーブル型の名前
 *	\param		yourlist	実際に生成したいハッシュテーブル型と関数のベースの名前
 *	\remarks	当該リスト型を操作する関数もyourlist_xxxという命名になります。
 */
#define	KEYHASH_T_(yourhash)					yourhash##_t

/**
 *	\brief		yourhash_iterator_t
 *	\brief		Definition of the iterator for the hash table
 *	\tparam	yourlist
 *	\remarks	Same as the "treename_iterator_t"
 *
 */
#define	KEYHASH_ITERATOR_T_(yourhash)			yourhash##_iterator_t

/**
 *	\brief		yourhash_init(*self)
 *	\brief		Initiate the hash table.
 *	\param		self		(yourhash_t*)取り扱うツリー
 *	\param		allow_eq	(int)同値の同居を許すかどうか。0で不許可。それ以外でOK
 *	\param		comp_node	(keytree_comp_node_cb)ツリー挿入用の比較関数
 *	\param		make_node	(keytree_make_node_cb)ツリー探索用の仮想比較ノード構築関数
 *	\param		calc_hash	(keyhash_calc_hash_cb)ハッシュ計算用関数
 *	\return				(void)
 */
#define	KEYHASH_INIT_(yourhash)					yourhash##_init

/**
 *	\brief		yourhash_set_eq_comp(*self, eq_comp)
 *	\brief		Set the comparator between equivalent nodes.
 *	\param		self		(yourhash_t*)Hash instance.
 *	\param		eq_comp		(keytree_comp_node_cb)Comparator for between equivalent nodes.
 *	\return				(void)
 */
#define	KEYHASH_SET_EQ_COMP_(yourhash)			yourhash##_set_eq_comp

/**
 *	\brief		yourhash_get_count(*self)
 *	\brief		Get the count of nodes on the hashtable.
 *	\param		self	(yourhash_t*)Hashtable instance.
 *	\return			(int)
 */
#define	KEYHASH_GET_COUNT_(yourhash)	yourhash##_get_count

/**
 *	\brief		yourhash_add
 *	\brief		ハッシュテーブルにノードを加える。この際、比較はself中に定義されたものを使用。
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYHASH_ADD_(yourhash)					yourhash##_add

/**
 *	\brief		yourhash_del
 *	\brief		ハッシュテーブルから該当するノードを削除する
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYHASH_DEL_(yourhash)					yourhash##_del

/**
 *	\brief		yourhash_search
 *	\brief		Pick up the node which has the value equals to the arg pointer.
 *	\param		self		(yourhash_t*)Table instanceル
 *	\param		value		(void*)Pointer of the value for picking the matched node up..
 *	\param		value_len	(size_t)Byte length of *value instance.
 *	\return				(node_type_t*)First node having the value. NULL for not found.
 */
#define	KEYHASH_SEARCH_(yourhash)				yourhash##_search

/**
 *	\brief		yourhash_search_wildcard
 *	\brief		Pick up the node which has the wildcard matching with the arg pointer.
 *	\param		self		(yourhash_t*)Table instanceル
 *	\param		value		(void*)Pointer of the value for picking the matched node up..
 *	\param		value_len	(size_t)Byte length of *value instance.
 *	\return				(node_type_t*)First node having the matched value. NULL for not found.
 */
#define	KEYHASH_SEARCH_WILDCARD_(yourhash)		yourhash##_search_wildcard

/**
 *	\brief		yourhash_setup_iterator
 *	\brief		Setup the Iterator for only on specified value.
 *	\param		self		(yourhash_t*)Table instance.
 *	\param		iterator	(yourhash_iterator_t*)Iterator.
 *	\param		value		(void*)Pointer of the value for picking the eq-valued node up..
 *	\param		value_len	(size_t)Byte length of *value instance.
 *	\return				(int) 0 if the node was found. -1 for not found.
 */
#define	KEYHASH_SETUP_ITERATOR_(yourhash)		yourhash##_setup_iterator


/**
 *	\brief		yourhash_setup_iterator_wildcard
 *	\brief		Setup the Iterator for node detected as wildcard.
 *	\param		self		(yourhash_t*)Table instance.
 *	\param		iterator	(yourhash_iterator_t*)Iterator.
 *	\return				(int)Always 0.
 */
#define	KEYHASH_SETUP_ITERATOR_WILDCARD_(yourhash)	yourhash##_setup_iterator_wildcard

/**
 *	\brief		yourhash_iterator_move(*iterator, *index_node)
 *  \brief		Move the iterator to one step before the specified node.
 *  \param		iterator	iterator instance
 *  \param		index_node	The node you want to set as the first point.
 *  \return	0: success.
 *  \return	-2: error[*index_node doesn't belong to the tree which is src of iterator].
 *  \remarks	After this, next "keytree_iterator_forward/backward" returns *index_node as you specified.
 *  \remarks	index_node == NULL means to make the iterator to the state on initiated.
 */
#define	KEYHASH_ITERATOR_MOVE_(yourhash)		yourhash##_iterator_move

/**
 *	\brief		yourhash_iterator_forward(*iterator)
 *	\brief		Get the next node on the Iterator..
 *	\param		iterator	(yourhash_iterator_t*)Iterator.
 *	\return				(nodetype_t*)Gotten node. If null, the iteration has ended.
 */
#define	KEYHASH_ITERATOR_FORWARD_(yourhash)		yourhash##_iterator_forward

/**
 *	\brief		yourhash_iterator_backward(*iterator)
 *	\brief		Get the previous node on the Iterator..
 *	\param		iterator	(yourhash_iterator_t*)Iterator.
 *	\return				(nodetype_t*)Gotten node. If null, the iteration has ended.
 */
#define	KEYHASH_ITERATOR_BACKWARD_(yourhash)	yourhash##_iterator_backward

/**
 *	\brief		yourhash_dbg_dump
 *	\brief		デバッグ用	
 *	\param		self	(yourhash_t*)対象テーブル
 *	\param		dump	(*(int)(nodetype_t* node, char *buf, int buflen))見つけたノードを取り扱う関数。負の値を返すと中断。
 *	\return	(int)	(int)	ダンプした数
 */
#define	KEYHASH_DBG_DUMP_(yourhash)				yourhash##_dbg_dump

#endif	/* !KEYHASH_FUNCTIONS_H_ */
