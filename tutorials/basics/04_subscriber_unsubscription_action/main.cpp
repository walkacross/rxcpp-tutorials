#include <iostream>
#include <rxcpp/rx.hpp>

void bad_case(){
    auto subscription = rxcpp::composite_subscription();
    auto subscriber = rxcpp::make_subscriber<int>(
            subscription,
            [&](int v){
                printf("OnNext: %d\n", v);
                if (v == 2)
                    subscription.unsubscribe();
            },
            [](){
                printf("OnCompleted\n");
            });

    rxcpp::observable<>::create<int>(
            [](rxcpp::subscriber<int> s){
                for (int i = 0; i < 5; ++i) {
                    s.on_next(i);
                    printf("Just sent: OnNext(%d)\n", i);
                }
                s.on_completed();
                printf("Just sent: OnCompleted()\n");
            }).subscribe(subscriber);
}

void good_case(){
    auto subscription = rxcpp::composite_subscription();
    auto subscriber = rxcpp::make_subscriber<int>(
            subscription,
            [&](int v){
                printf("OnNext: %d\n", v);
                if (v == 2)
                    subscription.unsubscribe();
            },
            [](){
                printf("OnCompleted\n");
            });
    rxcpp::observable<>::create<int>(
            [](rxcpp::subscriber<int> s){
                for (int i = 0; i < 5; ++i) {
                    if (!s.is_subscribed()) // Stop emitting if nobody is listening
                        break;
                    s.on_next(i);
                    printf("Just sent: OnNext(%d)\n", i);
                }
                s.on_completed();
                printf("Just sent: OnCompleted()\n");
            }).subscribe(subscriber);
}

int main(){
    std::cout << "-----------------bad case--------------------------" << std::endl;
    bad_case();

    std::cout << "-----------------good case--------------------------" << std:;endl;
    good_case();
    return 0;
}