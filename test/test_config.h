#ifndef	TEST_CONFIG_H_
#define	TEST_CONFIG_H_

#define	LOOP_COUNT 5000000
#define	NODENUM 10
#define	PRINT_WHILE_TEST 0

#define	SAME_VALUE_RATIO_TREE 1

#define db_printf(...)\
	do{if(PRINT_WHILE_TEST){printf(__VA_ARGS__);}}while(0)

#endif	/* !TEST_CONFIG_H_ */
