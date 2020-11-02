#include <keycollection/keytree.h>
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

int poly_tree_test(){
	
	keytree_t	tree;
	keytree_t	*ptree = &tree;
	
	keytree_iterator_t iterator;
	keytree_iterator_t *it = &iterator;
	
	tree_type_t	nodes[NODENUM * SAME_VALUE_RATIO_TREE];
	tree_type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(tree_type_t, lebs.link);
	
	size_t	nodes_num = NODENUM * SAME_VALUE_RATIO_TREE;
	
	int i, ret;
	
	
	keytree_init_for(ptree, 1, tree_type_compare_a, tree_type_t, lebs.link);
	
	memset(nodes, 0, sizeof(tree_type_t) * nodes_num);
	
	db_printf("%s: test of keytree_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < nodes_num; i++){
		pnode = &nodes[i];
		pnode->a = i / SAME_VALUE_RATIO_TREE;
		pnode->d = (uint64_t)(NODENUM - (i / SAME_VALUE_RATIO_TREE));
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add(ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		keytree_get_count(ptree),
		keytree_ref_head(ptree),
		keytree_ref_tail(ptree)
	);
	
	db_printf("\n\n");
	
	db_printf("%s: test of keytree_iterating\n", __func__);
	
	db_printf("\n\n");
	db_printf("%s: fast forward iterating\n", __func__);
	for(pnode = keytree_ref_head(ptree); pnode != NULL; pnode = keytree_get_next(ptree, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add(ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	keytree_init_iterator(ptree, it);
	db_printf("%s: iterator forward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keytree_iterator_forward(it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add(ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	db_printf("%s: fast backward iterating\n", __func__);
	for(pnode = keytree_ref_tail(ptree); pnode != NULL; pnode = keytree_get_prev(ptree, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add(ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	keytree_init_iterator(ptree, it);
	db_printf("%s: iterator backward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keytree_iterator_backward(it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, keytree_add(ptree, pnode));
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	db_printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	i = NODENUM / 2;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	i = NODENUM + 1;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	
	i = -1;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	i = -2;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	i = -9;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	i = -10;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	i = -20;
	pnode = keytree_ref_nth(ptree, i);
	db_printf("%s: index: %d\n", __func__, i);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("\n\n");
	db_printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	db_printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = keytree_ref_nth(ptree, i);
	db_printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, keytree_del(ptree, pnodeC));
	tree_type_dbg_printf(pnodeC, lebs.link);
	
	i = NODENUM - 2;
	db_printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = keytree_ref_nth(ptree, i);
	tree_type_dbg_printf(pnode, lebs.link);
	db_printf("%s: ret=%d\n", __func__, keytree_insert_after(ptree, pnode, pnodeC));
	
	if(keytree_iterator_move(it, pnode) == 0){
		while((pnode = keytree_iterator_forward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
	}
	
	db_printf("\n\n");
	db_printf("%s: popping from head\n", __func__);
	pnodeC = keytree_pop_head(ptree);
	tree_type_dbg_printf(pnodeC, lebs.link);
	
	i = NODENUM - 1 - (NODENUM / 3);
	db_printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = keytree_ref_nth(ptree, i);
	tree_type_dbg_printf(pnode, lebs.link);
	db_printf("%s: ret=%d\n", __func__, keytree_insert_before(ptree, pnode, pnodeC));
	
	if(keytree_iterator_move(it, pnode) == 0){
		while((pnode = keytree_iterator_backward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = keytree_ref_head(ptree); pnode != NULL; pnode = keytree_get_next(ptree, pnode)){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = keytree_ref_tail(ptree); pnode != NULL; pnode = keytree_get_prev(ptree, pnode)){
		tree_type_dbg_printf(pnode, lebs.link);
		db_printf("%s: tree[%p] has this node[%p] ?->%d\n", __func__, ptree, pnode, keytree_has_node(ptree, pnode));
		//db_printf("%s: belongs to %p\n", __func__, keytree_link_get_belong(pnode));
	}
	
	db_printf("\n\n");
	/*
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	keytree_init_iterator(ptree, it);
	while((pnode = keytree_iterator_forward(it)) != NULL){
		tree_type_dbg_printf(pnode, lebs.link);
		if(pnode->a % 3 == 2){
			db_printf("%s ->move to head.\n", __func__);
			keytree_del(ptree, pnode);
			//keytree_add(ptree, pnode);
			keytree_insert_after(ptree, NULL, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = keytree_ref_head(ptree); pnode != NULL; pnode = keytree_link_get_next(pnode)){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = keytree_ref_tail(ptree); pnode != NULL; pnode = keytree_link_get_prev(pnode)){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	*/
	db_printf("\n\n");
	/*
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	keytree_init_iterator(ptree, it);
	while((pnode = keytree_iterator_backward(it)) != NULL){
		tree_type_dbg_printf(pnode, lebs.link);
		if(pnode->a % 2 == 0){
			db_printf("%s ->move to tail.\n", __func__);
			keytree_del(ptree, pnode);
			//keytree_add(ptree, pnode);
			keytree_insert_before(ptree, NULL, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	keytree_foreach_forward(pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	keytree_foreach_backward(pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	*/
	db_printf("\n\n");
	
	db_printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while((pnode = keytree_pop_tail(ptree)) != NULL){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = keytree_ref_head(ptree); pnode != NULL; pnode = keytree_get_next(ptree, pnode)){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = keytree_ref_tail(ptree); pnode != NULL; pnode = keytree_get_prev(ptree, pnode)){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for inserting before/after NULL\n", __func__);
	db_printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < nodes_num; i++){
		pnode = &nodes[i];
		db_printf("[%p] start.\n", pnode);
		tree_type_dbg_printf(pnode, lebs.link);
		if(pnode->a & 0x01){
			/*奇数*/
			db_printf("%s:odd[%d]\n", __func__, keytree_insert_before(ptree, NULL, pnode));
		}
		else{
			/*偶数*/
			db_printf("%s:even[%d]\n", __func__, keytree_insert_after(ptree, NULL, pnode));
		}
		db_printf("%s: tree count is %d\n", __func__, keytree_get_count(ptree));
	}
	
	db_printf("%s: check the situation\n", __func__);
	
	keytree_foreach_forward(pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	keytree_foreach_backward(pnode, ptree){
		tree_type_dbg_printf(pnode, lebs.link);
	}
	
	ret = keytree_init_iterator_ranged(
		ptree,
		it,
		keytree_ref_nth(ptree, 7),
		keytree_ref_nth(ptree, 2)
	);
	
	//keytree_iterator_move(it, keytree_ref_nth(ptree, 3));
	
	db_printf("%s: test for ranged iteration: %d\n", __func__, ret);
	if(ret == 0){
		while((pnode = keytree_iterator_forward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
	}
	
	ret = keytree_iterator_move(it, NULL);
	db_printf("%s: test for ranged iteration:(forward-moved) %d\n", __func__, ret);
	if(ret == 0){
		while((pnode = keytree_iterator_forward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
	}
	
	ret = keytree_iterator_move(it, NULL);
	db_printf("%s: test for ranged iteration:(backward-moved) %d\n", __func__, ret);
	if(ret == 0){
		while((pnode = keytree_iterator_backward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
	}
	
	int tmp;
	tree_type_t v;
	
	tmp = 3;
	db_printf("%s: test for searching.: num: %d\n", __func__, tmp);
	
	tree_type_make_node(&v, &tmp, sizeof(int));
	
	db_printf("%s: find left edge of eq\n", __func__);
	pnode = keytree_find_eq_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find right edge of eq\n", __func__);
	pnode = keytree_find_eq_node_end(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find right edge of lt\n", __func__);
	pnode = keytree_find_lt_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find left edge of gt\n", __func__);
	pnode = keytree_find_gt_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find right edge of le\n", __func__);
	pnode = keytree_find_le_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find left edge of ge\n", __func__);
	pnode = keytree_find_ge_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	tmp = 11;
	db_printf("%s: test for searching.: num: %d\n", __func__, tmp);
	
	tree_type_make_node(&v, &tmp, sizeof(int));
	
	db_printf("%s: find left edge of eq\n", __func__);
	pnode = keytree_find_eq_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find right edge of eq\n", __func__);
	pnode = keytree_find_eq_node_end(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find right edge of lt\n", __func__);
	pnode = keytree_find_lt_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find left edge of gt\n", __func__);
	pnode = keytree_find_gt_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find right edge of le\n", __func__);
	pnode = keytree_find_le_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	db_printf("%s: find left edge of ge\n", __func__);
	pnode = keytree_find_ge_node(ptree, &v);
	tree_type_dbg_printf(pnode, lebs.link);
	
	tmp = 5;
	db_printf("%s: test for searching.: num: %d\n", __func__, tmp);
	tree_type_make_node(&v, &tmp, sizeof(int));
	
	ret = keytree_init_iterator_ranged(
		ptree,
		it,
		keytree_find_ge_node(ptree, &v),
		keytree_find_lt_node(ptree, &v)
	);
	
	db_printf("%s: test for search and ranged-iteration: %d\n", __func__, ret);
	
	
	if(ret == 0){
		while((pnode = keytree_iterator_forward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
		keytree_iterator_move(it, NULL);
		while((pnode = keytree_iterator_backward(it)) != NULL){
			tree_type_dbg_printf(pnode, lebs.link);
		}
	}
	
	return 0;
}
