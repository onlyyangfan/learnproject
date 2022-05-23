/*
 *
 *	File Name: Thread.cpp
 *	Author: YangFan
 *	Email: onlyyangfan@protonmail.com
 *	Create Time: Mon 23 May 2022 10:42:31 PM CST
 *
 */

#include "../include/Thread.hpp"


inline ThreadPool::ThreadPool(size_t t_poolSize) {
	for (auto i = 0; i <  t_poolSize; i++) {
		this->m_threadPool.emplace_back([this] {
				while (true) {
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> uniqlck(this->m_queueMetex);
					this->m_condVar.wait(uniqlck, [this] {return !this->m_tasks.empty();});
					task = std::move(this->m_tasks.front());
					this->m_tasks.pop();
				}
					task();
				}
		}
	);
	}	
}

void ThreadPool::enqueueTask(std::function<void()>&& t_fuction) {
	{
		std::unique_lock<std::mutex> uniqLck(this->m_queueMetex);
		this->m_tasks.push(t_fuction);
	}

	this->m_condVar.notify_one();
}

inline ThreadPool::~ThreadPool() {
	this->m_condVar.notify_all();

	for (std::thread &thd : this->m_threadPool) {
		thd.join();
	}
}
