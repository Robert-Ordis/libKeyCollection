#include <stdlib.h>

#include "keycollection/keytree.h"
#include "keycollection/private/keycollection_commons.h"
#include "keycollection/keytree_raw.h"


void		keytree_init(keytree_t *self, int allow_eq, keytree_comp_node_cb comp_node);


int			keytree_get_count(keytree_t *self);


void*		keytree_ref_head(keytree_t *self);


void*		keytree_ref_tail(keytree_t *self);


void*		keytree_pop_head(keytree_t *self);


void*		keytree_pop_tail(keytree_t *self);


void*		keytree_ref_nth(keytree_t *self, int nth);


int			keytree_add(keytree_t *self, void *node);


int			keytree_del(keytree_t *self, void *node);

/*keytree_insert_before*/

/*keytree_insert_after*/


int			keytree_has_node(keytree_t *self, void *node);

/*keytree_get_belong(void *node);*/


void*		keytree_get_next(keytree_t *self, void *node);


void*		keytree_get_prev(keytree_t *self, void *node);


void*		keytree_find_eq_node(keytree_t *self, void *index_node);
/*void*		keytree_find_eq_value(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_eq_node_end(keytree_t *self, void *index_node);
/*void*		keytree_find_eq_value_end(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_lt_node(keytree_t *self, void *index_node);
/*void*		keytree_find_lt_value(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_gt_node(keytree_t *self, void *index_node);
/*void*		keytree_find_gt_node(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_le_node_raw(keytree_t *self, void *index_node);
/*void*		keytree_find_le_value(keytree_t *self, void *value, size_t value_len);*/


void*		keytree_find_ge_node(keytree_t *self, void *index_node);
/*void*		keytree_find_ge_value(keytree_t *self, void *value, size_t value_len);*/


int			keytree_init_iterator(keytree_t *self, keytree_iterator_t *iterator);


int			keytree_init_iterator_ranged(keytree_t *self, keytree_iterator_t *iterator, void *head, void *tail);


int			keytree_iterator_move(keytree_iterator_t *iterator, void *index_node);


void*		keytree_iterator_forward(keytree_iterator_t *iterator);


void*		keytree_iterator_backward(keytree_iterator_t *iterator);



