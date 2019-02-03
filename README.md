 *Verbosely commented out redis source code based on version 5.0.2(forked from the original repository: [https://github.com/antirez/redis](https://github.com/antirez/redis)), with actual steps and phases for a novice(in particular, me) to start with.*

主要用来记录自己阅读源码的顺序和想法。  
注释里很多地方用了“应该”，因为我是按照下面的顺序阅读源码的，很多时候是先看到声明或者定义，还没看到具体的用法，作者也没有注释，因此只能根据这些信息去推测用法，
再在随后的源码里面验证自己的猜想。

## 阅读源码的顺序(Phases of reading source code)
### Phase1: SDS(Redis实现的字符串)
#### 1. sds.h
定义了使用到的 sdshdr5-64，这是sds的数据结构；另外还有一些操作这些数据结构的函数。
#### 2. sds.c
操作sds的函数实现，比如新建sds（sdsnewlen）、连接sds（sdscatlen）、复制sds（sdsdup）、释放sds（sdsfree）等操作。
这些函数都使用了sds（char *）作为参数，该指针指向了sdshdr中的buf数组，因为结构体定义使用了`__attribute__ ((__packed__))`，
所以很容易就能得到结构体的flags变量的值和结构体大小，方便了随后的很多计算。
#### 3. adlist.h & adlist.c
这是一个简单链表的实现，作为数据结构里面学习的第一类数据结构，相对于上面的 sds 简单很多。
获取 list length/listAddNodeHead/listAddNodeTail 等的时间复杂度是O(1)，其他很多操作都是遍历，时间复杂度O(n)。
#### 4. dict.h
第一秒就想到 Python 的字典，Java 的 Map...
#### 5. siphash.c
redis用到的hash函数实现