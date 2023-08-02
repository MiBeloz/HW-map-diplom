#include "thread_pool.h"


thread_pool::~thread_pool() {
	for (auto& it : m_vector_th) {
		if (it.joinable()) {
			it.join();
		}
	}
}

void thread_pool::work() {
	m_vector_th.emplace_back(m_safe_q.pop());
}

void thread_pool::submit(const std::function<void()> func) {
	m_safe_q.push(func);
}
