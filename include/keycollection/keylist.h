/**
 *  \file		keylist.h
 *  \brief		A doubly linked list library using the defined member-field.
 *  \remarks	Due to treating a specified member-field to making link, 
 *				these functions are NOT restrictly type-safe.
 */
#ifndef	KEYLIST_H_
#define	KEYLIST_H_

#include <stdint.h>
#include <stddef.h>

/**
 *  \brief		Set of members for composing a doubly linked list.
 *  \details	First, set this as a member of the struct you want to make Doubly Linked List.
 */
typedef struct keylist_link_s keylist_link_t;

/**
 *  \brief		Doubly linked list container(Generic/Raw type)
 *
 */
typedef struct keylist_s keylist_t;

/**
 *  \brief		Iterator for doubly linked list.(may be same in binary tree)
 *  \brief		While iterating by this, the nearby node in the collection can be edited.
 */
typedef struct keylist_iterator_s keylist_iterator_t;

/**
 *  \brief		Initialize the list.
 *  \param		*self	list instance.
 *  \remarks	If you  use this func, target struct must contains keylist_link_t as the first member.
 */
void		keylist_init(keylist_t *self);

/**
 *  \brief		Get contained num on the List.
 *  \param		*self	list instance.
 *  \return	Number of nodes in the list.
 *  \remarks	Experimental implementation with macro.
 */
int			keylist_get_count(keylist_t *self);

/**
 *
 *  \brief		Get top node in the list.
 *  \param		*self	list instance.
 *  \return	Top node in the list.
 */
void*		keylist_ref_head(keylist_t *self);

/**
 *
 *  \brief		Get last node in the list.
 *  \param		*self	list instance.
 *  \return	Last node in the list.
 */
void*		keylist_ref_tail(keylist_t *self);

/**
 *
 *  \brief		Get and delete the top node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Top node in the list.(It is already removed from *self);
 */
void*		keylist_pop_head(keylist_t *self);

/**
 *
 *  \brief		Get and delete the last node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Last node in the list.(It is already removed from *self);
 */
void*		keylist_pop_tail(keylist_t *self);

/**
 *
 *  \brief		Get the nth(Top = 0th) node from the list.
 *  \param		*self	list instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
void*		keylist_ref_nth(keylist_t *self, int nth);

/**
 *
 *  \brief		Add a node to the tail of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add(keylist_t *self, void *node);

/**
 *
 *  \brief		Add a node to the head of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add_head(keylist_t *self, void *node);

/**
 *
 *  \brief		Add a node to the tail of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add_tail(keylist_t *self, void *node);

/**
 *
 *  \brief		Delete the node from the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
int			keylist_del(keylist_t *self, void *node);

/**
 *
 *  \brief		Insert the node to the list, before the *index_node.
 *  \param		*self	list instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong in *self]
 *  \remarks	If index_node == NULL, node will be add in the tail.
 */
int			keylist_insert_before(keylist_t *self, void *index_node, void *node);

/**
 *
 *  \brief		Insert the node to the list, before the *index_node.
 *  \param		*self	list instance.
 *  \param		*index_node	Index node. *node will be inserted before this.
 *  \param		*node	The node you want to add into *self.
 *  \return	0: success
 *  \return	-1: error[tried to add the *node already belonging in some list]
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	If index_node == NULL, node will be add in the head.
 */
int			keylist_insert_after(keylist_t *self, void *index_node, void *node);

/**
 *
 *  \brief		Check if *self has the node specified as *node.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	1 if has. 0 if doesn't.
 */
int			keylist_has_node(keylist_t *self, void *node);

/**
 *
 *  \brief		Get the next node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keylist_get_next(keylist_t *self, void *node);

/**
 *
 *  \brief		Get the previous node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keylist_get_prev(keylist_t *self, void *node);


/**
 *
 *  \brief		Initialize the keylist_iterator_t.
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top.But once done, cannot reversely iterate to the other edge.
 */
int			keylist_init_iterator(keylist_t *self, keylist_iterator_t *iterator);

/**
 *
 *  \brief		Move the iterator to one step before the specified node.
 *  \param		*iterator	iterator instance
 *  \param		*index_node	The node you want to set as the first point.
 *  \return	0: success.
 *  \return	-2: error[*index_node doesn't belong to the list which is src of iterator].
 *  \remarks	After this, next "keylist_iterator_forward/backward" returns *index_node as you specified.
 *  \remarks	index_node == NULL means to make iterator th the state after keylist_init_iterator(keylist_t*, keylist_iterator_t*)
 */
int			keylist_iterator_move(keylist_iterator_t *iterator, void *index_node);

/**
 *
 *  \brief		Iterate to the next node.
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keylist_iterator_forward(keylist_iterator_t *iterator);

/**
 *
 *  \brief		Iterate to the previous node.
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keylist_iterator_backward(keylist_iterator_t *iterator);


/**
 *
 *  \brief		Syntax sugar for fast forward iterating
 *	\param		offset	offset length to link member of the node
 *	\param		*node	working pointer of picking node
 *	\param		*self	list instance
 */
#define		keylist_foreach_forward(node, self)\
	for(\
		node = keylist_ref_head(self);\
		node != NULL;\
		node = keylist_get_next(self, node)\
	)

/**
 *
 *  \brief		Syntax sugar for fast backward iterating
 *	\param		offset	offset length to link member of the node
 *	\param		*node	working pointer of picking node
 *	\param		*self	list instance
 */
#define		keylist_foreach_backward(node, self)\
	for(\
		node = keylist_ref_tail(self);\
		node != NULL;\
		node = keylist_get_prev(self, node)\
	)

/**
 *
 *  \brief		Initialize the keylist for treating the specified structure and link-member.
 *  \param		*self	list instance
 *  \param		type	target structure type
 *  \param		member	link member for making linked list.
 */
#define		keylist_init_for(self, type, member)\
	do{\
		keylist_init(self);\
		(self)->ofst = offsetof(type, member);\
	}while(0)\
		
/**
 *  \brief		Actual definition of link structure for Linked-list .
 */
struct keylist_link_s {
	/**previous pointer*/
	struct keylist_link_s	*prev;
	
	/**next pointer.*/
	struct keylist_link_s	*next;
	
	/**pointer of container(e.g. keylist_t)*/
	struct keylist_s		*coll;
};

/**
 *  \brief		Actual definition of Linked-list Container.
 */
struct keylist_s {
	/**Pointer to head link.*/
	struct keylist_link_s*	head;
	
	/**Pointer to tail link.*/
	struct keylist_link_s*	tail;
	
	/**Counter for having nodes.*/
	int						size;
	
	/**DIRTY MEMBER. FOR PSEUDO POLYMORPHISM...LOL*/
	size_t					ofst;
	
	/*
	2020-10-04/KK: ロックの搭載を試みたものの、今のバージョンではやめた。
	コンセプトとしてdestroyを提供しない以上、init & destroyをAPIとして提供するﾓﾉとは相性が悪い。
	スレッドセーフティについては、外側から提供してください。
	*/
};

/**
 *  \brief		Actual definition of Linked-list Iterator.
 */
struct keylist_iterator_s {
	/**Pointer to previous node(gotten in iterator_backward)*/
	struct keylist_link_s	*prev;	
	
	/**Pointer to current node(for more robustness against deleting)*/
	struct keylist_link_s	*curr;
	
	/**Pointer to next node(gotten in iterator_forward)*/
	struct keylist_link_s	*next;
	
	/**Collection which made the iterator*/
	struct keylist_s		*coll;
};


#endif	/* !KELIST_H_ */
