# hw2
软件学院：刘博非 2021010612
## 编译运行
编译运行方法：在当前文件夹中的命令行（cmd或Powershell）中输入命令make或rebuild，回车，生成可执行文件，执行即可。

## 运行结果
方法1-6分别为遍历次序，ijk，ikj，jik，jki，kij，kji
```
n=64
Way1 TimeConsume:0.0093741
Way2 TimeConsume:0.0055368
Way3 TimeConsume:0.0037025
Way4 TimeConsume:0.0084548
Way5 TimeConsume:0.0084615
Way6 TimeConsume:0.0108476

n=128
Way1 TimeConsume:0.0547436
Way2 TimeConsume:0.0473814
Way3 TimeConsume:0.0406097
Way4 TimeConsume:0.073427
Way5 TimeConsume:0.19358
Way6 TimeConsume:0.196923

n=256
Way1 TimeConsume:0.319862
Way2 TimeConsume:0.447902
Way3 TimeConsume:0.257547
Way4 TimeConsume:0.621713
Way5 TimeConsume:1.79638
Way6 TimeConsume:1.86838

n=512
Way1 TimeConsume:1.96972
Way2 TimeConsume:3.91165
Way3 TimeConsume:1.97646
Way4 TimeConsume:5.63355
Way5 TimeConsume:14.6597
Way6 TimeConsume:15.1947
```
## 分析
* 循环为ijk和jik顺序的运行快，循环为kij，kji的很慢。而且数据范围越大，不同顺
序之间运行时间差距越大。
* 三种循环运算次数均为$n + n^2 + n^3$次。那么造成差异是调取数据的速度。
* 三维数组在内存空间以链状连续存储。元素[i][j][k]和[i][j][k+1]距离为1;[i][j][k]和[i][j+1][k]距离为$n$;[i][j][k]与[i+1][j][k]距离为$n^2$;在计算过程中，指针在内存中移动距离越小，计算就应越快。 
* 在ijk和jik顺序中，绝大多数的时间指针一次移动距离都是1。而在kji，kij中，指针绝大多数时间移动距离都是$n^2$。当n越大的时候，指针移动距离差距更大，运行效率差距就更大。