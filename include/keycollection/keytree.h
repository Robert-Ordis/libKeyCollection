/**
 *  \file		keytree.h
 *  \brief		固定メンバ変数式リンクリストをマクロで定義するためのライブラリ
 *  \remarks	メンバを直接使うライブラリにつき、
 */

#include "./private/keycollection_commons.h"

#include <stdint.h>
#include <stddef.h>

#ifndef	KEYTREE_H_
#define	KEYTREE_H_

/**
 *  \typedef	keytree_comp_node_cb
 *  \brief		Callback for nodes comparison.
 *  \param		*node_a	A node.
 *  \param		*node_b B node.
 *  \return	(int) ret >= 1 if A > B / ret = 0 if A==B, / <= 1 if A < B.
 *  \remarks	This function indicates A - B.
 */
typedef int	(*keytree_comp_node_cb)(void *node_a, void *node_b);

/**
 *  \typedef	keytree_make_node_cb
 *  \brief		Callback for making nodes for searching.
 *  \param		*node		Node for searching. (Will not be NULL).
 *  \param		*value		Value pointer.
 *  \param		value_len	Byte length of *value.
 */
typedef void	(*keytree_make_node_cb)(void *node, void *value, size_t value_len);

/**
 *  \struct	keytree_link_t
 *  \brief		Set of members for composing a doubly linked list.
 */
typedef struct keytree_link_s keytree_link_t;
struct keytree_link_s {
	//KEYLISTのマクロを流用するので、メンバ名は共通
	//For reusing KEYLIST macros, some member names are same as keylist_link_t.
	struct keytree_link_s	*prev;			///previous pointer
	struct keytree_link_s	*next;			///next pointer.
	struct keytree_s		*coll;			///pointer of container(e.g. keytree_t)

	//以下はツリー用。/ Belows are for keytree.
	struct keytree_link_s	*ge;			///pointer for value evaled as "Greater Equal" this.
	struct keytree_link_s	*lt;			///pointer for value evaled as "Lesser than" this.
	struct keytree_link_s	*up;			///pointer for the parent of this.

	//平衡2分木機能用。/ For self-balancing.
	long					h_pri;			///Priority on "Treap"
};

/**
 *  \struct	keytree_t
 *  \brief		Binary tree container(Generic/Raw type)
 *
 */
typedef struct keytree_s keytree_t;
struct keytree_s {
	//KEYLISTのマクロを流用するので、メンバ名は共通
	//For reusing KEYLIST macros, some member names are same as keylist_t.
	struct keytree_link_s*	head;	///Pointer to head link.
	struct keytree_link_s*	tail;	///Pointer to tail link.
	int						size;	///Counter for having nodes.
	size_t					ofst;	///DIRTY MEMBER. FOR PSEUDO POLYMORPHISM...LOL
	//2020-10-04/KK: ロックの搭載を試みたものの、今のバージョンではやめた。
	//コンセプトとしてdestroyを提供しない以上、init & destroyをAPIとして提供するﾓﾉとは相性が悪い。
	//スレッドセーフティについては、外側から提供してください。
	struct keytree_link_s*	root;		///Root node on the tree.
	int						allow_eq;	///1 if allowing to insert the "Equals" node to "ge" pointer.
	unsigned short			rng[3];		///work for reentrant RNG(jrand48)
	keytree_comp_node_cb	comp_node;	///Node comparator
	keytree_make_node_cb	make_node;	///Node value setter..
};

/**
 *  \struct	keytree_iterator_t
 *  \brief		Iterator for Binary search tree.(Same in my Doubly linked list.)
 *  \brief		While iterating by this, the nearby node in the collection can be edited.
 */
typedef struct keytree_iterator_s keytree_iterator_t;
struct keytree_iterator_s {
	struct keytree_link_s	*prev;
	struct keytree_link_s	*curr;
	struct keytree_link_s	*next;
	struct keytree_link_s	*head;
	struct keytree_link_s	*tail;
	struct keytree_s		*coll;
};

/**
 *  \fn			keytree_init
 *  \brief		Initialize the list.
 *  \param		*self	list instance.
 *  \remarks	If you  use this func, target struct must contains keytree_link_t as the first member.
 */
void		keytree_init(keytree_t *self);

//数の取得など、変数を直接示すようなマクロは左辺にできないようにする
/**
 *  \fn			keytree_get_count
 *  \brief		Get contained num on the List.
 *  \param		*self	list instance.
 *  \return	Number of nodes in the list.
 *  \remarks	Experimental implementation with macro.
 */
int			keytree_get_count(keytree_t *self);

/**
 *  \fn			keytree_ref_head
 *  \brief		Get top node in the list.
 *  \param		*self	list instance.
 *  \return	Top node in the list.
 */
void*		keytree_ref_head(keytree_t *self);

/**
 *  \fn			keytree_ref_tail
 *  \brief		Get last node in the list.
 *  \param		*self	list instance.
 *  \return	Last node in the list.
 */
void*		keytree_ref_tail(keytree_t *self);

/**
 *  \fn			keytree_pop_head
 *  \brief		Get and delete the top node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Top node in the list.(It is already removed from *self);
 */
void*		keytree_pop_head(keytree_t *self);

/**
 *  \fn			keytree_pop_tail
 *  \brief		Get and delete the last node from the list.
 *  \param		offset	offset length to link member of the node.
 *  \param		*self	list instance.
 *  \return	Last node in the list.(It is already removed from *self);
 */
void*		keytree_pop_tail(keytree_t *self);

/**
 *  \fn			keytree_ref_nth
 *  \brief		Get the nth(Top = 0th) node from the list.
 *  \param		*self	list instance.
 *  \param		nth		number which you want to get. minus indicates the count from the last.(last is -1)
 *  \return	The node in the number shown as nth. If out of bounds, this will return NULL.
 *  \remarks	Minus number is an experimental implementation.
 */
void*		keytree_ref_nth(keytree_t *self, int nth);

/**
 *  \fn			keytree_add
 *  \brief		Add a node to the tail of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keytree_add(keytree_t *self, void *node);

/**
 *  \fn			keytree_add_head
 *  \brief		Add a node to the head of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keytree_add_head(keytree_t *self, void *node);

/**
 *  \fn			keytree_add_tail
 *  \brief		Add a node to the tail of the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to add to *self.
 *  \return	0: success, -1: error[tried to add the node already belongin in some list]
 */
int			keytree_add_tail(keytree_t *self, void *node);

/**
 *  \fn			keytree_del
 *  \brief		Delete the node from the list.
 *  \param		*self	list instance.
 *  \param		*node	The node you want to remove from *self.
 *  \return	0: success.
 *  \return	-2: error[*node doesn't belongs in *self]
 */
int			keytree_del(keytree_t *self, void *node);


/**
 *  \fn			keytree_init_iterator
 *  \brief		Initialize the keytree_iterator_t.
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \return	0: success
 *  \remarks	This can start from the both of tail and top.But once done, cannot reversely iterate to the other side.
 */
int			keytree_init_iterator(keytree_t *self, keytree_iterator_t *iterator);

/**
 *  \fn			keytree_init_iterator_from
 *  \brief		Initialize the keytree_iterator_t, which is ready to iterate from *index_node.
 *  \param		*self	list instance.
 *  \param		*iterator	iterator instance.
 *  \param		*index_node	The node you want to set as the start point.
 *  \return	0: success
 *  \return	-2: error[*index_node doesn't belong to *self]
 *  \remarks	After this, next "keytree_iterator_forward/backward" returns *index_node as you specified.
 */
int			keytree_init_iterator_from(keytree_t *self, keytree_iterator_t *iterator, void *index_node);

/**
 *  \fn			keytree_iterator_forward
 *  \brief		Iterate to the next node.
 *  \param		*iterator	iterator instance.
 *  \return	Next node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keytree_iterator_forward(keytree_iterator_t *iterator);

/**
 *  \fn			keytree_iterator_backward
 *  \brief		Iterate to the previous node.
 *  \param		*iterator	iterator instance.
 *  \return	Previous node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keytree_iterator_backward(keytree_iterator_t *iterator);

/**
 *  \fn		keytree_iterator_ref_current
 *  \brief		Refer the current node on the iterator.
 *  \param		*iterator	iterator instance.
 *  \return	Current node. If in the tail, NULL will be returned.
 *  \remarks	While iterating by this, You can safely delete the node from the list.
 */
void*		keytree_iterator_ref_current(keytree_iterator_t *iterator);

/**
 *  \fn		keytree_iterator_is_head
 *  \brief		Check if the current node is the head.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the head.
 *  \remarks	MAY NOT BE NEEDED.
 */
int			keytree_iterator_is_head(keytree_iterator_t *iterator);

/**
 *  \fn		keytree_iterator_is_tail
 *  \brief		Check if the current node is the tail.
 *  \param		*iterator	iterator instance.
 *  \return	1 if the current is in the tail.
 *  \remarks	MAY NOT BE NEEDED.
 */
int			keytree_iterator_is_tail(keytree_iterator_t *iterator);

/**
 *  \fn		keytree_has_node
 *  \brief		Check if the list has node specified in arg.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The list instance which the node belongs to.
 */
keytree_t*	keytree_link_get_belong(void *node);

/**
 *  \fn			keytree_get_next
 *  \brief		Get the next node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The next node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keytree_get_next(keytree_t *self, void *node);

/**
 *  \fn			keytree_get_prev
 *  \brief		Get the previous node of the node directly.
 *  \param		*self	list instance
 *  \param		*node	node instance.
 *  \return	The previous node. Or NULL if the node doesn't have.
 *  \return	If node doesn't belong to self, this returns NULL.
 *  \remarks	This is for Fast Iterating. But NEVER EDIT THE LIST WHILE ITERATING BY THIS.
 */
void*		keytree_get_prev(keytree_t *self, void *node);

/**
 *  \def		keytree_foreach_forward
 *  \brief		Syntax sugar for fast forward iterating
 *	\param		offset	offset length to link member of the node
 *	\param		*node	working pointer of picking node
 *	\param		*self	list instance
 */
#define		keytree_foreach_forward(node, self)\
	for(\
		node = keytree_ref_head(self);\
		node != NULL;\
		node = keytree_get_next(self, node)\
	)

/**
 *  \def		keytree_foreach_backward
 *  \brief		Syntax sugar for fast backward iterating
 *	\param		offset	offset length to link member of the node
 *	\param		*node	working pointer of picking node
 *	\param		*self	list instance
 */
#define		keytree_foreach_backward(node, self)\
	for(\
		node = keytree_ref_tail(self);\
		node != NULL;\
		node = keytree_get_prev(self, node)\
	)

/**
 *  \def		keytree_init_for
 *  \brief		Initialize the keytree for treating the specified structure and member.
 *  \param		*self	list instance
 *  \param		type	target structure type
 *  \param		member	link member for making linked list.
 */
#define		keytree_init_for(self, type, member)\
	do{\
		(self)->head = NULL;\
		(self)->tail = NULL;\
		(self)->size = 0;\
		(self)->ofst = offsetof(type, member);\
	}while(0)\
		


#endif	/* !KELIST_H_ */
