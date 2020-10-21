#include <keycollection/keylist.h>
#include <keycollection/keylist_raw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "./sampleCollection.h"

#define	NODENUM 10


//コンセプト：めんどくさいキャストを排除。リストには常に一定の型しか入れない
//コンセプト：イテレーションの実装

int type_test();


static int poly_test(){
	
	keylist_t	list;
	keylist_t	*plist = &list;
	
	keylist_iterator_t iterator;
	keylist_iterator_t *it = &iterator;
	
	type_t	nodes[NODENUM];
	type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(type_t, lebs.link2);
	
	int i, ret;
	
	
	keylist_init_for(plist, type_t, lebs.link2);
	
	memset(nodes, 0, sizeof(type_t) * NODENUM);
	
	printf("%s: test of keylist_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		keylist_get_count(plist),
		keylist_ref_head(plist),
		keylist_ref_tail(plist)
	);
	
	printf("\n\n");
	
	printf("%s: test of keylist_iterating\n", __func__);
	
	printf("\n\n");
	printf("%s: fast forward iterating\n", __func__);
	for(pnode = keylist_ref_head(plist); pnode != NULL; pnode = keylist_get_next(plist, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	keylist_init_iterator(plist, it);
	printf("%s: iterator forward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_forward(it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, keylist_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	printf("%s: fast backward iterating\n", __func__);
	for(pnode = keylist_ref_tail(plist); pnode != NULL; pnode = keylist_get_prev(plist, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	keylist_init_iterator(plist, it);
	printf("%s: iterator backward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_backward(it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, keylist_add(plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM / 2;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM + 1;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	
	i = -1;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -2;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -9;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -10;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -20;
	pnode = keylist_ref_nth(plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	printf("\n\n");
	printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = keylist_ref_nth(plist, i);
	printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, keylist_del(plist, pnodeC));
	type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 2;
	printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = keylist_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link2);
	printf("%s: ret=%d\n", __func__, keylist_insert_after(plist, pnode, pnodeC));
	
	if(keylist_iterator_move(it, pnode) == 0){
		while((pnode = keylist_iterator_forward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	printf("\n\n");
	printf("%s: popping from head\n", __func__);
	pnodeC = keylist_pop_head(plist);
	type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 1 - (NODENUM / 3);
	printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = keylist_ref_nth(plist, i);
	type_dbg_printf(pnode, lebs.link2);
	printf("%s: ret=%d\n", __func__, keylist_insert_before(plist, pnode, pnodeC));
	
	if(keylist_iterator_move(it, pnode) == 0){
		while((pnode = keylist_iterator_backward(it)) != NULL){
			type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head(plist); pnode != NULL; pnode = keylist_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail(plist); pnode != NULL; pnode = keylist_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
		printf("%s: belongs to %p->%d\n", __func__, plist, keylist_has_node(plist, pnode));
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator(plist, it);
	while(pnode = keylist_iterator_forward(it)){
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 3 == 2){
			printf("%s ->move to head.\n", __func__);
			keylist_del(plist, pnode);
			keylist_add_head(plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head(plist); pnode != NULL; pnode = keylist_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail(plist); pnode != NULL; pnode = keylist_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator(plist, it);
	while(pnode = keylist_iterator_backward(it)){
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 2 == 0){
			printf("%s ->move to tail.\n", __func__);
			keylist_del(plist, pnode);
			keylist_add_tail(plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	/*
	for(pnode = keylist_ref_head(plist); pnode != NULL; pnode = keylist_link_get_next(pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail(plist); pnode != NULL; pnode = keylist_link_get_prev(pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	*/
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	
	printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while(pnode = keylist_pop_tail(plist)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head(plist); pnode != NULL; pnode = keylist_get_next(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail(plist); pnode != NULL; pnode = keylist_get_prev(plist, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	
	printf("%s: test for inserting before/after NULL\n", __func__);
	printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a & 0x01){
			//奇数
			printf("%s:odd[%d]\n", __func__, keylist_insert_before(plist, NULL, pnode));
		}
		else{
			//偶数
			printf("%s:even[%d]\n", __func__, keylist_insert_after(plist, NULL, pnode));
		}
		printf("%s: list count is %d\n", __func__, keylist_get_count(plist));
	}
	
	printf("%s: check the situation\n", __func__);
	
	keylist_foreach_forward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	keylist_foreach_backward(pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	return 0;
}

static int raw_test(){
	
	keylist_t	list;
	keylist_t	*plist = &list;
	
	keylist_iterator_t iterator;
	keylist_iterator_t *it = &iterator;
	
	type_t	nodes[NODENUM];
	type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(type_t, lebs.link2);
	
	int i, ret;
	
	
	keylist_init_raw(offset, plist);
	
	memset(nodes, 0, sizeof(type_t) * NODENUM);
	
	printf("%s: test of keylist_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		keylist_get_count_raw(offset, plist),
		keylist_ref_head_raw(offset, plist),
		keylist_ref_tail_raw(offset, plist)
	);
	
	printf("\n\n");
	
	printf("%s: test of keylist_iterating\n", __func__);
	
	printf("\n\n");
	printf("%s: fast forward iterating\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	keylist_init_iterator_raw(offset, plist, it);
	printf("%s: iterator forward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_forward_raw(offset, it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	printf("%s: fast backward iterating\n", __func__);
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	keylist_init_iterator_raw(offset, plist, it);
	printf("%s: iterator backward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_backward_raw(offset, it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM / 2;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = NODENUM + 1;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	
	i = -1;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -2;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -9;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -10;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	i = -20;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode, lebs.link2);
	
	printf("\n\n");
	printf("%s: test for popping.\n", __func__);
	i = NODENUM / 10;
	printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, keylist_del_raw(offset, plist, pnodeC));
	type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 2;
	printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = keylist_ref_nth_raw(offset, plist, i);
	type_dbg_printf(pnode, lebs.link2);
	printf("%s: ret=%d\n", __func__, keylist_insert_after_raw(offset, plist, pnode, pnodeC));
	
	if(keylist_iterator_move_raw(offset, it, pnode) == 0){
		while((pnode = keylist_iterator_forward_raw(offset, it)) != NULL){
			type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	printf("\n\n");
	printf("%s: popping from head\n", __func__);
	pnodeC = keylist_pop_head_raw(offset, plist);
	type_dbg_printf(pnodeC, lebs.link2);
	
	i = NODENUM - 1 - (NODENUM / 3);
	printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = keylist_ref_nth_raw(offset, plist, i);
	type_dbg_printf(pnode, lebs.link2);
	printf("%s: ret=%d\n", __func__, keylist_insert_before_raw(offset, plist, pnode, pnodeC));
	
	if(keylist_iterator_move_raw(offset, it, pnode) == 0){
		while((pnode = keylist_iterator_backward_raw(offset, it)) != NULL){
			type_dbg_printf(pnode, lebs.link2);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
		printf("%s: belongs to %p\n", __func__, keylist_link_get_belong_raw(offset, pnode));
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator_raw(offset, plist, it);
	while(pnode = keylist_iterator_forward_raw(offset, it)){
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 3 == 2){
			printf("%s ->move to head.\n", __func__);
			keylist_del_raw(offset, plist, pnode);
			keylist_add_head_raw(offset, plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator_raw(offset, plist, it);
	while(pnode = keylist_iterator_backward_raw(offset, it)){
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a % 2 == 0){
			printf("%s ->move to tail.\n", __func__);
			keylist_del_raw(offset, plist, pnode);
			keylist_add_tail_raw(offset, plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	/*
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	*/
	keylist_foreach_forward_raw(offset, pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	keylist_foreach_backward_raw(offset, pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	
	printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while(pnode = keylist_pop_tail_raw(offset, plist)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	printf("\n\n");
	
	printf("%s: test for inserting before/after NULL\n", __func__);
	printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode, lebs.link2);
		if(pnode->a & 0x01){
			//奇数
			printf("%s:odd[%d]\n", __func__, keylist_insert_before_raw(offset, plist, NULL, pnode));
		}
		else{
			//偶数
			printf("%s:even[%d]\n", __func__, keylist_insert_after_raw(offset, plist, NULL, pnode));
		}
		printf("%s: list count is %d\n", __func__, keylist_get_count_raw(offset, plist));
	}
	
	printf("%s: check the situation\n", __func__);
	
	keylist_foreach_forward_raw(offset, pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	keylist_foreach_backward_raw(offset, pnode, plist){
		type_dbg_printf(pnode, lebs.link2);
	}
	
	return 0;
}




int main(int argc, char *argv[]){
	raw_test();
	poly_test();
	type_test();
}

