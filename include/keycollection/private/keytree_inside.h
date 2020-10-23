/**
 *  \file	keytree_inside.h
 *  \brief	二分木に関する実装コードのパーツの寄せ集め
 *  \brief	二分木のノードに関することだけ。リンクリスト部分はここには書かない。ポインタのポインタは使える。
 */
#ifndef	PRIVATE_KEYTREE_INSIDE_H_
#define	PRIVATE_KEYTREE_INSIDE_H_
/*
 *ret: [-1]->既に所属済みのノードを加えようとした
 *ret: [-2]->参照用のノードは指定のリストとは違うものに所属している
 */


/*該当リストからの消去。selfはリスト相当、linkはリンクメンバのポインタ、retは戻り値*/
#define	KEYTREE_IMPL_DEL_(self, link, ret)\
	do{\
		if((link)->coll != self){\
			ret = -2;\
			break;\
		}\
		\
		/*自身のprevのnextを自身のnextにつなぎなおす*/\
		if((link)->prev != NULL){\
			(link)->prev->next = (link)->next;\
		}\
		else{\
			(self)->head = (link)->next;\
		}\
		\
		/*自身のnextのprevを自身のprevにつなぎなおす*/\
		if((link)->next != NULL){\
			(link)->next->prev = (link)->prev;\
		}\
		else{\
			(self)->tail = (link)->prev;\
		}\
		/*自分をまっさらにする*/\
		(link)->prev = (link)->next = NULL;\
		(link)->coll = NULL;\
		\
		/*コレクションのカウンタを1減らす*/\
		self->size--;\
		\
		ret = 0;\
	}while(0)

/*該当リストの末尾へ追加。*/
#define	KEYTREE_IMPL_ADD_(self, link, ret)\
	do{\
		if((link)->coll != NULL){\
			ret = -1;\
			break;\
		}\
		\
		(link)->prev = (self)->tail;\
		(link)->next = NULL;\
		(link)->coll = self;\
		(self)->tail = link;\
		(self)->size++;\
		/*すでに末尾に誰かがいるのなら、巻き込んで再接続*/\
		if((link)->prev != NULL){\
			(link)->prev->next = link;\
		}\
		else{\
			/*末尾にも誰もいないなら、先頭も自分になる*/\
			(self)->head = link;\
		}\
		\
		ret = 0;\
	}while(0)



#endif	/* !PRIVATE_KEYTREE_INSIDE_H_ */
