/**
 *  \file	private/keyhash_inside.h
 *  \brief	ハッシュに関する実装コードのパーツの寄せ集め
 */
#ifndef	PRIVATE_KEYHASH_INSIDE_H_
#define	PRIVATE_KEYHASH_INSIDE_H_

//ハッシュ値の計算
#define			KEYHASH_IMPL_CALC_HASH_(self, node, ret)\
	do{\
		ret = (self)->hash(node);\
		if(ret >= 0){\
			ret = ret % (self)->hash_width;\
		}\
	}while(0)

#endif	/* !PRIVATE_KEYHASH_INSIDE_H_ */
