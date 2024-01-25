# Data Types in CPP

Using the variables in our current object

## BYTE REPRESENTATION

The representation of a given `1-byte` can be viewed in many numerical systems,
as for us we will try to build our understanding around the `binary`, `hex` and
the `decimal`. The `1-byte` as a building block to store a data in memeory and
handled in the processor and storge is the basics block for store data. It can
be represented as:

```sh
                                      +----------------------------+
                                      |   BYTE REPRESENTATION      |
                                      +----------------------------+
                                                   [] : 1-byte
                                                    |
                                                    v
              +-------------------------------------- -------------------------------------+
              |                                                                            |
              v                                                                            v
  +----------------------------+                                              +----------------------------+
  |  BINARY REPRESENTATION     |                                              | HEXADECIAML REPRESENTATION |
  +----------------------------+                                              +----------------------------+
    1 byte = 8 bits (8 blocks)                                                 1 byte = 2 bits (2 block)
    [0][0][0][0]-[0][0][0][0]                                                          [0][0]
    written: 0b00000000                                                         Written: 0x00
    Each bit either `1/0`                                                       Each block eather `0,1,2,3...A,B,C,D,E,F` up to 16
    Maximum number can hold, when all bits are set to 1                         Maximum number can hold, when all bits are set to `F`
    [1][1][1][1]-[1][1][1][1] or 0b11111111                                     [F][F] or 0xFF
    Means (1 * 2^0 + 1* 2^1 + 1 * 2^2                                           Means (15 * 16^0 + 15 * 16^1 = 255)
            + 1 * 2^3 + 1* 2^4 + 1* 2^5 +1* 2^6 +1* 2^7  = 255)
    Decimal representation = 255                                                Decimal representation = 255

```

- The representation between maximum and minimum values can be held for one byte is provided as:

| idx | Minimum value        | Maximum value        |
| --- | -------------------- | -------------------- |
| 1   | Binary: `0b00000000` | Binary: `0b11111111` |
| 2   | Hexadecimal: 0x00    | Hexadecimal: `0xFF`  |
| 3   | Octal: 00            | Octal: `0377`        |
| 4   | Decimal: 0           | Decimal: `255`       |

## Int values represnetation

I will provide information about the size and numerical limits for various
integer types in C++, including:

1. `int`
2. `unsigned int`
3. `signed int`
4. `short int`
5. `unsigned short int`
6. `signed short int`
7. `long int`
8. `unsigned long int`
9. `signed long int`
10. `long long int`
11. `unsigned long long int`
12. `signed long long int`

For each type, I'll provide:

- The maximum size in bytes that the type can hold.
- The maximum size represented in hexadecimal, binary, and decimal.
- The numerical limits: maximum, minimum, and lowest values it can hold.

Let's calculate these values.

Here are the details for various integer types in C++:

| Integer Type                      | Max Size (Bytes) | Max Value (Hex)         | Max Value (Binary)                                                      | Max Value (Decimal)        | Min Value (Decimal)        | Lowest Value (Decimal)     |
| --------------------------------- | ---------------- | ----------------------- | ----------------------------------------------------------------------- | -------------------------- | -------------------------- | -------------------------- |
| `int` (assumed int32)             | 4                | 7F-FF-FF-FF             | 11111111-11111111-11111111-1111111                                      | 2,147,483,647              | -2,147,483,648             | -2,147,483,648             |
| `unsigned int` (uint32)           | 4                | FF-FF-FF-FF             | 11111111-11111111-11111111-11111111                                     | 4,294,967,295              | 0                          | 0                          |
| `signed int` (int32)              | 4                | 7F-FF-FF-FF             | 11111111-11111111-11111111-1111111                                      | 2,147,483,647              | -2,147,483,648             | -2,147,483,648             |
| `short int` (int16)               | 2                | 7F-FF                   | 11111111-1111111                                                        | 32,767                     | -32,768                    | -32,768                    |
| `unsigned short int` (uint16)     | 2                | FF-FF                   | 11111111-11111111                                                       | 65,535                     | 0                          | 0                          |
| `signed short int` (int16)        | 2                | 7F-FF                   | 11111111-1111111                                                        | 32,767                     | -32,768                    | -32,768                    |
| `long int` (assumed int64)        | 8                | 7F-FF-FF-FF-FF-FF-FF-FF | 11111111-11111111-11111111-11111111-11111111-11111111-1111111-11111111  | 9,223,372,036,854,775,807  | -9,223,372,036,854,775,808 | -9,223,372,036,854,775,808 |
| `unsigned long int` (uint64)      | 8                | FF-FF-FF-FF-FF-FF-FF-FF | 11111111-11111111-11111111-11111111-11111111-11111111-1111111-111111111 | 18,446,744,073,709,551,615 | 0                          | 0                          |
| `signed long int` (int64)         | 8                | 7F-FF-FF-FF-FF-FF-FF-FF | 11111111-11111111-11111111-11111111-11111111-11111111-1111111-11111111  | 9,223,372,036,854,775,807  | -9,223,372,036,854,775,808 | -9,223,372,036,854,775,808 |
| `long long int` (int64)           | 8                | 7F-FF-FF-FF-FF-FF-FF-FF | 11111111-11111111-11111111-11111111-11111111-11111111-1111111-11111111  | 9,223,372,036,854,775,807  | -9,223,372,036,854,775,808 | -9,223,372,036,854,775,808 |
| `unsigned long long int` (uint64) | 8                | FF-FF-FF-FF-FF-FF-FF-FF | 11111111-11111111-11111111-11111111-11111111-11111111-1111111-111111111 | 18,446,744,073,709,551,615 | 0                          | 0                          |
| `signed long long int` (int64)    | 8                | 7F-FF-FF-FF-FF-FF-FF-FF | 11111111-11111111-11111111-11111111-11111111-11111111-1111111-11111111  | 9,223,372,036,854,775,807  | -9,223,372,036,854,775,808 | -9,223,372,036,854,775,808 |

These values assume a typical modern system with 32-bit `int`, 16-bit `short
int`, and 64-bit `long int` and `long long int`. The maximum and minimum values
are presented in decimal, hexadecimal, and binary formats. Note that the
"minimum" and "lowest" values are the same for these integer types.

## Float values represnetation

Here are the details for the `float` and `double` types in C++, including the
maximum size they can hold in bytes, their maximum size represented in
hexadecimal, binary, and decimal, and the numerical limits (maximum, minimum,
and lowest values they can hold):

| Floating Point Type | Max Size (Bytes) | Max Value (Hex) | Max Value (Binary)                    | Max Value (Decimal)     | Min Value (Decimal)      | Lowest Value (Decimal)   |
| ------------------- | ---------------- | --------------- | ------------------------------------- | ----------------------- | ------------------------ | ------------------------ |
| `float` (float32)   | 4                | 0xFF-FF-7F-7F   | 0b11111111-11111111-01111111-01111111 | 3.4028235e+38           | -3.4028235e+38           | -3.4028235e+38           |
| `double` (float64)  | 8                | 0x00-00-80-7F   | 0b00000000-00000000-10000000-01111111 | 1.7976931348623157e+308 | -1.7976931348623157e+308 | -1.7976931348623157e+308 |

Please note:

- The hexadecimal and binary representations are for the maximum positive value
  these types can hold.
- For floating-point types, the `min` function returns the smallest positive
  normalized value, not the most negative value. The most negative value is the
  same as the lowest value.
- The binary and hexadecimal representations are split into bytes for clarity.

## REFERENCES

- [HEX-DECMIAL-BINARY-OCT Calculator](https://www.rapidtables.com/convert/number/hex-to-decimal.html)
