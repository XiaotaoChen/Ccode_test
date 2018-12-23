#include<iostream>

int ca_var = 10;
class CA {    
public:    
  int ca_var;    
  int add(int a, int b);    
  int add(int a);    
};   
//那么在实现这个函数时，必须这样书写：    
int CA::add(int a, int b)    
{    
  return a + b;    
}
  //另外，双冒号也常常用于在类变量内部作为当前类实例的元素进行表示，比如:    
int CA::add(int a)    
{    
  return a + this->ca_var;    
}

int main(){
  CA* a = new CA();
  a->ca_var = 0;
  a->ca_var = 2;
  std::cout<<"a.ca_var:"<<a->ca_var<<std::endl;
  int b = a->add(2);
  std::cout<<"b:"<<b<<std::endl;
}       
