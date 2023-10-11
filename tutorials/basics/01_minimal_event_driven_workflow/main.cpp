#include <iostream>
#include <rxcpp/rx.hpp>

int main() {

    // create event list by built-in functions
    auto event_streams = rxcpp::observable<>::range(1, 6);

    // subscribe by subscriber
    auto subscriber = rxcpp::make_subscriber<int>(
            [](int v){printf("OnNext: %d\n", v);},
            [](){printf("OnCompleted\n");});

    // subscribe the on_next and on_complete callback functions
    event_streams.subscribe(subscriber);
    return 0;
}

