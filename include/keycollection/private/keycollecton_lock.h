#include "../keycollection_config.h"

#ifndef	PRIVATE_KEYCOLLECTION_LOCK_H_
#define	PRIVATE_KEYCOLLECTION_LOCK_H_

#include <stdlib.h>

//オフセットを指定すると、リンク構造体のポインタを内包する構造体を持ってこれる。
#define	KEYCOLLECT_LOCK_ACQUIRE_(self)\
	do{\
	}while(0)\

//オフセットを指定すると、リンク構造体のポインタを持ってきてくれる
#define	KEYCOLLECT_LOCK_RELEASE_(self)\
	do{\
	}while(0)\


#endif	/* !PRIVATE_KEYCOLLECTION_LOCK_H_ */
