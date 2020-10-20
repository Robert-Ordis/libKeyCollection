/**
 *  \file		keytree_raw.h
 *  \brief		definitions for linked tree determines the linking-member's address by offset.
 *  \brief		1st arg is the offset address distance for linking-member of the structure.
 *  \remarks	This is just experimental API.
 *  \remarks	This may NOT be usable for incomplete type.
 */
#ifndef	KEYTREE_RAW_H_
#define	KEYTREE_RAW_H_

#include "./private/keycollection_commons.h"


/**
 *  \def		keytree_init_raw
 *  \brief		Get contained num on the List.
 *  \param		offset	unused
 *  \param		*self	tree instance.
 *  \remarks	Experimental implementation with macro.
 */
#define		keytree_init_raw(offset, self, allowEq, compNode, makeNode)\
	do{\
		(self)->head = NULL;\
		(self)->tail = NULL;\
		(self)->size = 0;\
		(self)->ofst = offset;\
		(self)->root = NULL;\
		(self)->allow_eq = allowEq;\
		(self)->comp_node = compNode;\
		(self)->make_node = makeNode;\
	}while(0)\

//数の取得など、変数を直接示すようなマクロは左辺にできないようにする
/**
 *  \def		keytree_get_count_raw
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
 *  \brief		Add a node to the tree.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some tree]
 */
int			keytree_add_raw(size_t offset, keytree_t *self, void *node);

/**
 *  \fn			keytree_insert_before_raw
 *  \brief		*FOR INSIDE USING OF KEYHASH*
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance, but this is same as keylist_t due to not have a comparator.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong in *self]
 *  \remarks	If index_node == NULL, node will be add in the tail.
 *  \remarks	If *self has a comparator, this is just an ADD operation.
 */
int			keytree_insert_before_raw(size_t offset, keylist_t *self, void *index_node, void *node);

/**
 *  \fn			keytree_insert_after_raw
 *  \brief		*FOR INSIDE USING OF KEYHASH*
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance, but this is same as keylist_t due to not have a comparator.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	If index_node == NULL, node will be add in the head..
 *  \remarks	If *self has a comparator, this is just an ADD operation.
 */
int			keytree_insert_after_raw(size_t offset, keylist_t *self, void *index_node, void *node);

/**
 *  \fn			keytree_find_eq_node_raw
 *  \brief		Find a node having value which equals to specified *node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*c_node	The node for comparison through the tree.
 */
void*		keytree_find_eq_node_raw(size_t offset, keytree_t *self, void *c_node);

//nodetype_t* yourtree_find_eq_value(keytree_t *self, void *value, size_t value_len);

/**
 *  \fn			keytree_find_eq_node_end_raw
 *  \brief		Find a TAIL node having value which equals to specified *node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*c_node	The node for comparison through the tree.
 *  \remarks	This is for the allow_eq == 1 tree, which has same-value nodes.
 */
void*		keytree_find_eq_node_end_raw(size_t offset, keytree_t *self, void *c_node);

/**
 *  \fn			keytree_find_ge_node_raw
 *  \brief		Find a node having value which is "GREATER THAN OR EQUAL TO(>=)" the specified *node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*c_node	The node for comparison through the tree.
 */
void*		keytree_find_ge_node_raw(size_t offset, keytree_t *self, void *c_node);

/**
 *  \fn			keytree_find_lt_node_raw
 *  \brief		Find a node having value which is "LESSER THAN(<)" the specified *node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*c_node	The node for comparison through the tree.
 */
void*		keytree_find_lt_node_raw(size_t offset, keytree_t *self, void *c_node);

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
 *  \fn			keytree_init_iterator_from_raw
 *  \brief		Initialize the keytree_iterator_t, which is already iterated to *index_node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*iterator	iterator instance.
 *  \param		*index_node	The node you want to set as the start point.
 *  \return	0: success
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	After this, next "keytree_iterator_forward_raw/backward_raw" returns *index_node as you specified.
 */
int			keytree_init_iterator_from_raw(size_t offset, keytree_t *self, keytree_iterator_t *iterator, void *index_node);

/**
 *  \fn			keytree_init_iterator_ranged_raw
 *  \brief		Initialize the keytree_iterator_t, which is limited to specified node range.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	tree instance.
 *  \param		*iterator	iterator instance.
 *  \param		*head		The node you want to set as HEAD node.
 *  \param		*index_node	The node you want to set as the start point.
 *  \param		*tail		The node you want to set as TAIL node.
 *  \return	0: success
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	After this, next "keytree_iterator_forward_raw/backward_raw" returns *index_node as you specified.
 */
int			keytree_init_iterator_from_raw(size_t offset, keytree_t *self, keytree_iterator_t *iterator, void *index_node);


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
 *  \def		keytree_iterator_ref_current_raw
 *  \brief		Refer the current node on the iterator.
 *  \param		offset	offset length to link member of the node..
 *  \param		*iterator	iterator instance.
 *  \return	Current node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the tree.
 */
#define		keytree_iterator_ref_current_raw(offset, iterator)\
	(keycollection_get_container_ptr(offset, (iterator)->curr))

/**
 *  \def		keytree_iterator_is_head_raw
 *  \brief		Check if the current node is the head.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the head.
 *  \remarks	MAY NOT BE NEEDED.
 */
#define		keytree_iterator_is_head_raw(offset, iterator)\
	((iterator)->head == (iterator)->curr)

/**
 *  \def		keytree_iterator_is_tail_raw
 *  \brief		Check if the current node is the tail.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the tail.
 *  \remarks	MAY NOT BE NEEDED.
 */
#define		keytree_iterator_is_tail_raw(offset, iterator)\
	((iterator)->tail == (iterator)->curr)

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
 *  \def		keytree_link_get_next_raw
 *  \brief		Get the next node of the node directly.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE TREE WHILE ITERATING BY THIS.
 */
#define		keytree_link_get_next_raw(offset, node)\
	(keycollection_get_container_ptr(offset, ((keytree_link_t *)keycollection_get_link_ptr(offset, node))->next))

/**
 *  \def		keytree_link_get_prev_raw
 *  \brief		Get the previous node of the node directly.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE TREE WHILE ITERATING BY THIS.
 */
#define		keytree_link_get_prev_raw(offset, node)\
	(keycollection_get_container_ptr(offset, ((keytree_link_t *)keycollection_get_link_ptr(offset, node))->prev))

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
