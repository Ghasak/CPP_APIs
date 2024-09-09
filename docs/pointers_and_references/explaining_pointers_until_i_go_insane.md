# Pointer Shape and How I imagine it

The following diagram for visualizing the concept of a `pointer` communicates
multiple pieces of information and each one holds significance. This
understanding is based on my fundamental comprehension of pointers.

## Pointers

Just a

```sh
          ┌────────┐
    ┌─────│ MEMORY ├─────┐
    │     └────────┘     │
    │ ┌────────────────┐ │               ┌────────────────┐
    │ │ 0x5555555592a0 │ │               │ 0x7fffffffa571 │
    │ └────────────────┘ │               │ 0x7fffffffa570 │
    │ ┌────────────────┐ │               │ 0x7fffffffa57f │
    │ │ 0x5555555592a1 │ │               │ 0x7fffffffa57e │
    │ └────────────────┘ │    ◀──────────│ 0x7fffffffa57k │
    │ ┌────────────────┐ │               │      .         │
    │ │ 0x5555555592a2 │ │               │      .         │
    │ └────────────────┘ │               │      .         │
    │ ┌────────────────┐ │               │ 0x7fffffffa574 │
    │ │ 0x5555555592a3 │ │               │ 0x7fffffffa575 │
    │ └────────────────┘ │               │ 0x7fffffffa576 │
    └────────────────────┘               └────────────────┘

```

- Starting to answer the following question
  - What is this?

```cpp
int (*(*x())[])(){};

int (*x())[20];

char *(*(*x[][8])())[];

char *(*(*(**x[])())[])();

int *(*(*x[])(char *, int *(*)(char *))[])(char **, char *(*)());

```

- Try to answer this question,
  - `int *(*(**x[][])())[8];`
    - x is array of array of 8 pointers to functions returning pointer to array of poonteer to a pointer to int
    - x is a function that takes as input an array of 8 pointers o pointer to an array and returns a pointer to array of poointer to int
    - x is an array of pointers to pointer to function return ing 8 poiiinters to array of pointers to int <- `answer`
    - x is an array of 8 pointers to functions, where each function returns a pointer to a function returing a pointer to a function returning a pointer to an interger.

## Pointers - session 1

```c


int main(){
    // A little-endian system [ ... ] stores the least-significant byte at the smallest address.

    int * x;
    char* y;

    x = (int*)malloc(sizeof(int));
    *x = INT_MAX;
    y = (char*)malloc(sizeof(int));
    *y = 'F';  // 46 in HEX
    *x = 32;

    free(x);
    free(y);

    return 0;
}


```

- How about this `struct`, which is same as we did before.

```c

// Define a struct
typedef struct Fucker
{
    char name[6];
    unsigned char age;


} FUCKER;



int main(){
    FUCKER* f;
    void* v;

    f = (FUCKER *)malloc((sizeof(char)* (6))+ sizeof(unsigned char));
    strcpy(f -> name, "Sonic");
    f->age = UCHAR_MAX;

    free(f);
    free(v);
}

```

- If you see the memeory you can see: `&f: 0x7fffffffd5a0`, this is the
  address of `f: 0x5555555592a0`, and this is the value that is stored in the
  address.

```sh
00005555555592a0 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f D e c 0 d e d     B y t e s
00005555555592a0 53 6f 6e 69 00 ff 00 00 00 00 S  0  n   i  c null  null null null null null

```


- Pointers can be stored in an array

```c

main(){

    char* string;
    string = (char*)malloc(sizeof(char) * 4);

    string[0] = 'F';
    string[1] = 'u';
    string[2] = 'c';
    string[3] = '\0';

    free(string);
}


```
