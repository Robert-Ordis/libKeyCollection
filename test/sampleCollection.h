#include <keycollection/keylist.h>
#include <keycollection/keylist_raw.h>
#include <keycollection/keylist_witchcraft.h>

#include "./test_config.h"

#include <inttypes.h>

#ifndef	SAMPLE_COLLECTION_H_
#define	SAMPLE_COLLECTION_H_


typedef struct type_s{
	int			a;
	double		b;
	char		c;
	uint64_t	d;
	struct sampleLink{
		keylist_link_t	link;
		keylist_link_t	link2;
	}lebs;
} type_t;


#define type_dbg_printf(pnode, link_member)\
	do{\
		\
		if(pnode == NULL){\
			db_printf("%s: nullptr\n", __func__);\
			break;\
		}\
		db_printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%lu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);	\
		db_printf("%s: [%p], "#link_member"->%p, "#link_member".next->%p, "#link_member".prev->%p, "#link_member".coll->%p\n", \
			__func__, pnode, &pnode->link_member, \
			pnode->link_member.next, pnode->link_member.prev, pnode->link_member.coll\
		);\
		\
	}while(0)
	

keylist_define_prototypes(typelink, type_t, lebs.link);
keylist_define_prototypes(typelinkl, type_t, lebs.link2);

#endif	/* !SAMPLE_COLLECTION_H_ */
