/**
 *  \file	keylist.h
 *  \brief	固定メンバ変数式リンクリストをマクロで定義するためのライブラリ
 */

#include "./keycollect_config.h"
#include "./keylist_functions.h"

#include <stdint.h>
//Linux上でならば、リソースリークを気にせずスレッドセーフ化できる。
#if defined(__linux__) && defined(KEYCOLLECT_PTHREAD_SAFETY_)
	#include <pthread.h>
#endif /* __linux__ && KEYCOLLECT_PTHREAD_SAFETY_ */


#ifndef	KEYLIST_H_
#define	KEYLIST_H_

/**
 *	\struct	keylist_link_t
 *	\brief		Set of members for composing a doubly linked list.
 */
typedef struct keylist_link_s keylist_link_t;
struct keylist_link_s {
	struct keylist_link_s	prev;			///previous pointer
	struct keylist_link_s	next;			///next pointer.
	void					*coll;	///pointer of container(e.g. keylist_t)
}

/**
 *	\struct	keylist_t
 *	\brief		Doubly linked list container(Generic/Raw type)
 *
 */
typedef struct keylist_s keylist_t;
struct keylist_s {
	struct keylist_link_s	*head;	///Pointer to head link.
	struct keylist_link_s	*tail;	///Pointer to tail link.
	int						size;	///Counter for having nodes.
	
	int						if_lock;	///Flag if this instance is made as thread safe.
#if defined(__linux__) && defined(KEYCOLLECT_PTHREAD_SAFETY)
	pthread_mutex_t			lock;		///lock(ONLY ENABLED IN LINUX THREADS)
#else
	void*					lock;		///dummy.
#endif /* __linux__ && KEYCOLLECT_PTHREAD_SAFETY */
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
