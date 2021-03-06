#include "input.h"

void input_mgr::Run_Action(int key_input_value)
{
	Map_mutex.lock();
	Key_Action_Map[key_input_value]();
	Map_mutex.unlock();
}

void input_mgr::Register_Action(int key_input_value, std::function<void()> action)
{
	Map_mutex.lock();
	Key_Action_Map[key_input_value] = action;
	Map_mutex.unlock();

	inputQ_mutex.lock();
	Queued_Input[key_input_value] = false;
	inputQ_mutex.unlock();
}

void input_mgr::Add(int key_input_value)
{
	inputQ_mutex.lock();
	if ( !Queued_Input[key_input_value] )
	{
		input_list.push_back(key_input_value);
		Queued_Input[key_input_value] = true;
	}
	inputQ_mutex.unlock();
}

void input_mgr::Remove(int key_input_value)
{
	inputQ_mutex.lock();
	if ( Queued_Input[key_input_value] )
	{
		for ( int i = 0; i < input_list.size(); ++i )
		{
			if ( key_input_value == input_list[i] )
			{
				input_list.erase(input_list.begin() + i);
				Queued_Input[key_input_value] = false;
			}
		}
	}
	inputQ_mutex.unlock();
}

void input_mgr::ProcessQueue()
{
	do
	{
		inputQ_mutex.lock();
		for ( auto key_queued : input_list )
		{
			if ( Key_Action_Map.find(key_queued) != Key_Action_Map.end() )
			{
				Run_Action(key_queued);
			}
		}
		inputQ_mutex.unlock();
	} while ( thread_running );
}

void input_mgr::MouseInput()
{
	while (thread_running)
	{
		result = GetCursorPos(&curPos);
		//while loop based on bool
		if (result)
		{
			std::cout << "The x is: " << curPos.x;
			std::cout << "\nThe Y is: " << curPos.y;
		}
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			std::cout << "Hello" << std::endl;
		}
	}
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
