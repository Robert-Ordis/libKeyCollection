/**
 *  \file	keyhash_implementations.h
 *  \brief	ハッシュに関する実装コードのパーツの寄せ集め
 */
#ifndef	KEYHASH_IMPLEMENTATIONS_H_
#define	KEYHASH_IMPLEMENTATIONS_H_

//ハッシュ値の計算
#define			KEYHASH_IMPL_CALC_HASH_(self, node, ret)\
	do{\
		ret = (self)->hash(node);\
		if(ret >= 0){\
			ret = ret % (self)->hash_width;\
		}\
	}while(0)

#endif	/* !KEYHASH_IMPLEMENTATIONS_H_ */
