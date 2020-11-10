/**
 *  \file		keytree_witchcraft.small.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	This is an implementation part defined as raw-funcations caller.
 */

#include <stdint.h>
#include <stddef.h>
#include "../keytree.h"
#include "../keytree_raw.h"
#include "../keytree_functions.h"
#include "../keycollection_config.h"

#ifndef	KEYTREE_WITCHCRAFT_H_
#error	NEVER INCLUDE THIS DIRECTLY
#endif

#ifndef	PRIVATE_KEYTREE_WITCHCRAFT_SMALL_H_
#define	PRIVATE_KEYTREE_WITCHCRAFT_SMALL_H_

/**
 *  \def	keytree_define_implements
 *  \brief	Witchcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourtree_add/_del/...) are generated.
 *  \param	yourtree		Defining the types and functions based on this arg.(yourtree_t and yourtree_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */
#define	keytree_define_implements_small(yourtree, nodetype_s, link_member)\
	\
	void			KEYTREE_INIT_(yourtree)(KEYTREE_T_(yourtree) *self, int allow_eq, keytree_comp_node_cb comp_node, keytree_make_node_cb make_node){\
		keytree_init_raw(offsetof(nodetype_s, link_member), self, allow_eq, comp_node);\
		(self)->make_node = make_node;\
	}\
	\
	void			KEYTREE_SET_EQ_COMP_(yourtree)(KEYTREE_T_(yourtree) *self, keytree_comp_node_cb eq_sort){\
		keytree_set_eq_comp_raw(offsetof(nodetype_s, link_member), self, eq_sort);\
	}\
	\
	int				KEYTREE_GET_COUNT_(yourtree)(KEYTREE_T_(yourtree) *self){\
		return keytree_get_count_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYTREE_REF_HEAD_(yourtree)(KEYTREE_T_(yourtree) *self){\
		return (nodetype_s *)keytree_ref_head_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYTREE_REF_TAIL_(yourtree)(KEYTREE_T_(yourtree) *self){\
		return (nodetype_s *)keytree_ref_tail_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYTREE_POP_HEAD_(yourtree)(KEYTREE_T_(yourtree) *self){\
		return (nodetype_s *)keytree_pop_head_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYTREE_POP_TAIL_(yourtree)(KEYTREE_T_(yourtree) *self){\
		return (nodetype_s *)keytree_pop_tail_raw(offsetof(nodetype_s, link_member), self);\
	}\
	\
	nodetype_s*		KEYTREE_REF_NTH_(yourtree)(KEYTREE_T_(yourtree) *self, int nth){\
		return (nodetype_s *)keytree_ref_nth_raw(offsetof(nodetype_s, link_member), self, nth);\
	}\
	\
	int				KEYTREE_ADD_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		return keytree_add_raw(offsetof(nodetype_s, link_member), self, node);\
	}\
	\
	int				KEYTREE_DEL_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		return keytree_del_raw(offsetof(nodetype_s, link_member), self, node);\
	}\
	\
	int				KEYTREE_INSERT_BEFORE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node){\
		return keytree_insert_before_raw(offsetof(nodetype_s, link_member), self, index_node, node);\
	}\
	\
	int				KEYTREE_INSERT_AFTER_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node){\
		return keytree_insert_after_raw(offsetof(nodetype_s, link_member), self, index_node, node);\
	}\
	\
	int				KEYTREE_HAS_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		return self == keytree_link_get_belong_raw(offsetof(nodetype_s, link_member), node);\
	}\
	\
	nodetype_s*		KEYTREE_GET_NEXT_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		if((node)->link_member.coll != self){\
			return NULL;\
		}\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), (node)->link_member.next);\
	}\
	\
	nodetype_s*		KEYTREE_GET_PREV_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node){\
		if((node)->link_member.coll != self){\
			return NULL;\
		}\
		return keycollection_get_container_ptr(offsetof(nodetype_s, link_member), (node)->link_member.prev);\
	}\
	\
	KEYTREE_T_(yourtree)* KEYTREE_GET_BELONG_(yourtree)(nodetype_s* node){\
		return (node)->link_member.coll;\
	}\
	nodetype_s*		KEYTREE_FIND_EQ_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node){\
		return keytree_find_eq_node_raw(offsetof(nodetype_s, link_member), self, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_EQ_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		self->make_node(&v_node, value, value_len);\
		return keytree_find_eq_node_raw(offsetof(nodetype_s, link_member), self, &v_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_EQ_NODE_END_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node){\
		return keytree_find_eq_node_end_raw(offsetof(nodetype_s, link_member), self, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_EQ_VALUE_END_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		self->make_node(&v_node, value, value_len);\
		return keytree_find_eq_node_end_raw(offsetof(nodetype_s, link_member), self, &v_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_LT_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node){\
		return keytree_find_lt_node_raw(offsetof(nodetype_s, link_member), self, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_LT_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		self->make_node(&v_node, value, value_len);\
		return keytree_find_lt_node_raw(offsetof(nodetype_s, link_member), self, &v_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_GT_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node){\
		return keytree_find_gt_node_raw(offsetof(nodetype_s, link_member), self, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_GT_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		self->make_node(&v_node, value, value_len);\
		return keytree_find_gt_node_raw(offsetof(nodetype_s, link_member), self, &v_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_LE_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node){\
		return keytree_find_le_node_raw(offsetof(nodetype_s, link_member), self, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_LE_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		self->make_node(&v_node, value, value_len);\
		return keytree_find_le_node_raw(offsetof(nodetype_s, link_member), self, &v_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_GE_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node){\
		return keytree_find_ge_node_raw(offsetof(nodetype_s, link_member), self, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_FIND_GE_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len){\
		nodetype_s v_node;\
		self->make_node(&v_node, value, value_len);\
		return keytree_find_ge_node_raw(offsetof(nodetype_s, link_member), self, &v_node);\
	}\
	\
	int				KEYTREE_INIT_ITERATOR_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		return keytree_init_iterator_raw(offsetof(nodetype_s, link_member), self, iterator);\
	}\
	\
	int				KEYTREE_INIT_ITERATOR_RANGED_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator, nodetype_s *head, nodetype_s *tail){\
		return keytree_init_iterator_ranged_raw(offsetof(nodetype_s, link_member), self, iterator, head, tail);\
	}\
	\
	int				KEYTREE_ITERATOR_MOVE_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator, nodetype_s *index_node){\
		return keytree_iterator_move_raw(offsetof(nodetype_s, link_member), iterator, index_node);\
	}\
	\
	nodetype_s*		KEYTREE_ITERATOR_FORWARD_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		return (nodetype_s *)keytree_iterator_forward_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
	\
	nodetype_s*		KEYTREE_ITERATOR_BACKWARD_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator){\
		return (nodetype_s *)keytree_iterator_backward_raw(offsetof(nodetype_s, link_member), iterator);\
	}\
	
	

#endif	/* !PRIVATE_KEYTREE_WITCHCRAFT_SMALL_H_ */
