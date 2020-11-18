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
 *  \def		KEYTREE_ROUGHLY_TREAP_DELETION
 *  \brief		(config) Config for determine deletion algorithm
 *  \remarks	If this is defined, Do belows at delete.
 *  			1: Delete with the original method of binary tree.
 *  			2: Copy the priority of the deleted on the heap will copied to the proxy node.
 *
 */
#define	KEYTREE_ROUGHLY_TREAP_DELETION

/**
 *  \def		KEYTREE_TREAP_RNG
 *  \brief		(config) Config for determin which algorithm to use as rng.
 *  \remarks	0 = Linear congurential generator, 1 = xorshift.
 *
 */
#define	KEYTREE_TREAP_RNG 1

#endif	/* !KEYCOLLECT_CONFIG_H_ */
