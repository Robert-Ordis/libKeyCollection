#include <stdlib.h>

#include "keycollection/keytree.h"
#include "keycollection/private/keycollection_commons.h"
#include "keycollection/keytree_raw.h"


void		keytree_init(keytree_t *self, int allow_eq, keytree_comp_node_cb comp_node){
	keytree_init_raw(0, self, allow_eq, comp_node);
}

void		keytree_set_eq_comp(keytree_t *self, keytree_comp_node_cb eq_comp){
	keytree_set_eq_comp_raw(0, self, eq_comp);
}

int			keytree_get_count(keytree_t *self){
	return keytree_get_count_raw(self->ofst, self);
}


void*		keytree_ref_head(keytree_t *self){
	return keytree_ref_head_raw(self->ofst, self);
}


void*		keytree_ref_tail(keytree_t *self){
	return keytree_ref_tail_raw(self->ofst, self);
}


void*		keytree_pop_head(keytree_t *self){
	return keytree_pop_head_raw(self->ofst, self);
}


void*		keytree_pop_tail(keytree_t *self){
	return keytree_pop_tail_raw(self->ofst, self);
}


void*		keytree_ref_nth(keytree_t *self, int nth){
	return keytree_ref_nth_raw(self->ofst, self, nth);
}


int			keytree_add(keytree_t *self, void *node){
	return keytree_add_raw(self->ofst, self, node);
}


int			keytree_del(keytree_t *self, void *node){
	return keytree_del_raw(self->ofst, self, node);
}

/*keytree_insert_before*/
int			keytree_insert_before(keytree_t *self, void *index_node, void *node){
	return keytree_insert_before_raw(self->ofst, self, index_node, node);
}

/*keytree_insert_after*/
int			keytree_insert_after(keytree_t *self, void *index_node, void *node){
	return keytree_insert_after_raw(self->ofst, self, index_node, node);
}

int			keytree_has_node(keytree_t *self, void *node){
	return keytree_link_get_belong_raw(self->ofst, node) == self;
}

/*keytree_get_belong(void *node);*/


void*		keytree_get_next(keytree_t *self, void *node){
	return keytree_link_get_next_raw(self->ofst, node);
}


void*		keytree_get_prev(keytree_t *self, void *node){
	return keytree_link_get_prev_raw(self->ofst, node);
}


void*		keytree_find_eq_node(keytree_t *self, void *index_node){
	return keytree_find_eq_node_raw(self->ofst, self, index_node);
}
/*void*		keytree_find_eq_value(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_eq_node_end(keytree_t *self, void *index_node){
	return keytree_find_eq_node_end_raw(self->ofst, self, index_node);
}
/*void*		keytree_find_eq_value_end(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_lt_node(keytree_t *self, void *index_node){
	return keytree_find_lt_node_raw(self->ofst, self, index_node);
}
/*void*		keytree_find_lt_value(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_gt_node(keytree_t *self, void *index_node){
	return keytree_find_gt_node_raw(self->ofst, self, index_node);
}
/*void*		keytree_find_gt_node(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_le_node(keytree_t *self, void *index_node){
	return keytree_find_le_node_raw(self->ofst, self, index_node);
}
/*void*		keytree_find_le_value(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_ge_node(keytree_t *self, void *index_node){
	return keytree_find_ge_node_raw(self->ofst, self, index_node);
}
/*void*		keytree_find_ge_value(keytree_t *self, void *value, size_t value_len);*/


int			keytree_init_iterator(keytree_t *self, keytree_iterator_t *iterator){
	return keytree_init_iterator_raw(self->ofst, self, iterator);
}


int			keytree_init_iterator_ranged(keytree_t *self, keytree_iterator_t *iterator, void *head, void *tail){
	return keytree_init_iterator_ranged_raw(self->ofst, self, iterator, head, tail);
}


int			keytree_iterator_move(keytree_iterator_t *iterator, void *index_node){
	return keytree_iterator_move_raw(iterator->coll->ofst, iterator, index_node);
}


void*		keytree_iterator_forward(keytree_iterator_t *iterator){
	return keytree_iterator_forward_raw(iterator->coll->ofst, iterator);
}


void*		keytree_iterator_backward(keytree_iterator_t *iterator){
	return keytree_iterator_backward_raw(iterator->coll->ofst, iterator);
}



