#include <iostream>
#include <rxcpp/rx.hpp>

// typed as rxcpp::observable<>, this is a collection of factory methods that return an observable

//Create an observable that emits items every specified interval of time
auto create_event_stream_by_every_specified_interval(){
    auto start = std::chrono::steady_clock::now() + std::chrono::milliseconds(1);
    auto period = std::chrono::milliseconds(1000);
    auto event_streams = rxcpp::observable<>::interval(start, period);
    return event_streams;
}

//Create an observable that emits items in the specified interval of time
auto create_event_stream_by_specified_interval(){
    //auto start = std::chrono::steady_clock::now() + std::chrono::milliseconds(1);
    auto period = std::chrono::milliseconds(6000);
    auto event_streams = rxcpp::observable<>::timer(period);
    return event_streams;
}

int main(){
    auto event_streams = create_event_stream_by_every_specified_interval();
    event_streams.take(10).
            subscribe(
            [](int v){printf("OnNext: %d\n", v);},
            [](){printf("OnCompleted\n");});

    std::cout << "---------------create another----------------------------" << std::endl;
    auto specified_interval_event_stream = create_event_stream_by_specified_interval();
    specified_interval_event_stream.subscribe(
            [](int v){printf("OnNext: %d\n", v);},
            [](){printf("OnCompleted\n");});
    return 0;
}