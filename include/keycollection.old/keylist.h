/**
 *  \file	keylist.h
 *  \brief	固定式リンクリストをマクロで定義するためのライブラリ
 */

#include <stdint.h>
#include <pthread.h>
#include "./keylist_functions.h"
#include "./private/keylist_implementations.h"
#ifndef	KEYLIST_H_
#define	KEYLIST_H_


//公開マクロ中にて使用する各種マクロ

#define	KEYLIST_INNER_TYPE_S_(basename)			struct keylist_##basename##_s

/**
 *	\struct	keylist_link_basename_t
 *	\brief		name_t構造体において、リンクリストを構成するキーになるメンバの構造体
 */
#define	KEYLIST_LINK_TYPE_T_(basename)		keylist_link_##basename##_t					//メンバ用リンク構造体
#define	KEYLIST_LINK_TYPE_S_(basename)		struct keylist_link_##basename##_s			//素のメンバ用リンク構造体定義
#define	KEYLIST_INNER_ITERATOR_TYPE_S_(basename)	struct keylist_iterator_##basename##_s				//イテレータ


//プライベート
#ifdef __linux__
	#define	KEYLIST_LOCK_INIT_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_init(&(self)->lock, NULL);\
		}while(0)\

	#define	KEYLIST_LOCK_ACQUIRE_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_lock(&(self)->lock);\
		}while(0)\
		
	#define	KEYLIST_LOCK_RELEASE_(self)\
		do{\
			if((self)->if_lock)\
				pthread_mutex_unlock(&(self)->lock);\
		}while(0)\

	#define	KEYLIST_LOCKER_T	pthread_mutex_t

#else
	#define	KEYLIST_LOCK_INIT_(self)\
		do{\
		}while(0)\

	#define	KEYLIST_LOCK_ACQUIRE_(self)\
		do{\
		}while(0)\
		
	#define	KEYLIST_LOCK_RELEASE_(self)\
		do{\
		}while(0)\

	#define	KEYLIST_LOCKER_T	void*

#endif /* __linux__ */

/**
 *	\def	keylist_define_basetype
 *	\brief	構造体の前に行う最初の宣言。
 */

#define	keylist_define_basetype(basename, nodetype_s)\
	typedef KEYLIST_LINK_TYPE_S_(basename) {\
		nodetype_s	*prev;\
		nodetype_s	*next;\
		void		*list;\
	} KEYLIST_LINK_TYPE_T_(basename);\
	\
	KEYLIST_INNER_ITERATOR_TYPE_S_(basename){\
		nodetype_s	*prev;\
		nodetype_s	*curr;\
		nodetype_s	*next;\
		nodetype_s	*head;\
		nodetype_s	*tail;\
		void		*list;\
	};\
	\
	KEYLIST_INNER_TYPE_S_(basename){\
		nodetype_s			*head;\
		nodetype_s			*tail;\
		uint32_t			count;\
		int					if_lock;\
		KEYLIST_LOCKER_T	lock;\
	}
	
/**
 *	\def	keylist_define_prototypes
 *	\param	yourlist		yourlist_t及び関連型や関連関数(yourlist_xxx)の宣言が出来上がる。
 *	\param	basename		keylist_define_basetypeで使用したbasetypeをそのまま使う。
 *	\param	nodetype_s		実際に取り扱いたいノード型。struct nodetype_sでやるのが無難。
 *	\param	link_member		今回のリストにおけるリンカとして用いるメンバ変数名
 *	\brief	構造体の後に行う各種宣言。
 *	\brief	yourlist_tとyourlist_iterator_t及び関連関数(yourlist_xxx)がの宣言出来上がる。
 */
#define	keylist_define_prototypes(yourlist, basename, nodetype_s, link_member)\
	typedef			KEYLIST_INNER_TYPE_S_(basename) KEYLIST_T_(yourlist);\
	typedef			KEYLIST_INNER_ITERATOR_TYPE_S_(basename) KEYLIST_ITERATOR_T_(yourlist);\
	\
	void			KEYLIST_INIT_(yourlist)(KEYLIST_T_(yourlist) *self, int if_lock);\
	\
	int				KEYLIST_GET_COUNT_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_FIRST_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_LAST_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_POP_FIRST_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_POP_LAST_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	KEYLIST_T_(yourlist)* KEYLIST_GET_BELONGED_(yourlist)(nodetype_s* node);\
	\
	int				KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_DEL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_INSERT_BEFORE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYLIST_INSERT_AFTER_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYLIST_INIT_ITERATOR_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_INIT_ITERATOR_FROM_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator, nodetype_s *node);\
	\
	nodetype_s*		KEYLIST_ITERATE_FORWARD_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	nodetype_s*		KEYLIST_ITERATE_BACKWARD_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_ITERATOR_IS_HEAD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_ITERATOR_IS_TAIL_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	nodetype_s*		KEYLIST_GET_NEXT_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	nodetype_s*		KEYLIST_GET_PREV_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	
/**
 *	\def	keylist_define_implements
 *	\param	yourlist		yourlist_t及び関連型や関連関数(yourlist_xxx)の実装が出来上がる。
 *	\param	basename		keylist_define_basetypeで使用したbasetypeをそのまま使う。
 *	\param	nodetype_s		実際に取り扱いたいノード型。struct nodetype_sでやるのが無難。
 *	\param	link_member		今回のリストにおけるリンカとして用いるメンバ変数名
 *	\brief	
 *	\brief	
 */
#define	keylist_define_implements(yourlist, basename, nodetype_s, link_member)\
	\
	int				KEYLIST_DEL_INLOCK_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){ \
		int ret;\
		KEYLIST_IMPL_DEL_(self, node, link_member, ret);\
		return ret;\
	}\
	\
	void			KEYLIST_INIT_(yourlist)(KEYLIST_T_(yourlist) *self, int if_lock){\
		self->if_lock = (if_lock != 0);\
		KEYLIST_LOCK_INIT_(self);\
		self->head = NULL;\
		self->tail = NULL;\
		self->count = 0;\
	}\
	\
	int				KEYLIST_GET_COUNT_(yourlist)(KEYLIST_T_(yourlist) *self){\
		int ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			ret = self->count;\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYLIST_REF_FIRST_(yourlist)(KEYLIST_T_(yourlist) *self){\
		nodetype_s	*ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			ret = self->head;\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYLIST_REF_LAST_(yourlist)(KEYLIST_T_(yourlist) *self){\
		nodetype_s	*ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			ret = self->tail;\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYLIST_POP_FIRST_(yourlist)(KEYLIST_T_(yourlist) *self){\
		nodetype_s *ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			if((ret = self->head) != NULL){\
				KEYLIST_DEL_INLOCK_(yourlist)(self, ret);\
			}\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYLIST_POP_LAST_(yourlist)(KEYLIST_T_(yourlist) *self){\
		nodetype_s *ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			if((ret = self->tail) != NULL){\
				KEYLIST_DEL_INLOCK_(yourlist)(self, ret);\
			}\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	KEYLIST_T_(yourlist)* KEYLIST_GET_BELONGED_(yourlist)(nodetype_s* node){\
		return (node)->link_member.list;\
	}\
	\
	int				KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		nodetype_s *prev;\
		int ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ADD_(self, node, prev, link_member, ret);\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_DEL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		int ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			ret = KEYLIST_DEL_INLOCK_(yourlist)(self, node);\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_INSERT_BEFORE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node){\
		int ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INSERT_BEFORE_(self, index_node, node, link_member, ret);\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_INSERT_AFTER_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node){\
		int ret;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INSERT_AFTER_(self, index_node, node, link_member, ret);\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_INIT_ITERATOR_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		(iterator)->prev = (self)->tail;\
		(iterator)->next = (self)->head;\
		(iterator)->curr = NULL;\
		(iterator)->list = self;\
		(iterator)->head = (self)->head;\
		(iterator)->tail = (self)->tail;\
		return 0;\
	}\
	\
	int				KEYLIST_INIT_ITERATOR_FROM_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator, nodetype_s *node){\
		if(node == NULL){\
			return KEYLIST_INIT_ITERATOR_(yourlist)(self, iterator);\
		}\
		if((node)->link_member.list != self){\
			return -1;\
		}\
		(iterator)->curr = node;\
		(iterator)->next = (node)->link_member.next;\
		(iterator)->prev = (node)->link_member.prev;\
		(iterator)->list = self;\
		(iterator)->head = (self)->head;\
		(iterator)->tail = (self)->tail;\
		return 0;\
	}\
	\
	nodetype_s*		KEYLIST_ITERATE_FORWARD_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		nodetype_s *ret = NULL;\
		nodetype_s *next = (iterator)->next;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATE_FORWARD_(self, iterator, next, link_member, ret);\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
		\
	}\
	\
	nodetype_s*		KEYLIST_ITERATE_BACKWARD_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		nodetype_s *ret = NULL;\
		nodetype_s *prev = (iterator)->prev;\
		KEYLIST_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATE_BACKWARD_(self, iterator, prev, link_member, ret);\
		}KEYLIST_LOCK_RELEASE_(self);\
		return ret;\
		\
	}\
	\
	int				KEYLIST_ITERATOR_IS_HEAD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return (iterator)->head == (iterator)->curr;\
	}\
	\
	int				KEYLIST_ITERATOR_IS_TAIL_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return (iterator)->tail == (iterator)->curr;\
	}\
	\
	nodetype_s*		KEYLIST_GET_NEXT_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		if(node == NULL){\
			return self->head;\
		}\
		return self == (node)->link_member.list ? (node)->link_member.next : NULL;\
	}\
	\
	nodetype_s*		KEYLIST_GET_PREV_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		if(node == NULL){\
			return (self)->tail;\
		}\
		return (self == (node)->link_member.list) ? (node)->link_member.prev : NULL;\
	}\
	

	
	
#endif	/* !KELIST_H_ */
