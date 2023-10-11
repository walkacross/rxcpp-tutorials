#include <iostream>
#include <rxcpp/rx.hpp>

void publish_subject_sample(){
    printf("//! [publish subject sample]\n");
    std::cout << "Main Thead ID => " << std::this_thread::get_id() << std::endl;

    auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(50), rxcpp::observe_on_new_thread()).take(5).publish();

    // Subscribe from the beginning
    values.subscribe(
                [](long v){std::cout << "[1] OnNext: " << v << "thread_id: " << std::this_thread::get_id() << std::endl;},
                [](){printf("[1] OnCompleted\n");});

    // Another subscription from the beginning
    values.subscribe(
                [](long v){std::cout << "[2] OnNext: " << v << "thread_id: " << std::this_thread::get_id() << std::endl;},
                [](){printf("[2] OnCompleted\n");});

    // Start emitting
    std::cout << "before .connect()" << std::endl;
    values.connect();
    std::cout << "after .connect()" << std::endl;
    // Wait before subscribing
    rxcpp::observable<>::timer(std::chrono::milliseconds(75)).subscribe([&](long){
        values.subscribe(
                        [](long v){std::cout << "[3] OnNext: " << v << "thread_id: " << std::this_thread::get_id() << std::endl;},
                        [](){printf("[3] OnCompleted\n");});
    });

    std::cout << "Main Thead ID => " << std::this_thread::get_id() << std::endl;
    // Add blocking subscription to see results
    values.as_blocking().subscribe();
    std::cout << "Main Thead ID => " << std::this_thread::get_id() << std::endl;
    printf("//! [publish subject sample]\n");
}

int main(){
    publish_subject_sample();
    return 0;
}