/**
 *  \file	keylist_implementations.h
 *  \brief	リンクリストに関する実装コードのパーツの寄せ集め
 */
#ifndef	KEYLIST_IMPLEMENTATIONS_H_
#define	KEYLIST_IMPLEMENTATIONS_H_

//該当リストからの消去。selfはリスト相当、nodeは対象ノード、link_memberはいじるリンク用メンバ、retは戻り値
#define	KEYLIST_IMPL_DEL_(self, node, link_member, ret)\
	do{\
		if((node)->link_member.list != self){\
			ret = -1;\
			break;\
		}\
		if((node)->link_member.prev != NULL){\
			(node)->link_member.prev->link_member.next = (node)->link_member.next;\
		}\
		else{\
			(self)->head = (node)->link_member.next;\
		}\
		if((node)->link_member.next != NULL){\
			(node)->link_member.next->link_member.prev = (node)->link_member.prev;\
		}\
		else{\
			(self)->tail = (node)->link_member.prev;\
		}\
		(self)->count--;\
		(node)->link_member.prev = (node)->link_member.next = NULL;\
		(node)->link_member.list = NULL;\
		ret = 0;\
	}while(0)

//該当リストからの消去。prevがあるよ。
#define	KEYLIST_IMPL_ADD_(self, node, prev_node, link_member, ret)\
	do{\
		if((node)->link_member.list != NULL){\
			ret = -1;\
			break;\
		}\
		prev_node = (self)->tail;\
		(self)->tail = node;\
		(node)->link_member.prev = prev_node;\
		(node)->link_member.next = NULL;\
		if(prev_node != NULL){\
			prev_node->link_member.next = node;\
		}\
		else{\
			(self)->head = node;\
		}\
		(node)->link_member.list = self;\
		(self)->count++;\
		ret = 0;\
	}while(0)

//指定ノードの前への挿入。index_nodeの前に挿入する。
#define	KEYLIST_IMPL_INSERT_BEFORE_(self, index_node, node, link_member, ret)\
	do{\
		if((node)->link_member.list != NULL){\
			ret = -1;\
			break;\
		}\
		if(index_node != NULL){\
			if((index_node)->link_member.list != self){\
				ret = -1;\
				break;\
			}\
		}\
		(node)->link_member.next = index_node;\
		if(index_node == NULL){\
			(node)->link_member.prev = (self)->tail;\
			(self)->tail = node;\
		}\
		else{\
			(node)->link_member.prev = (index_node)->link_member.prev;\
			(index_node)->link_member.prev = node;\
		}\
		if((node)->link_member.prev != NULL){\
			(node)->link_member.prev->link_member.next = node;\
		}\
		else{\
			(self)->head = node;\
		}\
		(self)->count++;\
		(node)->link_member.list = self;\
		ret = 0;\
	}while(0)

//指定ノードの後への挿入。index_nodeの後に挿入する。
#define	KEYLIST_IMPL_INSERT_AFTER_(self, index_node, node, link_member, ret)\
	do{\
		if((node)->link_member.list != NULL){\
			ret = -1;\
			break;\
		}\
		if(index_node != NULL){\
			if((index_node)->link_member.list != self){\
				ret = -1;\
				break;\
			}\
		}\
		(node)->link_member.prev = index_node;\
		if(index_node == NULL){\
			(node)->link_member.next = (self)->head;\
			(self)->head = node;\
		}\
		else{\
			(node)->link_member.next = (index_node)->link_member.next;\
			(index_node)->link_member.next = node;\
		}\
		if((node)->link_member.next != NULL){\
			(node)->link_member.next->link_member.prev = node;\
		}\
		else{\
			(self)->tail = node;\
		}\
		(self)->count++;\
		(node)->link_member.list = self;\
		ret = 0;\
	}while(0)

//前方イテレーションのパーツ
#define	KEYLIST_IMPL_ITERATE_FORWARD_(self, iterator, next, link_member, ret)\
	do{\
		ret = NULL;\
		if((iterator)->list != self){\
			break;\
		}\
		if(next != NULL && (next)->link_member.list != self){\
			next = NULL;\
			if((iterator)->curr != NULL && (iterator)->curr->link_member.list == self){\
				next = (iterator)->curr->link_member.next;\
			}\
		}\
		if(next != NULL){\
			(iterator)->prev = (iterator)->curr;\
			(iterator)->curr = next;\
			(iterator)->next = (next)->link_member.next;\
			ret = next;\
		}\
	}while(0)
	
//後方イテレーションのパーツ
#define	KEYLIST_IMPL_ITERATE_BACKWARD_(self, iterator, prev, link_member, ret)\
	do{\
		ret = NULL;\
		if((iterator)->list != self){\
			break;\
		}\
		if(prev != NULL && (prev)->link_member.list != self){\
			prev = NULL;\
			if((iterator)->curr != NULL && (iterator)->curr->link_member.list == self){\
				prev = (iterator)->curr->link_member.prev;\
			}\
		}\
		if(prev != NULL){\
			(iterator)->next = (iterator)->curr;\
			(iterator)->curr = prev;\
			(iterator)->prev = (prev)->link_member.prev;\
			ret = prev;\
		}\
	}while(0)

#endif	/* !KEYLIST_IMPLEMENTATIONS_H_ */
