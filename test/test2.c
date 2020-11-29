#include <keycollection/keylist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "./sampleCollection.h"



int type_test(){
	
	typelink_t	list;
	typelink_t	*plist = &list;
	
	typelink_iterator_t iterator;
	typelink_iterator_t *it = &iterator;
	
	type_t	nodes[NODENUM];
	type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(type_t, lebs.link);
	
	int i, ret;
	
	
	typelink_init(plist);
	
	memset(nodes, 0, sizeof(type_t) * NODENUM);
	
	db_printf("%s: test of typelink_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		typelink_get_count(plist),
		typelink_ref_head(plist),
		typelink_ref_tail(plist)
	);
	
	db_printf("\n\n");
	
	db_printf("%s: test of typelink_iterating\n", __func__);
	
	db_printf("\n\n");
	db_printf("%s: fast forward iterating\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	typelink_init_iterator(plist, it);
	db_printf("%s: iterator forward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->super.curr, it->super.next, it->super.prev, it->super.coll
	);
	while((pnode = typelink_iterator_forward(it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	db_printf("%s: fast backward iterating\n", __func__);
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	typelink_init_iterator(plist, it);
	db_printf("%s: iterator backward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->super.curr, it->super.next, it->super.prev, it->super.coll
	);
	while((pnode = typelink_iterator_backward(it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	db_printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = NODENUM / 2;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = NODENUM + 1;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	
	i = -1;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -2;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -9;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -10;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -20;
	pnode = typelink_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	db_printf("\n\n");
	db_printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	db_printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = typelink_ref_nth(plist, i);
	db_printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, typelink_del(plist, pnodeC));
	type_dbg_printf(pnodeC, lebs.link);
	
	i = NODENUM - 2;
	db_printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = typelink_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link);
	db_printf("%s: ret=%d\n", __func__, typelink_insert_after(plist, pnode, pnodeC));
	
	if(typelink_iterator_move(it, pnode) == 0){
		while((pnode = typelink_iterator_forward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link);
		}
	}
	
	db_printf("\n\n");
	db_printf("%s: popping from head\n", __func__);
	pnodeC = typelink_pop_head(plist);
	type_dbg_printf(pnodeC, lebs.link);
	
	i = NODENUM - 1 - (NODENUM / 3);
	db_printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = typelink_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link);
	db_printf("%s: ret=%d\n", __func__, typelink_insert_before(plist, pnode, pnodeC));
	
	if(typelink_iterator_move(it, pnode) == 0){
		while((pnode = typelink_iterator_backward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
		db_printf("%s: belongs to %p->%d\n", __func__, plist, typelink_has_node(plist, pnode));
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	typelink_init_iterator(plist, it);
	while((pnode = typelink_iterator_forward(it)) != NULL){
		type_dbg_printf(pnode, lebs.link);
		if(pnode->a % 3 == 2){
			db_printf("%s ->move to head.\n", __func__);
			typelink_del(plist, pnode);
			typelink_add_head(plist, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	typelink_init_iterator(plist, it);
	while((pnode = typelink_iterator_backward(it)) != NULL){
		type_dbg_printf(pnode, lebs.link);
		if(pnode->a % 2 == 0){
			db_printf("%s ->move to tail.\n", __func__);
			typelink_del(plist, pnode);
			typelink_add_tail(plist, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	/*
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_link_get_next(pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_link_get_prev(pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	*/
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while((pnode = typelink_pop_tail(plist)) != NULL){
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for inserting before/after NULL\n", __func__);
	db_printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		db_printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode, lebs.link);
		if(pnode->a & 0x01){
			/*奇数*/
			db_printf("%s:odd[%d]\n", __func__, typelink_insert_before(plist, NULL, pnode));
		}
		else{
			/*偶数*/
			db_printf("%s:even[%d]\n", __func__, typelink_insert_after(plist, NULL, pnode));
		}
		db_printf("%s: list count is %d\n", __func__, typelink_get_count(plist));
	}
	
	db_printf("%s: check the situation\n", __func__);
	
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link);
	}
	
	return 0;
}



