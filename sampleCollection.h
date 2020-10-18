#include <keycollection/keylist.h>
#include <keycollection/keylist_raw.h>
#include <keycollection/keylist_witchcraft.h>

#ifndef	SAMPLE_COLLECTION_H_
#define	SAMPLE_COLLECTION_H_

typedef struct {
	int			a;
	double		b;
	char		c;
	uint64_t	d;
	struct{
		keylist_link_t	link;
		keylist_link_t	link2;
	}lebs;
} type_t;

#define type_dbg_printf(pnode, link_member)\
	do{\
		if(pnode == NULL){\
			printf("%s: nullptr\n", __func__);\
			break;\
		}\
		printf("%s: [%p], a->%d, b->%f, c->0x%02x d->%llu\n", __func__, pnode, pnode->a, pnode->b, pnode->c, pnode->d);	\
		printf("%s: [%p], #link_member#->%p, #link_member#.next->%p, #link_member#.prev->%p, #link_member#.coll->%p\n", \
			__func__, pnode, &pnode->link_member, \
			pnode->link_member.next, pnode->link_member.prev, pnode->link_member.coll\
		);\
	}while(0)
		

keylist_define_prototypes(typelink, type_t, lebs.link);

#endif	/* !SAMPLE_COLLECTION_H_ */
