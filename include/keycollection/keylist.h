/**
 *  \file		keylist.h
 *  \brief		固定メンバ変数式リンクリストをマクロで定義するためのライブラリ
 *  \remarks	メンバを直接使うライブラリにつき、
 */

#include "./keylist_functions.h"
#include "./private/keycollection_commons.h"

#include <stdint.h>



#ifndef	KEYLIST_H_
#define	KEYLIST_H_

/**
 *  \struct	keylist_link_t
 *  \brief		Set of members for composing a doubly linked list.
 */
typedef struct keylist_link_s keylist_link_t;
struct keylist_link_s {
	struct keylist_link_s	*prev;			///previous pointer
	struct keylist_link_s	*next;			///next pointer.
	void					*coll;			///pointer of container(e.g. keylist_t)
};

/**
 *  \struct	keylist_t
 *  \brief		Doubly linked list container(Generic/Raw type)
 *
 */
typedef struct keylist_s keylist_t;
struct keylist_s {
	struct keylist_link_s*	head;	///Pointer to head link.
	struct keylist_link_s*	tail;	///Pointer to tail link.
	int						size;	///Counter for having nodes.
	size_t					ofst;	///DIRTY MEMBER. FOR PSEUDO POLYMORPHISM...LOL
	//2020-10-04/KK: ロックの搭載を試みたものの、今のバージョンではやめた。
	//コンセプトとしてdestroyを提供しない以上、init & destroyをAPIとして提供するﾓﾉとは相性が悪い。
	//スレッドセーフティについては、外側から提供してください。
};

/**
 *  \struct	keylist_iterator_t
 *  \brief		Iterator for doubly linked list.(may be same in binary tree)
 *  \brief		While iterating by this, the nearby node in the collection can be edited.
 */
typedef struct keylist_iterator_s keylist_iterator_t;
struct keylist_iterator_s {
	struct keylist_link_s	*prev;
	struct keylist_link_s	*curr;
	struct keylist_link_s	*next;
	struct keylist_link_s	*head;
	struct keylist_link_s	*tail;
	void					*coll;
};

#endif	/* !KELIST_H_ */
