//generic版は使用が思ったよりめんどくさかったのでやめようかなと。

//keylistに関しては、polymorphism版とgenerator版を書けばもう問題なく動くはずよ。
//でもまあ、ここでしっかり立ち止まって、コード削減版と贅沢版の2つを作り分けられることを実証してあげなきゃ。

#if defined(KEYLIST_GENERATE_FUNCS_AS_WRAPPER)

#define	keylist_define_implements\
	/*put codes as just wrapper.*/\
	
#else

#define	keylist_define_implements\
	/*put codes directly*/\

#endif /* KEYLIST_GENERATE_FUNCS_AS_WRAPPER */
	

//keytree、だね。問題は。
//keytree_xxx_rawでは、find_xx_valueが組めない。(VLAとかallocaにおんぶ抱っこは怖いお)


//rotate_xx系統は容量削減目当てなら外に追いやっちまう。

//keytreeに関しては、ジェネリック実装はあやしい
//→主に、検索関連で。
//→malloc禁止なら自動変数の中で比較用の仮想ノードを作らなければいけない。
//→おまけにallocaは危険だとか、VLSはオプションだとかでさすがプレーンなC言語は頭が固い。
//ってことで、じゃあどうするのよ。

keytree_add_raw(offset, ptree, pnode)

//答え：外で仮想ノードを作って注入する
pnode = &dat;
pnode->value = something;
pnodeLT = keytree_find_lt_node_raw(offset, ptree, pnode);

yourtree_find_lt_value(ptree, value_ptr, value_len);
//→自動生成専用関数。
//→youtree_initのところでは、virtを必須化。
//→削減版では自動変数を作るところまで生成、残りは共通関数を使用。
//→return keytree_find_lt_node_raw(offset, ptree, &vnode);(削減版)
//→KEYTREE_FIND_LT_NODE_(ptree, &vnode, ret_node);(贅沢高速版)
//オペークポインタで触らせることを念頭に置くのなら、関数生成してAPI提供してあげてね。

//keytreeの乱数は普通にrandomで生成する。rand_rはなくなるそうだよ。

//keyhashに関しては、旧来の生成方式じゃないと破綻どころかそもそも組めない…ｗ
//→本当か？…せめて共通化できるところは共通化、っていう方針じゃねかなあ。
//

yourhash_remap(self, node);
yourhash_remap_all(self);
//→全チェーンからノード根こそぎ徴収し、再分配する