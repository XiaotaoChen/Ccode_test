#include <iostream> 
#include "file2.hpp"

void fn();
int n; //定义静态全局变量 

int main()
{
	n=20;
	std::cout<<n<<std::endl;
	fn();

    return 0;
} 