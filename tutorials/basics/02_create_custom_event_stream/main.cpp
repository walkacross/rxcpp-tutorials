#include <iostream>
#include <rxcpp/rx.hpp>
#include <memory>

auto create_event_stream_by_built_in_functions(){
    auto event_streams = rxcpp::observable<>::range(1, 6);
    return event_streams;
}

auto create_simple_custom_event_stream(){
    auto simple_event_streams = rxcpp::observable<>::create<int>([](rxcpp::subscriber<int> s) {
        s.on_next(1);
        s.on_next(4);
        s.on_next(9);
        s.on_completed();
    });
    return simple_event_streams;
}


class event {
public:
    virtual std::int64_t gen_time() const = 0;

    virtual std::int32_t msg_type() const = 0;
};


class Data : public event {
public:
    std::int32_t msg_type_{0};
    std::int64_t gen_time_{1030};

    Data(std::int32_t msg_type,std::int64_t gen_time):msg_type_(msg_type),gen_time_(gen_time){

    }

    std::int64_t gen_time() const override{
        return gen_time_;
    }
    std::int32_t msg_type() const override{
        return msg_type_;
    }
};

using event_ptr = std::shared_ptr<event>;

auto create_custom_definition_event_stream(){

    auto custom_event_streams = rxcpp::observable<>::create<event_ptr>([](rxcpp::subscriber<event_ptr> s) {
        s.on_next(std::make_shared<Data>(1,103000));
        s.on_next(std::make_shared<Data>(1,103100));
        s.on_next(std::make_shared<Data>(1,103200));
        s.on_completed();
    });
    return custom_event_streams;
}

int main (){
    //
    // subscribe by subscriber
    auto int_subscriber = rxcpp::make_subscriber<int>(
            [](int v){printf("OnNext: %d\n", v);},
            [](){printf("OnCompleted\n");});

    std::cout << "create event streams from built-in functions" << std::endl;
    auto event_stream_from_built_in =  create_event_stream_by_built_in_functions();
    // subscribe the on_next and on_complete callback functions
    event_stream_from_built_in.subscribe(int_subscriber);

    std::cout << "-----------------create simple custom event stream----------------------------" << std::endl;
    auto another_int_subscriber = rxcpp::make_subscriber<int>(
            [](int v){printf("OnNext: %d\n", v);},
            [](){printf("OnCompleted\n");});
    auto simple_custom_event_streams = create_simple_custom_event_stream();
    simple_custom_event_streams.subscribe(another_int_subscriber);

    std::cout << "-----------------create custom definition event stream----------------------------" << std::endl;


    auto custom_event_subscriber = rxcpp::make_subscriber<event_ptr>(
            [](event_ptr v) { printf("OnNext: %ld\n", v->gen_time()); },
            [](){printf("OnCompleted\n");});

    auto cumtom_event_streams = create_custom_definition_event_stream();
    cumtom_event_streams.subscribe(custom_event_subscriber);
    return 0;
}