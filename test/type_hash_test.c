#include <keycollection/keyhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "./sampleHashCollection.h"

static int hash_type_compare_a(void *node_a, void *node_b){
	hash_type_t *a = (hash_type_t *)node_a;
	hash_type_t *b = (hash_type_t *)node_b;
	
	//printf("%s: a[%d] vs b[%d]\n", __func__, a->a, b->a);
	
	return (a->a - b->a);
}

static int hash_type_compare_b(void *node_a, void *node_b){
	hash_type_t *a = (hash_type_t *)node_a;
	hash_type_t *b = (hash_type_t *)node_b;
	
	//printf("%s: a[%lu] vs b[%lu]\n", __func__, a->d, b->d);
	
	if(a->b > b->b){
		return -1;
	}
	else if(a->b == b->b){
		return 0;
	}
	return 1;
}

static void hash_type_make_node(void *node_ptr, void *value, size_t value_len){
	int i = *((int *)value);
	hash_type_t *node = (hash_type_t *)node_ptr;
	node->a = i;
}

static int hash_type_calc_hash(void *node_ptr){
	
	hash_type_t *node = (hash_type_t *)node_ptr;
	int ret = node->a;
	
	return ret == (NODENUM / 2) ? -1:ret;
}

/*
コンセプト：めんどくさいキャストを排除。リストには常に一定の型しか入れない
コンセプト：イテレーションの実装
*/

int type_hash_test(){
	typehash_t hash;
	typehash_iterator_t iterator;
	
	typehash_t *phash = &hash;
	typehash_iterator_t *it = &iterator;
	
	hash_type_t	nodes[NODENUM *SAME_VALUE_RATIO_HASH];
	hash_type_t *pnode, *pnodeC;
	size_t offset = offsetof(hash_type_t, lebs.link);
	int i;
	
	size_t nodes_num = NODENUM * SAME_VALUE_RATIO_HASH;
	
	
	typehash_init(phash, 1, hash_type_compare_a, hash_type_make_node, hash_type_calc_hash);
	typehash_set_eq_comp(phash, hash_type_compare_b);
	
	memset(nodes, 0, sizeof(hash_type_t) * nodes_num);
	
	db_printf("%s: test of typetree_xxx_raw. Make nodes\n", __func__);
	for(i = 0; i < nodes_num; i++){
		pnode = &nodes[i];
		pnode->a = i / SAME_VALUE_RATIO_HASH;
		pnode->d = (uint64_t)(NODENUM - (i / SAME_VALUE_RATIO_HASH));
		pnode->b = (double)i / 2.0;
		pnode->c = (char)i;
		db_printf("[%p] start.\n", pnode);
		db_printf("%s: result of hash_add is %d\n", __func__, typehash_add(phash, pnode));
		hash_type_dbg_printf(pnode, lebs.link);
	}
	
	i = 2;
	
	
	printf("%s: iterate with value: %d[%d]\n", __func__, i, typehash_setup_iterator(phash, it, &i, sizeof(i)));
	i = 0;
	pnodeC = NULL;
	while((pnode = typehash_iterator_forward(it)) != NULL){
		hash_type_dbg_printf(pnode, lebs.link);
		if(i++ == 3){
			db_printf("%s: ->DELETE!!\n", __func__);
			pnodeC = pnode;
			typehash_del(phash, pnode);
		}
	}
	
	printf("%s: iterator reset.%d\n", __func__, typehash_iterator_move(it, NULL));
	while((pnode = typehash_iterator_forward(it)) != NULL){
		hash_type_dbg_printf(pnode, lebs.link);
	}
	if(pnodeC != NULL){
		printf("%s: add deleted node back again and iterate backward\n", __func__);
		typehash_add(phash, pnodeC);
		i = 2;
		typehash_setup_iterator(phash, it, &i, sizeof(i));
		while((pnode = typehash_iterator_backward(it)) != NULL){
			hash_type_dbg_printf(pnode, lebs.link);
		}
	}
	return 0;
}
