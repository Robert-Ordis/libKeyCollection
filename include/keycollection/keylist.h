/**
 *  \file		keylist.h
 *  \brief		固定メンバ変数式リンクリストをマクロで定義するためのライブラリ
 *  \remarks	メンバを直接使うライブラリにつき、
 */
#ifndef	KEYLIST_H_
#define	KEYLIST_H_

#include <stdint.h>
#include <stddef.h>

/**
 *  \struct	keylist_link_t
 *  \brief		Set of members for composing a doubly linked list.
 *  \details	First, set this as a member of the struct you want to make Doubly Linked List.
 */
typedef struct keylist_link_s keylist_link_t;

/**
 *  \struct	keylist_t
 *  \brief		Doubly linked list container(Generic/Raw type)
 *
 */
typedef struct keylist_s keylist_t;

/**
 *  \struct	keylist_iterator_t
 *  \brief		Iterator for doubly linked list.(may be same in binary tree)
 *  \brief		While iterating by this, the nearby node in the collection can be edited.
 */
typedef struct keylist_iterator_s keylist_iterator_t;

/**
 *  \fn			keylist_init
 *  \brief		Initialize the list.
 *  \param		*self	list instance.
 *  \remarks	If you  use this func, target struct must contains keylist_link_t as the first member.
 */
void		keylist_init(keylist_t *self);

/**
 *  \fn			keylist_get_count
 *  \brief		Get contained num on the List.
 *  \param		*self	list instance.
 *  \return	Number of nodes in the list.
 *  \remarks	Experimental implementation with macro.
 */
int			keylist_get_count(keylist_t *self);

/**
 *  \fn			keylist_ref_head
 *  \brief		Get top node in the list.
 *  \param		*self	list instance.
 *  \return	Top node in the list.
 */
void*		keylist_ref_head(keylist_t *self);

/**
 *  \fn			keylist_ref_tail
 *  \brief		Get last node in the list.
 *  \param		*self	list instance.
 *  \return	Last node in the list.
 */
void*		keylist_ref_tail(keylist_t *self);

/**
 *  \fn			keylist_pop_head
 *  \brief		Get and delete the top node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Top node in the list.(It is already removed from *self);
 */
void*		keylist_pop_head(keylist_t *self);

/**
 *  \fn			keylist_pop_tail
 *  \brief		Get and delete the last node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Last node in the list.(It is already removed from *self);
 */
void*		keylist_pop_tail(keylist_t *self);

/**
 *  \fn			keylist_ref_nth
 *  \brief		Get the nth(Top = 0th) node from the list.
 *  \param		*self	list instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
void*		keylist_ref_nth(keylist_t *self, int nth);

/**
 *  \fn			keylist_add
 *  \brief		Add a node to the tail of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add(keylist_t *self, void *node);

/**
 *  \fn			keylist_add_head
 *  \brief		Add a node to the head of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add_head(keylist_t *self, void *node);

/**
 *  \fn			keylist_add_tail
 *  \brief		Add a node to the tail of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keylist_add_tail(keylist_t *self, void *node);

/**
 *  \fn			keylist_del
 *  \brief		Delete the node from the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
int			keylist_del(keylist_t *self, void *node);

/**
 *  \fn			keylist_insert_before
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
 *  \fn			keylist_insert_after
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
 *  \fn			keylist_has_node
 *  \brief		Get the next node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
int			keylist_has_node(keylist_t *self, void *node);

/**
 *  \fn			keylist_get_next
 *  \brief		Get the next node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keylist_get_next(keylist_t *self, void *node);

/**
 *  \fn			keylist_get_prev
 *  \brief		Get the previous node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keylist_get_prev(keylist_t *self, void *node);


/**
 *  \fn			keylist_init_iterator
 *  \brief		Initialize the keylist_iterator_t.
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top.But once done, cannot reversely iterate to the other edge.
 */
int			keylist_init_iterator(keylist_t *self, keylist_iterator_t *iterator);

/**
 *  \fn			keylist_iterator_move
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
 *  \fn			keylist_iterator_forward
 *  \brief		Iterate to the next node.
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keylist_iterator_forward(keylist_iterator_t *iterator);

/**
 *  \fn			keylist_iterator_backward
 *  \brief		Iterate to the previous node.
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keylist_iterator_backward(keylist_iterator_t *iterator);


/**
 *  \def		keylist_foreach_forward
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
 *  \def		keylist_foreach_backward
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
 *  \def		keylist_init_for
 *  \brief		Initialize the keylist for treating the specified structure and member.
 *  \param		*self	list instance
 *  \param		type	target structure type
 *  \param		member	link member for making linked list.
 */
#define		keylist_init_for(self, type, member)\
	do{\
		(self)->head = NULL;\
		(self)->tail = NULL;\
		(self)->size = 0;\
		(self)->ofst = offsetof(type, member);\
	}while(0)\
		

struct keylist_link_s {
	struct keylist_link_s	*prev;			/**previous pointer*/
	struct keylist_link_s	*next;			/**next pointer.*/
	struct keylist_s		*coll;			/**pointer of container(e.g. keylist_t)*/
};

struct keylist_s {
	struct keylist_link_s*	head;	/**Pointer to head link.*/
	struct keylist_link_s*	tail;	/**Pointer to tail link.*/
	int						size;	/**Counter for having nodes.*/
	size_t					ofst;	/**DIRTY MEMBER. FOR PSEUDO POLYMORPHISM...LOL*/
	/*
	2020-10-04/KK: ロックの搭載を試みたものの、今のバージョンではやめた。
	コンセプトとしてdestroyを提供しない以上、init & destroyをAPIとして提供するﾓﾉとは相性が悪い。
	スレッドセーフティについては、外側から提供してください。
	*/
};

struct keylist_iterator_s {
	struct keylist_link_s	*prev;
	struct keylist_link_s	*curr;
	struct keylist_link_s	*next;
	struct keylist_s		*coll;
};


#endif	/* !KELIST_H_ */
