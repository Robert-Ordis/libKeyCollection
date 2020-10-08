//自分のコードで書き直してあげれば、今度こそ胸を張って公開できるお。


#if defined(__linux__) && defined(KEYCOLLECT_PTHREAD_SAFETY)

	#define keycollect_lock_acquire(self)\
		do{\
			pthread_mutex_lock(&((self)->lock));\
		} while(0)\
		
	#define keycollect_lock_release(self)\
		do{\
			pthread_mutex_unlock(&((self)->lock));\
		} while(0)\

#else
	#define keycollect_lock_acquire(self)\
		do{\
			\
		} while(0)\
		
	#define keycollect_lock_release(self)\
		do{\
			\
		} while(0)\
#endif


typedef struct keylist_s {
	struct keylist_link_t	*head;
	struct keylist_link_t	*tail;
	int						count;
	
#if defined(__linux__) && defined(KEYCOLLECT_PTHREAD_SAFETY)
	int						if_lock;
	pthread_mutex_t			lock;
#endif /* __linux__ && KEYCOLLECT_PTHREAD_SAFETY */
	
} keylist_t;


struct keylist_link_t {
	struct keylist_link_t	*prev;
	struct keylist_link_t	*next;
	void					*list;
}

#define KEYLIST_REF_FIRST_RAW_(offset, self)\
	(void*)(((char*) self->head) - offset)

void* keylist_ref_first_raw(size_t offset, keylist_t *self){
	return KEYLIST_REF_FIRST_RAW_(offset, self);
}

#define keylist_ref_first_generic(type, member, self)\
	keylist_ref_first_raw(offsetof(type, member), self)


//xxx_genericの実装に関しては、_rawを素直に呼び出すマクロに置き換えよう。リターンコード書けない。

//reducing codesize
int KEYLIST_APPEND_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node){
	return keylist_append_generic(nodetype_s, member, self);
}

//prefer speed
int KEYLIST_APPEND_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *index_node){
	int ret;
	keycollect_lock_acquire(self);{
		KEYLIST_APPEND_RAW_(self, offseted(index_node, nodetype_s, member);
	}keycollect_lock_release(self);
}
