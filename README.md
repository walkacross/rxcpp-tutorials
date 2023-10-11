# rxcpp-tutorials
rxcpp-tutorials

# how to use rxcpp in cmake-based c++ project

RxCpp is header only library, so you have not to build one at all inside your project. The only thing you should do is to customize include search path to RxCpp with include_directory:
~~~
INCLUDE_DIRECTORIES(${RXCPP_HOME} $ENV{RXCPP_HOME}) 
~~~









# appendix
1. https://github.com/ReactiveX/RxCpp/tree/main/Rx/v2/examples/doxygen

2. https://github.com/PacktPublishing/CPP-Reactive-Programming