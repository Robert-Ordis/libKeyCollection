/**
 *  \file		keylist_generic.h
 *  \brief		definitions for generic linked list determined by type, member
 *  \brief		1st arg is type of target structure.
 *  \brief		2nd arg is keylist_link_t member in the target determined as 1st arg.
 *  \remarks	This is just experimental API.
 *  \remarks	This is NOT usable for incomplete type.
 */
#include <stddef.h>
#include "./keylist.h"
#include "./keylist_raw.h"

#ifndef	KEYLIST_GENERIC_H_
#define	KEYLIST_GENERIC_H_

/**
 *  \def		keylist_init_generic
 *  \brief		Get contained num on the List.
 *  \param		type	unused
 *  \param		member	unused
 *  \param		*self	list instance.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_init_generic(type, member, self)\
			keylist_init_raw(offsetof(type, member), self)

//数の取得など、「参照だけ」になるマクロは左辺値にできないようにする
/**
 *  \def		keylist_get_count_generic
 *  \brief		Get contained num on the List.
 *  \param		type	unused
 *  \param		member	unused
 *  \param		*self	list instance.[]
 *  \return	Number of nodes in the list.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_get_count_generic(type, member, self)\
			keylist_get_count_raw(offsetof(type, member), self)

/**
 *  \def		keylist_ref_head_generic
 *  \brief		Get top node in the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Top node in the list.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_ref_head_generic(type, member, self)\
	(type *)keylist_ref_head_raw(offsetof(type, member), self)

/**
 *  \def		keylist_ref_tail_generic
 *  \brief		Get last node in the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Last node in the list.
 *  \remarks	Experimental implementation with macro.
 */
#define		keylist_ref_tail_generic(type, member, self)\
	(type *)keylist_ref_tail_raw(offsetof(type, member), self)

/**
 *  \fn			keylist_pop_head_generic
 *  \brief		Get and delete the top node from the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \return	Top node in the list.(It is already removed from *self);
 */
#define		keylist_pop_head_generic(type, member, self)\
	(type *)keylist_pop_head_raw(offsetof(type, member), self)

/**
 *  \fn			keylist_pop_tail_generic
 *  \brief		Get and delete the last node from the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \return	Last node in the list.(It is already removed from *self);
 */
#define		keylist_pop_tail_generic(type, member, self)\
	(type *)keylist_pop_tail_raw(offsetof(type, member), self)

/**
 *  \fn			keylist_ref_nth_generic
 *  \brief		Get the nth(Top = 0th) node from the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
#define		keylist_ref_nth_generic(type, member, self, nth)\
	(type *)keylist_ref_nth_raw(offsetof(type, member), self, nth)

/**
 *  \fn			keylist_add_generic
 *  \brief		Add a node to the tail of the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
#define		keylist_add_generic(type, member, self, node)\
			keylist_add_raw(offsetof(type, member), self, (type *)node)

/**
 *  \fn			keylist_add_head_generic
 *  \brief		Add a node to the head of the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
#define		keylist_add_head_generic(type, member, self, node)\
			keylist_add_head_raw(offsetof(type, member), self, (type *)node)

/**
 *  \fn			keylist_add_tail_generic
 *  \brief		Add a node to the tail of the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
#define		keylist_add_tail_generic(type, member, self, node)\
			keylist_add_tail_raw(offsetof(type, member), self, (type *)node)
/**
 *  \fn			keylist_del_generic
 *  \brief		Delete the node from the list.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
#define		keylist_del_generic(type, member, self, node)\
			keylist_del_raw(offsetof(type, member), self, (type *)node)

/**
 *  \fn			keylist_insert_before_generic
 *  \brief		Insert the node to the list, before the *index_node.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong in *self]
 *  \remarks	If index_node == NULL, node will be add in the tail.
 */
#define		keylist_insert_before_generic(type, member, self, index_node, node)\
			keylist_insert_before_raw(offsetof(type, member), self, (type *)index_node, (type *)node)

/**
 *  \fn			keylist_insert_after_generic
 *  \brief		Insert the node to the list, before the *index_node.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	If index_node == NULL, node will be add in the head.
 */
#define		keylist_insert_after_generic(type, member, self, index_node, node)\
			keylist_insert_after_raw(offsetof(type, member), self, (type *)index_node, (type *)node)

/**
 *  \fn			keylist_init_iterator_generic
 *  \brief		Initialize the keylist_iterator_t.
 *  \param		type	unused
 *  \param		member	unused
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top.But once done, cannot reversely iterate to the other side.
 */
#define		keylist_init_iterator_generic(type, member, self, iterator)\
			keylist_init_iterator_raw(offsetof(type, member), self, iterator)

/**
 *  \fn			keylist_init_iterator_from_generic
 *  \brief		Initialize the keylist_iterator_t, which is already iterated to *index_node.
 *  \param		type	Type of the node that *self contains.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \param		*index_node	The node you want to set as the start point.
 *  \return	0: success
 *  \return	-2: error[*index_node doesn't belong to *self]
 */
#define		keylist_init_iterator_from_generic(type, member, self, iterator, index_node)\
			keylist_init_iterator_from_raw(offsetof(type, member), self, iterator, (type *)index_node)

/**
 *  \fn			keylist_iterator_forward_generic
 *  \brief		Iterate to the next node.
 *  \param		type	Type of the node that *iterator treats.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
#define		keylist_iterator_forward_generic(type, member, iterator)\
	(type *)keylist_iterator_forward_raw(offsetof(type, member), iterator)

/**
 *  \fn			keylist_iterator_backward_generic
 *  \brief		Iterate to the previous node.
 *  \param		type	Type of the node that *iterator treats.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
#define		keylist_iterator_backward_generic(type, member, iterator)\
	(type *)keylist_iterator_backward_raw(offsetof(type, member), iterator)

/**
 *  \def		keylist_iterator_ref_current_generic
 *  \brief		Refer the current node on the iterator.
 *  \param		type	Type of the node that *iterator treats.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*iterator	iterator instance.
 *  \return	Current node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
#define		keylist_iterator_ref_current_generic(type, member, iterator)\
	(type *)keylist_iterator_ref_current_raw(offsetof(type, member), iterator)

/**
 *  \def		keylist_iterator_is_head_generic
 *  \brief		Check if the current node is the head.
 *  \param		type	unused
 *  \param		member	unused
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the head.
 *  \remarks	MAY NOT BE NEEDED.
 */
#define		keylist_iterator_is_head_generic(type, member, iterator)\
			keylist_iterator_is_head_raw(offsetof(type, member), iterator)

/**
 *  \def		keylist_iterator_is_tail_generic
 *  \brief		Check if the current node is the tail.
 *  \param		offset	unused.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the tail.
 *  \remarks	MAY NOT BE NEEDED.
 */
#define		keylist_iterator_is_tail_generic(type, member, iterator)\
			keylist_iterator_is_tail_raw(offsetof(type, member), iterator)

/**
 *  \def		keylist_link_get_belong_generic
 *  \brief		Get the list instance which the node belongs to.
 *  \param		type	Type of the *node.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*node	node instance.
 *  \return	The list instance which the node belongs to.
 */
#define		keylist_link_get_belong_generic(type, member, node)\
	(keylist_t *)(node->member.coll)
	
/**
 *  \def		keylist_link_get_next_generic
 *  \brief		Get the next node of the node directly.
 *  \param		type	Type of the *node.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
#define		keylist_link_get_next_generic(type, member, node)\
	(type *)(keycollection_get_container_ptr(offsetof(type, member), ((type *)node)->member.next))

/**
 *  \def		keylist_link_get_prev_generic
 *  \brief		Get the previous node of the node directly.
 *  \param		type	Type of the *node.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
#define		keylist_link_get_prev_generic(type, member, node)\
	(type *)(keycollection_get_container_ptr(offsetof(type, member), ((type *)node)->member.prev))

/**
 *  \def		keylist_foreach_forward_generic
 *  \brief		Syntax sugar for fast forward iterating
 *  \param		type	Type of the *node.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *	\param		*node	working pointer of picking node
 *	\param		*self	list instance
 */
#define		keylist_foreach_forward_generic(type, member, node, self)\
	for(\
		node = keylist_ref_head_generic(type, member, self);\
		node != NULL;\
		node = keylist_link_get_next_generic(type, member, node)\
	)

/**
 *  \def		keylist_foreach_backward_generic
 *  \brief		Syntax sugar for fast backward iterating
 *  \param		type	Type of the *node.
 *  \param		member	The member in the (type). "member" must be defined as the link(keylist_link_t*)
 *	\param		*node	working pointer of picking node
 *	\param		*self	list instance
 */
#define		keylist_foreach_backward_generic(type, member, node, self)\
	for(\
		node = keylist_ref_tail_generic(type, member, self);\
		node != NULL;\
		node = keylist_link_get_prev_generic(type, member, node)\
	)

#endif	/* !KEYLIST_GENERIC_H_ */
