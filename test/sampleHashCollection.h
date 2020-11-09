#include <keycollection/keyhash.h>

#include "./test_config.h"

#include <inttypes.h>

#ifndef	SAMPLE_HASH_COLLECTION_H_
#define	SAMPLE_HASH_COLLECTION_H_


typedef struct type_s{
	int			a;
	double		b;
	char		c;
	uint64_t	d;
	struct sampleLink{
		keytree_link_t	link;
		keytree_link_t	link2;
	}lebs;
} hash_type_t;



#define hash_type_dbg_printf(pnode, link_member)\
	do{\
		\
		if(pnode == NULL){\
			db_printf("%s: nullptr\n", __func__);\
			break;\
		}\
		db_printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%lu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);\
		db_printf("%s: [%p], "#link_member"->%p, "#link_member".next->%p, "#link_member".prev->%p, "#link_member".coll->%p\n", \
			__func__, pnode, &pnode->link_member, \
			pnode->link_member.next, pnode->link_member.prev, pnode->link_member.coll\
		);\
		db_printf("%s: [%p], "#link_member".up->%p, "#link_member".lt->%p, "#link_member".ge->%p\n", \
			__func__, pnode, pnode->link_member.up, \
			pnode->link_member.lt, pnode->link_member.ge\
		);\
		\
	}while(0)
	

keytree_define_prototypes(hashpart, hash_type_t, lebs.link);
//keylist_define_prototypes(typelinkl, type_t, lebs.link2);

keyhash_define_prototypes(typehash, hash_type_t, hashpart, SAMPLE_HASH_WIDTH);
//keyhash_define_prototypes(typehash, hash_type_t, lebs.link, 128);
//keyhash_link_t link;

#endif	/* !SAMPLE_TREE_COLLECTION_H_ */
