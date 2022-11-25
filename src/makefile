#框架头文件路径
FrameIncl = -I../frame

#框架程序路径
FramePath = ../frame/_freecplus.cpp

all:transform

transform:transform.cpp
	g++ -o transform transform.cpp $(FrameIncl) $(FramePath)
	mv transform ../bin

clean:
	rm -rf transform
