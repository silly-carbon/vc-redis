 *Verbosely commented out redis source code based on version 5.0.2(forked from the original repository: [https://github.com/antirez/redis](https://github.com/antirez/redis)), with actual steps and phases for a novice(in particular, me) to start with.*

主要用来记录自己阅读源码的顺序和想法。  
注释里很多地方用了“应该”，因为我是按照下面的顺序阅读源码的，很多时候是先看到声明或者定义，还没看到具体的用法，作者也没有注释，因此只能根据这些信息去推测用法，
再在随后的源码里面验证自己的猜想。

## 阅读源码的顺序(Phases of reading source code)
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
dict数据结构的组织是：
```
dictEntry保存key、value和指向下一个dictEntry的指针next，以便形成解决hash冲突的链表；
多个dictEntry组成dictht结构体的table数组，这些dictEntry是buckets；每一个哈希之后的entry肯定属于某个bucket，多个entry如果哈希到同一个bucket，那么就发生冲突，解决冲突的办法就是使用链表，根据时间局部性原理（temporal locality），新来的entry插入到链表的首部。一个bucket可能会在尾部连着多个entry，形成链表；
dict里面有两个dictht，使用数组ht[2]保存。平时使用ht[0]，rehash的时候会哈希到ht[1]然后用ht[1]替换掉ht[0]；
dict的size需要改变的时候会进行rehash，rehash是渐进式的，摊销到后续的多个操作上面，避免阻塞太久；

遍历字典的方法 dictScan 使用的是 Pieter Noordhuis 的算法，可以保证每个bucket被访问 at least once
暂时没看懂，还是那句话：一顿操作猛如虎，可惜我是二百五
以后再回过头来看
```
#### 5. siphash.c
redis用到的hash函数实现

#### 6. intset.h & intset.c
这是整数集合的实现。  
整数集合可以保存三种不同encoding的（16，32，64位整数）整数，不过不能并存；可以实现
encoding的升级（但是没有encoding降级的实现，在代码里很多处都利用这一特点，如果查找的value的encoding大于
整数集合现在的encoding，说明value肯定不在整数集合之中）。  
查找整数集合中元素的时候使用的是二分查找法，这就要求整数集合是有序的，但是其中有个函数`intsetUpgradeAndAdd`在插入的时候却不会保持顺序，
有点费解，待后续回顾（更新：这个插入函数也确实是有序的，intset.c中有解释）。    
在往intset中插入数据前先进行查找，没找到才插入，由此符合SET的特性。