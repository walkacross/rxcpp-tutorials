#include <iostream>
#include <rxcpp/rx.hpp>

auto create_basic_event_stream_with_operators(){
    auto event_streams_after_transformation = rxcpp::observable<>::range(1, 6).filter([](int v){return v%2==0;}).map([](int v){return v*v;});
    return event_streams_after_transformation;
}

auto create_event_stream_with_operators_pipe_equivalent(){
/*
 * Composing Operators through the pipe Operator
 * The RxCpp library allows devolopers to chain or compose Operators to enable Operator composition. The library allows you to use the pipe (|) Operator to compose Operators (instead of the usual fluent interface using the  "." ), and programmers can pipe the output of one Operator to another as if they are in the command line of a UNIX shell. This assists in comprehension (about what a piece of code does ). The following program uses the | Operator to map a range. The RxCpp samples contain many examples usin
 */
    auto event_streams_with_pipe_operator = rxcpp::observable<>::range(1, 6) | rxcpp::operators::filter([](int v){return v%2==0;}) | rxcpp::operators::map([](int v){return v*v;});
    return event_streams_with_pipe_operator;

}


int main() {

    std::cout  << "--------------------basic operators--------------------------------" << std::endl;
    // create event list by built-in functions
    auto event_streams_after_transformation = create_basic_event_stream_with_operators();

    // subscribe the on_next and on_complete callback functions
    event_streams_after_transformation.subscribe([](int v) { printf("OnNext: %d\n", v); },
                            []() {
                                printf("OnCompleted sequences\n");
                            });

    std::cout  << "------------------statistic operators----------------------------------" << std::endl;
    auto event_streams_with_pipe_operator = create_event_stream_with_operators_pipe_equivalent();
    event_streams_with_pipe_operator.subscribe([](int v) { printf("OnNext: %d\n", v); },
                                                 []() {
                                                     printf("OnCompleted sequences\n");
                                                 });


    return 0;
}