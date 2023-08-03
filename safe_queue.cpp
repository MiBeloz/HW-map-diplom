#include "safe_queue.h"


void safe_queue::push(const std::function<void()>& func) noexcept {
	std::lock_guard<std::mutex> lg(m_mtx);
	m_queue.push(func);
	m_cv.notify_one();
}

std::function<void()> safe_queue::pop() noexcept {
	std::unique_lock<std::mutex> lg(m_mtx);
	m_cv.wait(lg, [this] {return !m_queue.empty(); });
	std::function<void()> val = m_queue.front();
	m_queue.pop();

	return val;
}
