#include "sds.h"
#include <stdio.h>
// some test units
int test_sdssplitlen();
int test_sdssplitargs();

int main(){
	return test_sdssplitargs();
}

int test_sdssplitargs(){
	char * s = "test 'splitargs' \"\\xf3\"";
	int count = 0;
	sds* res = sdssplitargs(s, &count);
	printf("count=%d\n", count);
	for (int i = 0; i < count; i++){
			printf("%s\n", res[i]);
	}
	printf("last=%d\n", (unsigned char)res[count-1][0]);
	return 0;
}


// test sdssplitlen
int test_sdssplitlen(){
	int count = 0;
	sds* res = sdssplitlen("hello world therll", 18, "ll", 2, &count);
	printf("count = %d\n", count);
	for(int i = 0; i < count; i ++){
			printf("%s\n", res[i]);
	}
	return 0;
}

int test_sdscatrepr(){
	sds x = sdsnewlen("\a\n\0foo\r",7);
    sds y = sdscatrepr(sdsempty(),x,sdslen(x));
	printf("%s\n", y);
	return 0;
}
