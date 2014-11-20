#ifndef _INPUT_H_
#define _INPUT_H_

//Version 1.2
//Last Updated: 2014.11.20@11:30am

#include <vector>
#include <thread>
#include <map>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <algorithm>
#include <Windows.h>
#include <iostream>

class input_mgr
{
private:
	std::mutex inputQ_mutex;
	std::mutex Map_mutex;
	std::thread P1;
	std::vector<int> input_list;
	std::unordered_map<int, bool> Queued_Input;
	std::unordered_map<int, std::function<void()>> Key_Action_Map;
	POINT curPos;
	BOOL result;

protected:
	bool thread_running = false;
	inline void Run_Action(int key_input_value);

public:
	void Register_Action(int key_input_value, std::function<void()> action);
	void ProcessQueue();
	
	void Add(int key_input_value);
	void Remove(int key_input_value);

	void MouseInput();

	void Start();
	void Stop();
	
};

#endif
