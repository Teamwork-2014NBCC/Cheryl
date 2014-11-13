#include "input.h"

void input_mgr::Run_Action(int key_input_value)
{
	Lock();
	(Key_Action_Map.find(key_input_value))->second();
	Unlock();
}

void input_mgr::Register_Action(int key_input_value, std::function<void()> action)
{
	Lock();
	Key_Action_Map[key_input_value] = action;
	Unlock();
}

void input_mgr::Add(int key_input_value)
{
	Lock();
	input_list.push_back(key_input_value);
	Unlock();
}

void input_mgr::Remove(int key_input_value)
{
	Lock();
	for ( int i = 0; i < input_list.size(); ++i )
	{
		if ( key_input_value == input_list[i] )
		{
			input_list.erase(input_list.begin() + i);
		}
	}
	Unlock();
}

void input_mgr::ProcessQueue()
{
	do
	{
		Lock();
		for ( auto key_queued : input_list )
		{
			Run_Action(key_queued);
		}
		Unlock();
	} while ( thread_running );
}

void input_mgr::Lock()
{
	input_mutex.lock();
}

void input_mgr::Unlock()
{
	input_mutex.unlock();
}

void input_mgr::Start()
{
	thread_running = true;
	P1 = std::thread(&input_mgr::ProcessQueue, this);
}

void input_mgr::Stop()
{
	if ( P1.joinable() )
	{
		thread_running = false;
		P1.join();
	}
}
