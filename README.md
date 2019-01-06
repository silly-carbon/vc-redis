 *Verbosely commented out redis source code based on version 5.0.2(forked from the original repository: [https://github.com/antirez/redis](https://github.com/antirez/redis)), with actual steps and phases for a novice to start with.*

主要用来记录自己阅读源码的顺序和想法。  
注释里很多地方用了“应该”，因为我是按照下面的顺序阅读源码的，很多时候是先看到声明或者定义，还没看到具体的用法，作者也没有注释，因此只能根据这些信息去推测用法，
再在随后的源码里面验证自己的猜想。

## 阅读源码的顺序(Phases of reading source code)
### Phase1: SDS(Redis实现的字符串)
#### 1. sds.h
定义了使用到的 sdshdr5-64，这是sds的数据结构，以及一些操作这些数据结构的函数。

