/**
 *  \file		keylist_witchcraft.large.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	This is an implementation part defined as raw implementation.
 */

#include <stdint.h>
#include <stddef.h>
#include "../keylist.h"
#include "../keylist_raw.h"
#include "../keylist_functions.h"
#include "../keycollection_config.h"

#include "./keylist_inside.h"
#include "./keycollection_lock.h"

#ifndef	KEYLIST_WITCHCRAFT_H_
#error	NEVER INCLUDE THIS DIRECTLY
#endif

#ifndef	PRIVATE_KEYLIST_WITCHCRAFT_LARGE_H_
#define	PRIVATE_KEYLIST_WITCHCRAFT_LARGE_H_

/**
 *  \def	keylist_define_implements_large
 *  \brief	Witchcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the types and functions based on this arg.(yourlist_t and yourlist_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */
#define	keylist_define_implements_large(yourlist, nodetype_s, link_member)\
	void			KEYLIST_INIT_(yourlist)(KEYLIST_T_(yourlist) *self){\
		keylist_init_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	int				KEYLIST_GET_COUNT_(yourlist)(KEYLIST_T_(yourlist) *self){\
		return keylist_get_count_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYLIST_REF_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self){\
		return (nodetype_s *)keylist_ref_head_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYLIST_REF_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self){\
		return (nodetype_s *)keylist_ref_tail_raw(offsetof(nodetype_s, link_member), self);\
	}\
	/*--------------------マクロじゃないので手実装---------------*/\
	nodetype_s*		KEYLIST_POP_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self){\
		keylist_link_t *link = NULL;\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			if(self->head != NULL){\
				link = self->head;\
				KEYLIST_IMPL_DEL_(self, link, ret);\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), link);\
	}\
	\
	nodetype_s*		KEYLIST_POP_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self){\
		keylist_link_t *link = NULL;\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			if(self->tail != NULL){\
				link = self->tail;\
				KEYLIST_IMPL_DEL_(self, link, ret);\
			}\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), link);\
	}\
	\
	nodetype_s*		KEYLIST_REF_NTH_(yourlist)(KEYLIST_T_(yourlist) *self, int nth){\
		keylist_link_t *link = NULL;\
		int i = nth;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_REF_NTH_(self, link, i);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), link);\
	}\
	\
	int				KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ADD_TAIL_(self, &((node)->link_member), ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_ADD_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ADD_HEAD_(self, &((node)->link_member), ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_ADD_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ADD_TAIL_(self, &((node)->link_member), ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_DEL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_DEL_(self, &((node)->link_member), ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_HAS_NODE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		return self == (node)->link_member.coll;\
	}\
	\
	int				KEYLIST_INSERT_BEFORE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node){\
		int ret = -3;\
		keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offsetof(nodetype_s, link_member), node);\
		keylist_link_t *index_link = (keylist_link_t *)keycollection_get_link_ptr(offsetof(nodetype_s, link_member), index_node);\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INSERT_BEFORE_(self, index_link, link, ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_INSERT_AFTER_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node){\
		int ret = -3;\
		keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offsetof(nodetype_s, link_member), node);\
		keylist_link_t *index_link = (keylist_link_t *)keycollection_get_link_ptr(offsetof(nodetype_s, link_member), index_node);\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INSERT_AFTER_(self, index_link, link, ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_INIT_ITERATOR_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		int ret = 0;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_INIT_ITERATOR_(self, iterator, ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	int				KEYLIST_ITERATOR_MOVE_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator, nodetype_s *index_node){\
		int ret = 0;\
		keylist_link_t *link = (index_node == NULL) ? NULL : &((index_node)->link_member);\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATOR_MOVE_(iterator, link, ret);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return ret;\
	}\
	\
	nodetype_s*		KEYLIST_ITERATOR_FORWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		keylist_link_t	*tmp_link = iterator->next;\
		keylist_link_t	*ret_link;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATE_FORWARD_(iterator, tmp_link, ret_link);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), ret_link);\
	}\
	\
	nodetype_s*		KEYLIST_ITERATOR_BACKWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		keylist_link_t	*tmp_link = iterator->prev;\
		keylist_link_t	*ret_link;\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			KEYLIST_IMPL_ITERATE_BACKWARD_(iterator, tmp_link, ret_link);\
		}KEYCOLLECT_LOCK_RELEASE_(self);\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), ret_link);\
	}\
	/*----------------ここ以降は全部マクロ…----------------*/\
	\
	nodetype_s*		KEYLIST_GET_NEXT_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		if((node)->link_member.coll != self){\
			return NULL;\
		}\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), (node)->link_member.next);\
	}\
	\
	nodetype_s*		KEYLIST_GET_PREV_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		if((node)->link_member.coll != self){\
			return NULL;\
		}\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), (node)->link_member.prev);\
	}\
	\
	KEYLIST_T_(yourlist)* KEYLIST_GET_BELONG_(yourlist)(nodetype_s* node){\
		return (node)->link_member.coll;\
	}\
	
#endif	/* !PRIVATE_KEYLIST_WITCHCRAFT_LARGE_H_ */
