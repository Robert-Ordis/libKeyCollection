#include "./sampleHashCollection.h"

keytree_define_implements(hashpart, hash_type_t, lebs.link);
keyhash_define_implements(typehash, hash_type_t, hashpart, SAMPLE_HASH_WIDTH);
