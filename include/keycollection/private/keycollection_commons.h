#ifndef	PRIVATE_KEYCOLLECTION_COMMONS_H_
#define	PRIVATE_KEYCOLLECTION_COMMONS_H_

#include <stdlib.h>

/*オフセットを指定すると、リンク構造体のポインタを内包する構造体を持ってこれる。*/
#define	keycollection_get_container_ptr(offset, plink)\
	((void*)((plink != NULL) ? ((char*)plink - offset) : NULL))

/*オフセットを指定すると、リンク構造体のポインタを持ってきてくれる*/
#define	keycollection_get_link_ptr(offset, pstruct)\
	((void*)((pstruct != NULL) ? ((char*)pstruct + offset) : NULL))


#endif	/* !PRIVATE_KEYCOLLECTION_COMMONS_H_ */
