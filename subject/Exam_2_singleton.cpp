//main.cpp
#include <iostream>
#include "Singleton.h"
int main(int argc, char *argv[])
{
    std::cout << "main work" << std::endl;
    auto single = Singleton::GetInstance();
    std::cout << single << std::endl;
}

//Singleton.h
#ifndef __SINGLETON_H__
#define __SINGLETON_H__
#include <iostream>
#include <memory>    //std::shared_ptr
#include <mutex>     //std::mutex,std::lock_guard
#include <pthread.h> //pthread_once

/**
 * 单例模式的注意点：
 * 1.私有构造函数，确保无法在外部创建实例
 * 2.依托智能指针确保程序结束时执行析构函数
 * 3.为了确保线程安全，有饿汉、懒汉(DCL有乱序问题)、pthread_once三种实现方法
 */

/*--------------------- 1.饿汉式 eager initialize---------------------*/
/**
 * 饿汉式（线程安全），进入main之前创建Singleton实例；
 * 智能指针能在程序结束时调用析构函数，执行关闭文件描述
 * 符等资源回收操作，普通指针不行。
 */
//Singleton.h
/* class Singleton
{
  public:
    static const std::shared_ptr<Singleton> GetInstance() { return sm_pInstance; }
    ~Singleton() { std::cout << "destruct singleton object" << std::endl; }

  private:
    static std::shared_ptr<Singleton> sm_pInstance;

    Singleton() { std::cout << "construct singleton object" << std::endl; }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
}; */
//Singleton.cpp
//调用std::make_shared<Singleton>()初始化会报错，还没找到原因
// std::shared_ptr<Singleton> Singleton::sm_pInstance(new Singleton());

/*--------------------- 2.懒汉式 ---------------------*/
/**
 * 懒汉式(线程安全):双重检测锁定（double checked locking）
 * 需要时创建实例，双重检测避免了创建后每次调用都要加锁，提
 * 高了效率
 */
//Singleton.h
/* class Singleton
{
  public:
    static const std::shared_ptr<Singleton> GetInstance()
    {
        if (!sm_pInstance) //避免创建了实例后，每次调用还要加锁
        {
            std::lock_guard<std::mutex> guard(sm_mutex);
            if (!sm_pInstance)
                sm_pInstance.reset(new Singleton());
        }
        return sm_pInstance;
    }
    ~Singleton() { std::cout << "destruct singleton object" << std::endl; }

  private:
    static std::shared_ptr<Singleton> sm_pInstance;
    static std::mutex sm_mutex;

    Singleton() { std::cout << "construct singleton object" << std::endl; }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
}; */
//Singleton.cpp
// std::shared_ptr<Singleton> Singleton::sm_pInstance;
// std::mutex Singleton::sm_mutex;

/*--------------------- 3.pthread_once ---------------------*/
/**
 * pthread_once函数能够确保多线程状态下，函数init只执行一次
 * 前提：1.所有线程都调用了pthread_once 2.sm_ponce是非本地变量，即全局或静态变量
 * 因此这是线程安全的方法
 */
//Singleton.h
class Singleton
{
  public:
    static const std::shared_ptr<Singleton> GetInstance()
    {
        pthread_once(&sm_ponce, &Singleton::init); //可以确保多线程时init函数只执行一次
        return sm_pInstance;
    }
    ~Singleton() { std::cout << "destruct singleton object" << std::endl; }

  private:
    static std::shared_ptr<Singleton> sm_pInstance;
    static pthread_once_t sm_ponce; //必须是非本地变量

    Singleton() { std::cout << "construct singleton object" << std::endl; }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    static void init() { sm_pInstance.reset(new Singleton()); }
};
//Singleton.cpp
// std::shared_ptr<Singleton> Singleton::sm_pInstance;
// pthread_once_t Singleton::sm_ponce = PTHREAD_ONCE_INIT; //必须这样初始化
#endif