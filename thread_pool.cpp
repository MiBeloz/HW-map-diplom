#include "thread_pool.h"


thread_pool::thread_pool(const unsigned short max_threads) : m_max_threads(max_threads) {
	if (m_max_threads > std::thread::hardware_concurrency()) {
		throw std::logic_error("Неккоректное число потоков!");
	}
	for (unsigned short i = 0; i < m_max_threads; ++i) {
		std::thread* th;
		m_vector_th.emplace_back(th);
	}
}

thread_pool::~thread_pool() {
	for (auto& it : m_vector_th) {
		if (it->joinable()) {
			it->join();
		}
		delete it;
	}
}

void thread_pool::work() {
	m_vector_th.at(m_current_threads - m_local_threads) = new std::thread(m_safe_q.pop());
	m_local_threads--;
}

void thread_pool::work_all() {
	while (m_local_threads > 0) {
		work();
	}
}

void thread_pool::submit(const std::function<void()> func) noexcept {
	if (m_current_threads < m_max_threads) {
		m_safe_q.push(func);
		m_current_threads++;
		m_local_threads++;
	}
}

bool thread_pool::is_full() const noexcept {
	if (m_current_threads >= m_max_threads) {
		return true;
	}
	return false;
}
