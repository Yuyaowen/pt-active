# Motion 与 Pelco-d 云台桥接软件

编译：
+ 修改Makefile，将CROSS_COMPILE设置为目标交叉编译链前缀(不交叉编译则设置为空)；
+ 执行make

编译后：
+ pt-active：控制云台转动
+ tracker.sh：根据跟踪参数调用pt-active
