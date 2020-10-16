#ifndef	KEYCOLLECT_CONFIG_H_
#define	KEYCOLLECT_CONFIG_H_

/**
 *  \def		KEYLIST_GENERATE_FUNCS_AS_WRAPPER
 *  \brief		(config) making the generated Doubly linked list functions as wrapper or not.
 *  \remarks	If this is undefed, the generated funcs code will be bit faster but enlarged.
 *  \remarks	Because, in undefed case, code of funcs will be defined DIRECTLY.
 */
#define	KEYLIST_GENERATE_FUNCS_AS_WRAPPER

/**
 *  \def		KEYTREE_GENERATE_FUNCS_AS_WRAPPER
 *  \brief		(config) making the generated Binary tree functions as wrapper or not.
 *  \remarks	If this is undefed, the generated funcs code will be bit faster but enlarged.
 *  \remarks	Because, in undefed case, code of funcs will be defined DIRECTLY.
 */
#define	KEYTREE_GENERATE_FUNCS_AS_WRAPPER

#endif	/* !KEYCOLLECT_CONFIG_H_ */
