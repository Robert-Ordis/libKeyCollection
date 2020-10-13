/**
 *  \file		keyhash.h
 *  \brief		ハッシュテーブルをマクロで定義するためのライブラリ
 *	\remarks	ハッシュテーブルはハッシュとツリー/リンクリストで定義される
 *	\remarks	「検索対象の一部ノード自体がワイルドカード」の場合に特に効果を発揮します
 */
#include <assert.h>
 
#include "keyhash_functions.h"
#include "./private/keyhash_implementations.h"
#ifndef	KEYHASH_H_
#define	KEYHASH_H_

//プライベート
#ifdef __linux__
	#define	KEYHASH_LOCK_INIT_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_init(&(self)->lock, NULL);\
		}while(0)\

	#define	KEYHASH_LOCK_ACQUIRE_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_lock(&(self)->lock);\
		}while(0)\
		
	#define	KEYHASH_LOCK_RELEASE_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_unlock(&(self)->lock);\
		}while(0)\

	#define	KEYHASH_LOCKER_T	pthread_mutex_t

#else
	#define	KEYHASH_LOCK_INIT_(self)\
		do{\
		}while(0)\

	#define	KEYHASH_LOCK_ACQUIRE_(self)\
		do{\
		}while(0)\
		
	#define	KEYHASH_LOCK_RELEASE_(self)\
		do{\
		}while(0)\

	#define	KEYHASH_LOCKER_T	void*
#endif /* __linux__ */

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
	typedef	int		(*KEYHASH_NODE_COMP_T_(yourhash))(nodetype_s *node_a, nodetype_s *node_b);\
	typedef	void	(*KEYHASH_NODE_VIRT_T_(yourhash))(nodetype_s *node, void *value, size_t value_len);\
	typedef	int		(*KEYHASH_NODE_HASH_T_(yourhash))(nodetype_s *node_a);\
	\
	typedef struct {\
		KEYTREE_T_(treename)	hash_chain[hash_max];	/*通常のハッシュテーブル*/\
		KEYTREE_T_(treename)	wild_chain;				/*ワイルドカードレコードの格納場（リストとしての用途のみ）*/\
		KEYHASH_NODE_COMP_T_(yourhash)	comp;			/*比較関数。ツリーにもつける*/\
		KEYHASH_NODE_VIRT_T_(yourhash)	virt;			/*比較前準備。ツリーにもつける*/\
		KEYHASH_NODE_HASH_T_(yourhash)	hash;			/*ハッシュ計算関数*/\
		int								hash_width;		/*自身のハッシュの広さ*/\
		int								allow_eq;		/*同値の挿入を許すなら１*/\
		int								if_lock;		/*操作毎にロックをかけるなら１*/\
		KEYHASH_LOCKER_T				lock;			/*ロック*/\
	} KEYHASH_T_(yourhash);\
	\
	\
	typedef struct {\
		KEYHASH_T_(yourhash)			*hash;			/*ハッシュテーブル*/\
		nodetype_s						v_node;			/*比較用の仮想ノード（仮）*/\
		int								v_hash;			/*ハッシュ値*/\
		nodetype_s						*prev;			/*イテレーションの「前ノード」*/\
		nodetype_s						*next;			/*イテレーションの「後ノード」*/\
		nodetype_s						*curr;			/*今見ているノード*/\
		KEYTREE_ITERATOR_T_(treename)	iter;			/*イテレータ*/\
	} KEYHASH_FINDER_T_(yourhash);\
	\
	\
	void		KEYHASH_INIT_(yourhash)(KEYHASH_T_(yourhash) *self, int if_lock, int allow_eq, \
					KEYHASH_NODE_COMP_T_(yourhash) comp,\
					KEYHASH_NODE_VIRT_T_(yourhash) virt,\
					KEYHASH_NODE_HASH_T_(yourhash) hash,\
					int hash_width);\
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
	/*通常等価→ワイルドカードの順で前方から検索*/\
	nodetype_s *KEYHASH_GET_NODE_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	\
	/*ワイルドカード→通常等価の順で後方から検索*/\
	nodetype_s *KEYHASH_GET_NODE_END_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	\
	/*検索処理。普通の等価のうちの下っ端を当てる*/\
	nodetype_s *KEYHASH_GET_NORMAL_NODE_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	/*検索処理。等価のうちの大きいものを当てる*/\
	nodetype_s *KEYHASH_GET_NORMAL_NODE_END_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	/*ワイルドカードの該当する最初を引き当てる*/\
	nodetype_s *KEYHASH_GET_WILDCARD_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
	/*ワイルドカードの該当する最後を引き当てる*/\
	nodetype_s *KEYHASH_GET_WILDCARD_END_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len);\
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
	void		KEYHASH_INIT_(yourhash)(KEYHASH_T_(yourhash) *self, int if_lock, int allow_eq, \
					KEYHASH_NODE_COMP_T_(yourhash) comp,\
					KEYHASH_NODE_VIRT_T_(yourhash) virt,\
					KEYHASH_NODE_HASH_T_(yourhash) hash,\
					int hash_width){\
		assert(self != NULL);\
		assert(comp != NULL);\
		assert(virt != NULL);\
		assert(hash != NULL);\
		(self)->if_lock = (if_lock != 0);\
		KEYHASH_LOCK_INIT_(self);\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			int i;\
			(self)->comp = comp;\
			(self)->virt = virt;\
			(self)->hash = hash;\
			/*ハッシュテーブルの整備。広さを限界値を超えたりゼロにしたりしないよう気を付ける*/\
			(self)->hash_width = (hash_width > hash_max || hash_width < 1) ? hash_max : hash_width;\
			for(i = 0; i < (self)->hash_width; i++){\
				/*各通常チェインの初期化*/\
				KEYTREE_INIT_(treename)(&((self)->hash_chain[i]), 0, allow_eq, comp, virt);\
			}\
			/*ワイルドカードチェインの初期化。比較関数等をゼロとすることで線形リストとして定義づける*/\
			KEYTREE_INIT_(treename)(&((self)->wild_chain), 0, allow_eq, NULL, NULL);\
		}KEYHASH_LOCK_RELEASE_(self);\
	}\
	\
	\
	/*単純に各チェインの合計数を取得する*/\
	int			KEYHASH_GET_COUNT_(yourhash)(KEYHASH_T_(yourhash) *self){\
		int ret = KEYTREE_GET_COUNT_(treename)(&((self)->wild_chain));\
		int i;\
		for(i = 0; i < (self)->hash_width; i++){\
			ret += KEYTREE_GET_COUNT_(treename)(&((self)->hash_chain[i]));\
		}\
		return ret;\
	}\
	\
	/*追加処理。ハッシュ特定→ツリーアド。ツリーなので自動的にソートされますお*/\
	int			KEYHASH_ADD_(yourhash)(KEYHASH_T_(yourhash) *self, nodetype_s *node){\
		int ret = -1;\
		int hash_index;\
		KEYTREE_T_(treename) *dst = NULL;\
		\
		/*ハッシュ計算*/\
		KEYHASH_IMPL_CALC_HASH_(self, node, hash_index);\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			if(hash_index == -1){\
				/*算出値が-1だった場合にのみワイルドカードチェインを提供*/\
				dst = &((self)->wild_chain);\
			}\
			else if(hash_index >= 0){\
				/*そうでないのなら普通にチェーン提供*/\
				dst = &((self)->hash_chain[hash_index]);\
			}\
			if(dst != NULL){\
				/*チェーンに加える。ツリーなのでソートは自動で行われる*/\
				ret = KEYTREE_ADD_(treename)(dst, node);\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*削除処理。確認のためハッシュ特定→削除処理*/\
	int			KEYHASH_DEL_(yourhash)(KEYHASH_T_(yourhash) *self, nodetype_s *node){\
		int ret = -1;\
		int hash_index = (self)->hash(node);\
		KEYTREE_T_(treename) *dst = NULL;\
		KEYTREE_T_(treename) *belong = KEYTREE_GET_BELONGED_(treename)(node);\
		\
		/*ハッシュ計算*/\
		KEYHASH_IMPL_CALC_HASH_(self, node, hash_index);\
		if(belong == NULL){\
			/*そもそもどこにも所属していないのなら何もしない*/\
			return ret;\
		}\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			if(hash_index == -1){\
				/*算出値が-1だった場合にのみワイルドカードチェインを提供*/\
				dst = &((self)->wild_chain);\
			}\
			else if(hash_index >= 0){\
				/*そうでないのなら普通にチェーン提供*/\
				dst = &((self)->hash_chain[hash_index]);\
			}\
			if(dst != NULL){\
				/*そのチェーンが、nodeが属するもの*/\
				assert(dst == belong);\
				ret = KEYTREE_DEL_(treename)(dst, node);\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	/*通常ノード→ワイルドカードの順で一致するものを前方から検索する*/\
	nodetype_s *KEYHASH_GET_NODE_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s *ret_node = NULL;\
		nodetype_s v_node;\
		int hash;\
		\
		(self)->virt(&v_node, value, value_len);\
		KEYHASH_IMPL_CALC_HASH_(self, &v_node, hash);\
		\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			if(hash >= 0){\
				/*最初は普通に探す*/\
				ret_node = KEYTREE_FIND_EQ_(treename)(&(self)->hash_chain[hash], value, value_len);\
			}\
			if(ret_node == NULL){\
				/*もしヒットしなければワイルドカードから探す*/\
				KEYTREE_T_(treename) *dst = &((self)->wild_chain);\
				KEYTREE_ITERATOR_T_(treename) it;\
				KEYTREE_INIT_ITERATOR_(treename)(dst, &it);\
				while((ret_node = KEYTREE_ITERATE_FORWARD_(treename)(dst, &it)) != NULL){\
					/*ワイルドカードチェインを前から回して比較==0→「一致」が出たら終わる。*/\
					if((self)->comp(&v_node, ret_node) == 0){\
						break;\
					}\
				}\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret_node;\
	}\
	\
	/*ワイルドカード→通常ノードの順で一致するものを後方から検索する*/\
	nodetype_s *KEYHASH_GET_NODE_END_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s *ret_node = NULL;\
		nodetype_s v_node;\
		int hash;\
		\
		(self)->virt(&v_node, value, value_len);\
		\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			/*ワイルドカードの後ろから回す*/\
			KEYTREE_T_(treename) *dst = &((self)->wild_chain);\
			KEYTREE_ITERATOR_T_(treename) it;\
			KEYTREE_INIT_ITERATOR_(treename)(dst, &it);\
			while((ret_node = KEYTREE_ITERATE_BACKWARD_(treename)(dst, &it)) != NULL){\
				/*ワイルドカードチェインを前から回して比較==0→「一致」が出たら終わる。*/\
				if((self)->comp(&v_node, ret_node) == 0){\
					break;\
				}\
			}\
			\
			if(ret_node == NULL){\
				/*ワイルドカードで出なかったら通常チェーンから探す*/\
				KEYHASH_IMPL_CALC_HASH_(self, &v_node, hash);\
				if(hash >= 0){\
					ret_node = KEYTREE_FIND_EQ_END_(treename)(&(self)->hash_chain[hash], value, value_len);\
				}\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret_node;\
	}\
	\
	/*検索処理。普通の等価のうちの下っ端を当てる*/\
	nodetype_s *KEYHASH_GET_NORMAL_NODE_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		nodetype_s *ret_node = NULL;\
		(self)->virt(&v_node, value, value_len);\
		int hash;\
		KEYHASH_IMPL_CALC_HASH_(self, &v_node, hash);\
		\
		if(hash >= 0){\
			KEYHASH_LOCK_ACQUIRE_(self);{\
				ret_node = KEYTREE_FIND_EQ_(treename)(&(self)->hash_chain[hash], value, value_len);\
			}KEYHASH_LOCK_RELEASE_(self);\
		}\
		return ret_node;\
	}\
	/*検索処理。等価のうちの大きいものを当てる*/\
	nodetype_s *KEYHASH_GET_NORMAL_NODE_END_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		nodetype_s *ret_node = NULL;\
		(self)->virt(&v_node, value, value_len);\
		int hash;\
		KEYHASH_IMPL_CALC_HASH_(self, &v_node, hash);\
		\
		if(hash >= 0){\
			KEYHASH_LOCK_ACQUIRE_(self);{\
				ret_node = KEYTREE_FIND_EQ_END_(treename)(&(self)->hash_chain[hash], value, value_len);\
			}KEYHASH_LOCK_RELEASE_(self);\
		}\
		return ret_node;\
	}\
	/*ワイルドカードの該当する最初を引き当てる*/\
	nodetype_s *KEYHASH_GET_WILDCARD_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		nodetype_s *ret_node = NULL;\
		(self)->virt(&v_node, value, value_len);\
		\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			KEYTREE_T_(treename) *dst = &((self)->wild_chain);\
			KEYTREE_ITERATOR_T_(treename) it;\
			KEYTREE_INIT_ITERATOR_(treename)(dst, &it);\
			while((ret_node = KEYTREE_ITERATE_FORWARD_(treename)(dst, &it)) != NULL){\
				/*ワイルドカードチェインをひたすら回して比較==0→「一致」が出たら終わる。*/\
				if((self)->comp(&v_node, ret_node) == 0){\
					break;\
				}\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret_node;\
	}\
	/*ワイルドカードの該当する最後を引き当てる*/\
	nodetype_s *KEYHASH_GET_WILDCARD_END_(yourhash)(KEYHASH_T_(yourhash) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		nodetype_s *ret_node = NULL;\
		(self)->virt(&v_node, value, value_len);\
		\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			KEYTREE_T_(treename) *dst = &((self)->wild_chain);\
			KEYTREE_ITERATOR_T_(treename) it;\
			KEYTREE_INIT_ITERATOR_(treename)(dst, &it);\
			while((ret_node = KEYTREE_ITERATE_BACKWARD_(treename)(dst, &it)) != NULL){\
				/*ワイルドカードチェインをひたすら回して比較==0→「一致」が出たら終わる。*/\
				if((self)->comp(&v_node, ret_node) == 0){\
					break;\
				}\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret_node;\
	}\
	/*探索子（仮）を初期化する*/\
	int			KEYHASH_INIT_FINDER_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_FINDER_T_(yourhash) *finder, void *value, size_t value_len){\
		int ret = 0;\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			/*まずは比較用の仮想ノードを用意する*/\
			(self)->virt(&((finder)->v_node), value, value_len);\
			/*次に、ノードのハッシュ値を計算する*/\
			(finder)->v_hash = (self)->hash(&((finder)->v_node));\
			/*TODO: ここでもうnextとprevを据えておいた方がいいかも？*/\
			(finder)->curr = NULL;\
			(finder)->next = NULL;\
			(finder)->prev = NULL;\
			(finder)->hash = self;\
		}KEYHASH_LOCK_RELEASE_(self);\
		return ret;\
	}\
	/*探索子をもって、次ノードを取得する*/\
	nodetype_s	*KEYHASH_FIND_NEXT_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_FINDER_T_(yourhash) *finder){\
	}\
	/*探索子をもって、前ノードを取得する*/\
	nodetype_s	*KEYHASH_FIND_PREV_(yourhash)(KEYHASH_T_(yourhash) *self, KEYHASH_FINDER_T_(yourhash) *finder){\
	}\
	int			KEYHASH_DBG_DUMP_(yourhash)(KEYHASH_T_(yourhash) *self, void *userdata, int (*dump)(nodetype_s*, void*, char*, int)){\
		KEYTREE_ITERATOR_T_(treename) it;\
		nodetype_s	*node;\
		int i;\
		int ret;\
		int loop_ret = 0;\
		KEYHASH_LOCK_ACQUIRE_(self);{\
			\
			char buf[64];\
			for(i = 0; i < (self)->hash_width; i++){\
				printf("%s: chain number->%d\n", __func__, i);\
				KEYTREE_INIT_ITERATOR_(treename)(&((self)->hash_chain[i]), &it);\
				while((node = KEYTREE_ITERATE_FORWARD_(treename)(&((self)->hash_chain[i]), &it)) != NULL){\
					KEYHASH_LOCK_RELEASE_(self);\
					ret++;\
					if(dump != NULL){\
						loop_ret = (*dump)(node, userdata, buf, 64);\
					}\
					KEYHASH_LOCK_ACQUIRE_(self);\
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
				KEYHASH_LOCK_RELEASE_(self);\
				return ret;\
			}\
			KEYTREE_INIT_ITERATOR_(treename)(&((self)->wild_chain), &it);\
			printf("%s: wild chain\n", __func__);\
			while((node = KEYTREE_ITERATE_FORWARD_(treename)(&((self)->wild_chain), &it)) != NULL){\
				KEYHASH_LOCK_RELEASE_(self);\
				ret++;\
				if(dump != NULL){\
					loop_ret = (*dump)(node, userdata, buf, 64);\
				}\
				KEYHASH_LOCK_ACQUIRE_(self);\
				printf("%s:[%p(%03d)]:val->%s\n", __func__, node, -1, buf);\
				if(loop_ret < 0){\
					break;\
				}\
			}\
		}KEYHASH_LOCK_RELEASE_(self);\
		\
		return ret;\
	}\
	
#endif	/* !KEYHASH_H_ */
