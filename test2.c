#include <keycollection/keylist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "./sampleCollection.h"

#define	NODENUM 10


//コンセプト：めんどくさいキャストを排除。リストには常に一定の型しか入れない
//コンセプト：イテレーションの実装


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
	
	printf("%s: test of typelink_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		typelink_get_count(plist),
		typelink_ref_head(plist),
		typelink_ref_tail(plist)
	);
	
	printf("\n\n");
	
	printf("%s: test of typelink_iterating\n", __func__);
	
	printf("\n\n");
	printf("%s: fast forward iterating\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("\n\n");
	typelink_init_iterator(plist, it);
	printf("%s: iterator forward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = typelink_iterator_forward(it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("\n\n");
	printf("%s: fast backward iterating\n", __func__);
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("\n\n");
	typelink_init_iterator(plist, it);
	printf("%s: iterator backward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = typelink_iterator_backward(it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, typelink_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("\n\n");
	printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = NODENUM / 2;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = NODENUM + 1;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	
	i = -1;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -2;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -9;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -10;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	i = -20;
	pnode = typelink_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link);
	
	printf("\n\n");
	printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = typelink_ref_nth(plist, i);
	printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, typelink_del(plist, pnodeC));
	type_dbg_printf(pnodeC, lebs.link);
	
	i = NODENUM - 2;
	printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = typelink_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link);
	printf("%s: ret=%d\n", __func__, typelink_insert_after(plist, pnode, pnodeC));
	
	if(typelink_init_iterator_from(plist, it, pnode) == 0){
		while((pnode = typelink_iterator_forward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link);
		}
	}
	
	printf("\n\n");
	printf("%s: popping from head\n", __func__);
	pnodeC = typelink_pop_head(plist);
	type_dbg_printf(pnodeC, lebs.link);
	
	i = NODENUM - 1 - (NODENUM / 3);
	printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = typelink_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link);
	printf("%s: ret=%d\n", __func__, typelink_insert_before(plist, pnode, pnodeC));
	
	if(typelink_init_iterator_from(plist, it, pnode) == 0){
		while((pnode = typelink_iterator_backward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
		printf("%s: belongs to %p->%d\n", __func__, plist, typelink_has_node(plist, pnode));
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	typelink_init_iterator(plist, it);
	while(pnode = typelink_iterator_forward(it)){
		type_dbg_printf(pnode, lebs.link);
		if(pnode->a % 3 == 2){
			printf("%s ->move to head.\n", __func__);
			typelink_del(plist, pnode);
			typelink_add_head(plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	typelink_init_iterator(plist, it);
	while(pnode = typelink_iterator_backward(it)){
		type_dbg_printf(pnode, lebs.link);
		if(pnode->a % 2 == 0){
			printf("%s ->move to tail.\n", __func__);
			typelink_del(plist, pnode);
			typelink_add_tail(plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
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
	
	printf("\n\n");
	
	printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while(pnode = typelink_pop_tail(plist)){
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = typelink_ref_head(plist); pnode != NULL; pnode = typelink_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	for(pnode = typelink_ref_tail(plist); pnode != NULL; pnode = typelink_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link);
	}
	
	printf("\n\n");
	
	printf("%s: test for inserting before/after NULL\n", __func__);
	printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode, lebs.link);
		if(pnode->a & 0x01){
			//奇数
			printf("%s:odd[%d]\n", __func__, typelink_insert_before(plist, NULL, pnode));
		}
		else{
			//偶数
			printf("%s:even[%d]\n", __func__, typelink_insert_after(plist, NULL, pnode));
		}
		printf("%s: list count is %d\n", __func__, typelink_get_count(plist));
	}
	
	printf("%s: check the situation\n", __func__);
	
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link);
	}
	
	return 0;
}



