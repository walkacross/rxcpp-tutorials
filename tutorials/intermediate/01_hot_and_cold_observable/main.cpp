#include <iostream>
#include <rxcpp/rx.hpp>
#include <unistd.h>

void a_hot_observable_example(){
    auto period = std::chrono::milliseconds(500);
    auto hot_event_stream = rxcpp::observable<>::interval(period).take(5);

    std::cout << "------before first subscribe --------" <<  std::endl;
    // Subscribe from the beginning
    hot_event_stream.subscribe(
            [](int v){std::cout << "[1] OnNext: " << v <<  std::endl;},
            [](){printf("[1] OnCompleted\n");});
    std::cout << "------after first subscribe --------" <<  std::endl;

    std::cout << "------------------do something before next subscribe-------------------------" << std::endl;
    sleep(0.01);
    // Another subscription from the beginning
    hot_event_stream.subscribe(
            [](int v){std::cout << "[2] OnNext: " << v << std::endl;},
            [](){printf("[2] OnCompleted\n");});
}

//Turn a cold observable hot and allow connections to the source to be independent of subscriptions.
void a_cold_observable_example(){
    auto period = std::chrono::milliseconds(500);

    auto cold_event_stream = rxcpp::observable<>::interval(period).take(5).publish();

    std::cout << "------before first subscribe --------" <<  std::endl;
    // Subscribe from the beginning
    cold_event_stream.subscribe(
            [](int v){std::cout << "[1] OnNext: " << v <<  std::endl;},
            [](){printf("[1] OnCompleted\n");});
    std::cout << "------after first subscribe --------" <<  std::endl;

    std::cout << "------------------do something before next subscribe-------------------------" << std::endl;
    sleep(0.8);
    // Another subscription from the beginning
    cold_event_stream.subscribe(
            [](int v){std::cout << "[2] OnNext: " << v << std::endl;},
            [](){printf("[2] OnCompleted\n");});

    cold_event_stream.connect();

}

int main(){
    std::cout << "--------------------a_hot_observable_example------------------------------" << std::endl;
    a_hot_observable_example();

    std::cout << "------------a_cold_observable_example----------------------" << std::endl;
    a_cold_observable_example();
    return 0;
}