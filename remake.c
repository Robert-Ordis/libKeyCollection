//自分のコードで書き直してあげれば、今度こそ胸を張って公開できるお。


#if defined(__linux__) && defined(KEYCOLLECT_PTHREAD_SAFETY)

	#define keycollect_lock_acquire(self)\
		do{\
			if(self->if_lock){\
				pthread_mutex_lock(&((self)->lock));\
			}\
		} while(0)\
		
	#define keycollect_lock_release(self)\
		do{\
			if(self->if_lock){\
				pthread_mutex_unlock(&((self)->lock));\
			}\
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

//おおむねいえることは、
//「ライブラリの中身はkeylist_link_tだけで操作する」
//「インターフェースの段階でnodetype_tに変換する」
//っていうところかな？
//特に、マクロでポンと実装する部分に関してはkeylist_link_sだけで送させねヴぁならぬよ

typedef struct keylist_s {
	struct keylist_link_s	*head;
	struct keylist_link_s	*tail;
	int						count;
	
#if defined(__linux__) && defined(KEYCOLLECT_PTHREAD_SAFETY)
	int						if_lock;
	pthread_mutex_t			lock;
#endif /* __linux__ && KEYCOLLECT_PTHREAD_SAFETY */
	
} keylist_t;


typedef struct keylist_link_s {
	struct keylist_link_s	*prev;
	struct keylist_link_s	*next;
	void					*list;
} keylist_link_t;

#define	keycollect_get_container_(offset, plink) ((void*)((char*)plink - (char*)offset)

#define KEYLIST_REF_FIRST_RAW_(offset, self)\
	(void*)(((char*) self->head) - offset)

void* keylist_ref_first_raw(size_t offset, keylist_t *self){
	return KEYLIST_REF_FIRST_RAW_(offset, self);
}

#define keylist_ref_first_generic(type, member, self)\
	(type *)keylist_ref_first_raw(offsetof(type, member), self)

//or

#define keylist_ref_first_generic(type, member) keylist_ref_first_raw(offsetof(type, member), self)
→これはできない。

//xxx_genericは、構造体の実態が明らかな場合に使用可能。rawは原則使用禁止。

//xxx_genericの実装に関しては、_rawを素直に呼び出すマクロで書こうか。中をマクロにしてもリターンコード書けないし、関数1個なら…
//→んで、↓のやつにつながるわけですを。

int keylist_add_raw(size_t offset, keylist_t *self, void *node){
	int ret;
	keycollect_lock_acquire(self);{
		KEYLIST_IMPL_ADD_TAIL_(
			self,
			keycollection_get_link_ptr_(offset, node),
			ret
		);
	}keycollect_lock_release(self);
	return ret;
}

#define keylist_ref_first_generic(type, member, self)\
	(type*)keylist_ref_first_raw_(offsetof(type, member), self)

#define keylist_add_generic(type, member, self, node)\
	keylist_add_raw_(offsetof(type, member), self, (void*)node)



//reducing codesize
int KEYLIST_APPEND_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){
	return keylist_add_generic(nodetype_s, member, self, node);
}

//prefer speed
int KEYLIST_ADD_(yourlist)(KEYLIST_T_(yourlist) *self, nodetype_s *node){
	int ret;
	keycollect_lock_acquire(self);{
		KEYLIST_IMPL_ADD_TAIL_(
			self,
			keycollection_get_link_ptr_(offsetof(nodetype_s, member), node),
			ret
		);
	}keycollect_lock_release(self);
	return ret;
}

