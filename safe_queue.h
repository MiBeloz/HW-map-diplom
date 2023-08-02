#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>


class safe_queue final {
public:
	safe_queue() {}
	~safe_queue() {}

	safe_queue(const safe_queue& other) = delete;
	safe_queue(safe_queue&& other) noexcept = delete;
	safe_queue& operator=(const safe_queue& other) = delete;
	safe_queue& operator=(safe_queue&& other) noexcept = delete;

	void push(const std::function<void()>& func);
	std::function<void()> pop();
	bool empty() const;

private:
	std::mutex m_mtx;
	std::condition_variable m_cv;
	std::queue<std::function<void()>> m_queue;
};
