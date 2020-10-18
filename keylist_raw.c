#include <stdlib.h>

#include "./include/keycollection/keylist.h"
#include "./include/keycollection/keylist_raw.h"
#include "./include/keycollection/private/keylist_inside.h"
#include "./include/keycollection/private/keycollection_lock.h"

//void		keylist_init_raw(size_t offset, keylist_t *self);

//int		keylist_get_count_raw(size_t offset, keylist_t *self);

//void*		keylist_ref_head_raw(size_t offset, keylist_t *self);

//void*		keylist_ref_tail_raw(size_t offset, keylist_t *self);

void*			keylist_pop_head_raw(size_t offset, keylist_t *self){
	keylist_link_t *link = NULL;
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		if(self->head != NULL){
			link = self->head;
			KEYLIST_IMPL_DEL_(self, link, ret);
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	
	return keycollection_get_container_ptr(offset, link);
}

void*			keylist_pop_tail_raw(size_t offset, keylist_t *self){
	keylist_link_t *link = NULL;
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		//link = keylist_ref_tail_raw(size_t offset, keylist_t *self);
		if(self->tail != NULL){
			link = self->tail;
			KEYLIST_IMPL_DEL_(self, link, ret);
		}
	}KEYCOLLECT_LOCK_RELEASE_(self);
	
	return keycollection_get_container_ptr(offset, link);
}

void*			keylist_ref_nth_raw(size_t offset, keylist_t *self, int nth){
	keylist_link_t *link = NULL;\
	int i = nth;\
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_REF_NTH_(self, link, i);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return keycollection_get_container_ptr(offset, link);
}

int				keylist_add_raw(size_t offset, keylist_t *self, void *node){
	keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offset, node);
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_ADD_TAIL_(self, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keylist_add_head_raw(size_t offset, keylist_t *self, void *node){
	keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offset, node);
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_ADD_HEAD_(self, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keylist_add_tail_raw(size_t offset, keylist_t *self, void *node){
	keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offset, node);
	int ret = 0;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_ADD_TAIL_(self, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keylist_del_raw(size_t offset, keylist_t *self, void *node){
	keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offset, node);
	int ret = -3;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_DEL_(self, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keylist_insert_before_raw(size_t offset, keylist_t *self, void *index_node, void *node){
	keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offset, node);
	keylist_link_t *index_link = (keylist_link_t *)keycollection_get_link_ptr(offset, index_node);
	int ret = -3;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_INSERT_BEFORE_(self, index_link, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keylist_insert_after_raw(size_t offset, keylist_t *self, void *index_node, void *node){
	keylist_link_t *link = (keylist_link_t *)keycollection_get_link_ptr(offset, node);
	keylist_link_t *index_link = (keylist_link_t *)keycollection_get_link_ptr(offset, index_node);
	int ret = -3;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_INSERT_AFTER_(self, index_link, link, ret);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return ret;
}

int				keylist_init_iterator_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator){
	iterator->prev = self->tail;
	iterator->next = self->head;
	iterator->curr = NULL;
	iterator->coll = self;
	iterator->head = self->head;
	iterator->tail = self->tail;
	return 0;
}

int				keylist_init_iterator_from_raw(size_t offset, keylist_t *self, keylist_iterator_t *iterator, void *index_node){
	keylist_link_t *index_link = (keylist_link_t *)keycollection_get_link_ptr(offset, index_node);
	if(index_link == NULL){
		return keylist_init_iterator_raw(offset, self, iterator);
	}
	if(index_link->coll != self){
		return -2;
	}
	iterator->curr = NULL;
	iterator->next = index_link;
	iterator->prev = index_link;
	iterator->coll = (void*)self;
	iterator->head = self->head;
	iterator->tail = self->tail;
	return 0;
}

void*			keylist_iterator_forward_raw(size_t offset, keylist_iterator_t *iterator){
	keylist_link_t	*tmp_link = iterator->next;
	keylist_link_t	*ret_link;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_ITERATE_FORWARD_(iterator, tmp_link, ret_link);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return keycollection_get_container_ptr(offset, ret_link);
}

void*			keylist_iterator_backward_raw(size_t offset, keylist_iterator_t *iterator){
	keylist_link_t	*tmp_link = iterator->prev;
	keylist_link_t	*ret_link;
	KEYCOLLECT_LOCK_ACQUIRE_(self);{
		KEYLIST_IMPL_ITERATE_BACKWARD_(iterator, tmp_link, ret_link);
	}KEYCOLLECT_LOCK_RELEASE_(self);
	return keycollection_get_container_ptr(offset, ret_link);
}

//int			keylist_iterator_is_head_raw(size_t offset, iterator);


//int			keylist_iterator_is_tail_raw(size_t offset, iterator);

//keylist_t*	keylist_link_get_belonged_raw(offset, node);

//void*			keylist_link_get_next_raw(offset, node);

//void*			keylist_link_get_prev_raw(offset, node);



