# CPP Learning

## Changing log

- `Mon. Oct. 23rd`: Added more experimentals.
- `Sun. Sep. 3rd.`: Finished the right,

## Details

- CPP learning is a special directory where I put all the necessary fundamentals
  of learning `C++` concepts and ideas.

## CLI Running

- Using the following command to allow the `clang` to run the current file
  system.

```sh
clang++ -std=c++17 -o ./build/debug/main src/main.cpp  && ./build/debug/main
```

## Running in progress

```sh
fswatch -o src/ | xargs -n1 -I{} make all
```
