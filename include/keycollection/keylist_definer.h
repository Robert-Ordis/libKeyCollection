/**
 *  \file	keylist_witchcraft.h
 *  \brief	witchcraft-like code generator macros.
 */

#include <stdint.h>
#include "./keycollection_config.h"

#ifndef	KEYLIST_WITCHCRAFT_H_
#define	KEYLIST_WITCHCRAFT_H_


/**
 *  \def	keylist_define_prototypes
 *  \brief	Withcraft used in public header.
 *  \brief	By this macro, yourlist_t and related functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the types and functions based on this arg.(yourlist_t and yourlist_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */
#define	keylist_define_prototypes(yourlist, nodetype_s, link_member)\
	typedef			struct keylist_s			KEYLIST_T_(yourlist);\
	typedef			struct keylist_iterator_s	KEYLIST_ITERATOR_T_(yourlist);\
	\
	void			KEYLIST_INIT_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	int				KEYLIST_GET_COUNT_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_POP_FIRST_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_POP_LAST_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	int				KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_ADD_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_ADD_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
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
	nodetype_s*		KEYLIST_ITERATOR_FORWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	nodetype_s*		KEYLIST_ITERATOR_BACKWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_ITERATOR_IS_HEAD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_ITERATOR_IS_TAIL_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_ITERATOR_REF_CURRENT_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	nodetype_s*		KEYLIST_LINK_GET_NEXT_(yourlist)(nodetype_s *node);\
	\
	nodetype_s*		KEYLIST_LINK_GET_PREV_(yourlist)(nodetype_s *node);\
	\
	KEYLIST_T_(yourlist)* KEYLIST_LINK_GET_BELONGED_(yourlist)(nodetype_s* node);\
	\

/**
 *  \def	keylist_define_implements
 *  \brief	Withcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the types and functions based on this arg.(yourlist_t and yourlist_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */
#if defined(KEYLIST_GENERATE_FUNCS_AS_WRAPPER)
	
#else
	
#endif


#endif	/* !KEYLIST_WITCHCRAFT_H_ */
