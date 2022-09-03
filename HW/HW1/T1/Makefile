main: main.cpp Member.h Member.cpp
	g++ main.cpp Member.h Member.cpp -o main

clean:
	del *.exe	# make.exe使用的不是Powershell而是cmd!!!

rebuild: clean main

.PHONY: clean rebuild    #设置伪目标（不是用来生成文件的，类比void函数），忽略目录下的clean文件（否则无法执行clean）