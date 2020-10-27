#include <keycollection/keytree.h>
#include <keycollection/keytree_raw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "./sampleTreeCollection.h"

static int tree_type_compare_a(void *node_a, void *node_b){
	tree_type_t *a = (tree_type_t *)node_a;
	tree_type_t *b = (tree_type_t *)node_b;
	
	//printf("%s: a[%d] vs b[%d]\n", __func__, a->a, b->a);
	
	return (a->a - b->a);
}

static int tree_type_compare_d(void *node_a, void *node_b){
	tree_type_t *a = (tree_type_t *)node_a;
	tree_type_t *b = (tree_type_t *)node_b;
	
	//printf("%s: a[%lu] vs b[%lu]\n", __func__, a->d, b->d);
	
	if(a->d > b->d){
		return 1;
	}
	else if(a->d == b->d){
		return 0;
	}
	return -1;
}

static void tree_type_make_node(void *node_ptr, void *value, size_t value_len){
	int i = *((int *)value);
	tree_type_t *node = (tree_type_t *)node_ptr;
	node->a = i;
}

/*
コンセプト：めんどくさいキャストを排除。リストには常に一定の型しか入れない
コンセプト：イテレーションの実装
*/

int raw_tree_test(){
	
	keytree_t	tree;
	keytree_t	*ptree = &tree;
	
	keytree_iterator_t iterator;
	keytree_iterator_t *it = &iterator;
	
	tree_type_t	nodes[NODENUM];
	tree_type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(tree_type_t, lebs.link2);
	
	int i, ret;
	
	
	keytree_init_raw(offset, ptree, 1, tree_type_compare_a);
	
	memset(nodes, 0, sizeof(tree_type_t) * NODENUM);
	
	db_printf("%s: test of keytree_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add_raw(offset, ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		keytree_get_count_raw(offset, ptree),
		keytree_ref_head_raw(offset, ptree),
		keytree_ref_tail_raw(offset, ptree)
	);
	
	db_printf("\n\n");
	
	db_printf("%s: test of keytree_iterating\n", __func__);
	
	db_printf("\n\n");
	db_printf("%s: fast forward iterating\n", __func__);
	for(pnode = keytree_ref_head_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_next_raw(offset, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add_raw(offset, ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	keytree_init_iterator_raw(offset, ptree, it);
	db_printf("%s: iterator forward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keytree_iterator_forward_raw(offset, it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add_raw(offset, ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	db_printf("%s: fast backward iterating\n", __func__);
	for(pnode = keytree_ref_tail_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_prev_raw(offset, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add_raw(offset, ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	keytree_init_iterator_raw(offset, ptree, it);
	db_printf("%s: iterator backward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keytree_iterator_backward_raw(offset, it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add_raw(offset, ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	db_printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM / 2;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM + 1;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	
	i = -1;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	i = -2;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	i = -9;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	i = -10;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	i = -20;
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("\n\n");
	db_printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	db_printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = keytree_ref_nth_raw(offset, ptree, i);
	db_printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, keytree_del_raw(offset, ptree, pnodeC));
	tree_type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 2;
	db_printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	db_printf("%s: ret=%d\n", __func__, keytree_insert_after_raw(offset, ptree, pnode, pnodeC));
	
	if(keytree_iterator_move_raw(offset, it, pnode) == 0){
		while((pnode = keytree_iterator_forward_raw(offset, it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	db_printf("\n\n");
	db_printf("%s: popping from head\n", __func__);
	pnodeC = keytree_pop_head_raw(offset, ptree);
	tree_type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 1 - (NODENUM / 3);
	db_printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = keytree_ref_nth_raw(offset, ptree, i);
	tree_type_dbg_printf(pnode, lebs.link2);
	db_printf("%s: ret=%d\n", __func__, keytree_insert_before_raw(offset, ptree, pnode, pnodeC));
	
	if(keytree_iterator_move_raw(offset, it, pnode) == 0){
		while((pnode = keytree_iterator_backward_raw(offset, it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = keytree_ref_head_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_next_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keytree_ref_tail_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_prev_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
		db_printf("%s: belongs to %p\n", __func__, keytree_link_get_belong_raw(offset, pnode));
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	keytree_init_iterator_raw(offset, ptree, it);
	while((pnode = keytree_iterator_forward_raw(offset, it)) != NULL){
		tree_type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 3 == 2){
			db_printf("%s ->move to head.\n", __func__);
			keytree_del_raw(offset, ptree, pnode);
			//keytree_add_raw(offset, ptree, pnode);
			keytree_insert_after_raw(offset, ptree, NULL, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = keytree_ref_head_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_next_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keytree_ref_tail_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_prev_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	keytree_init_iterator_raw(offset, ptree, it);
	while((pnode = keytree_iterator_backward_raw(offset, it)) != NULL){
		tree_type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 2 == 0){
			db_printf("%s ->move to tail.\n", __func__);
			keytree_del_raw(offset, ptree, pnode);
			//keytree_add_raw(offset, ptree, pnode);
			keytree_insert_before_raw(offset, ptree, NULL, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	/*
	for(pnode = keytree_ref_head_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_next_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keytree_ref_tail_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_prev_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	*/
	keytree_foreach_forward_raw(offset, pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	keytree_foreach_backward_raw(offset, pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while((pnode = keytree_pop_tail_raw(offset, ptree)) != NULL){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = keytree_ref_head_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_next_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keytree_ref_tail_raw(offset, ptree); pnode != NULL; pnode = keytree_link_get_prev_raw(offset, pnode)){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for inserting before/after NULL\n", __func__);
	db_printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		db_printf("[%p] start.\n", pnode);
		tree_type_dbg_printf(pnode, lebs.link2);
		if(pnode->a & 0x01){
			/*奇数*/
			db_printf("%s:odd[%d]\n", __func__, keytree_insert_before_raw(offset, ptree, NULL, pnode));
		}
		else{
			/*偶数*/
			db_printf("%s:even[%d]\n", __func__, keytree_insert_after_raw(offset, ptree, NULL, pnode));
		}
		db_printf("%s: tree count is %d\n", __func__, keytree_get_count_raw(offset, ptree));
	}
	
	db_printf("%s: check the situation\n", __func__);
	
	keytree_foreach_forward_raw(offset, pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	keytree_foreach_backward_raw(offset, pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link2);
	}
	
	ret = keytree_init_iterator_ranged_raw(
		offset,
		ptree,
		it,
		keytree_ref_nth_raw(offset, ptree, 7),
		keytree_ref_nth_raw(offset, ptree, 2)
	);
	
	//keytree_iterator_move_raw(offset, it, keytree_ref_nth_raw(offset, ptree, 3));
	
	db_printf("%s: test for ranged iteration: %d\n", __func__, ret);
	if(ret == 0){
		while((pnode = keytree_iterator_forward_raw(offset, it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	ret = keytree_iterator_move_raw(offset, it, NULL);
	db_printf("%s: test for ranged iteration:(forward-moved) %d\n", __func__, ret);
	if(ret == 0){
		while((pnode = keytree_iterator_forward_raw(offset, it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	ret = keytree_iterator_move_raw(offset, it, NULL);
	db_printf("%s: test for ranged iteration:(backward-moved) %d\n", __func__, ret);
	if(ret == 0){
		while((pnode = keytree_iterator_backward_raw(offset, it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	int tmp;
	tree_type_t v;
	
	tmp = 3;
	db_printf("%s: test for searching.: num: %d\n", __func__, tmp);
	
	tree_type_make_node(&v, &tmp, sizeof(int));
	
	db_printf("%s: find eq\n", __func__);
	pnode = keytree_find_eq_node_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("%s: find eq(right edge)\n", __func__);
	pnode = keytree_find_eq_node_end_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("%s: find right edge of lt\n", __func__);
	pnode = keytree_find_lt_node_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("%s: find left edge of ge\n", __func__);
	pnode = keytree_find_ge_node_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	tmp = 11;
	db_printf("%s: test for searching.: num: %d\n", __func__, tmp);
	
	tree_type_make_node(&v, &tmp, sizeof(int));
	
	db_printf("%s: find eq\n", __func__);
	pnode = keytree_find_eq_node_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("%s: find eq(right edge)\n", __func__);
	pnode = keytree_find_eq_node_end_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("%s: find right edge of lt\n", __func__);
	pnode = keytree_find_lt_node_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	db_printf("%s: find left edge of ge\n", __func__);
	pnode = keytree_find_ge_node_raw(offset, ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link2);
	
	return 0;
}
