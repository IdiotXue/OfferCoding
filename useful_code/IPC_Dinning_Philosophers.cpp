#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using std::condition_variable;
using std::mutex;
using std::thread;
using std::vector;

/**
 * 哲学家就餐问题：5个哲学家绕着圆桌坐，5支筷子
 * 平权：哲学家问题是一个平权的问题，每个哲学家有自己的线程，并且都可以拿到筷子（资源），这使得资源争抢严重，
 *      因为一个线程要同时获得两个资源才能运行，一个资源可以被两个线程争夺。或许换用集权的方式可以避免这种争抢
 * 集权：一个专门的线程负责给哲学家分配筷子，每个哲学家wait在自己的条件变量上，当然也可以只有一个条件变量，不过
 *      就只能随机通知，有可用的2支筷子了就通知一个哲学家，给个线程让他进餐，显然这种方式相当于实现一个消息队列。
 * 效率上可能两者差不多，但实现上肯定是集权方式简单。
 */

/**
 * 用于分派任务的类，重载()函数调用操作符号
 */
class Dispatch
{
  public:
    enum class State
    {
        THINK,
        HUNGRY, //表示想拿筷子
        EATING  //表示拿起了2支筷子
    };
    size_t m_nNum;                      //人数
    vector<State> m_vState;             //跟踪每位哲学家的状态，注意进入EATING相当于锁住2支筷子
    mutex m_mutex;                      //临界区的互斥锁，针对5个哲学家的状态，也可以说针对5支筷子
    vector<condition_variable> m_vCond; //每个哲学家分配一个条件变量
    size_t m_nCount;                    //记录循环Eating总次数，确认多个线程共享了同一个Dispatch

  public:
    explicit Dispatch(size_t n) : m_nNum(n), m_vState(m_nNum, State::THINK), m_vCond(m_nNum), m_nCount(0) {}
    ~Dispatch() {}
    Dispatch(const Dispatch &) = delete;
    const Dispatch &operator=(const Dispatch &) = delete;
    inline size_t Left(size_t n) const { return (n + 1) % m_nNum; }
    inline size_t Right(size_t n) const { return (n + m_nNum - 1) % m_nNum; }
    void JudgeNotify(size_t tid)
    {
        //正在THINK或EATING的都不用通知
        if (m_vState[tid] == State::HUNGRY && m_vState[Left(tid)] != State::EATING && m_vState[Right(tid)] != State::EATING)
        { //通知可以进餐了
            m_vState[tid] = State::EATING;
            m_vCond[tid].notify_one();
        }
    }
    // void operator()(size_t tid); //其实也可以定义running函数用于传入thread
    void running(size_t tid); //其实也可以定义running函数用于传入thread
};

/**
 * 安排每个哲学家的就餐的过程，tid可以理解为哲学家的编号
 */
void Dispatch::running(size_t tid)
{

    int count = 3; //每个哲学家要进餐count次
    for (int i = 0; i < count; ++i)
    {
        usleep(500000); //微秒，THINK思考状态，还不打算进餐
        {               //改变哲学家状态（尝试拿起2支筷子）的临界区
            std::unique_lock<mutex> lck(m_mutex);
            // printf("Count: %lu\n", ++m_nCount);
            m_vState[tid] = State::HUNGRY; //想要进餐
            //尝试获取2支筷子
            if (m_vState[Left(tid)] != State::EATING && m_vState[Right(tid)] != State::EATING)
                m_vState[tid] = State::EATING; //表示拿起了2支筷子，可以就餐
            else
            {
                printf("%lu is waiting\n", tid);
                m_vCond[tid].wait(lck, [this, tid] { return m_vState[tid] == State::EATING; }); //lambda中的条件会被循环检查，不会出现伪唤醒
                printf("%lu is wake up --- ", tid);
            }
            printf("%lu can eat \n", tid);
        }
        //进餐区，只有拿起了2支筷子，即进入EATING状态，才会到达这里
        usleep(500000);
        { //改变哲学家状态的临界区，
            std::lock_guard<mutex> guard(m_mutex);
            m_vState[tid] = State::THINK; //表示放下了2支筷子，接下来要通知相邻哲学家
            printf("%lu stop eating \n", tid);
            // usleep(500000);
            JudgeNotify(Left(tid));
            JudgeNotify(Right(tid));
        }
    }
}

int main()
{
    size_t n = 5; //为5个哲学家分派就餐
    Dispatch disp(n);
    vector<thread> vtPool; //线程池，一个线程代表一个哲学家
    for (size_t i = 0; i < n; ++i)
        vtPool.push_back(thread(std::bind(&Dispatch::running, &disp, i)));
    //vtPool.push_back(thread(disp, i));会报错：调用了被delete的拷贝构造函数，为什么会调用？可能与重载()的机制有关

    for (auto &t : vtPool)
        if (t.joinable())
            t.join();
    std::cout << "thread pool stoping " << std::endl;
}
