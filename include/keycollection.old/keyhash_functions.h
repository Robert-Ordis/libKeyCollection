/**
 *  \file   keyhash_functions.h
 *  \brief ハッシュテーブル用の関数定義を集めました
 */

#include <stdint.h>
#include <pthread.h>
#ifndef	KEYHASH_FUNCTIONS_H_
#define	KEYHASH_FUNCTIONS_H_

/**
 *	\typedef	yourhash_t
 *	\brief		ユーザーが定義するハッシュテーブル型の名前
 *	\param		yourlist	実際に生成したいリスト型と関数のベースの名前
 *	\remarks	当該リスト型を操作する関数もyourlist_xxxという命名になります。
 */
#define	KEYHASH_T_(yourhash)					yourhash##_t

#define	KEYHASH_FINDER_T_(yourhash)				yourhash##_finder_t


/**
 *	\typedef	keytree_comp_basename_t
 *	\brief		所定のノード同士を比較するための関数ポインタ型名
 *	\arg		node_a	(nodetype_t*)比較対象A
 *	\arg		node_b	(nodetype_t*)比較対象B
 *	\return			(int) node_a - node_bに相当する演算結果。1か-1か0だけでも守っておけばOK
 */
#define	KEYHASH_NODE_COMP_T_(basename)			keyhash_comp_##basename##_t

/**
 *	\typedef	keytree_virt_basename_t
 *	\brief		値からノードを求めるための仮想ノード構築関数ポインタ名
 *	\arg		node		(nodetype_t*)構築対象の仮想ノード
 *	\arg		value		(void*)キーとする値
 *	\arg		value_len	(size_t)valueの長さ
 *	\return			void
 */
#define	KEYHASH_NODE_VIRT_T_(basename)			keyhash_virt_##basename##_t

/**
 *	\typedef	keytree_hash_basename_t
 *	\brief		値からハッシュ値を求めるための関数ポインタ
 *	\arg		node	(nodetype_t*)構築対象の仮想ノード
 *	\arg		value	(int)ハッシュ値
 *	\return			void
 */
#define	KEYHASH_NODE_HASH_T_(basename)			keyhash_hash_##basename##_t


/**
 *	\fn			yourhash_init(*self, if_lock)
 *	\brief		ツリーの初期化
 *	\param		self		(yourhash_t*)取り扱うツリー
 *	\param		if_lock		(int)ツリー自身にロックを持たせる場合1、そうではなく、ロックは外でやる場合0
 *	\param		allow_eq	(int)同値の同居を許すかどうか。0で不許可。それ以外でOK
 *	\param		comp		(keyhash_comp_yourhash_t)ツリー挿入用の比較関数
 *	\param		virt		(keyhash_virt_yourhash_t)ツリー探索用の仮想比較ノード構築関数
 *	\param		hash		(keyhash_hash_yourhash_t)ハッシュ計算用関数
 *	\param		hash_width	(int)今回使うハッシュ幅
 *	\return				(void)
 */
#define	KEYHASH_INIT_(yourhash)					yourhash##_init

/**
 *	\fn			yourhash_get_count
 *	\brief		ハッシュテーブルが抱えているノード数を取得
 *	\param		self	(yourhash_t*)取り扱うハッシュテーブル
 *	\return			(int)テーブル中の格納数
 */
#define	KEYHASH_GET_COUNT_(yourhash)	yourhash##_get_count

/**
 *	\fn			yourhash_add
 *	\brief		ハッシュテーブルにノードを加える。この際、比較はself中に定義されたものを使用。
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYHASH_ADD_(yourhash)					yourhash##_add

/**
 *	\fn			yourhash_del
 *	\brief		ハッシュテーブルから該当するノードを削除する
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYHASH_DEL_(yourhash)					yourhash##_del

/**
 *	\fn			yourhash_get_node
 *	\brief		テーブルから該当する値の先頭ノードを探る
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち最小に位置するノード。ない場合はNULL
 *	\remarks	ワイルドカードノードも対象に入れています
 */
#define	KEYHASH_GET_NODE_(yourhash)				yourhash##_get_node

/**
 *	\fn			yourhash_get_node_end
 *	\brief		テーブルから該当する値の末尾ノードを探る
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち末尾に位置するノード。ない場合はNULL
 *	\remarks	ワイルドカードも対象に入れるため、ワイルドカードの末尾から探します。
 */
#define	KEYHASH_GET_NODE_END_(yourhash)			yourhash##_get_node_end

/**
 *	\fn			yourhash_get_node
 *	\brief		テーブルから該当する値の通常先頭ノードを探る
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち先頭に位置するノード。ない場合はNULL
 *	\remarks	ワイルドカードは対象外です
 */
#define	KEYHASH_GET_NORMAL_NODE_(yourhash)		yourhash##_get_normal_node

/**
 *	\fn			yourhash_get_node_end
 *	\brief		テーブルから該当する値の通常末尾ノードを探る
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち末尾に位置するノード。ない場合はNULL
 *	\remarks	ワイルドカードは対象外です
 */
#define	KEYHASH_GET_NORMAL_NODE_END_(yourhash)	yourhash##_get_normal_node_end

/**
 *	\fn			yourhash_get_wildcard
 *	\brief		テーブルに登録されたワイルドカードから、valueでヒットする先頭ノードを取得する
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち先頭に位置するノード。ない場合はNULL
 *	\remarks	ワイルドカードのみから探します
 */
#define	KEYHASH_GET_WILDCARD_(yourhash)			yourhash##_get_wildcard

/**
 *	\fn			yourhash_get_wildcard_end
 *	\brief		テーブルに登録されたワイルドカードから、valueでヒットする末尾ノードを取得する
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち先頭に位置するノード。ない場合はNULL
 *	\remarks	ワイルドカードのみから探します
 */
#define	KEYHASH_GET_WILDCARD_END_(yourhash)		yourhash##_get_wildcard_end

/**
 *	\fn			yourhash_init_finder
 *	\brief		「指定の値にヒットするノード」のみでイテレートするfinderを初期化
 *	\param		self		(yourhash_t*)取り扱うテーブル
 *	\param		finder		(yourhash_finder_t*)ファインダー
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(nodetype_t*)成功で該当ノード。失敗でNULL：例えばそんな値では何一つ見つからないとか
 *	\remarks	
 */
#define	KEYHASH_INIT_FINDER_(yourhash)		yourhash##_init_finder

/**
 *	\fn			yourhash_find_next
 *	\brief		「指定の値にヒットするノード」縛りで次のノードを取得
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		finder	(yourhash_finder_t*)ファインダー
 *	\return			(nodetype_t*)ノード。続かない場合はNULL
 *	\remarks	loop中、returnされたノードは削除してもよい。
 *	\remarks	通常ノードのイテレーションが終わったらワイルドカードで回す。
 */
#define	KEYHASH_FIND_NEXT_(yourhash)			yourhash##_find_next

/**
 *	\fn			yourhash_find_prev
 *	\brief		「指定の値にヒットするノード」縛りで前のノードを取得
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		finder	(yourhash_finder_t*)ファインダー
 *	\return			(nodetype_t*)ノード。続かない場合はNULL
 *	\remarks	loop中、returnされたノードは削除してもよい。
 *	\remarks	ワイルドカードのイテレーションが終わったら通常ノードで回す。
 */
#define	KEYHASH_FIND_PREV_(yourhash)			yourhash##_find_prev

/**
 *	\fn			yourhash_finder_in_wildcard
 *	\brief		ファインダーが現在ワイルドカードを見ているかどうか。
 *	\param		self	(yourhash_t*)取り扱うテーブル
 *	\param		finder	(yourhash_finder_t*)ファインダー
 *	\return			(int)0で偽、1で真
 */
#define	KEYHASH_FINDER_IN_WILDCARD_(yourhash)	yourhash##_finder_in_wildcard

/**
 *	\fn			yourhash_dbg_dump
 *	\brief		デバッグ用	
 *	\param		self	(yourhash_t*)対象テーブル
 *	\param		dump	(*(int)(nodetype_t* node, char *buf, int buflen))見つけたノードを取り扱う関数。負の値を返すと中断。
 *	\return	(int)	(int)	ダンプした数
 */
#define	KEYHASH_DBG_DUMP_(yourhash)				yourhash##_dbg_dump

#endif	/* !KEYHASH_FUNCTIONS_H_ */
