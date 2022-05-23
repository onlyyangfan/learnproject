/*
 *
 *	File Name: Thread.hpp
 *	Author: YangFan
 *	Email: onlyyangfan@protonmail.com
 *	Create Time: Mon 23 May 2022 06:39:40 PM CST
 *
 */
#ifndef THREAD_HPP
#define THREAD_HPP

#include "../include/utilies.hpp"
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>


class ThreadPool {
public:
	ThreadPool(size_t);
	~ThreadPool();

	void enqueueTask(std::function<void()> &&);
private:
	std::vector<std::thread> m_threadPool;
	std::queue<std::function<void()>> m_tasks;

	std::mutex m_queueMetex;

	std::condition_variable m_condVar;

	
};



#endif
