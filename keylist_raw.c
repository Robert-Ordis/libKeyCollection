#include <stdlib.h>

#include "./include/keylist.h"
#include "./include/keylist_raw.h"

//void		keylist_init_raw(size_t offset, keylist_t *self);

//int		keylist_get_count_raw(size_t offset, keylist_t *self);

//void*		keylist_ref_head_raw(size_t offset, keylist_t *self);

//void*		keylist_ref_tail_raw(size_t offset, keylist_t *self);

void*			keylist_pop_head_raw(size_t offset, keylist_t *self){
	return NULL;
}

void*			keylist_pop_tail_raw(size_t offset, keylist_t *self){
	return NULL;
}

void*			keylist_ref_nth_raw(size_t offset, keylist_t *self, int nth){
	return NULL;
}

int				keylist_add_raw(size_t offset, keylist_t *self, void *node){
	return 0;
}

int				keylist_del_raw(size_t offset, keylist_t *self, void *node){
	return 0;
}

int				keylist_insert_before_raw(size_t offset, keylist_t *self, void *index_node, void *node){
	return 0;
}

int				keylist_insert_after_raw(size_t offset, keylist_t *self, void *index_node, void *node){
	return 0;
}

int				keylist_init_iterator_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator){
	return 0;
}

int				keylist_init_iterator_from_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator, keylist_link_t *index_node){
	return 0;
}

keylist_link_t*	keylist_iterator_forward_raw(size_t offset, keylist_iterator_t *iterator){
	return NULL;
}

keylist_link_t*	keylist_iterator_backward_raw(size_t offset, keylist_iterator_t *iterator){
	return NULL;
}

//int			keylist_iterator_is_head_raw(size_t offset, iterator);


//int			keylist_iterator_is_tail_raw(size_t offset, iterator);

//keylist_t*	keylist_link_get_belonged_raw(offset, node);

//void*			keylist_link_get_next_raw(offset, node);

//void*			keylist_link_get_prev_raw(offset, node);



