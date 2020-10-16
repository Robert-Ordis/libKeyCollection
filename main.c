#include <keycollection/keylist.h>
#include <keycollection/keylist_raw.h>
#include <keycollection/keylist_generic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define	NODENUM 10


//コンセプト：めんどくさいキャストを排除。リストには常に一定の型しか入れない
//コンセプト：メモリ仕様のやり方を突いた方法をとらない。これで複数リストを同一ノードで構成できる。（関数は増えるが）
//コンセプト：イテレーションの実装

typedef struct {
	int			a;
	double		b;
	char		c;
	uint64_t	d;
	keylist_link_t	link;
} type_t;

#define type_dbg_printf(pnode)\
	do{\
		if(pnode == NULL){\
			printf("%s: nullptr\n", __func__);\
			break;\
		}\
		printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%llu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);	\
		printf("%s: [%p], link->%p, link.next->%p, link.prev->%p, link.coll->%p\n", __func__, pnode, &pnode->link, pnode->link.next, pnode->link.prev, pnode->link.coll);\
	}while(0)

static int raw_test(){
	
	keylist_t	list;
	keylist_t	*plist = &list;
	
	keylist_iterator_t iterator;
	keylist_iterator_t *it = &iterator;
	
	type_t	nodes[NODENUM];
	type_t	*pnode, *pnodeC;
	size_t	offset = offsetof(type_t, link);
	
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
		type_dbg_printf(pnode);
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
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	keylist_init_iterator_raw(offset, plist, it);
	printf("%s: iterator forward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_forward_raw(offset, it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	printf("%s: fast backward iterating\n", __func__);
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	keylist_init_iterator_raw(offset, plist, it);
	printf("%s: iterator backward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_backward_raw(offset, it)) != NULL){
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	i = NODENUM / 2;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	i = NODENUM + 1;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	
	i = -1;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	i = -2;
	pnode = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	printf("\n\n");
	printf("%s: test fo popping.\n", __func__);
	i = NODENUM / 10;
	printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = keylist_ref_nth_raw(offset, plist, i);
	printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, keylist_del_raw(offset, plist, pnodeC));
	type_dbg_printf(pnodeC);
	
	i = NODENUM - 2;
	printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = keylist_ref_nth_raw(offset, plist, i);
	type_dbg_printf(pnode);
	printf("%s: ret=%d\n", __func__, keylist_insert_after_raw(offset, plist, pnode, pnodeC));
	
	if(keylist_init_iterator_from_raw(offset, plist, it, pnode) == 0){
		do{
			pnode = keylist_iterator_ref_current_raw(offset, it);
			type_dbg_printf(pnode);
		}while(keylist_iterator_forward_raw(offset, it) != NULL);
	}
	
	printf("\n\n");
	printf("%s: popping from head\n", __func__);
	pnodeC = keylist_pop_head_raw(offset, plist);
	type_dbg_printf(pnodeC);
	
	i = NODENUM - 1 - (NODENUM / 3);
	printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = keylist_ref_nth_raw(offset, plist, i);
	type_dbg_printf(pnode);
	printf("%s: ret=%d\n", __func__, keylist_insert_before_raw(offset, plist, pnode, pnodeC));
	
	if(keylist_init_iterator_from_raw(offset, plist, it, pnode) == 0){
		do{
			pnode = keylist_iterator_ref_current_raw(offset, it);
			type_dbg_printf(pnode);
		}while(keylist_iterator_backward_raw(offset, it) != NULL);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode);
		printf("%s: belongs to %p\n", __func__, keylist_link_get_belong_raw(offset, pnode));
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator_raw(offset, plist, it);
	while(pnode = keylist_iterator_forward_raw(offset, it)){
		type_dbg_printf(pnode);
		if(pnode->a % 3 == 2){
			printf("%s ->move to head.\n", __func__);
			keylist_del_raw(offset, plist, pnode);
			keylist_add_head_raw(offset, plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator_raw(offset, plist, it);
	while(pnode = keylist_iterator_backward_raw(offset, it)){
		type_dbg_printf(pnode);
		if(pnode->a % 2 == 0){
			printf("%s ->move to tail.\n", __func__);
			keylist_del_raw(offset, plist, pnode);
			keylist_add_tail_raw(offset, plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	/*
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	*/
	keylist_foreach_forward_raw(offset, pnode, plist){
		type_dbg_printf(pnode);
	}
	keylist_foreach_backward_raw(offset, pnode, plist){
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	
	printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while(pnode = keylist_pop_tail_raw(offset, plist)){
		type_dbg_printf(pnode);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_prev_raw(offset, pnode)){
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	
	printf("%s: test for inserting before/after NULL\n", __func__);
	printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode);
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
		type_dbg_printf(pnode);
	}
	keylist_foreach_backward_raw(offset, pnode, plist){
		type_dbg_printf(pnode);
	}
	
	return 0;
}

static int generic_test(){
	
	keylist_t	list;
	keylist_t	*plist = &list;
	
	keylist_iterator_t iterator;
	keylist_iterator_t *it = &iterator;
	
	type_t	nodes[NODENUM];
	type_t	*pnode, *pnodeC;
	
	int i, ret;
	
	
	keylist_init_generic(type_t, link, plist);
	
	memset(nodes, 0, sizeof(type_t) * NODENUM);
	
	printf("%s: test of keylist_xxx_generic. Make nodes\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		pnode->a = i;
		pnode->d = (uint64_t)(NODENUM - i);
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_generic is %d\n", __func__, keylist_add_generic(type_t, link, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		keylist_get_count_generic(type_t, link, plist),
		keylist_ref_head_generic(type_t, link, plist),
		keylist_ref_tail_generic(type_t, link, plist)
	);
	
	printf("\n\n");
	
	printf("%s: test of keylist_iterating\n", __func__);
	
	printf("\n\n");
	printf("%s: fast forward iterating\n", __func__);
	for(pnode = keylist_ref_head_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_next_generic(type_t, link, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_generic is %d\n", __func__, keylist_add_generic(type_t, link, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	keylist_init_iterator_generic(type_t, link, plist, it);
	printf("%s: iterator forward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_forward_generic(type_t, link, it)) != NULL){
		printf("%s: result of add_generic is %d\n", __func__, keylist_add_generic(type_t, link, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	printf("%s: fast backward iterating\n", __func__);
	for(pnode = keylist_ref_tail_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_prev_generic(type_t, link, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: result of add_generic is %d\n", __func__, keylist_add_generic(type_t, link, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	keylist_init_iterator_generic(type_t, link, plist, it);
	printf("%s: iterator backward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_backward_generic(type_t, link, it)) != NULL){
		printf("%s: result of add_generic is %d\n", __func__, keylist_add_generic(type_t, link, plist, pnode));
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	printf("%s: test for picking up\n", __func__);
	
	i = 0;
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	i = NODENUM / 2;
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	i = NODENUM + 1;
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	
	i = -1;
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	i = -2;
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	printf("%s: index: %d\n", __func__, i);
	type_dbg_printf(pnode);
	
	printf("\n\n");
	printf("%s: test fo popping.\n", __func__);
	i = NODENUM / 10;
	printf("%s: pop %dth node (shown as below)\n", __func__, i);
	pnodeC = keylist_ref_nth_generic(type_t, link, plist, i);
	printf("%s: deleting %p[a->%d] = %d\n", __func__, pnodeC, pnodeC->a, keylist_del_generic(type_t, link, plist, pnodeC));
	type_dbg_printf(pnodeC);
	
	i = NODENUM - 2;
	printf("%s: insert after %dth(shown as below)\n", __func__, i);
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	type_dbg_printf(pnode);
	printf("%s: ret=%d\n", __func__, keylist_insert_after_generic(type_t, link, plist, pnode, pnodeC));
	
	if(keylist_init_iterator_from_generic(type_t, link, plist, it, pnode) == 0){
		do{
			pnode = keylist_iterator_ref_current_generic(type_t, link, it);
			type_dbg_printf(pnode);
		}while(keylist_iterator_forward_generic(type_t, link, it) != NULL);
	}
	
	printf("\n\n");
	printf("%s: popping from head\n", __func__);
	pnodeC = keylist_pop_head_generic(type_t, link, plist);
	type_dbg_printf(pnodeC);
	
	i = NODENUM - 1 - (NODENUM / 3);
	printf("%s: insert before %d th(below)\n", __func__, i);
	pnode = keylist_ref_nth_generic(type_t, link, plist, i);
	type_dbg_printf(pnode);
	printf("%s: ret=%d\n", __func__, keylist_insert_before_generic(type_t, link, plist, pnode, pnodeC));
	
	if(keylist_init_iterator_from_generic(type_t, link, plist, it, pnode) == 0){
		do{
			pnode = keylist_iterator_ref_current_generic(type_t, link, it);
			type_dbg_printf(pnode);
		}while(keylist_iterator_backward_generic(type_t, link, it) != NULL);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_next_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_prev_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
		printf("%s: belongs to %p\n", __func__, keylist_link_get_belong_generic(type_t, link, pnode));
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator_generic(type_t, link, plist, it);
	while(pnode = keylist_iterator_forward_generic(type_t, link, it)){
		type_dbg_printf(pnode);
		if(pnode->a % 3 == 2){
			printf("%s ->move to head.\n", __func__);
			keylist_del_generic(type_t, link, plist, pnode);
			keylist_add_head_generic(type_t, link, plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_next_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_prev_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	
	printf("%s: test for iterate-delete-insert test\n", __func__);
	keylist_init_iterator_generic(type_t, link, plist, it);
	while(pnode = keylist_iterator_backward_generic(type_t, link, it)){
		type_dbg_printf(pnode);
		if(pnode->a % 2 == 0){
			printf("%s ->move to tail.\n", __func__);
			keylist_del_generic(type_t, link, plist, pnode);
			keylist_add_tail_generic(type_t, link, plist, pnode);
		}
	}
	
	printf("%s: check the situation\n", __func__);
	/*
	for(pnode = keylist_ref_head_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_next_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_prev_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	*/
	keylist_foreach_forward_generic(type_t, link, pnode, plist){
		type_dbg_printf(pnode);
	}
	keylist_foreach_backward_generic(type_t, link, pnode, plist){
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	
	printf("%s: test for clearing iteration (pop tail)\n", __func__);
	while(pnode = keylist_pop_tail_generic(type_t, link, plist)){
		type_dbg_printf(pnode);
	}
	
	printf("%s: check the situation\n", __func__);
	for(pnode = keylist_ref_head_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_next_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	for(pnode = keylist_ref_tail_generic(type_t, link, plist); pnode != NULL; pnode = keylist_link_get_prev_generic(type_t, link, pnode)){
		type_dbg_printf(pnode);
	}
	
	printf("\n\n");
	
	printf("%s: test for inserting before/after NULL\n", __func__);
	printf("%s: odd->before NULL(as tail), even->after(as head)\n", __func__);
	for(i = 0; i < NODENUM; i++){
		pnode = &nodes[i];
		printf("[%p] start.\n", pnode);
		type_dbg_printf(pnode);
		if(pnode->a & 0x01){
			//奇数
			printf("%s:odd[%d]\n", __func__, keylist_insert_before_generic(type_t, link, plist, NULL, pnode));
		}
		else{
			//偶数
			printf("%s:even[%d]\n", __func__, keylist_insert_after_generic(type_t, link, plist, NULL, pnode));
		}
		printf("%s: list count is %d\n", __func__, keylist_get_count_generic(type_t, link, plist));
	}
	
	printf("%s: check the situation\n", __func__);
	
	keylist_foreach_forward_generic(type_t, link, pnode, plist){
		type_dbg_printf(pnode);
	}
	keylist_foreach_backward_generic(type_t, link, pnode, plist){
		type_dbg_printf(pnode);
	}
	
	return 0;
}

int main(int argc, char *argv[]){
	raw_test();
	generic_test();
}

