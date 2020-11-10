/**
 *  \file		keytree_raw.h
 *  \brief		definitions for binary tree with determining the linking-member's address by offset.
 *  \brief		1st arg is the offset address: distance to linking-member from the head of the structure.
 *  \remarks	This is for inside implement of witchcraft.small macro.
 *  \remarks	This may NOT be usable for incomplete type.
 */

#include <string.h>

#include "./private/keycollection_commons.h"

#ifndef	KEYTREE_RAW_H_
#define	KEYTREE_RAW_H_

/**
 *  \brief		Get contained num on the List.
 *  \param		offset	unused
 *  \param		*self	tree instance.
 *  \remarks	Experimental implementation with macro.
 */
#define		keytree_init_raw(offset, self, allowEq, compNode)\
	do{\
		/*some members are same as keytree.*/\
		(self)->head = NULL;\
		(self)->tail = NULL;\
		(self)->size = 0;\
		(self)->ofst = offset;\
		/*tree*/\
		(self)->root = NULL;\
		(self)->allow_eq = allowEq;\
		(self)->comp_node = compNode;\
		(self)->comp_equivalent = NULL;\
		(self)->make_node = NULL;\
		/*treap*/\
		memcpy(&((self)->rng), self, (sizeof((self)->rng) > sizeof(self)) ? sizeof(self) : sizeof((self)->rng));\
	}while(0)\

#define		keytree_set_eq_comp_raw(offset, self, eq_comp)\
	do{\
		(self)->comp_equivalent = eq_comp;\
	}while(0)\

/*数の取得など、変数を直接示すようなマクロは左辺にできないようにする*/
/**
 *  \brief		Get contained num on the List.
 *  \param		offset	unused.
 *  \param		*self	tree instance.[]
 *  \return	Number of nodes in the tree.
 *  \remarks	Experimental implementation with macro.
 */
#define		keytree_get_count_raw(offset, self)\
	((self)->size + 0)

/**
 *  \def		keytree_ref_head_raw
 *  \brief		Get top node in the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \return	Top node in the tree.
 *  \remarks	Experimental implementation with macro.
 */
#define		keytree_ref_head_raw(offset, self)\
	(keycollection_get_container_ptr(offset, (self)->head))

/**
 *  \def		keytree_ref_tail_raw
 *  \brief		Get last node in the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \return	Last node in the tree.
 *  \remarks	Experimental implementation with macro.
 */
#define		keytree_ref_tail_raw(offset, self)\
	(keycollection_get_container_ptr(offset, (self)->tail))

/**
 *  \fn			keytree_pop_head_raw
 *  \brief		Get and delete the top node from the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \return	Top node in the tree.(It is already removed from *self);
 */
void*		keytree_pop_head_raw(size_t offset, keytree_t *self);

/**
 *  \fn			keytree_pop_tail_raw
 *  \brief		Get and delete the last node from the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \return	Last node in the tree.(It is already removed from *self);
 */
void*		keytree_pop_tail_raw(size_t offset, keytree_t *self);

/**
 *  \fn			keytree_ref_nth_raw
 *  \brief		Get the nth(Top = 0th) node from the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
void*		keytree_ref_nth_raw(size_t offset, keytree_t *self, int nth);

/**
 *  \fn			keytree_add_raw
 *  \brief		Add a node to the tail of the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some tree]
 */
int			keytree_add_raw(size_t offset, keytree_t *self, void *node);

/**
 *  \fn			keytree_del_raw
 *  \brief		Delete the node from the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
int			keytree_del_raw(size_t offset, keytree_t *self, void *node);

/**
 *  \fn			keytree_insert_before_raw
 *  \brief		Insert the node to the tree, before the *index_node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some tree]
 *  \return	-2: error[*index_node doesn't belong in *self]
 *  \remarks	This is an secret function, for keyhash implementation.
 *  \remarks	If index_node == NULL, node will be add in the tail.
 */
int			keytree_insert_before_raw(size_t offset, keytree_t *self, void *index_node, void *node);

/**
 *  \fn			keytree_insert_after_raw
 *  \brief		Insert the node to the tree, before the *index_node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some tree]
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	This is an secret function, for keyhash implementation.
 *  \remarks	If index_node == NULL, node will be add in the head.
 */
int			keytree_insert_after_raw(size_t offset, keytree_t *self, void *index_node, void *node);

/**
 *  \fn			keytree_find_eq_node_raw
 *  \brief		Get the left edge node having value equals to specified node's.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_eq_node_raw(size_t offset, keytree_t *self, void *index_node);

/**
 *  \fn			keytree_find_eq_node_end_raw
 *  \brief		Get the right edge node having value equals to specified node's.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_eq_node_end_raw(size_t offset, keytree_t *self, void *index_node);

/**
 *  \fn			keytree_find_lt_node_raw
 *  \brief		Get the right edge node having value lesser than specified node's.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_lt_node_raw(size_t offset, keytree_t *self, void *index_node);

/**
 *  \fn			keytree_find_gt_node_raw
 *  \brief		Get the right edge node having value greater than specified node's.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_gt_node_raw(size_t offset, keytree_t *self, void *index_node);

/**
 *  \fn			keytree_find_le_node_raw
 *  \brief		Get the left edge node having value lesser than or equals to specified node's.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_le_node_raw(size_t offset, keytree_t *self, void *index_node);

/**
 *  \fn			keytree_find_ge_node_raw
 *  \brief		Get the left edge node having value greater than or equals to specified node's.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance
 *  \param		*index_node	node instance.
 *  \return	The node explained in the above brief.
 *  \return	NULL if no one has the value.
 *  \remarks	This is not usable for opaque pointer which doesn't have API for manipulating data.
 */
void*		keytree_find_ge_node_raw(size_t offset, keytree_t *self, void *index_node);

/**
 *  \fn			keytree_init_iterator_raw
 *  \brief		Initialize the keytree_iterator_t.
 *  \param		offset	unused.
 *  \param		*self	tree instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top.But once done, cannot reversely iterate to the other side.
 */
int			keytree_init_iterator_raw(size_t offset, keytree_t *self, keytree_iterator_t *iterator);

/**
 *  \fn			keytree_init_iterator_ranged_raw
 *  \brief		Initialize the range-limited keytree_iterator_t.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*iterator	iterator instance.
 *  \param		*head	Head for the iterator.Start from this on forward, End at this on backward.
 *  \param		*tail	Tail for the iterator.Start from this on backward, End at this on forward.
 *  \return	0: success -1:head > tail. -2: head/tail doesn't belong to *self.
 *  \remarks	head = NULL means using Tree's Head.
 *  \remarks	tail = NULL means using Tree's Tail.
 *  \remarks	The behavior when head/tail is removed on iterating is undefined. BE CAREFUL AT MULTI-THREADING.
 */
int			keytree_init_iterator_ranged_raw(size_t offset, keytree_t *self, keytree_iterator_t *iterator, void *head, void *tail);

/**
 *  \fn			keytree_iterator_move
 *  \brief		Move the iterator to one step before the specified node.
 *  \param		offset		offset length to link member of the node
 *  \param		*iterator	iterator instance
 *  \param		*index_node	The node you want to set as the first point.
 *  \return	0: success.
 *  \return	-2: error[*index_node doesn't belong to the tree which is src of iterator].
 *  \remarks	After this, next "keytree_iterator_forward/backward" returns *index_node as you specified.
 *  \remarks	index_node == NULL means to make iterator th the state after keytree_init_iterator(keytree_t*, keytree_iterator_t*)
 */
int			keytree_iterator_move_raw(size_t offset, keytree_iterator_t *self, void *index_node);

/**
 *  \fn			keytree_iterator_forward_raw
 *  \brief		Iterate to the next node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the tree.
 */
void*		keytree_iterator_forward_raw(size_t offset, keytree_iterator_t *iterator);

/**
 *  \fn			keytree_iterator_backward_raw
 *  \brief		Iterate to the previous node.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the tree.
 */
void*		keytree_iterator_backward_raw(size_t offset, keytree_iterator_t *iterator);

/**
 *  \def		keytree_link_get_belong_raw
 *  \brief		Get the tree instance which the node belongs to.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The tree instance which the node belongs to.
 */
#define		keytree_link_get_belong_raw(offset, node)\
	((keytree_t *)(((keytree_link_t *)keycollection_get_link_ptr(offset, node))->coll))

/**
 *  \fn			keytree_link_get_next_raw
 *  \brief		Get the next node of the node directly.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE TREE WHILE ITERATING BY THIS.
 */
void*		keytree_link_get_next_raw(size_t offset, void* node);

/**
 *  \fn			keytree_link_get_prev_raw
 *  \brief		Get the previous node of the node directly.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE TREE WHILE ITERATING BY THIS.
 */
void*		keytree_link_get_prev_raw(size_t offset, void* node);

/**
 *  \def		keytree_foreach_forward_raw
 *  \brief		Syntax sugar for fast forward iterating
 *	\param		offset	offset length to link member of the node
 *	\param		*node	working pointer of picking node
 *	\param		*self	tree instance
 */
#define		keytree_foreach_forward_raw(offset, node, self)\
	for(\
		node = keytree_ref_head_raw(offset, self);\
		node != NULL;\
		node = keytree_link_get_next_raw(offset, node)\
	)

/**
 *  \def		keytree_foreach_backward_raw
 *  \brief		Syntax sugar for fast backward iterating
 *	\param		offset	offset length to link member of the node
 *	\param		*node	working pointer of picking node
 *	\param		*self	tree instance
 */
#define		keytree_foreach_backward_raw(offset, node, self)\
	for(\
		node = keytree_ref_tail_raw(offset, self);\
		node != NULL;\
		node = keytree_link_get_prev_raw(offset, node)\
	)

#endif	/* !KEYTREE_RAW_H_ */
