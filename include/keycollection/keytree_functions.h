/**
 *  \file   keytree_functions.h
 *  \brief ツリー（二分探索木）用の関数定義を集めました
 */

#include <stdint.h>
#include <pthread.h>
#ifndef	KEYTREE_FUNCTIONS_H_
#define	KEYTREE_FUNCTIONS_H_

/**
 *	\typedef	yourtree_t
 *	\brief		ユーザーが定義するツリー型の名前
 *	\param		yourtree	実際に生成したいツリー型と関数のベースの名前
 *	\remarks	当該ツリー型を操作する関数もyourtree_xxxという命名になります。
 */
#define	KEYTREE_T_(yourtree)			yourtree##_t

/**
 *	\typedef	yourtree_iterator_t
 *	\brief		ユーザーが定義するツリーにおけるイテレータ型の名前
 *	\param		yourtree	実際に生成したいイテレータ型のベースの名前
 *	
 */
#define	KEYTREE_ITERATOR_T_(yourtree)	yourtree##_iterator_t


/**
 *	\typedef	keytree_comp_basename_t
 *	\brief		所定のノード同士を比較するための関数ポインタ型名
 *	\arg		node_a	(nodetype_t*)比較対象A
 *	\arg		node_b	(nodetype_t*)比較対象B
 *	\return			(int) node_a - node_bに相当する演算結果。1か-1か0だけでも守っておけばOK
 */
#define	KEYTREE_NODE_COMP_T_(basename)		keytree_comp_##basename##_t

/**
 *	\typedef	keytree_virt_basename_t
 *	\brief		値からノードを求めるための仮想ノード構築関数ポインタ名
 *	\arg		node		(nodetype_t*)構築対象の仮想ノード
 *	\arg		value		(void*)キーとする値
 *	\arg		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				void
 */
#define	KEYTREE_NODE_VIRT_T_(basename)		keytree_virt_##basename##_t

/**
 *	\fn			yourtree_init(*self, if_lock)
 *	\brief		ツリーの初期化
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		if_lock		(int)ツリー自身にロックを持たせる場合1、そうではなく、ロックは外でやる場合0
 *	\param		allow_eq	(int)同値の同居を許すかどうか。0で不許可。それ以外でOK
 *	\param		comp		(keytree_comp_basename_t)ツリー挿入用の比較関数
 *	\param		virt		(keytree_virt_basename_t)ツリー探索用の仮想比較ノード構築関数
 *	\return				(void)
 */
#define	KEYTREE_INIT_(yourtree)			yourtree##_init

/**
 *	\fn			yourtree_get_count
 *	\brief		ツリーが抱えているノード数を取得
 *	\param		self	(yourtree_t*)取り扱うツリー
 *	\return			(int)ツリー中の格納数
 */
#define	KEYTREE_GET_COUNT_(yourtree)	yourtree##_get_count

/**
 *	\fn			yourtree_refer_first
 *	\brief		ツリー中の先頭のノードを参照する（ルートではなく最小値ノード）
 *	\param		self	(yourtree_t*)取り扱うツリー
 *	\return			(nodetype_t*)先頭ノードのポインタ。ない場合はNULL
 */
#define	KEYTREE_REF_FIRST_(yourtree)	yourtree##_refer_first

/**
 *	\fn			yourtree_refer_last
 *	\brief		ツリー中の最後のノードを参照する
 *	\param		self	(yourtree_t*)取り扱うツリー
 *	\return			(nodetype_t*)末尾ノードのポインタ。ない場合はNULL
 */
#define	KEYTREE_REF_LAST_(yourtree)		yourtree##_refer_last


/**
 *	\fn			yourtree_get_belonged
 *	\brief		ノードが所属するツリーを参照する
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(yourtree_t*)所属するツリーのポインタ。ない場合はNULL。
 */
#define	KEYTREE_GET_BELONGED_(yourtree)	yourtree##_get_belonged

/**
 *	\fn			yourtree_rotate_right
 *	\brief		ノードを起点に右回転
 *	\param		self	(yourtree_t*)対象のツリー（いらないかも）
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)0で成功。
 */
#define	KEYTREE_ROTATE_RIGHT_(yourtree)	yourtree##_rotate_right

/**
 *	\fn			yourtree_rotate_left
 *	\brief		ノードを起点に左回転。対象ノードは下に降りる。
 *	\param		self	(yourtree_t*)対象のツリー（いらないかも）
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)0で成功。
 */
#define	KEYTREE_ROTATE_LEFT_(yourtree)	yourtree##_rotate_left

/**
 *	\fn			yourtree_rotate_left
 *	\brief		ノードが昇格するように回転。対象ノードは上に昇る。
 *	\param		self	(yourtree_t*)対象のツリー（いらないかも）
 *	\param		node	(nodetype_t*)対象ノード
 *	\return			(int)0で成功。
 */
#define	KEYTREE_ROTATE_UP_(yourtree)	yourtree##_rotate_up

/**
 *	\fn			yourtree_add
 *	\brief		ツリーにノードを加える。この際、比較はツリー中に定義されたものを使用。
 *	\param		self	(yourtree_t*)取り扱うツリー
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYTREE_ADD_(yourtree)			yourtree##_add

/**
 *	\fn			yourtree_del
 *	\brief		ツリーから該当するノードを削除する
 *	\param		self	(yourtree_t*)取り扱うツリー
 *	\param		node	(node_type_t*)対象ノード
 *	\return			(int)成功時0、失敗時マイナス
 */
#define	KEYTREE_DEL_(yourtree)			yourtree##_del

//insert_beforeとinsert_afterは、一定条件下でのみ成立する
/**
 *	\fn			yourtree_insert_before
 *	\brief		リスト同然になったツリーに対し、所定のノードの前に挿入する
 *	\param		self		(yourtree_t*)取り扱うツリー（実質線形リスト）
 *	\param		index_node	(node_type_t*)挿入位置指定ノード。NULLで末尾挿入
 *	\param		node		(node_type_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
#define	KEYTREE_INSERT_BEFORE_(yourtree)	yourtree##_insert_before

/**
 *	\fn			yourtree_insert_after
 *	\brief		リスト同然になったツリーに対し、所定のノードの後に挿入する
 *	\param		self		(yourtree_t*)取り扱うツリー（実質線形リスト）
 *	\param		index_node	(node_type_t*)挿入位置指定ノード。NULLで先頭挿入
 *	\param		node		(node_type_t*)対象ノード
 *	\return				(int)成功時0、失敗時マイナス
 */
#define	KEYTREE_INSERT_AFTER_(yourtree)		yourtree##_insert_after

/**
 *	\fn			yourtree_find_eq
 *	\brief		ツリーから該当する値「同等」の最小ノードを探る
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち最小に位置するノード。ない場合はNULL
 */
#define	KEYTREE_FIND_EQ_(yourtree)		yourtree##_find_eq

/**
 *	\fn			yourtree_find_eq_end
 *	\brief		ツリーから該当する値「同等」の最大ノードを探る
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち最小に位置するノード。ない場合はNULL
 */
#define	KEYTREE_FIND_EQ_END_(yourtree)	yourtree##_find_eq_end

/**
 *	\fn			yourtree_find_ge
 *	\brief		ツリーから該当する値「以上」の最小ノードを探る
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち最小に位置するノード。ない場合はNULL
 *	\brief		まあ、主にイテレーションの末尾を取る用って考えておけばいいです。
 */
#define	KEYTREE_FIND_GE_(yourtree)		yourtree##_find_ge

/**
 *	\fn			yourtree_find_lt
 *	\brief		ツリーから該当する値「未満」の最大ノードを探る
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		value		(void*)キーとする値のポインタ
 *	\param		value_len	(size_t)valueポインタの長さ。例えば文字列長
 *	\return				(node_type_t*)該当するうち最小に位置するノード。ない場合はNULL
 *	\brief		まあ、主にイテレーションの頭を取る用って考えておけばいいです。
 */
#define	KEYTREE_FIND_LT_(yourtree)		yourtree##_find_lt

/**
 *	\fn			yourtree_init_iterator
 *	\brief		ツリーのループを取るためのイテレータを初期化する
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(int)0
 *	\remarks	ここからtype_iterate_forwardを用いることで先頭からループを回す
 *	\remarks	ここからtype_iterate_backwardを用いることで末尾からループを回す
 */
#define	KEYTREE_INIT_ITERATOR_(yourtree)	yourtree##_init_iterator

/**
 *	\fn			yourtree_init_iterator_from
 *	\brief		ツリーループのイテレータを、ループ開始ノードを指定して初期化する
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\param		node_from	(node_type_t*)開始位置の指定。
 *	\return				(int)成功で0、失敗でマイナス
 *	\remarks	node_from=NULLでtype_init_iteratorと等価
 *	\remarks	node_fromは必ずselfに所属してなければならない
 */
#define	KEYTREE_INIT_ITERATOR_FROM_(yourtree)	yourtree##_init_iterator_from

/**
 *	\fn			yourtree_iterate_forward
 *	\brief		前方向イテレーションを行う
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYTREE_ITERATE_FORWARD_(yourtree)		yourtree##_iterate_forward

/**
 *	\fn			yourtree_iterate_backward
 *	\brief		後方向イテレーションを行う
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYTREE_ITERATE_BACKWARD_(yourtree)		yourtree##_iterate_backward

/**
 *	\fn			yourtree_iterator_is_head
 *	\brief		イテレーションが「初期化時における」先頭かどうかを判定する。
 *	\param		iterator	(yourtree_iterator_t*)取り扱うイテレータ
 *	\return				(int)先頭なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYTREE_ITERATOR_IS_HEAD_(yourtree)		yourtree##_is_head_of_iterator

/**
 *	\fn			yourtree_iterator_is_tail
 *	\brief		イテレーションが「初期化時における」末尾かどうかを判定する。
 *	\param		iterator	(yourtree_iterator_t*)イテレータ
 *	\return				(int)末尾なら1。それ以外では0。
 *	\remarks	ループ中、returnされたノードは削除してもよい。
 */
#define	KEYTREE_ITERATOR_IS_TAIL_(yourtree)		yourtree##_is_tail_of_iterator

/**
 *	\fn			yourtree_get_next
 *	\brief		指定ノードの「次」を取得する
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		node		(node_type_t*)前に扱ったノード。NULLで先頭を返す。
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYTREE_GET_NEXT_(yourtree)	yourtree##_get_next

/**
 *	\fn			yourtree_get_prev
 *	\brief		指定ノードの「前」を取得する
 *	\param		self		(yourtree_t*)取り扱うツリー
 *	\param		node		(node_type_t*)前に扱ったノード。NULLで末尾を返す。
 *	\return				(node_type_t*)取得できたもの。もう続かない場合はNULL
 *	\remarks	これを用いたループ中、returnされたノードを削除/編集してはならない。
 */
#define	KEYTREE_GET_PREV_(yourtree)	yourtree##_get_prev

/**
 *	\fn			yourtree_dbg_traverse
 *	\brief		指定したツリーをプリオーダーで走査する
 *	\param		self		(yourtree_t*)	取り扱うツリー
 *	\param		root		(nodetype_t*)	起点とするノード。NULLでルートと等価
 *	\param		level		(int)			深さカウンタ。0を入れましょう。
 *	\param		dump		(*(int)(nodetype_t* node, char *buf, int buflen))見つけたノードを取り扱う関数。負の値を返すと中断。
 *	\return				(int)負の値で走査を中断したことを示す
 *	\remarks	デバッグ用です。再帰関数を使っていたりデータの検査をしていなかったりするので、普段使いはしないでください。
 */
#define	KEYTREE_DBG_TRAVERSE_(yourtree)	yourtree##_dbg_traverse

//一応非公開関数。削除処理が大体共通するのでロックなしのものを設置。
#define	KEYTREE_DEL_INLOCK_(yourtree)			yourtree##_del_inlock



#endif	/* !KEYTREE_FUNCTIONS_H_ */
