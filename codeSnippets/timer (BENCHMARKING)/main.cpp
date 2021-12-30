#include <iostream>
#include <chrono>
#include <memory>

class Timer {
	public:
		Timer() {
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}
		
		~Timer() {
			auto endTimetpoint = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimetpoint).time_since_epoch().count();
			
			auto duration = end - start;
			double ms = duration * 0.001;
			
			std::cout << "TIME: " << duration << " (" << ms << " ms)" << std::endl;
		}
	
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	
};

int main(int argc, char* argv[]){
	
	{
		Timer timer;
		
		//CODE TO TIME
		std::cout << "PRINT" << std::endl;
	}
	
	return 0;
}
