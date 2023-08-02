#pragma once

#include <vector>
#include <functional>

#include "safe_queue.h"


class thread_pool final {
public:
	thread_pool() {}
	~thread_pool();

	thread_pool(const thread_pool& other) = delete;
	thread_pool(thread_pool&& other) noexcept = delete;
	thread_pool& operator=(const thread_pool& other) = delete;
	thread_pool& operator=(thread_pool&& other) noexcept = delete;

	void work();
	void submit(const std::function<void()> func);

private:
	std::vector<std::thread> m_vector_th;
	safe_queue m_safe_q;
};
