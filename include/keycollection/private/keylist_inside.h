/**
 *  \file	keylist_inside.h
 *  \brief	リンクリストに関する実装コードのパーツの寄せ集め
 *  \brief	二分木にも使われるので、細かい実装はマクロで共通化。型不定につき、ﾎﾟｲﾝﾀ=ﾉ=ﾎﾟｲﾝﾀは使えない。
 */
#ifndef	PRIVATE_KEYLIST_INSIDE_H_
#define	PRIVATE_KEYLIST_INSIDE_H_

//ret: [-1]->既に所属済みのノードを加えようとした
//ret: [-2]->参照用のノードは指定のリストとは違うものに所属している

//該当リストからの消去。selfはリスト相当、linkはリンクメンバのポインタ、retは戻り値
#define	KEYLIST_IMPL_DEL_(self, link, ret)\
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

//該当リストの末尾へ追加。
#define	KEYLIST_IMPL_ADD_TAIL_(self, link, ret)\
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
	
//該当リストの先頭へ追加。
#define	KEYLIST_IMPL_ADD_HEAD_(self, link, ret)\
	do{\
		if((link)->coll != NULL){\
			ret = -1;\
			break;\
		}\
		\
		(link)->next = (self)->head;\
		(link)->prev = NULL;\
		(link)->coll = self;\
		(self)->head = link;\
		(self)->size++;\
		/*すでに先頭に誰かがいるのなら、巻き込んで再接続*/\
		if((link)->next != NULL){\
			(link)->next->prev = link;\
		}\
		else{\
			/*先頭にも誰もいないなら、末尾も自分になる*/\
			(self)->tail = link;\
		}\
		\
		ret = 0;\
	}while(0)



//指定ノードの前への挿入。「index_linkの前」として挿入する。NULLなら末尾として。
#define	KEYLIST_IMPL_INSERT_BEFORE_(self, index_link, link, ret)\
	do{\
		if((index_link) == NULL){\
			/*末尾として挿入する*/\
			KEYLIST_IMPL_ADD_TAIL_(self, link, ret);\
			break;\
		}\
		if((link)->coll != NULL){\
			ret = -1;\
			break;\
		}\
		if((index_link)->coll != self){\
			ret = -2;\
			break;\
		}\
		/*ここからはindex_linkは非NULL(コードサイズはちょっと増えるが…まあいいや)*/\
		(link)->coll = self;\
		/*index_linkの前（の前任）がいるのなら、そこもつなぎなおす。いないならlinkがhead*/\
		if((index_link)->prev != NULL){\
			(index_link)->prev->next = link;\
		}\
		else{\
			(self)->head = link;\
		}\
		/*index_linkの前につなぐので、自分(link)の前はindex_link->prev*/\
		(link)->prev = (index_link)->prev;\
		/*index_linkの前として自分を定義。自分の次はindex_link*/\
		(index_link)->prev = link;\
		(link)->next = index_link;\
		\
		(self)->size++;\
		\
		ret = 0;\
	}while(0)

//指定ノードの後への挿入。index_nodeの後に挿入する。NULLなら先頭として。
#define	KEYLIST_IMPL_INSERT_AFTER_(self, index_link, link, ret)\
	do{\
		if((index_link) == NULL){\
			/*先頭として挿入する*/\
			KEYLIST_IMPL_ADD_HEAD_(self, link, ret);\
			break;\
		}\
		if((link)->coll != NULL){\
			ret = -1;\
			break;\
		}\
		if((index_link)->coll != self){\
			ret = -2;\
			break;\
		}\
		\
		(link)->coll = self;\
		/*index_linkの後（の前任）がいるのなら、そこもつなぎなおす。いないならlinkがhead*/\
		if((index_link)->next != NULL){\
			(index_link)->next->prev = link;\
		}\
		else{\
			(self)->tail = link;\
		}\
		/*index_linkの後につなぐので、自分(link)の後はindex_link->next*/\
		(link)->next = (index_link)->next;\
		/*index_linkの前として自分を定義。自分の次はindex_link*/\
		(index_link)->next = link;\
		(link)->prev = index_link;\
		\
		(self)->size++;\
		\
		ret = 0;\
	}while(0)

//イテレーションのパーツ。
//型不定につき、(next|prev)_nodeを別途外部で定義しなければラナイ

//前方イテレーションのパーツ。retに「次のノード」を入れる。
#define	KEYLIST_IMPL_ITERATE_FORWARD_(iterator, next_link, ret)\
	do{\
		ret = NULL;\
		if(next_link != NULL && (next_link)->coll != (iterator)->coll){\
			/*nextの所属がイテレータと違う→書き換えられた可能性。手でnextを取り直す*/\
			next_link = NULL;\
			if((iterator)->curr != NULL && (iterator)->curr->coll == (iterator)->coll){\
				next_link = (iterator)->curr->next;\
			}\
		}\
		if(next_link != NULL){\
			/*イテレータを一つ進める*/\
			(iterator)->prev = (iterator)->curr;\
			(iterator)->curr = next_link;\
			(iterator)->next = (next_link)->next;\
			ret = next_link;\
		}\
	}while(0)
	
//後方イテレーションのパーツ。retに「前のノード」を入れる。
#define	KEYLIST_IMPL_ITERATE_BACKWARD_(iterator, prev_link, ret)\
	do{\
		ret = NULL;\
		if(prev_link != NULL && (prev_link)->coll != (iterator)->coll){\
			/*prevの所属がイテレータと違う→書き換えられた可能性。手でprevを取り直す*/\
			prev_link = NULL;\
			if((iterator)->curr != NULL && (iterator)->curr->coll == (iterator)->coll){\
				prev_link = (iterator)->curr->prev;\
			}\
		}\
		if(prev_link != NULL){\
			/*イテレータを一つ戻す*/\
			(iterator)->next = (iterator)->curr;\
			(iterator)->curr = prev_link;\
			(iterator)->prev = (prev_link)->prev;\
			ret = prev_link;\
		}\
	}while(0)

#endif	/* !PRIVATE_KEYLIST_INSIDE_H_ */
