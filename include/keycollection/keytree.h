/**
 *  \file		keytree.h
 *  \brief		A binary search tree library using the defined member-field.
 *  \remarks	Due to treating a specified member-field to making link, 
 *				these functions are NOT restrictly type-safe.
 */

#include "./private/keycollection_commons.h"

#include <stdint.h>
#include <stddef.h>

#ifndef	KEYTREE_H_
#define	KEYTREE_H_

/**
 *  \typedef	keytree_link_t
 *  \brief		Set of members for composing a doubly linked tree.
 */
typedef struct keytree_link_s keytree_link_t;

/**
 *  \typedef	keytree_t
 *  \brief		Binary tree container(Generic/Raw type)
 *
 */
typedef struct keytree_s keytree_t;

/**
 *  \typedef	keytree_iterator_t
 *  \brief		Iterator for Binary search tree.(Same in my Doubly linked tree.)
 *  \brief		While iterating by this, the nearby node in the collection can be edited.
 */
typedef struct keytree_iterator_s keytree_iterator_t;

/**
 *  \typedef	keytree_comp_node_cb
 *  \brief		Callback for nodes comparison.
 *  \param		*node_a	A node.
 *  \param		*node_b B node.
 *  \return	(int) ret >= 1 if A > B / ret = 0 if A==B, / <= 1 if A < B.
 *  \remarks	This function must indicates A - B.
 */
typedef int	(*keytree_comp_node_cb)(void *node_a, void *node_b);

/**
 *  \typedef	keytree_make_node_cb
 *  \brief		Callback for making nodes for searching.
 *  \param		*node		Node for searching. (Will not be NULL).
 *  \param		*value		Value pointer.
 *  \param		value_len	Byte length of *value.
 *  \remarks	This is only used in xxx_find_*_value codes that are generated with witchcraft macro.
 */
typedef void	(*keytree_make_node_cb)(void *node, void *value, size_t value_len);

/**
 *
 *  \brief		Initialize the tree.
 *  \param		*self	tree instance.
 *  \param		allow_eq	0 if you don't want to add same-valued node in the tree. Otherwise if you allow.
 *  \param		comp_node	Comparator for the nodes on this tree.
 *  \remarks	If you  use this func, target struct must contains keytree_link_t as the first member.
 */
void		keytree_init(keytree_t *self, int allow_eq, keytree_comp_node_cb comp_node);

/**
 *
 *  \brief		Get contained num on the List.
 *  \param		*self	tree instance.
 *  \return	Number of nodes in the tree.
 */
int			keytree_get_count(keytree_t *self);

/**
 *
 *  \brief		Get top node in the tree.
 *  \param		*self	tree instance.
 *  \return	Top node in the tree.
 */
void*		keytree_ref_head(keytree_t *self);

/**
 *
 *  \brief		Get last node in the tree.
 *  \param		*self	tree instance.
 *  \return	Last node in the tree.
 */
void*		keytree_ref_tail(keytree_t *self);

/**
 *
 *  \brief		Get and delete the top node from the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \return	Top node in the tree.(It is already removed from *self);
 */
void*		keytree_pop_head(keytree_t *self);

/**
 *
 *  \brief		Get and delete the last node from the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \return	Last node in the tree.(It is already removed from *self);
 */
void*		keytree_pop_tail(keytree_t *self);

/**
 *
 *  \brief		Get the nth(Top = 0th) node from the tree.
 *  \param		*self	tree instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
void*		keytree_ref_nth(keytree_t *self, int nth);

/**
 *
 *  \brief		Add a node to the tree.
 *  \param		*self	tree instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some tree]
 */
int			keytree_add(keytree_t *self, void *node);

/**
 *
 *  \brief		Delete the node from the tree.
 *  \param		*self	tree instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
int			keytree_del(keytree_t *self, void *node);

/*keytree_insert_before*/

/*keytree_insert_after*/

/**
 *
 *  \brief		Check if *self has the node specified as *node.
 *  \param		*self	tree instance
 *  \param		*node	node instance.
 *  \return	1 if has. 0 if doesn't..
 */
int			keytree_has_node(keytree_t *self, void *node);

/*keytree_get_belong(void *node);*/

/**
 *
 *  \brief		Get the next node of the node directly.
 *  \param		*self	tree instance
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keytree_get_next(keytree_t *self, void *node);

/**
 *
 *  \brief		Get the previous node of the node directly.
 *  \param		*self	tree instance
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keytree_get_prev(keytree_t *self, void *node);

/**
 *
 *  \brief		Get the left edge node having value equals to specified node's.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_eq_node(keytree_t *self, void *index_node);
/*void*		keytree_find_eq_value(keytree_t *self, void *value, size_t value_len);*/

/**
 *
 *  \brief		Get the right edge node having value equals to specified node's.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_eq_node_end(keytree_t *self, void *index_node);
/*void*		keytree_find_eq_value_end(keytree_t *self, void *value, size_t value_len);*/

/**
 *
 *  \brief		Get the right edge node having value lesser than specified node's.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_lt_node(keytree_t *self, void *index_node);
/*void*		keytree_find_lt_value(keytree_t *self, void *value, size_t value_len);*/

/**
 *
 *  \brief		Get the right edge node having value greater than specified node's.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_gt_node(keytree_t *self, void *index_node);
/*void*		keytree_find_gt_node(keytree_t *self, void *value, size_t value_len);*/

/**
 *
 *  \brief		Get the left edge node having value lesser than or equals to specified node's.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_le_node(keytree_t *self, void *index_node);
/*void*		keytree_find_le_value(keytree_t *self, void *value, size_t value_len);*/

/**
 *
 *  \brief		Get the left edge node having value greater than or equals to specified node's.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_ge_node(keytree_t *self, void *index_node);
/*void*		keytree_find_ge_value(keytree_t *self, void *value, size_t value_len);*/

/**
 *
 *  \brief		Initialize the keytree_iterator_t.
 *  \param		*self	tree instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top. 
 *  			But once done, cannot reversely iterate to the other side again.
 */
int			keytree_init_iterator(keytree_t *self, keytree_iterator_t *iterator);

/**
 *
 *  \brief		Initialize the range-limited keytree_iterator_t.
 *  \param		*self	tree instance.
 *  \param		*iterator	iterator instance.
 *  \param		*head	Head for the iterator.Start from this on forward, End at this on backward.
 *  \param		*tail	Tail for the iterator.Start from this on backward, End at this on forward.
 *  \return	0: success -1:head > tail. -2: head/tail doesn't belong to *self.
 *  \remarks	head = NULL means using Tree's Head.
 *  \remarks	tail = NULL means using Tree's Tail.
 *  \remarks	The behavior when head/tail is removed on iterating is undefined. BE CAREFUL AT MULTI-THREADING.
 */
int			keytree_init_iterator_ranged(keytree_t *self, keytree_iterator_t *iterator, void *head, void *tail);

/**
 *
 *  \brief		Move the iterator to one step before the specified node.
 *  \param		*iterator	iterator instance
 *  \param		*index_node	The node you want to set as the first point.
 *  \return	0: success.
 *  \return	-2: error[*index_node doesn't belong to the tree which is src of iterator].
 *  \remarks	After this, next "keytree_iterator_forward/backward" returns *index_node as you specified.
 *  \remarks	index_node == NULL means to make the iterator to the state on initiated.
 */
int			keytree_iterator_move(keytree_iterator_t *iterator, void *index_node);

/**
 *
 *  \brief		Iterate to the next node.
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the obtained node from the tree.
 */
void*		keytree_iterator_forward(keytree_iterator_t *iterator);

/**
 *
 *  \brief		Iterate to the previous node.
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the obtained node from the tree.
 */
void*		keytree_iterator_backward(keytree_iterator_t *iterator);

/**
 *
 *  \brief		Syntax sugar for fast forward iterating
 *	\param		*node	working pointer of picking node
 *	\param		*self	tree instance
 */
#define		keytree_foreach_forward(node, self)\
	for(\
		node = keytree_ref_head(self);\
		node != NULL;\
		node = keytree_get_next(self, node)\
	)

/**
 *
 *  \brief		Syntax sugar for fast backward iterating
 *	\param		*node	working pointer of picking node
 *	\param		*self	tree instance
 */
#define		keytree_foreach_backward(node, self)\
	for(\
		node = keytree_ref_tail(self);\
		node != NULL;\
		node = keytree_get_prev(self, node)\
	)

/**
 *
 *  \brief		Initialize the keytree for treating the specified structure and member.
 *  \param		*self	tree instance
 *  \param		type	target structure type
 *  \param		member	link member for making linked tree.
 */
#define		keytree_init_for(self, allow_eq, comp_node, type, member)\
	do{\
		keytree_init(self, allow_eq, comp_node);\
		(self)->ofst = offsetof(type, member);\
	}while(0)\
		

struct keytree_link_s {
	/*
		KEYLISTのマクロを流用するので、メンバ名は共通
		For reusing KEYLIST macros, some member names are same as keytree_link_t.
	 */
	struct keytree_link_s	*prev;			/**previous pointer*/
	struct keytree_link_s	*next;			/**next pointer.*/
	struct keytree_s		*coll;			/**pointer of container(e.g. keytree_t)*/

	/*以下はツリー用。/ Belows are for keytree.*/
	struct keytree_link_s	*ge;			/**pointer for value evaled as "Greater than/Equals to" this.*/
	struct keytree_link_s	*lt;			/**pointer for value evaled as "Lesser than" this.*/
	struct keytree_link_s	*up;			/**pointer for the parent of this. If the struct is root, this is NULL.*/

	/*平衡2分木機能用。/ For self-balancing.*/
	long int				h_pri;			/**Priority on "Treap". Parent->h_pri <= Child->h_pri on promotive rotation.*/
};

struct keytree_s {
	/*
		KEYLISTのマクロを流用するので、メンバ名は共通
		For reusing KEYLIST macros, some member names are same as keytree_link_t.
	*/
	struct keytree_link_s*	head;	/**Pointer to head link.*/
	struct keytree_link_s*	tail;	/**Pointer to tail link.*/
	int						size;	/**Counter for having nodes.*/
	size_t					ofst;	/**DIRTY MEMBER. FOR PSEUDO POLYMORPHISM...LOL*/
	/*
		2020-10-04/KK: ロックの搭載を試みたものの、今のバージョンではやめた。
		コンセプトとしてdestroyを提供しない以上、init & destroyをAPIとして提供するﾓﾉとは相性が悪い。
		スレッドセーフティについては、外側から提供してください。
	 */
	/*以下はツリー用。/ Belows are for keytree.*/
	struct keytree_link_s*	root;		/**Root node on the tree.*/
	int						allow_eq;	/**1 if allowing to insert the "Equals" node to "ge" pointer.*/
	keytree_comp_node_cb	comp_node;	/**Node comparator*/
	keytree_make_node_cb	make_node;	/**Node value setter*/
	
	/*平衡2分木機能用。/ For self-balancing.*/
	unsigned short			rng[3];		/**work for reentrant RNG(jrand48)*/
};

struct keytree_iterator_s {
	/*
		KEYLISTのマクロを流用するので、メンバ名は共通
		For reusing KEYLIST macros, some member names are same as keytree_link_t.
	*/
	struct keytree_link_s	*prev;
	struct keytree_link_s	*curr;
	struct keytree_link_s	*next;
	struct keytree_s		*coll;
	/*
		KEYTREEで範囲制限付きイテレータが生きると考え、導入
	*/
	struct keytree_link_s	*head;
	struct keytree_link_s	*tail;
};
#endif	/* !KELIST_H_ */
