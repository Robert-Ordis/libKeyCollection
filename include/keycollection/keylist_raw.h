#include "./keylist.h"
#include "./private/keycollection_commons.h"

#ifndef	KEYLIST_RAW_H_
#define	KEYLIST_RAW_H_

/**
 *  \def		keylist_init_raw
 *  \brief		Get contained num on the List.
 *  \param		offset	unused
 *  \param		*self	list instance.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_init_raw(offset, self)\
	do{\
		(self)->head = NULL;\
		(self)->tail = NULL;\
		(self)->size = 0;\
	}while(0)\

//数の取得など、「参照だけ」になるマクロは左辺値にできないようにする
/**
 *  \def		keylist_get_count_raw
 *  \brief		Get contained num on the List.
 *  \param		offset	unused.
 *  \param		*self	list instance.[]
 *  \return	Number of nodes in the list.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_get_count_raw(offset, self)\
	((self)->size + 0)

/**
 *  \def		keylist_ref_head_raw
 *  \brief		Get top node in the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Top node in the list.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_ref_head_raw(offset, self)\
	(keycollection_get_container_ptr(offset, (self)->head))

/**
 *  \def		keylist_ref_tail_raw
 *  \brief		Get last node in the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Last node in the list.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_ref_tail_raw(offset, self)\
	(keycollection_get_container_ptr(offset, (self)->tail))

/**
 *  \fn			keylist_pop_head_raw
 *  \brief		Get and delete the top node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Top node in the list.(It is already removed from *self);
 */
void*		keylist_pop_head_raw(size_t offset, keylist_t *self);

/**
 *  \fn			keylist_pop_tail_raw
 *  \brief		Get and delete the last node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Last node in the list.(It is already removed from *self);
 */
void*		keylist_pop_tail_raw(size_t offset, keylist_t *self);

/**
 *  \fn			keylist_ref_nth_raw
 *  \brief		Get the nth(Top = 0th) node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
void*		keylist_ref_nth_raw(size_t offset, keylist_t *self, int nth);

/**
 *  \fn			keylist_add_raw
 *  \brief		Add a node to the tail of the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add_raw(size_t offset, keylist_t *self, void *node);

/**
 *  \fn			keylist_del_raw
 *  \brief		Delete the node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
int			keylist_del_raw(size_t offset, keylist_t *self, void *node);

/**
 *  \fn			keylist_insert_before_raw
 *  \brief		Insert the node to the list, before the *index_node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong in *self]
 *  \remarks	If index_node == NULL, node will be add in the tail.
 */
int			keylist_insert_before_raw(size_t offset, keylist_t *self, void *index_node, void *node);

/**
 *  \fn			keylist_insert_after_raw
 *  \brief		Insert the node to the list, before the *index_node.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	If index_node == NULL, node will be add in the head.
 */
int			keylist_insert_after_raw(size_t offset, keylist_t *self, void *index_node, void *node);

/**
 *  \fn			keylist_init_iterator_raw
 *  \brief		Initialize the keylist_iterator_t.
 *  \param		offset	unused.
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top.But once done, cannot reversely iterate to the other side.
 */
int			keylist_init_iterator_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator);

/**
 *  \fn			keylist_init_iterator_from_raw
 *  \brief		Initialize the keylist_iterator_t, which is already iterated to *index_node.
 *  \param		offset	offset length to link member of the node..
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \param		*index_node	The node you want to set as the start point.
 *  \return	0: success
 *  \return	-2: error[*index_node doesn't belong to *self]
 */
int			keylist_init_iterator_from_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator, void *index_node);

/**
 *  \fn			keylist_iterator_forward_raw
 *  \brief		Iterate to the next node.
 *  \param		offset	offset length to link member of the node..
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keylist_iterator_forward_raw(size_t offset, keylist_iterator_t *iterator);

/**
 *  \fn			keylist_iterator_backward_raw
 *  \brief		Iterate to the previous node.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keylist_iterator_backward_raw(size_t offset, keylist_iterator_t *iterator);

/**
 *  \def			keylist_iterator_ref_current
 *  \brief		Refer the current node on the iterator.
 *  \param		offset	offset length to link member of the node..
 *  \param		*iterator	iterator instance.
 *  \return	Current node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
#define		keylist_iterator_ref_current(offset, iterator)\
	(keycollection_get_container_ptr(offset, (iterator)->curr)

/**
 *  \def			keylist_iterator_is_head_raw
 *  \brief		Check if the current node is the head.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the head.
 *  \remarks	MAY NOT BE NEEDED.
 */
#define		keylist_iterator_is_head_raw(offset, iterator)\
	((iterator)->head == (iterator)->curr)

/**
 *  \def			keylist_iterator_is_tail_raw
 *  \brief		Check if the current node is the tail.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the tail.
 *  \remarks	MAY NOT BE NEEDED.
 */
#define		keylist_iterator_is_tail_raw(offset, iterator)\
	((iterator)->tail == (iterator)->curr)

/**
 *  \def			keylist_link_get_belonged_raw
 *  \brief		Get the list instance which the node belongs to.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The list instance which the node belongs to.
 */
#define		keylist_link_get_belonged_raw(offset, node)\
	((keylist_t *)(((keylist_link_t *)keycollection_get_link_ptr(node))->coll))

/**
 *  \def			keylist_link_get_next_raw
 *  \brief		Get the next node of the node directly.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
#define		keylist_link_get_next_raw(offset, node)\
	(keycollection_get_container_ptr(offset, ((keylist_link_t *)keycollection_get_link_ptr(offset, node))->next))

/**
 *  \def			keylist_link_get_prev_raw
 *  \brief		Get the previous node of the node directly.
 *  \param		offset	offset length to link member of the node.
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
#define		keylist_link_get_prev_raw(offset, node)\
	(keycollection_get_container_ptr(offset, ((keylist_link_t *)keycollection_get_link_ptr(offset, node))->prev))


#endif	/* !KEYLIST_RAW_H_ */
