
#include <thread>
#include "threadutil.hpp"



int threadutil::get_optimal_thread_count(int task_count) {

	int cpu_count = std::thread::hardware_concurrency();
	return (task_count < cpu_count)? task_count: cpu_count;
}


int threadutil::get_tasks_per_thread(int task_count, int thread_count) {

	int tasks_per_thread = task_count / thread_count;
	return (tasks_per_thread == 0)? 1: tasks_per_thread;
}


int threadutil::get_remaining_tasks(int task_count, int thread_count) {

	if (task_count < thread_count) return 0;
	int remaining_tasks = task_count % thread_count;

	return remaining_tasks;
}


int threadutil::get_segment_start(int i, int tasks_per_thread, int remaining_tasks) {

	int segment_start = i * tasks_per_thread;
	if (i < remaining_tasks)
		segment_start += i;
	else
		segment_start += remaining_tasks;

	return segment_start;
}


int threadutil::get_segment_range(int i, int tasks_per_thread, int remaining_tasks) {

	int segment_range = tasks_per_thread;
	if (i < remaining_tasks)
		segment_range += 1;

	return segment_range;
}

