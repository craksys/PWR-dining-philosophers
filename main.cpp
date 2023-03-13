#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 5;

mutex forks[N];
mutex print_protect;
bool stop_mutex;
int score[N];


void stop(){
    while (getchar() != 'k');
    stop_mutex = true;
}
void philosopher(int id) {
    int left_fork = id; // lewy widelec to jego numer
    int right_fork = (id + 1) % N; // prawy widelec to następny numer

    while(true){
        int random;
        if(stop_mutex){
            return;
        }
        random = rand() % 4001 + 1000;
        this_thread::sleep_for(chrono::milliseconds(random)); //filozof mysli

        forks[left_fork].lock();//filozof zabiera lewy widelec


        if(forks[right_fork].try_lock()) {/
        }else{
            forks[left_fork].unlock();
            while(!forks[left_fork].try_lock() && !forks[right_fork].try_lock()){
                forks[left_fork].unlock();
                forks[right_fork].unlock();
                this_thread::sleep_for(chrono::milliseconds(5));
            }
        }
        // jedzenie
        print_protect.lock();
        cout << "Filozof " << id << " je spaghetti z serem" << endl;
        print_protect.unlock();
        score[id]++;

        random = rand() % 4001 + 1000;
        this_thread::sleep_for(chrono::milliseconds(random)); //filozof je sobie

        //filozof zwalnia zasoby
        forks[left_fork].unlock();
        forks[right_fork].unlock();
    }
}

int main() {
    srand(time(NULL));
    thread t(stop);
    thread philosophers[N];
    for (int i = 0; i < N; i++) {
        philosophers[i] = thread(philosopher, i);
    }

    for (int i = 0; i < N; i++) {
        philosophers[i].join();
    }

    for(int i = 0; i < N; i++){
        cout << "Filozof " << i << " jadl " << score[i] << " razy" << endl;
    }

    return 0;
}
