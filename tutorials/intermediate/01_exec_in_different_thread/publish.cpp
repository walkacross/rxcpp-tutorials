#include <iostream>
#include <rxcpp/rx.hpp>

void publish_subject_sample(){
    printf("//! [publish subject sample]\n");
    auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(50), rxcpp::observe_on_new_thread()).take(5).publish();

    // Subscribe from the beginning
    values.subscribe(
                [](long v){printf("[1] OnNext: %ld\n", v);},
                [](){printf("[1] OnCompleted\n");});

    // Another subscription from the beginning
    values.subscribe(
                [](long v){printf("[2] OnNext: %ld\n", v);},
                [](){printf("[2] OnCompleted\n");});

    // Start emitting
    values.connect();

    // Wait before subscribing
    rxcpp::observable<>::timer(std::chrono::milliseconds(75)).subscribe([&](long){
        values.subscribe(
                        [](long v){printf("[3] OnNext: %ld\n", v);},
                        [](){printf("[3] OnCompleted\n");});
    });

    // Add blocking subscription to see results
    values.as_blocking().subscribe();
    printf("//! [publish subject sample]\n");
}

int main(){
    publish_subject_sample();
    return 0;
}