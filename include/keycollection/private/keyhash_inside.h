/**
 *  \file	private/keyhash_inside.h
 *  \brief	ハッシュに関する実装コードのパーツの寄せ集め
 */
#ifndef	PRIVATE_KEYHASH_INSIDE_H_
#define	PRIVATE_KEYHASH_INSIDE_H_

//ハッシュ値の計算
#define			KEYHASH_IMPL_CALC_HASH_(self, node, width, ret)\
	do{\
		ret = (self)->calc_hash(node);\
		if(ret >= 0){\
			ret = ret % width;\
		}\
	}while(0)

#endif	/* !PRIVATE_KEYHASH_INSIDE_H_ */
