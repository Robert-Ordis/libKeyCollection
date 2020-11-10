//generic版は使用が思ったよりめんどくさかったのでやめようかなと。

//keylistに関しては、やりたかったことひとまず全部実装完了。

//keytree_iterator_tについて。
//is_tailとis_head, ref_current共にたぶんいらないかな？

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

//keytreeの乱数はlong jrand48(unsigned short work[3])で生成する。rand_rはなくなるそうだよ。

//random関数がスレッドセーフなのかそうじゃないのか、はっきりさせてよ…。

//mergeはひとまず没。あれはListでいうところのconcatなだけで順番を融合させるわけじゃ全然ない。
//→そもそもの定義から言ってそうなんだもん…。
//→もし順序立てて融合するのなら、かぶってる範囲を特定してsplit→片方は一個一個、もう片方でmergeって塩梅か。
//int keytree_merge(keytree_t dst, keytree_t trash);
//→trashの内容をdstに入れる。eq設定が違うものは不可。
//→eq設定が同じ0(=同値不可)であるなら、売れ残った子はtrashに入る。
//int keytree_split(keytree_t src, nodetype_t *border, keytree_t right);
//→srcツリーを、borderを境界として切断。borderより後ろがrightに入る。

//。。。まあ、split/mergeはひとまず置いておこう！

//keytree、やりたいことこれで全部かな。
//finderとsorterのアイデアはないこともないがkeyhashと衝突してしまうので断念。
//やるなら、hash_on_nodeとhash_on_valueの2つを持たせることになる。それでいいの？

//keyhashの素体は、チェーン数を決めれば一応組める。
//せめて共通化できるところは共通化、っていう方針じゃねかなあ。
//前回はtreeの関数指定させてやっていたんだけど、今回からはあれかな？
//keytree_rawファミリーができたんでそっち活用かな？

keyhash_t{
	keytree_t hash_chain[KEYHASH_DEFAULT_WIDTH];
	keytree_t wild_chain;
	keyhash_hash_node_cb	hash_node;
	int						allow_eq;
}

yourhash_remap(self, node);
yourhash_remap_all(self);
//→全チェーンからノード根こそぎ徴収し、再分配する

