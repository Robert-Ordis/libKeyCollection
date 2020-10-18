/**
 *  \file		keylist_witchcraft.small.h
 *  \brief		witchcraft-like code generator macros.
 *  \remark	
 */

#include <stdint.h>
#include "./keylist.h"
#include "./keycollection_config.h"

#ifndef	KEYLIST_WITCHCRAFT_H_
#define	KEYLIST_WITCHCRAFT_H_

/**
 *  \def	keylist_define_prototypes
 *  \brief	Withcraft used in public header.
 *  \brief	By this macro, yourlist_t and related functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the types and functions based on this arg.(yourlist_t and yourlist_add, e.g.)
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making a linkedlist on this definitions.
 */
#ifndef	keylist_define_prototypes

/**
 *  \def	keylist_define_implements
 *  \brief	Withcraft used in source code(*.c)
 *  \brief	By this macro, implementation of functions(yourlist_add/_del/...) are generated.
 *  \param	yourlist		Defining the functions related to below types: yourlist_t and yourlist_iterator_t.
 *  \param	nodetype_s		Target type you want to treat.
 *  \param	link_member		Target link member you want to use for making a linkedlist on this definitions.
 */
#ifndef	keylist_define_implements

#if defined(KEYLIST_GENERATE_FUNCS_AS_WRAPPER)
	#include "./private/keylist_witchcraft.small.h"
#else
	#include "./private/keylist_witchcraft.large.h"
#endif

#endif

#endif

#endif	/* !KEYLIST_WITCHCRAFT_SMALL_H_ */
