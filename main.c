#include "sampleList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	NODENUM 100


//コンセプト：めんどくさいキャストを排除。リストには常に一定の型しか入れない
//コンセプト：メモリ仕様のやり方を突いた方法をとらない。これで複数リストを同一ノードで構成できる。（関数は増えるが）
//コンセプト：イテレーションの実装



static int normal_list_test(){
	int i;
	
	type_t					typeNode[NODENUM];
	type_t					*pNode;
	type_t					*pNodeIndex;
	mylist_t				def_list;
	mylist_iterator_t		it;
	
	mylist_init(&def_list, 1);
	printf("%s: %d\n", __func__, mylist_get_count(&def_list));
	//リストに追加
	printf("%s: adding list...\n", __func__);
	for(i = 0; i < NODENUM; i++){
		if(i == NODENUM / 2){
			pNodeIndex = &typeNode[i];
		}
		memset(&typeNode[i], 0, sizeof(type_t));
		typeNode[i].keyId = i;
		sprintf(typeNode[i].str, "%d", i);
		mylist_add(&def_list, &typeNode[i]);
		printf("%s: added[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
	}
	
	//先頭から連続参照
	printf("%s: forward iterating list...\n", __func__);
	mylist_init_iterator(&def_list, &it);
	while((pNode = mylist_iterate_forward(&def_list, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	//末尾から連続参照
	printf("%s: backward iterating list...\n", __func__);
	mylist_init_iterator(&def_list, &it);
	while((pNode = mylist_iterate_backward(&def_list, &it)) != NULL){
		printf("%s: iterate_backward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	//リストの途中から参照。また、奇数番号のノードを消していく。
	printf("%s: forward iterating list from %p...\n", __func__, pNodeIndex);
	mylist_init_iterator_from(&def_list, &it, pNodeIndex);
	i = 0;
	for(pNode = pNodeIndex; pNode != NULL; pNode = mylist_iterate_forward(&def_list, &it)){
		printf("%s: iterate_forward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 1){
			mylist_del(&def_list, pNode);
			printf("->[DELETE!!]");
		}
		if(pNode->keyId == 16){
			pNodeIndex = pNode;
		}
		printf("\n");
	}
	
	//リストの途中から先頭に向かって参照。奇数番号ノードの削除。
	printf("%s: backward iterating list from %p...\n", __func__, pNodeIndex);
	mylist_init_iterator_from(&def_list, &it, pNodeIndex);
	for(pNode = pNodeIndex; pNode != NULL; pNode = mylist_iterate_backward(&def_list, &it)){
		printf("%s: iterate_backward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 1){
			mylist_del(&def_list, pNode);
			printf("->[DELETE!!]");
		}
		printf("\n");
	}
	
	//最終結果。
	printf("%s: final list result\n", __func__);
	mylist_init_iterator_from(&def_list, &it, NULL);
	while((pNode = mylist_iterate_forward(&def_list, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	printf("%s: %d\n", __func__, mylist_get_count(&def_list));
	
	return 0;
}

static int default_list_test(){
	int i;
	type_t					typeNode[NODENUM];
	type_t					*pNode;
	type_t					*pNodeIndex;
	keylist_type_t			def_list;
	keylist_type_iterator_t	it;
	
	keylist_type_init(&def_list, 1);
	printf("%s: %d\n", __func__, keylist_type_get_count(&def_list));
	
	//リストに追加
	printf("%s: adding list...\n", __func__);
	for(i = 0; i < NODENUM; i++){
		if(i == NODENUM / 2){
			pNodeIndex = &typeNode[i];
		}
		memset(&typeNode[i], 0, sizeof(type_t));
		typeNode[i].keyId = i;
		sprintf(typeNode[i].str, "%d", i);
		keylist_type_add(&def_list, &typeNode[i]);
		printf("%s: added[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
	}
	
	//先頭から連続参照
	printf("%s: forward iterating list...\n", __func__);
	keylist_type_init_iterator(&def_list, &it);
	while((pNode = keylist_type_iterate_forward(&def_list, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	//末尾から連続参照
	printf("%s: backward iterating list...\n", __func__);
	keylist_type_init_iterator(&def_list, &it);
	while((pNode = keylist_type_iterate_backward(&def_list, &it)) != NULL){
		printf("%s: iterate_backward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	//リストの途中から後方参照。また、奇数番号のノードを消していく。
	printf("%s: forward iterating list from %p...\n", __func__, pNodeIndex);
	keylist_type_init_iterator_from(&def_list, &it, pNodeIndex);
	i = 0;
	type_t *next;
	for(pNode = pNodeIndex; pNode != NULL; pNode = keylist_type_iterate_backward(&def_list, &it)){
		printf("%s: iterate_backward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 0 && pNode->keyId != 14){
			keylist_type_del(&def_list, pNode);
			keylist_type_insert_after(&def_list, pNodeIndex, pNode);
			printf("->[DELETE!!]->insert after %p", pNodeIndex);
		}
		if(pNode->keyId == 14){
			next = pNode;
		}
		printf("\n");
	}
	
	printf("%s: list result\n", __func__);
	keylist_type_init_iterator_from(&def_list, &it, NULL);
	while((pNode = keylist_type_iterate_forward(&def_list, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	pNodeIndex = next;
	
	//１４番から参照。また、奇数番号のノードを消しつつ14の前に加える。
	printf("%s: forward iterating list from %p with inserting\n", __func__, pNodeIndex);
	keylist_type_init_iterator_from(&def_list, &it, pNodeIndex);
	for(pNode = pNodeIndex; pNode != NULL; pNode = keylist_type_iterate_forward(&def_list, &it)){
		printf("%s: iterate_forward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 1){
			keylist_type_del(&def_list, pNode);
			
			keylist_type_insert_before(&def_list, pNodeIndex, pNode);
			printf("->[DELETE!!]->insert before %p", pNodeIndex);
		}
		printf("\n");
	}
	printf("%s: list result\n", __func__);
	keylist_type_init_iterator_from(&def_list, &it, NULL);
	while((pNode = keylist_type_iterate_forward(&def_list, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	//１４番を、１６番の前に入れる。
	printf("%s: insert 14 as order\n", __func__);
	keylist_type_del(&def_list, pNodeIndex);
	keylist_type_init_iterator_from(&def_list, &it, NULL);
	while((pNode = keylist_type_iterate_forward(&def_list, &it)) != NULL){
		if(pNode->keyId == 16){
			keylist_type_insert_before(&def_list, pNode, pNodeIndex);
			break;
		}
	}
	
	printf("%s: final list result\n", __func__);
	pNode = NULL;
	printf("%s: forward->%p\n", __func__, pNode);
	while((pNode = keylist_type_get_next(&def_list, pNode)) != NULL){
		//printf("%s: forward->%p vs %p\n", __func__, pNode, def_list.head);
		printf("%s: fast_iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	pNode = NULL;
	printf("%s: forward->%p\n", __func__, pNode);
	while((pNode = keylist_type_get_prev(&def_list, pNode)) != NULL){
		printf("%s: fast_iterate_backward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	printf("%s: %d\n", __func__, keylist_type_get_count(&def_list));
	
	return 0;
}
const static int RAND_RANGE = 64;
static int print_node(type_t *node, char *buf, int bufLen){
	snprintf(buf, bufLen, "%03d/%s", node->keyId, node->str);
	//printf("%s: level:%d, [%d/%s]\n", __func__, level, node->keyId, node->str);
	return 0;
}
static int mytree_test(){
	int i;
	type_t					typeNode[NODENUM];
	type_t					*pNode;
	type_t					*pNodeIndex;
	mytree_t				mytree;
	mytree_iterator_t		it;
	
	time_t					seed_time = time(NULL);
	//seed_time	= 1566535357;
	//seed_time	= 1566535545;
	//seed_time = 1566561958;
	
	sample_list_init(&mytree);
	printf("%s: %d\n", __func__, mytree_get_count(&mytree));
	printf("%s: seed time is %lld\n", __func__, seed_time);
	//リストに追加
	printf("%s: adding list...\n", __func__);
	int cnt = 0;
	srand(seed_time);
	for(i = NODENUM - 1; i >= 0; i--){
		memset(&typeNode[i], 0, sizeof(type_t));
		typeNode[i].keyId = (rand() % RAND_RANGE);
		//typeNode[i].keyId = i;
		sprintf(typeNode[i].str, "%03d", i);
		int ret = mytree_add(&mytree, &typeNode[i]);
		if(ret == 0){
			if(cnt == 1 || (RAND_RANGE == 1 && cnt == 0)){
				pNodeIndex = &typeNode[i];
			}
			cnt++;
			printf("%s: added[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
		}
		else{
			printf("%s: abandoned[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
		}
	}
	
	mytree_init_iterator(&mytree, &it);
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	pNode = mytree_refer_first(&mytree);
	printf("%s: first is [%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	
	pNode = mytree_refer_last(&mytree);
	printf("%s: last  is [%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	
	pNode = mytree.root;
	printf("%s: root  is [%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	pNode = pNodeIndex;
	printf("%s: delete this([%d/%s](%p))\n", __func__, pNode->keyId, pNode->str, pNode);
	mytree_del(&mytree, pNode);
	//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	mytree_init_iterator(&mytree, &it);
	int del_ret = 0;
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 1){
			del_ret = mytree_del(&mytree, pNode);
			printf("->[DELETE!!], ret=%d", del_ret);
			if(del_ret < 0){
				printf("\n");
				mytree_dbg_traverse(&mytree, NULL, 0, print_node);
				//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
				return del_ret;
			}
		}
		printf("\n");
	}
	printf("deleted filtered node.\n");
	mytree_init_iterator(&mytree, &it);
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
	int val = RAND_RANGE / 2;
	//val++;
	printf("%s: find with %d\n", __func__, val);
	pNode = mytree_find_eq(&mytree, val, 0);
	printf("%s: eq      ->%p\n", __func__, pNode);
	pNode = mytree_find_eq_end(&mytree, val, 0);
	printf("%s: eq_end  ->%p\n", __func__, pNode);
	pNode = mytree_find_ge(&mytree, val, 0);
	printf("%s: ge found->%p[%d/%s]\n", __func__, pNode, pNode->keyId, pNode->str);
	pNode = mytree_find_lt(&mytree, val, 0);
	printf("%s: lt found->%p[%d/%s]\n", __func__, pNode, pNode->keyId, pNode->str);
	//printf("%s: test for right rotate[%p]->%d\n", __func__, pNode, mytree_rotate_right(&mytree, pNode));
	//printf("%s: test for left rotate[%p]->%d\n", __func__, pNode, mytree_rotate_left(&mytree, pNode));
	//printf("%s: test for up rotate[%p]->%d\n", __func__, pNode, mytree_rotate_up(&mytree, pNode));
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	/*
	pNode = mytree_find_lt(&mytree, val);
	printf("%s: lt found->%p\n", __func__, pNode);
	pNode = mytree_find_ge(&mytree, val);
	printf("%s: ge found->%p\n", __func__, pNode);
	*/
	return 0;
}

int lesser_list(){
	int i;
	type_t					typeNode[NODENUM];
	type_t					*pNode;
	type_t					*pNodeIndex;
	mytree_t				mytree;
	mytree_iterator_t		it;
	
	time_t					seed_time = time(NULL);
	//seed_time	= 1566535357;
	//seed_time	= 1566535545;
	//seed_time = 1566561958;
	
	sample_lesser_list_init(&mytree);
	printf("%s: %d\n", __func__, mytree_get_count(&mytree));
	printf("%s: seed time is %lld\n", __func__, seed_time);
	//リストに追加
	printf("%s: adding list...\n", __func__);
	int cnt = 0;
	srand(seed_time);
	for(i = NODENUM - 1; i >= 0; i--){
		memset(&typeNode[i], 0, sizeof(type_t));
		typeNode[i].keyId = (rand() % RAND_RANGE);
		//typeNode[i].keyId = i;
		sprintf(typeNode[i].str, "%03d", i);
		int ret = mytree_add(&mytree, &typeNode[i]);
		if(ret == 0){
			if(cnt == 1 || (RAND_RANGE == 1 && cnt == 0)){
				pNodeIndex = &typeNode[i];
			}
			cnt++;
			printf("%s: added[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
		}
		else{
			printf("%s: abandoned[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
		}
	}
	
	mytree_init_iterator(&mytree, &it);
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	pNode = mytree_refer_first(&mytree);
	printf("%s: first is [%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	
	pNode = mytree_refer_last(&mytree);
	printf("%s: last  is [%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	
	
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	pNode = pNodeIndex;
	printf("%s: delete this([%d/%s](%p))\n", __func__, pNode->keyId, pNode->str, pNode);
	mytree_del(&mytree, pNode);
	//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	mytree_init_iterator(&mytree, &it);
	int del_ret = 0;
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 1){
			del_ret = mytree_del(&mytree, pNode);
			printf("->[DELETE!!], ret=%d", del_ret);
			if(del_ret < 0){
				printf("\n");
				mytree_dbg_traverse(&mytree, NULL, 0, print_node);
				//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
				return del_ret;
			}
		}
		printf("\n");
	}
	printf("deleted filtered node.\n");
	mytree_init_iterator(&mytree, &it);
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	
	/*
	pNode = mytree_find_lt(&mytree, val);
	printf("%s: lt found->%p\n", __func__, pNode);
	pNode = mytree_find_ge(&mytree, val);
	printf("%s: ge found->%p\n", __func__, pNode);
	*/
	return 0;
}

static int hash_print_node(type_t *node, void *userdata, char *buf, int bufLen){
	snprintf(buf, bufLen, "%03d/%s", node->keyId, node->str);
	//printf("%s: level:%d, [%d/%s]\n", __func__, level, node->keyId, node->str);
	return 0;
}
static int hash_clear_node(type_t *node, void *userdata, char *buf, int bufLen){
	myhash_t *myhash = (myhash_t*)userdata;
	if(node->keyId % 2 == 0){
		myhash_del(myhash, node);
	}
	return 0;
}
int	hash_test(){
	int i;
	type_t					typeNode[NODENUM];
	type_t					*pNode;
	type_t					*pNodeIndex;
	myhash_t				myhash;
	myhash_finder_t			myhash_finder;
	
	time_t					seed_time = time(NULL);
	//seed_time	= 1566535357;
	//seed_time	= 1566535545;
	//seed_time = 1566561958;
	
	
	sample_hash_init(&myhash);
	
	printf("%s: %d\n", __func__, myhash_get_count(&myhash));
	printf("%s: seed time is %lld\n", __func__, seed_time);
	//リストに追加
	printf("%s: adding into hash...\n", __func__);
	int cnt = 0;
	srand(seed_time);
	for(i = NODENUM - 1; i >= 0; i--){
		memset(&typeNode[i], 0, sizeof(type_t));
		typeNode[i].keyId = (rand() % RAND_RANGE) - (RAND_RANGE / 2);
		//typeNode[i].keyId = i;
		sprintf(typeNode[i].str, "%03d", i);
		int ret = myhash_add(&myhash, &typeNode[i]);
		if(ret == 0){
			if(cnt == 1 || (RAND_RANGE == 1 && cnt == 0)){
				pNodeIndex = &typeNode[i];
			}
			cnt++;
			printf("%s: added[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
		}
		else{
			printf("%s: abandoned[%d/%s](%p)\n", __func__, typeNode[i].keyId, typeNode[i].str, &typeNode[i]);
		}
	}
	printf("%s: total count is %d\n", __func__, myhash_get_count(&myhash));
	myhash_dbg_dump(&myhash, NULL, hash_print_node);
	cnt = 19;
	pNode = myhash_get_node_end(&myhash, cnt, 0);
	printf("%s: find [%d]->%p\n", __func__, cnt, pNode);
	myhash_dbg_dump(&myhash, &myhash, hash_clear_node);
	printf("%s: cleared\n", __func__);
	pNode = myhash_get_node_end(&myhash, cnt, 0);
	printf("%s: find [%d]->%p\n", __func__, cnt, pNode);
	myhash_dbg_dump(&myhash, NULL, hash_print_node);
	printf("%s: size of type_t is %d\n", __func__, sizeof(type_t));
/*
	mytree_init_iterator(&mytree, &it);
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	
	pNode = mytree_refer_first(&mytree);
	printf("%s: first is [%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	
	pNode = mytree_refer_last(&mytree);
	printf("%s: last  is [%d/%s](%p)\n", __func__, pNode->keyId, pNode-
	
	
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	pNode = pNodeIndex;
	printf("%s: delete this([%d/%s](%p))\n", __func__, pNode->keyId, pNode->str, pNode);
	mytree_del(&mytree, pNode);
	//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	mytree_init_iterator(&mytree, &it);
	int del_ret = 0;
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)", __func__, pNode->keyId, pNode->str, pNode);
		if(pNode->keyId % 2 == 1){
			del_ret = mytree_del(&mytree, pNode);
			printf("->[DELETE!!], ret=%d", del_ret);
			if(del_ret < 0){
				printf("\n");
				mytree_dbg_traverse(&mytree, NULL, 0, print_node);
				//mytree_dbg_traverse(&mytree, NULL, 0, NULL);
				return del_ret;
			}
		}
		printf("\n");
	}
	printf("deleted filtered node.\n");
	mytree_init_iterator(&mytree, &it);
	while((pNode = mytree_iterate_forward(&mytree, &it)) != NULL){
		printf("%s: iterate_forward[%d/%s](%p)\n", __func__, pNode->keyId, pNode->str, pNode);
	}
	mytree_dbg_traverse(&mytree, NULL, 0, print_node);
	*/
	return 0;
}

int main(int argc, char *argv[]){
	//normal_list_test();
	//default_list_test();
	lesser_list();
	mytree_test();
	hash_test();
	/*
	while(mytree_test() >= 0){
		sleep(1);
	}*/
	return 0;
}

