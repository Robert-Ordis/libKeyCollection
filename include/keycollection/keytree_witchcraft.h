/**
 *  \file		keytree_witchcraft.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	
 */
#ifndef	KEYTREE_WITCHCRAFT_H_
#define	KEYTREE_WITCHCRAFT_H_

#include <stdint.h>
#include "./keytree.h"
#include "./keycollection_config.h"
#include "./keytree_functions.h"
#include "./private/keytree_witchcraft.small.h"

/**
 *  \def	keytree_define_prototypes
 *  \brief	Witchcraft used in public header.
 *  \brief	By this macro, yourtree_t and related functions(yourtree_add/_del/...) are generated.
 *  \param	yourtree		Defining the types and functions based on this arg.(yourtree_t and yourtree_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */

#define	keytree_define_prototypes(yourtree, nodetype_s, link_member)\
	typedef			keytree_t			KEYTREE_T_(yourtree);\
	typedef			keytree_iterator_t	KEYTREE_ITERATOR_T_(yourtree);\
	\
	void			KEYTREE_INIT_(yourtree)(KEYTREE_T_(yourtree) *self, int allow_eq, keytree_comp_node_cb comp_node, keytree_make_node_cb make_node);\
	\
	int				KEYTREE_GET_COUNT_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_REF_HEAD_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_REF_TAIL_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_POP_HEAD_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_POP_TAIL_(yourtree)(KEYTREE_T_(yourtree) *self);\
	\
	nodetype_s*		KEYTREE_REF_NTH_(yourtree)(KEYTREE_T_(yourtree) *self, int nth);\
	\
	int				KEYTREE_ADD_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	int				KEYTREE_DEL_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	int				KEYTREE_INSERT_BEFORE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYTREE_INSERT_AFTER_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYTREE_HAS_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	nodetype_s*		KEYTREE_GET_NEXT_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	nodetype_s*		KEYTREE_GET_PREV_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *node);\
	\
	KEYTREE_T_(yourtree)* KEYTREE_GET_BELONG_(yourtree)(nodetype_s* node);\
	\
	nodetype_s*		KEYTREE_FIND_EQ_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_FIND_EQ_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_EQ_NODE_END_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_FIND_EQ_VALUE_END_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_LT_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_FIND_LT_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_GT_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_FIND_GT_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_LE_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_FIND_LE_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	nodetype_s*		KEYTREE_FIND_GE_NODE_(yourtree)(KEYTREE_T_(yourtree) *self, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_FIND_GE_VALUE_(yourtree)(KEYTREE_T_(yourtree) *self, void *value, size_t value_len);\
	\
	int				KEYTREE_INIT_ITERATOR_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	int				KEYTREE_INIT_ITERATOR_RANGED_(yourtree)(KEYTREE_T_(yourtree) *self, KEYTREE_ITERATOR_T_(yourtree) *iterator, nodetype_s *head, nodetype_s *tail);\
	\
	int				KEYTREE_ITERATOR_MOVE_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator, nodetype_s *index_node);\
	\
	nodetype_s*		KEYTREE_ITERATOR_FORWARD_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\
	nodetype_s*		KEYTREE_ITERATOR_BACKWARD_(yourtree)(KEYTREE_ITERATOR_T_(yourtree) *iterator);\
	\



/**
 *  \def	keytree_define_implements
 *  \brief	Witchcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourtree_add/_del/...) are generated.
 *  \param	yourtree		Defining the functions related to below types: yourtree_t and yourtree_iterator_t.
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making a linkedtree on this definitions.
 */
#ifndef	keytree_define_implements
	#define keytree_define_implements keytree_define_implements_small

#endif


#endif	/* !KEYTREE_WITCHCRAFT_SMALL_H_ */
