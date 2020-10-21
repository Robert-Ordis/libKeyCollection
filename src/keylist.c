#include <stdlib.h>

#include "keycollection/keylist.h"
#include "keycollection/private/keycollection_commons.h"
#include "keycollection/keylist_raw.h"

void		keylist_init(keylist_t *self){
	keylist_init_raw(0, self);
}

int			keylist_get_count(keylist_t *self){
	return keylist_get_count_raw(self->ofst, self);
}

void*		keylist_ref_head(keylist_t *self){
	return keylist_ref_head_raw(self->ofst, self);
}

void*		keylist_ref_tail(keylist_t *self){
	return keylist_ref_tail_raw(self->ofst, self);
}

void*		keylist_pop_head(keylist_t *self){
	return keylist_pop_head_raw(self->ofst, self);
}

void*		keylist_pop_tail(keylist_t *self){
	return keylist_pop_tail_raw(self->ofst, self);
}

void*		keylist_ref_nth(keylist_t *self, int nth){
	return keylist_ref_nth_raw(self->ofst, self, nth);
}

int			keylist_add(keylist_t *self, void *node){
	return keylist_add_raw(self->ofst, self, node);
}

int			keylist_add_head(keylist_t *self, void *node){
	return keylist_add_head_raw(self->ofst, self, node);
}

int			keylist_add_tail(keylist_t *self, void *node){
	return keylist_add_tail_raw(self->ofst, self, node);
}

int			keylist_del(keylist_t *self, void *node){
	return keylist_del_raw(self->ofst, self, node);
}

int			keylist_insert_before(keylist_t *self, void *index_node, void *node){
	return keylist_insert_before_raw(self->ofst, self, index_node, node);
}

int			keylist_insert_after(keylist_t *self, void *index_node, void *node){
	return keylist_insert_after_raw(self->ofst, self, index_node, node);
}

int			keylist_init_iterator(keylist_t *self, keylist_iterator_t *iterator){
	return keylist_init_iterator_raw(self->ofst, self, iterator);
}

int			keylist_iterator_move(keylist_iterator_t *iterator, void *index_node){
	return keylist_iterator_move_raw(iterator->coll->ofst, iterator, index_node);
}

void*		keylist_iterator_forward(keylist_iterator_t *iterator){
	return keylist_iterator_forward_raw(iterator->coll->ofst, iterator);
}

void*		keylist_iterator_backward(keylist_iterator_t *iterator){
	return keylist_iterator_backward_raw(iterator->coll->ofst, iterator);
}

int			keylist_has_node(keylist_t *self, void *node){
	size_t	offset = self->ofst;
	return self == keylist_link_get_belong_raw(offset, node);
}

void*		keylist_get_next(keylist_t *self, void *node){
	keylist_link_t	*link = keycollection_get_link_ptr(self->ofst, node);
	if(link->coll != self){
		return NULL;
	}
	return keycollection_get_container_ptr(self->ofst, link->next);
}

void*		keylist_get_prev(keylist_t *self, void *node){
	keylist_link_t	*link = keycollection_get_link_ptr(self->ofst, node);
	if(link->coll != self){
		return NULL;
	}
	return keycollection_get_container_ptr(self->ofst, link->prev);
}
