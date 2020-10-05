#include <keycollection/keylist.h>
#include <keycollection/keytree.h>
#include "sampleList.h"

keylist_define_implements(keylist_type,		type, struct type_s, test.def);
keylist_define_implements(mylist,			type, struct type_s, link1);
keylist_define_implements(mylist2,			type, struct type_s, link2);
keylist_define_implements(mylist3,			type, struct type_s, link3);

keytree_define_implements(mytree,			type, struct type_s, tlink1);
keytree_define_implements(hashtree,			type, type_t, for_hash);

keyhash_define_implements(myhash,			type_t, hashtree, 8);

static int sample_type_compare(type_t *nodeA, type_t *nodeB){
	printf("%s: A(%p)->%d, B(%p)->%d\n", __func__, nodeA, nodeA->keyId, nodeB, nodeB->keyId);
	return nodeA->keyId - nodeB->keyId;
}

static void sample_type_virtual(type_t *nodeV, void *value, size_t value_len){
	nodeV->keyId = (int)value;
	printf("%s: set %d into %p\n", __func__, value, &nodeV);
}

static int sample_type_hash(type_t *node){
	int ret = node->keyId;
	
	printf("%s: %d[%p]->hash is %d\n", __func__, node->keyId, node, ret);
	return (ret >= 0) ? ret:-1;
}

void sample_list_init(mytree_t *tree){
	mytree_init(tree, 1, 1, sample_type_compare, sample_type_virtual);
	//mytree_init(tree, 1, 1, NULL, NULL);
}

void sample_lesser_list_init(mytree_t *tree){
	mytree_init(tree, 1, 1, NULL, NULL);
}

void sample_hash_init(myhash_t *hash){
	myhash_init(hash, 1, 1, sample_type_compare, sample_type_virtual, sample_type_hash, 16);
}
