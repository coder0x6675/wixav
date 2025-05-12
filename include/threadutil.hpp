
#ifndef THREADUTIL_HPP
#define THREADUTIL_HPP


namespace threadutil {
 
// Calculates the optimal number of threads.
int get_optimal_thread_count(int task_count);

// Calculates the number of tasks per thread.
int get_tasks_per_thread(int task_count, int thread_count);

// Calculates the remaining number of tasks after evenly dividing per thread.
int get_remaining_tasks(int task_count, int thread_count);

// Calculates the start of a segment for a thread.
int get_segment_start(int i, int tasks_per_thread, int remaining_tasks);

// Calculates the range of a segment for a thread.
int get_segment_range(int i, int tasks_per_thread, int remaining_tasks);

}
 

#endif

