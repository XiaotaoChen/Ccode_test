
SRC_COM = nccl_multi_devices.cu
SRC = $(SRC_COM)

# $@  表示目标文件
# $^  表示所有的依赖文件
# $<  表示第一个依赖文件
# $?  表示比目标还要新的依赖文件列表

CXX = nvcc
# CXXFLAGS = -std=c++11 -g -O1 -I/opt/nccl_2.5.6-1+cuda10.0_x86_64/include -L/opt/nccl_2.5.6-1+cuda10.0_x86_64/lib -lnccl
CXXFLAGS = -std=c++11 -g -O1 -Xcompiler -pthread -lnccl -lmpi -I /root/3rdparty/openmpi4.0/include -L/root/3rdparty/openmpi4.0/lib
TARGET = test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf test test.dSYM

.PHONY: clean