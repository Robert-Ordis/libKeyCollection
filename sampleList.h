#ifndef	SAMPLELIST_H
#define	SAMPLELIST_H

#include <keycollection/keylist.h>
#include <keycollection/keytree.h>
#include <keycollection/keyhash.h>

typedef	struct type_s type_t;

//ベースのタイプ宣言
keylist_define_basetype(type, struct type_s);
keytree_define_basetype(type, struct type_s);

//各種コレクション関数生成用のマクロ
keylist_define_prototypes(keylist_type,		type, type_t, test.def);
keylist_define_prototypes(mylist2,			type, type_t, link2);
keylist_define_prototypes(mylist3,			type, type_t, link3);
keylist_define_prototypes(mylist,			type, type_t, link1);
keytree_define_prototypes(mytree,			type, type_t, tlink1);
keytree_define_prototypes(hashtree,			type, type_t, for_hash);

//構造体/共用体の宣言
typedef union {
	//mylist_t				tree;
	int64_t					i;
	double					d;
	char*					s;
	int						b;
	void*					n;
} mylist_union_t;

struct type_s{
	int aiueo;
	mylist_union_t unions;
	struct {
		keylist_link_type_t	def;
		int keytest;
	} test;
	
	keylist_link_type_t	link1;
	keylist_link_type_t	link2;
	keylist_link_type_t	link3;
	keytree_link_type_t	tlink1;
	keytree_link_type_t	for_hash;
	int	keyId;
	char	str[16];
};

//ハッシュだけは全部が生成し終わってからでないとダメ。
keyhash_define_prototypes(myhash,			type_t, hashtree, 8);


void sample_list_init(mytree_t *tree);

#endif	/*SAMPLELIST_H*/
