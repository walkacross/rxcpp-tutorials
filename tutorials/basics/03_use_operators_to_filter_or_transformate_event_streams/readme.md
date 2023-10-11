# different approche to register callback functions
1. observable.subscribe(subscriber)
2. observable.subscribe(call_back_functions)

# operators
One of the primary advantage of Stream-oriented processing is the fact that we can apply functional programming primitives on them. In RxCpp parlance, the processing is done using Operators. They are nothing but filters, transformations,aggregations, and reductions on Streams. We have already seen how the map,filter, and take operators work in the previous examples. Let us explore them further.

Composing Operators through the pipe Operator

The RxCpp library allows devolopers to chain or compose Operators to enable Operator composition. The library allows you to use the pipe (|) Operator to compose Operators (instead of the usual fluent interface using the  "." ), and programmers can pipe the output of one Operator to another as if they are in the command line of a UNIX shell. This assists in comprehension (about what a piece of code does ). The following program uses the | Operator to map a range. The RxCpp samples contain many examples usin