#ifndef _INPUT_H_
#define _INPUT_H_

#include <vector>
#include <thread>
#include <map>
#include <mutex>
#include <functional>
#include <algorithm>

class input_mgr
{
private:
	std::mutex input_mutex;
	std::thread P1;
	std::vector<int> input_list;
	std::map<int, std::function<void()>> Key_Action_Map;

protected:
	bool thread_running = false;
	inline void Run_Action(int key_input_value);
	void Lock();
	void Unlock();

public:
	void Register_Action(int key_input_value, std::function<void()> action);
	void ProcessQueue();
	
	void Add(int key_input_value);
	void Remove(int key_input_value);

	void Start();
	void Stop();
	
};

#endif
