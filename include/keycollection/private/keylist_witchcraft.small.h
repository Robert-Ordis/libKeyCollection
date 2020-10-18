/**
 *  \file		keylist_witchcraft.small.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	This is an implementation part define by calling raw-funcations.
 */

#include <stdint.h>
#include <stddef.h>
#include "../keylist.h"
#include "../keylist_raw.h"
#include "../keylist_functions.h"
#include "../keycollection_config.h"

#ifndef	KEYLIST_WITCHCRAFT_H_
#error	NEVER INCLUDE THIS DIRECTLY
#endif

#ifndef	KEYLIST_WITCHCRAFT_SMALL_H_
#define	KEYLIST_WITCHCRAFT_SMALL_H_

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
	\
	nodetype_s*		KEYLIST_POP_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self){\
		return (nodetype_s *)keylist_pop_head_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYLIST_POP_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self){\
		return (nodetype_s *)keylist_pop_tail_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYLIST_REF_NTH_(yourlist)(KEYLIST_T_(yourlist) *self, int nth){\
		return (nodetype_s *)keylist_ref_nth_raw(offsetof(nodetype_s, link_member), self, nth);\
	}\
	\
	int				KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		return keylist_add_raw(offsetof(nodetype_s, link_member), self, node);\
	}\
	\
	int				KEYLIST_ADD_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		return keylist_add_head_raw(offsetof(nodetype_s, link_member), self, node);\
	}\
	\
	int				KEYLIST_ADD_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		return keylist_add_tail_raw(offsetof(nodetype_s, link_member), self, node);\
	}\
	\
	int				KEYLIST_DEL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		return keylist_del_raw(offsetof(nodetype_s, link_member), self, node);\
	}\
	\
	int				KEYLIST_HAS_NODE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){\
		return self == keylist_link_get_belong_raw(offsetof(nodetype_s, link_member), node);\
	}\
	\
	int				KEYLIST_INSERT_BEFORE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node){\
		return keylist_insert_before_raw(offsetof(nodetype_s, link_member), self, index_node, node);\
	}\
	\
	int				KEYLIST_INSERT_AFTER_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node){\
		return keylist_insert_after_raw(offsetof(nodetype_s, link_member), self, index_node, node);\
	}\
	\
	int				KEYLIST_INIT_ITERATOR_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return keylist_init_iterator_raw(offsetof(nodetype_s, link_member), self, iterator);\
	}\
	\
	int				KEYLIST_INIT_ITERATOR_FROM_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator, nodetype_s *node){\
		return keylist_init_iterator_from_raw(offsetof(nodetype_s, link_member), self, iterator, node);\
	}\
	\
	nodetype_s*		KEYLIST_ITERATOR_FORWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return (nodetype_s *)keylist_iterator_forward_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
	\
	nodetype_s*		KEYLIST_ITERATOR_BACKWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator){\
		return (nodetype_s *)keylist_iterator_backward_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
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
	

#endif	/* !KEYLIST_WITCHCRAFT_SMALL_H_ */
