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


int type_test_large(){
	
	typelinkl_t	list;
	typelinkl_t	*plist = &list;
	
	typelinkl_iterator_t iterator;
	typelinkl_iterator_t *it = &iterator;
	
	type_t	nodes[NODENUM];
	type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(type_t, lebs.link2);
	
	int i, ret;
	
	
	typelinkl_init(plist);
	
	memset(nodes, 0, sizeof(type_t) * NODENUM);
	
	db_printf("%s: test of typelinkl_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, typelinkl_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		typelinkl_get_count(plist),
		typelinkl_ref_head(plist),
		typelinkl_ref_tail(plist)
	);
	
	db_printf("\n\n");
	
	db_printf("%s: test of typelinkl_iterating\n", __func__);
	
	db_printf("\n\n");
	db_printf("%s: fast forward iterating\n", __func__);
	for(pnode = typelinkl_ref_head(plist); pnode != NULL; pnode = typelinkl_get_next(plist, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, typelinkl_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	typelinkl_init_iterator(plist, it);
	db_printf("%s: iterator forward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = typelinkl_iterator_forward(it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, typelinkl_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	db_printf("%s: fast backward iterating\n", __func__);
	for(pnode = typelinkl_ref_tail(plist); pnode != NULL; pnode = typelinkl_get_prev(plist, pnode)){
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of add_raw is %d\n", __func__, typelinkl_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	typelinkl_init_iterator(plist, it);
	db_printf("%s: iterator backward iterating\n", __func__);
	db_printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = typelinkl_iterator_backward(it)) != NULL){
		db_printf("%s: result of add_raw is %d\n", __func__, typelinkl_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	db_printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM / 2;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM + 1;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	
	i = -1;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -2;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -9;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -10;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -20;
	pnode = typelinkl_ref_nth(plist, i);
	db_printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	db_printf("\n\n");
	db_printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	db_printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = typelinkl_ref_nth(plist, i);
	db_printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, typelinkl_del(plist, pnodeC));
	type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 2;
	db_printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = typelinkl_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link2);
	db_printf("%s: ret=%d\n", __func__, typelinkl_insert_after(plist, pnode, pnodeC));
	
	if(typelinkl_iterator_move(it, pnode) == 0){
		while((pnode = typelinkl_iterator_forward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	db_printf("\n\n");
	db_printf("%s: popping from head\n", __func__);
	pnodeC = typelinkl_pop_head(plist);
	type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 1 - (NODENUM / 3);
	db_printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = typelinkl_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link2);
	db_printf("%s: ret=%d\n", __func__, typelinkl_insert_before(plist, pnode, pnodeC));
	
	if(typelinkl_iterator_move(it, pnode) == 0){
		while((pnode = typelinkl_iterator_backward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = typelinkl_ref_head(plist); pnode != NULL; pnode = typelinkl_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = typelinkl_ref_tail(plist); pnode != NULL; pnode = typelinkl_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
		db_printf("%s: belongs to %p->%d\n", __func__, plist, typelinkl_has_node(plist, pnode));
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	typelinkl_init_iterator(plist, it);
	while((pnode = typelinkl_iterator_forward(it)) != NULL){
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 3 == 2){
			db_printf("%s ->move to head.\n", __func__);
			typelinkl_del(plist, pnode);
			typelinkl_add_head(plist, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = typelinkl_ref_head(plist); pnode != NULL; pnode = typelinkl_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = typelinkl_ref_tail(plist); pnode != NULL; pnode = typelinkl_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for iterate-delete-insert test\n", __func__);
	typelinkl_init_iterator(plist, it);
	while((pnode = typelinkl_iterator_backward(it)) != NULL){
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 2 == 0){
			db_printf("%s ->move to tail.\n", __func__);
			typelinkl_del(plist, pnode);
			typelinkl_add_tail(plist, pnode);
		}
	}
	
	db_printf("%s: check the situation\n", __func__);
	/*
	for(pnode = typelinkl_ref_head(plist); pnode != NULL; pnode = typelinkl_link_get_next(pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = typelinkl_ref_tail(plist); pnode != NULL; pnode = typelinkl_link_get_prev(pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	*/
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while((pnode = typelinkl_pop_tail(plist)) != NULL){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("%s: check the situation\n", __func__);
	for(pnode = typelinkl_ref_head(plist); pnode != NULL; pnode = typelinkl_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = typelinkl_ref_tail(plist); pnode != NULL; pnode = typelinkl_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	db_printf("\n\n");
	
	db_printf("%s: test for inserting before/after NULL\n", __func__);
	db_printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		db_printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a & 0x01){
			//奇数
			db_printf("%s:odd[%d]\n", __func__, typelinkl_insert_before(plist, NULL, pnode));
		}
		else{
			//偶数
			db_printf("%s:even[%d]\n", __func__, typelinkl_insert_after(plist, NULL, pnode));
		}
		db_printf("%s: list count is %d\n", __func__, typelinkl_get_count(plist));
	}
	
	db_printf("%s: check the situation\n", __func__);
	
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	return 0;
}



