# Hot And Cold Observables
> http://introtorx.com/Content/v1.0.10621.0/14_HotAndColdObservables.html

In this chapter, we will look at how to describe and handle two styles of observable sequences:

Sequences that are passive and start producing notifications on request (when subscribed to), and
Sequences that are active and produce notifications regardless of subscriptions.
In this sense, passive sequences are Cold and active are described as being Hot. You can draw some similarities between implementations of the IObservable<T> interface and implementations of the IEnumerable<T> interface with regards to hot and cold. With IEnumerable<T>, you could have an on-demand collection via the yield return syntax, or you could have an eagerly-evaluated collection by returning a populated List<T>. We can compare the two styles by attempting to read just the first value from a sequence. We can do this with a method like this:
~~~
public void ReadFirstValue(IEnumerable<int> list)
{
foreach (var i in list)
{
Console.WriteLine("Read out first value of {0}", i);
break;
}
}
~~~
As an alternative to the break statement, we could apply a Take(1) to the list. If we then apply this to an eagerly-evaluated sequence, such as a list, we see the entire list is first constructed, and then returned.

~~~
public static void Main()
{
ReadFirstValue(EagerEvaluation());
}
public IEnumerable<int> EagerEvaluation()
{
var result = new List<int>();
Console.WriteLine("About to return 1");
result.Add(1);
//code below is executed but not used.
Console.WriteLine("About to return 2");
result.Add(2);
return result;
}
Output:

About to return 1
About to return 2
Read out first value of 1
~~~

We now apply the same code to a lazily-evaluated sequence.
~~~
public IEnumerable<int> LazyEvaluation()
{
Console.WriteLine("About to return 1");
yield return 1;
//Execution stops here in this example
Console.WriteLine("About to return 2");
yield return 2;
}

Output:

About to return 1
Read out first value of 1
~~~

The lazily-evaluated sequence did not have to yield any more values than required. Lazy evaluation is good for on-demand queries whereas eager evaluation is good for sharing sequences so as to avoid re-evaluating multiple times. Implementations of IObservable<T> can exhibit similar variations in style.

Examples of hot observables that could publish regardless of whether there are any subscribers would be:

* mouse movements
* timer events
* broadcasts like ESB channels or UDP network packets.
* price ticks from a trading exchange

* Some examples of cold observables would be:

* asynchronous request (e.g. when using Observable.FromAsyncPattern)
* whenever Observable.Create is used
* subscriptions to queues
* on-demand sequences

# Cold observables
In this example, we fetch a list of products from a database. In our implementation, we choose to return an IObservable<string> and, as we get the results, we publish them until we have the full list, then complete the sequence.
~~~
private const string connectionString = @"Data Source=.\SQLSERVER;"+
@"Initial Catalog=AdventureWorksLT2008;Integrated Security=SSPI;"
private static IObservable<string> GetProducts()
{
return Observable.Create<string>(
o =>
{
using(var conn = new SqlConnection(connectionString))
using (var cmd = new SqlCommand("Select Name FROM SalesLT.ProductModel", conn))
{
conn.Open();
SqlDataReader reader = cmd.ExecuteReader(CommandBehavior.CloseConnection);
while (reader.Read())
{
o.OnNext(reader.GetString(0));
}
o.OnCompleted();
return Disposable.Create(()=>Console.WriteLine("--Disposed--"));
}
});
}
~~~
This code is just like many existing data access layers that return an IEnumerable<T>, however it would be much easier with Rx to access this in an asynchronous manner (using SubscribeOn and ObserveOn). This example of a data access layer is lazily evaluated and provides no caching. Each time the method is used, we reconnect to the database. This is typical of cold observables; calling the method does nothing. Subscribing to the returned IObservable<T> will however invoke the create delegate which connects to the database.

Here we have a consumer of our above code, but it explicitly only wants up to three values (the full set has 128 values). This code illustrates that the Take(3) expression will restrict what the consumer receives but GetProducts() method will still publish all of the values.
~~~
public void ColdSample()
{
var products = GetProducts().Take(3);
products.Subscribe(Console.WriteLine);
Console.ReadLine();
}
~~~
The GetProducts() code above is a pretty naive example, as it lacks the ability to cancel at any time. This means all values are read even though only three were requested. In the later chapter on scheduling, we cover examples on how to provide cancellation correctly.

# Hot observables
