# Most occuring substring using  generalized suffix tree (GST)*.


# Instructions

## Building

To build the program, you can use `make'. 
The executable is called `gsuffix.out`.
```Bash
>> make all
```

## Running

You can invoke the program as follows:
```Bash
>> # Initialise the program with the path to the trace file.
>> > ./gsuffix.out ./traces/sample.traces
>> # Find subsequences of minimum length 2.
>> > n 2
>> # Outputs will be printed here.
>> # Use `q` to quit the program.
>> > q
```
Enclosed with angle brackets are variables.

## Example

```Bash
>> ./gsuffix.out ./traces/example.traces
>> n 2
2 x a 
2 a b x 
2 b x 
2 b a
>> q
```

* not final version of the readme.