#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <clocale>
#include <cmath>
#include <cstring>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string>
#include <sys/stat.h>        /* For mode constants */
#include <chrono>
#include <iostream>
    
  const char *name = "/image";
int main()

{
bool retval;
 void *ptr = NULL;
  const int SIZE = 1000000;
   std::cout <<"entered read data func"  << std::endl;
    const char *sema1 = "fill";
    const char *sema2 = "avail";
    const char *sema3 = "mutex";
    sem_t *fill = NULL, *avail = NULL, *mutex = NULL;
    fill = sem_open(sema1, O_CREAT, 0666, 0);
    avail = sem_open(sema2, O_CREAT, 0666, 1);
    mutex = sem_open(sema3, O_CREAT, 0666, 1);
	 sem_t *ofill = NULL, *oavail = NULL, *omutex = NULL;
    const char *sema11 = "fill_out_prod";
    const char *sema22 = "avail_out_prod";
    const char *sema33 = "out_cons_mutex";

    ofill = sem_open(sema11, O_CREAT, 0666, 0);
    oavail = sem_open(sema22, O_CREAT, 0666, 1);
    omutex = sem_open(sema33, O_CREAT, 0666, 1);
	 int frameCount = 0;
    auto startTime = std::chrono::high_resolution_clock::now();
  
while(1)
{	
   
	
    sem_wait(fill);
	sem_wait(ofill);
	sem_wait(mutex);
	//std::cout <<".."  << std::endl;
	
	/*int shm_fd = shm_open(name, O_RDONLY, 0666);
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

        int size_of_buffer = *(int *)(ptr);
        int imageid = *((int *)ptr + 1);
        int imagetype = *((int *)ptr + 2);
         std::cout <<  " ID : " << imageid  << std::endl;

		 
*/
frameCount++;

        auto endTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        if (deltaTime >= 1000) {
            double fps = frameCount / (deltaTime / 1000.0);
            std::cout << "Frame rate: " << fps << " fps" << std::endl;
            frameCount = 0;
            startTime = endTime;
        }
auto now = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

        // Convert the time to a string with milliseconds
        auto currentTime = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        std::time_t currentTime_t = std::chrono::high_resolution_clock::to_time_t(currentTime);
        std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        std::string timeString = std::ctime(&currentTime_t);
        timeString.pop_back(); // remove the newline character from the end
        timeString += "." + std::to_string(milliseconds.count());

        // Print the time to the console
        std::cout << timeString << std::endl;



sem_post(mutex);
sem_post(avail);
//sem_post(fill);
		

  
	
	sem_wait(omutex);
	
	//std::cout <<"Op consumer"  << std::endl;
	sem_post(omutex);
	sem_post(oavail);
//	sem_post(ofill);
	
		
}
    sem_close(fill);
    sem_close(avail);
	sem_close(mutex);
	sem_close(ofill);
    sem_close(oavail);
    sem_close(omutex);
	

 }
	
	