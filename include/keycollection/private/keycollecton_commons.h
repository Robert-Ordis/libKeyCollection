#ifndef	PRIVATE_KEYCOLLECTION_COMMONS_H_
#define	PRIVATE_KEYCOLLECTION_COMMONS_H_

//オフセットを指定すると、リンク構造体のポインタを内包する構造体を持ってこれる。
#define	keycollection_get_container_ptr(offset, plink)\
	((void*)((plink != NULL) ? ((char*)plink - (char*)offset) : NULL))

//オフセットを指定すると、リンク構造体のポインタを持ってきてくれる
#define	keycollection_get_link_ptr(offset, pstruct)\
	((void*)((plink != NULL) ? ((char*)pstruct + (char*)offset) : NULL))

#endif	/* !PRIVATE_KEYCOLLECTION_COMMONS_H_ */
