#include "./include/keycollection/keylist.h"
#include "./include/keycollection/keylist_reference.h"
#include "./include/keycollection/keytree.h"
#include "./include/keycollection/keytree_reference.h"

keylist_define_implements(keylist, keylist_node, struct keylist_node_s, link);

keytree_define_implements(keytree, keytree_node, struct keytree_node_s, link);
