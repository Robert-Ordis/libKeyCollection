#include <keycollection/keylist.h>
#include <keycollection/keylist_raw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define	NODENUM 100


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


int main(int argc, char *argv[]){
	
	type_t	nodes[NODENUM];
	type_t	*pnode;
	size_t	offset = offsetof(type_t, link);
	
	int i, ret;
	
	keylist_t	list;
	keylist_t	*plist = &list;
	
	keylist_iterator_t iterator;
	keylist_iterator_t *it = &iterator;
	
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
		printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%llu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);		
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		printf("%s: [%p], link->%p, link.next->%p, link.prev->%p, link.coll->%p\n", __func__, pnode, &pnode->link, pnode->link.next, pnode->link.prev, pnode->link.coll);
	}
	
	keylist_init_iterator_raw(offset, plist, it);
	printf("%s: size->%d, head->%p, tail->%p\n", 
		__func__, 
		keylist_get_count_raw(offset, plist),
		keylist_ref_head_raw(offset, plist),
		keylist_ref_tail_raw(offset, plist)
	);
	printf("%s: test of keylist_iterating\n", __func__);
	
	printf("%s: fast forward iterating\n", __func__);
	for(pnode = keylist_ref_head_raw(offset, plist); pnode != NULL; pnode = keylist_link_get_next_raw(offset, pnode)){
		printf("[%p] start.\n", pnode);
		printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%llu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);	
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
		printf("%s: [%p], link->%p, link.next->%p, link.prev->%p, link.coll->%p\n", __func__, pnode, &pnode->link, pnode->link.next, pnode->link.prev, pnode->link.coll);
	}
	
	printf("%s: iterator forward iterating\n", __func__);
	printf("%s: [%p], curr->%p, next->%p, prev->%p, coll->%p\n", __func__,
		it, it->curr, it->next, it->prev, it->coll
	);
	while((pnode = keylist_iterator_forward_raw(offset, it)) != NULL){
		printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%llu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);	
		printf("%s: result of add_raw is %d\n", __func__, keylist_add_raw(offset, plist, pnode));
	}
	
	
	
	
	return 0;
}

