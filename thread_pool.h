#pragma once

#include <stdexcept>
#include <vector>
#include <functional>

#include "safe_queue.h"


class thread_pool final {
public:
	explicit thread_pool(const unsigned short max_threads);
	~thread_pool();

	thread_pool(const thread_pool& other) = delete;
	thread_pool(thread_pool&& other) noexcept = delete;
	thread_pool& operator=(const thread_pool& other) = delete;
	thread_pool& operator=(thread_pool&& other) noexcept = delete;

	void work();
	void work_all();
	void submit(const std::function<void()> func) noexcept;
	bool is_full() const noexcept;

private:
	const unsigned short m_max_threads;
	unsigned short m_current_threads = 0;
	unsigned short m_local_threads = 0;
	std::vector<std::thread*> m_vector_th;
	safe_queue m_safe_q;
};
