#include <iostream>
#include <rxcpp/rx.hpp>

int main() {

    // create event list by built-in functions
    auto event_sequences = rxcpp::observable<>::range(1, 6);

    // subscribe the on_next and on_complete callback functions
    event_sequences.subscribe([](int v) { printf("OnNext: %d\n", v); },
                              []() {
                                  printf("OnCompleted sequences\n");
                              });
    return 0;
}

