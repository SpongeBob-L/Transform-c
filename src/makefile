# 添加freecplus框架
freecplusAdd = -I../frame ../frame/_freecplus.cpp

all:transform

transform:transform.cpp
	g++ -o transform transform.cpp $(freecplusAdd)
	mv transform ../bin
	cp ../bin/transform ../

clean:
	rm -rf transform
