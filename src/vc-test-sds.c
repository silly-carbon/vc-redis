#include "sds.h"
#include <stdio.h>
// some test units
int test_sdssplitlen();

int main(){
	return test_sdssplitlen();
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
