/**
 *  \file		keylist_witchcraft.large.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	This is an implementation part defined by raw implementation.
 */

#include <stdint.h>
#include "../keylist.h"
#include "../keylist_raw.h"
#include "../keylist_functions.h"
#include "../keycollection_config.h"

#include "./keylist_inside.h"
#include "./keycollection_lock.h"

#ifndef	KEYLIST_WITCHCRAFT_H_
#error	NEVER INCLUDE THIS DIRECTLY
#endif

#ifndef	KEYLIST_WITCHCRAFT_LARGE_H_
#define	KEYLIST_WITCHCRAFT_LARGE_H_

/**
 *  \def	keylist_define_implements
 *  \brief	Withcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the types and functions based on this arg.(yourlist_t and yourlist_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */
#define	keylist_define_implements(yourlist, nodetype_s, link_member)\
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
		if(i >= self->size){\
			return NULL;\
		}\
		if(i < (self->size * -1)){\
			return NULL;\
		}\
		KEYCOLLECT_LOCK_ACQUIRE_(self);{\
			\
			if(i >= 0){\
				link = self->head;\
				for(; i > 0 && link != NULL; i--){\
					link = link->next;\
				}\
			}\
			\
			if(i < 0){\
				link = self->tail;\
				for(; i < -1 && link != NULL; i++){\
					link = link->prev;\
				}\
			}\
			\
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
		iterator->prev = self->tail;\
		iterator->next = self->head;\
		iterator->curr = NULL;\
		iterator->coll = self;\
		iterator->head = self->head;\
		iterator->tail = self->tail;\
		return 0;\
	}\
	\
	int				KEYLIST_INIT_ITERATOR_FROM_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator, nodetype_s *index_node){\
		if(index_node == NULL){\
			return keylist_init_iterator_raw(offsetof(nodetype_s, link_member), self, iterator);\
		}\
		if((index_node)->link_member.coll != self){\
			return -2;\
		}\
		iterator->curr = NULL;\
		iterator->next = &((index_node)->link_member);\
		iterator->prev = &((index_node)->link_member);\
		iterator->coll = (void*)self;\
		iterator->head = self->head;\
		iterator->tail = self->tail;\
		return 0;\
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
	nodetype_s*		KEYLIST_ITERATOR_REF_CURRENT_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return (nodetype_s *)keylist_iterator_ref_current_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
	int				KEYLIST_ITERATOR_IS_HEAD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return keylist_iterator_is_head_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
	\
	int				KEYLIST_ITERATOR_IS_TAIL_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return keylist_iterator_is_tail_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
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
	
#endif	/* !KEYLIST_WITCHCRAFT_LARGE_H_ */
