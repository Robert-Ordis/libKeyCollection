#include "./keylist.h"
#include "./keylist_commons.h"
#ifndef	KEYLIST_RAW_H_
#define	KEYLIST_RAW_H_

#define		keylist_init_raw(offset, self)\
	do{\
		(self)->head = NULL;\
		(self)->tail = NULL;\
		(self)->size = 0;\
	}while(0)\

//数の取得など、「参照だけ」になるマクロは左辺値にできないようにする
/**
 *  \fn			keylist_get_count_raw
 *  \brief		Get contained num on the List.
 *  \param		*self	list instance.
 *  \remarks	Experimental implementation with macro.
 */
#define			keylist_get_count_raw(offset, self)\
	((self)->size + 0)

#define			keylist_ref_head_raw(offset, self)\
	((void*)(keycollection_get_container_ptr(offset, (self)->head)))

#define			keylist_ref_tail_raw(offset, self)\
	((void*)(keycollection_get_container_ptr(offset, (self)->tail)))

void*			keylist_pop_head_raw(size_t offset, keylist_t *self);

void*			keylist_pop_tail_raw(size_t offset, keylist_t *self);

void*			keylist_ref_nth_raw(size_t offset, keylist_t *self, int nth);

	
int				keylist_add_raw(size_t offset, keylist_t *self, void *node);

int				keylist_del_raw(size_t offset, keylist_t *self, void *node);

int				keylist_insert_before_raw(size_t offset, keylist_t *self, void *index_node, void *node);

int				keylist_insert_after_raw(size_t offset, keylist_t *self, void *index_node, void *node);

int				keylist_init_iterator_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator);

int				keylist_init_iterator_from_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator, keylist_link_t *index_node);

keylist_link_t*	keylist_iterator_forward_raw(size_t offset, keylist_iterator_t *iterator);

keylist_link_t*	keylist_iterator_backward_raw(size_t offset, keylist_iterator_t *iterator);

#define			keylist_iterator_is_head_raw(offset, iterator)\
	((iterator)->head == (iterator)->curr)
	
#define			keylist_iterator_is_tail_raw(offset, iterator)\
	((iterator)->tail == (iterator)->curr)

#define		keylist_link_get_belonged_raw(offset, node)\
	((keylist_t *)((keylist_link_t *)keycollection_get_link_ptr(node)->coll))

#define		keylist_link_get_next_raw(offset, node)\
	((void *)(keycollection_get_container_ptr(offset, keycollection_get_link_ptr(offset, node)->next)))

#define		keylist_link_get_prev_raw(offset, node)\
	(void *)(keycollection_get_container_ptr(offset, ((keylist_link_t *)keycollection_get_link_ptr(offset, node))->prev))


#endif	/* !KEYLIST_RAW_H_ */
