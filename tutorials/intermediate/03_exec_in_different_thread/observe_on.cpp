#include <iostream>
#include <rxcpp/rx.hpp>
//#include "rxcpp/rx-test.hpp"
#include <thread>

std::string get_pid() {
    std::stringstream s;
    s << std::this_thread::get_id();
    return s.str();
}

/*
void observe_on_sample(){
    printf("//! [observe_on sample]\n");
    printf("[thread %s] Start task\n", get_pid().c_str());
    auto values = rxcpp::observable<>::range(1, 3).
            map([](int v){
            printf("[thread %s] Emit value %d\n", get_pid().c_str(), v);
            return v;});
    values.observe_on(rxcpp::synchronize_new_thread()).as_blocking().subscribe(
        [](int v){printf("[thread %s] OnNext: %d\n", get_pid().c_str(), v);},
        [](){printf("[thread %s] OnCompleted\n", get_pid().c_str());});
    printf("[thread %s] Finish task\n", get_pid().c_str());
    printf("//! [observe_on sample]\n");
}
*/

int main(){
    //observe_on_sample();
    // create event streams by factory function
    auto event_streams = rxcpp::observable<>::range(1,6).map([](int v){return v*v;});

    // emit the current thread details
    std::cout << "Main Thead ID => " << std::this_thread::get_id() << std::endl;

    // observe on another thread, make it blocking

    event_streams.observe_on(rxcpp::synchronize_new_thread()).
            as_blocking().
            subscribe(
            [](int v){std::cout << "[thread %s] OnNext: %d\n" << get_pid().c_str() << v << std::endl;},
            [](){ std::cout << "[thread %s] OnCompleted\n" << get_pid().c_str() << std::endl;});

    std::cout << "coming to the end " << std::endl;
    std::cout << "Main Thead ID => " << std::this_thread::get_id() << std::endl;
    return 0;
}