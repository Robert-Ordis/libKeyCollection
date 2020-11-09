/**
 *  \file		keyhash.h
 *  \brief		Hash chaining table library using the defined member filed.
 *  \remarks	Due to treat given value directly, hash-table is completely based on the templatal witchcraft.
 */
 
#include "./private/keycollection_commons.h"
#include "./private/keycollection_lock.h"
#include "./private/keyhash_inside.h"
#include "./keyhash_functions.h"
#include "./keytree_functions.h"

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include "./keytree_witchcraft.h"
#include "./keytree.h"

#ifndef	KEYHASH_H_
#define	KEYHASH_H_

typedef int (*keyhash_calc_hash_cb)(void*);

/**
 *	\def	keyhash_define_prototypes
 *	\param	yourhash		yourhash_t及び関連型や関連関数(yourhash_xxx)が出来上がる。
 *	\param	nodetype_s		実際に取り扱いたいノード型。struct nodetype_sでやるのが無難。
 *	\param	treename		内部で扱うツリー型及び関連関数のプレフィクス。
 *	\param	hashmax			ハッシュセットの広さ
 *	\brief	構造体とtreename, listnameに関するマクロ記述の後で記述するもの。
 */
#define	keyhash_define_prototypes(yourhash, nodetype_s, treename, hash_max)\
	\
	typedef	KEYTREE_ITERATOR_T_(treename) KEYHASH_ITERATOR_T_(yourhash);\
	\
	typedef struct {\
		KEYTREE_T_(treename)	hash_chain[hash_max];	/*通常のハッシュテーブル*/\
		KEYTREE_T_(treename)	wild_chain;				/*ワイルドカードレコードの格納場（リストとしての用途のみ）*/\
		keyhash_calc_hash_cb	calc_hash;				/*ハッシュ計算関数*/\
	} KEYHASH_T_(yourhash);\
	\
	\
	void		KEYHASH_INIT_(yourhash)(KEYHASH_T_(yourhash) *self, int allow_eq, \
					keytree_comp_node_cb comp,\
					keytree_make_node_cb make,\
					keyhash_calc_hash_cb hash\
				);\
	\
	/*単純に各チェインの合計数を取得する*/\
	int			KEYHASH_GET_COUNT_(yourhash)(KEYHASH_T_(yourhash) *self);\
	\
	/*追加処理。ハッシュ特定→ツリーアド。ツリーなので自動的にソートされますお*/\
	int			KEYHASH_ADD_(yourhash)(KEYHASH_T_(yourhash) *self, nodetype_s *node);\
	\
	/*削除処理。確認のためハッシュ特定→削除処理*/\
	int			KEYHASH_DEL_(yourhash)(KEYHASH_T_(yourhash) *self, nodetype_s *node);\
	\
	/*通常等価で前方を検索*/\
	nodetype_s*	KEYHASH_SEARCH_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	\
	/*ワイルドカードで前方を検索*/\
	nodetype_s*	KEYHASH_SEARCH_WILDCARD_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	\
	/*通常等価で回すイテレータをセット*/\
	int			KEYHASH_SETUP_ITERATOR_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_ITERATOR_T_(yourhash) *iterator, void *value, size_t value_len);\
	\
	/*ワイルドカードをめぐるイテレータをセット*/\
	int			KEYHASH_SETUP_ITERATOR_WILDCARD_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_ITERATOR_T_(yourhash) *iterator);\
	\
	int			KEYHASH_ITERATOR_MOVE_(yourhash)(KEYHASH_ITERATOR_T_(yourhash) *iterator, nodetype_s *index_node);\
	\
	nodetype_s*	KEYHASH_ITERATOR_FORWARD_(yourhash)(KEYHASH_ITERATOR_T_(yourhash) *iterator);\
	\
	nodetype_s*	KEYHASH_ITERATOR_BACKWARD_(yourhash)(KEYHASH_ITERATOR_T_(yourhash) *iterator);\
	\
	int			KEYHASH_DBG_DUMP_(yourhash)(KEYHASH_T_(yourhash) *self, void *userdata, int (*dump)(nodetype_s*, void*, char*, int));\
	
	
/**
 *	\def	keyhash_define_implements
 *	\param	yourhash		yourhash_t関連関数(yourhash_xxx)の実装が出来上がる。
 *	\param	nodetype_s		実際に取り扱いたいノード型。struct nodetype_sでやるのが無難。
 *	\param	treename		内部で扱うツリー型及び関連関数のプレフィクス。
 *	\param	hash_max			ハッシュテーブルの広さ
 *	\brief	ハッシュセットの実装を自動で行う
 */
#define	keyhash_define_implements(yourhash, nodetype_s, treename, hash_max)\
	void		KEYHASH_INIT_(yourhash)(KEYHASH_T_(yourhash) *self, int allow_eq, \
					keytree_comp_node_cb comp,\
					keytree_make_node_cb make,\
					keyhash_calc_hash_cb hash\
				){\
		assert(self != NULL);\
		assert(comp != NULL);\
		assert(make != NULL);\
		assert(hash != NULL);\
		\
		{\
			int i;\
			(self)->calc_hash = hash;\
			/*ハッシュテーブルの整備。広さを限界値を超えたりゼロにしたりしないよう気を付ける*/\
			for(i = hash_max - 1; i >= 0; --i){\
				/*各通常チェインの初期化*/\
				KEYTREE_INIT_(treename)(&((self)->hash_chain[i]), allow_eq, comp, make);\
			}\
			/*ワイルドカードチェインの初期化。比較関数等をゼロとすることで線形リストとして定義づける*/\
			KEYTREE_INIT_(treename)(&((self)->wild_chain), allow_eq, NULL, NULL);\
		}\
	}\
	\
	\
	/*単純に各チェインの合計数を取得する*/\
	int			KEYHASH_GET_COUNT_(yourhash)(KEYHASH_T_(yourhash) *self){\
		int ret = KEYTREE_GET_COUNT_(treename)(&((self)->wild_chain));\
		int i;\
		for(i = hash_max - 1; i >= 0; --i){\
			ret += KEYTREE_GET_COUNT_(treename)(&((self)->hash_chain[i]));\
		}\
		return ret;\
	}\
	\
	/*追加処理。ハッシュ特定→ツリー追加。ツリーなので自動的にソートされますお*/\
	int			KEYHASH_ADD_(yourhash)(KEYHASH_T_(yourhash) *self, nodetype_s *node){\
		int ret = -1;\
		int hash_index;\
		KEYTREE_T_(treename) *dst = NULL;\
		\
		/*ハッシュ計算*/\
		KEYHASH_IMPL_CALC_HASH_(self, node, hash_max, hash_index);\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			if(hash_index == -1){\
				/*算出値が-1だった場合にのみワイルドカードチェインを提供*/\
				dst = &((self)->wild_chain);\
			}\
			else if(hash_index >= 0){\
				/*そうでないのなら普通にチェーン提供*/\
				dst = &((self)->hash_chain[hash_index]);\
			}\
			if(dst != NULL){\
				/*チェーンに加える。通常ツリーならソートは自動で行われる*/\
				ret = KEYTREE_ADD_(treename)(dst, node);\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*削除処理。確認のためハッシュ特定→削除処理*/\
	int			KEYHASH_DEL_(yourhash)(KEYHASH_T_(yourhash) *self, nodetype_s *node){\
		int ret = -1;\
		int hash_index = (self)->calc_hash(node);\
		KEYTREE_T_(treename) *dst = NULL;\
		KEYTREE_T_(treename) *belong = KEYTREE_GET_BELONG_(treename)(node);\
		\
		if(belong == NULL){\
			/*そもそもどこにも所属していないのなら何もしない*/\
			return ret;\
		}\
		/*ハッシュ計算*/\
		KEYHASH_IMPL_CALC_HASH_(self, node, hash_max, hash_index);\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			if(hash_index == -1){\
				/*算出値が-1だった場合にのみワイルドカードチェインを提供*/\
				dst = &((self)->wild_chain);\
			}\
			else if(hash_index >= 0){\
				/*そうでないのなら普通にチェーン提供*/\
				dst = &((self)->hash_chain[hash_index]);\
			}\
			if(dst != NULL){\
				/*そのチェーンが、nodeが属するものかどうかは中の関数に任せる*/\
				ret = KEYTREE_DEL_(treename)(dst, node);\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*通常ノードにて一致する最初のノードをとる*/\
	nodetype_s *KEYHASH_SEARCH_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s *ret_node = NULL;\
		nodetype_s v_node;\
		int hash_index;\
		\
		(self)->hash_chain[0].make_node(&v_node, value, value_len);\
		KEYHASH_IMPL_CALC_HASH_(self, &v_node, hash_max, hash_index);\
		\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			if(hash_index >= 0){\
				/*普通に探す*/\
				ret_node = KEYTREE_FIND_EQ_NODE_(treename)(&(self)->hash_chain[hash_index], &v_node);\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret_node;\
	}\
	\
	/*ワイルドカードにて一致する最初のノードをとる*/\
	nodetype_s *KEYHASH_SEARCH_WILDCARD_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s *ret_node = NULL;\
		nodetype_s v_node;\
		keytree_comp_node_cb cmp = (self)->hash_chain[0].comp_node;\
		(self)->hash_chain[0].make_node(&v_node, value, value_len);\
		\
		/*ワイルドカードチェインを回して、一致したら抜ける*/\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			for(\
				ret_node = KEYTREE_REF_HEAD_(treename)(&(self)->wild_chain);\
				ret_node != NULL;\
				ret_node = KEYTREE_GET_NEXT_(treename)(&(self)->wild_chain, ret_node)){\
				\
				if(cmp(ret_node, &v_node) == 0){\
					break;\
				}\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret_node;\
	}\
	\
	int			KEYHASH_SETUP_ITERATOR_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_ITERATOR_T_(yourhash) *iterator, void *value, size_t value_len){\
		int ret = -1;\
		nodetype_s v_node;\
		int hash_index;\
		(self)->hash_chain[0].make_node(&v_node, value, value_len);\
		KEYHASH_IMPL_CALC_HASH_(self, &v_node, hash_max, hash_index);\
		\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			if(hash_index >= 0){\
				/*普通に探す*/\
				nodetype_s *head_node, *tail_node;\
				head_node = KEYTREE_FIND_EQ_NODE_(treename)(&(self)->hash_chain[hash_index], &v_node);\
				if(head_node != NULL){\
					tail_node = KEYTREE_FIND_EQ_NODE_END_(treename)(&(self)->hash_chain[hash_index], &v_node);\
					ret = KEYTREE_INIT_ITERATOR_RANGED_(treename)(&(self)->hash_chain[hash_index], iterator, head_node, tail_node);\
				}\
				\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		\
		return ret;\
	}\
	\
	int			KEYHASH_SETUP_ITERATOR_WILDCARD_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_ITERATOR_T_(yourhash) *iterator){\
		return KEYTREE_INIT_ITERATOR_(treename)(&(self)->wild_chain, iterator);\
	}\
	\
	int			KEYHASH_ITERATOR_MOVE_(yourhash)(KEYHASH_ITERATOR_T_(yourhash) *iterator, nodetype_s *index_node){\
		return KEYTREE_ITERATOR_MOVE_(treename)(iterator, index_node);\
	}\
	\
	nodetype_s*	KEYHASH_ITERATOR_FORWARD_(yourhash)(KEYHASH_ITERATOR_T_(yourhash) *iterator){\
		return KEYTREE_ITERATOR_FORWARD_(treename)(iterator);\
	}\
	\
	nodetype_s*	KEYHASH_ITERATOR_BACKWARD_(yourhash)(KEYHASH_ITERATOR_T_(yourhash) *iterator){\
		return KEYTREE_ITERATOR_BACKWARD_(treename)(iterator);\
	}\
	\
	int			KEYHASH_DBG_DUMP_(yourhash)(KEYHASH_T_(yourhash) *self, void *userdata, int (*dump)(nodetype_s*, void*, char*, int)){\
		KEYTREE_ITERATOR_T_(treename) it;\
		nodetype_s	*node;\
		int i;\
		int ret = 0;\
		int loop_ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			\
			char buf[64];\
			for(i = 0; i < hash_max; i++){\
				printf("%s: chain number->%d\n", __func__, i);\
				KEYTREE_INIT_ITERATOR_(treename)(&((self)->hash_chain[i]), &it);\
				while((node = KEYTREE_ITERATOR_FORWARD_(treename)(&it)) != NULL){\
					KEYCOLLECT_LOCK_RELEASE_(self);\
					ret++;\
					if(dump != NULL){\
						loop_ret = (*dump)(node, userdata, buf, 64);\
					}\
					KEYCOLLECT_LOCK_ACQUIRE_(self);\
					printf("%s:[%p(%03d)]:val->%s\n", __func__, node, i, buf);\
					if(loop_ret < 0){\
						break;\
					}\
				}\
				if(loop_ret < 0){\
					break;\
				}\
			}\
			if(loop_ret < 0){\
				KEYCOLLECT_LOCK_RELEASE_(self);\
				return ret;\
			}\
			KEYTREE_INIT_ITERATOR_(treename)(&((self)->wild_chain), &it);\
			printf("%s: wild chain\n", __func__);\
			while((node = KEYTREE_ITERATOR_FORWARD_(treename)(&it)) != NULL){\
				KEYCOLLECT_LOCK_RELEASE_(self);\
				ret++;\
				if(dump != NULL){\
					loop_ret = (*dump)(node, userdata, buf, 64);\
				}\
				KEYCOLLECT_LOCK_ACQUIRE_(self);\
				printf("%s:[%p(%03d)]:val->%s\n", __func__, node, -1, buf);\
				if(loop_ret < 0){\
					break;\
				}\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		\
		return ret;\
	}\
	
#endif	/* !KEYHASH_H_ */
