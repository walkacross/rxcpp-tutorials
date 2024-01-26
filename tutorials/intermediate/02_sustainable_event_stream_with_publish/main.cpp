#include <iostream>
#include <rxcpp/rx.hpp>
#include <exception>
#include <memory>

bool live_ = true;
int count_ =0;
std::int64_t init_gen_time = 103000;


class event {
public:
    virtual std::int64_t gen_time() const = 0;

    virtual std::int32_t msg_type() const = 0;
};

using event_ptr = std::shared_ptr<event>;


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


event_ptr get_a_event_ptr_from_somewhere(){
    std::int32_t msg_type = 1;
    std::int64_t gen_time = init_gen_time + count_;
    count_ = count_ + 1;
    return std::make_shared<Data>(msg_type, gen_time);
}

bool produce_one(const rxcpp::subscriber<event_ptr>& sb) {

    event_ptr a_event_ptr = get_a_event_ptr_from_somewhere();
    sb.on_next(a_event_ptr);
    if(count_ > 20){
        return false;
    } else {
        return true;
    }
}

void sustainable_produce(const rxcpp::subscriber<event_ptr>& sb)
{
    try
    {
        while (live_)
        {
            live_ = produce_one(sb) && live_;
        }
    } catch (...)
    {
        sb.on_error(std::current_exception());
    }
    sb.on_completed();
}

void run(){

    auto event_streams = rxcpp::observable<>::create<event_ptr>(
                [](rxcpp::subscriber<event_ptr> sb){
                    sustainable_produce(sb);
                })  | rxcpp::operators::publish();
    auto custom_event_subscriber = rxcpp::make_subscriber<event_ptr>(
            [](event_ptr v) { printf("OnNext: %ld\n", v->gen_time()); },
            [](){printf("OnCompleted\n");});

    event_streams.subscribe(custom_event_subscriber);
    event_streams.connect();
}

int main(){

    run();
    return 0;
}

