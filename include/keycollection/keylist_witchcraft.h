/**
 *  \file		keylist_witchcraft.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	
 */
#ifndef	KEYLIST_WITCHCRAFT_H_
#define	KEYLIST_WITCHCRAFT_H_

#include <stdint.h>
#include "./keylist.h"
#include "./keycollection_config.h"
#include "./keylist_functions.h"
#include "./private/keylist_witchcraft.small.h"
#include "./private/keylist_witchcraft.large.h"

/**
 *  \brief	Witchcraft used in public header.
 *  \brief	By this macro, yourlist_t and related functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the types and functions based on this arg.(yourlist_t and yourlist_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making link on this definitions.
 */

#define	keylist_define_prototypes(yourlist, nodetype_s, link_member)\
	typedef			keylist_t			KEYLIST_T_(yourlist);\
	typedef			keylist_iterator_t	KEYLIST_ITERATOR_T_(yourlist);\
	\
	void			KEYLIST_INIT_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	int				KEYLIST_GET_COUNT_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_POP_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_POP_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self);\
	\
	nodetype_s*		KEYLIST_REF_NTH_(yourlist)(KEYLIST_T_(yourlist) *self, int nth);\
	\
	int				KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_ADD_HEAD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_ADD_TAIL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_DEL_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_HAS_NODE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	int				KEYLIST_INSERT_BEFORE_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYLIST_INSERT_AFTER_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node, nodetype_s *node);\
	\
	int				KEYLIST_INIT_ITERATOR_(yourlist)(KEYLIST_T_(yourlist) *self, KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	int				KEYLIST_ITERATOR_MOVE_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator, nodetype_s *index_node);\
	\
	nodetype_s*		KEYLIST_ITERATOR_FORWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	nodetype_s*		KEYLIST_ITERATOR_BACKWARD_(yourlist)(KEYLIST_ITERATOR_T_(yourlist) *iterator);\
	\
	nodetype_s*		KEYLIST_GET_NEXT_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	nodetype_s*		KEYLIST_GET_PREV_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node);\
	\
	KEYLIST_T_(yourlist)* KEYLIST_GET_BELONG_(yourlist)(nodetype_s* node);\
	\



/**
 *  \brief	Witchcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the functions related to below types: yourlist_t and yourlist_iterator_t.
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making a linkedlist on this definitions.
 */
#ifndef	keylist_define_implements

	#if defined(KEYLIST_GENERATE_FUNCS_AS_WRAPPER)
		#define keylist_define_implements keylist_define_implements_small
	#else
		#define keylist_define_implements keylist_define_implements_large
	#endif

#endif


#endif	/* !KEYLIST_WITCHCRAFT_SMALL_H_ */
