#include <iostream>
#include <algorithm> //std::sort
#include <vector>
using std::cout;
using std::endl;
using std::vector;

/**
 * 不能继承的类
 * 思路：
 * 这题已经过时了，C++11有final关键字
 * class name final {}； 则name不能被继承
 * 
 * 书中方法如下：
 * 类构造顺序：先基类再派生类，且派生类构造函数中只负责调用其直接基类的构造函数；
 *           这种规则有一个例外，被虚继承的虚基类必须被任何一层的派生类直接构造
 *           因此Try无法调用MakeSealed的构造函数会报错
 */
template <typename T>
class MakeSealed
{
    friend T;

  private:
    MakeSealed() {}
    ~MakeSealed() {}
};

class SealedClass2 : virtual public MakeSealed<SealedClass2>
{
  public:
    SealedClass2() {}
    ~SealedClass2() {}
};

class Try : public SealedClass2
{
  public:
    Try() {}
    ~Try() {}
};
int main()
{
    SealedClass2 a;
}