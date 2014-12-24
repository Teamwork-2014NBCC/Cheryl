#include "input_mgr.h"
#include "Combat.h"
#include "Player.h"



void input_mgr::Run_Action(int key_input_value)
{
	map_mutex.lock();
	auto iter = Key_Action_Map.find( key_input_value );
	if ( iter != Key_Action_Map.end() )
	{
		iter->second();
	}
	map_mutex.unlock();
}

void input_mgr::Register_Action(int key_input_value, std::function<void()> action)
{
	map_mutex.lock();
	Key_Action_Map[key_input_value] = action;
	map_mutex.unlock();
}

void input_mgr::Add(int key_input_value)
{
	vector_mutex.lock();
	input_list.push_back(key_input_value);
	vector_mutex.unlock();
}

void input_mgr::Remove(int key_input_value)
{
	vector_mutex.lock();
	for ( auto iter = input_list.begin(); iter != input_list.end(); ++iter )
	{
		if ( key_input_value == *iter )
		{
			input_list.erase( iter );
			break;
		}
	}
	vector_mutex.unlock();
}

void input_mgr::ProcessQueue()
{
	do
	{
		vector_mutex.lock();
		for ( auto key_queued : input_list )
		{
			Run_Action(key_queued);
		}
		vector_mutex.unlock();
		std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
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
			//combat->B_Attack();
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
