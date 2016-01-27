# Dynamic Huffman coding

![Version](https://img.shields.io/badge/version-1.0.1-brightgreen.svg)

This program aims to compress file using *dynamic Huffman coding*.

This is a school project for *Polytech Marseille*.

## API

### io.s

This module handles operations onto files.

It is used to read from file and write to file. An important part is that it is able to write and read one bit at a time in a seamless way for other module.

#### Reading

The module reads from file `./input.file`

At the begining, the following function must be called to initialize reading.

``` c
int create_reader()
```

Return `1` on error, `0` otherwise.

---

After that, the following functions can be called to perfom reading operations

``` c
int read_byte()
```

Return the next byte readed from file. The value can be a number in `[0, 256[` or `EOF`.

---

``` c
int read_bit()
```

Return the next bit readed from file. The value can be a number in `[0, 1]` or `EOF`.

---

At the end, the following function must be called to terminate reading.

``` c
int delete_reader()
```

Return `1` on error, `0` otherwise.



#### Writing

The module writes to file `./output.file`

At the begining, the following function must be called to initialize writing.

``` c
int create_writer()
```

Return `1` on error, `0` otherwise.

---

After that, the following functions can be called to perfom writing operations

``` c
int write_byte(int byte)
```

- `byte` a value in `[0,256[` to write

Return `1` on error, `0` otherwise.

---

``` c
int write_bit(int bit)
```

- `bit` a value in `[0,1]` to write

Return `1` on error, `0` otherwise.

---

At the end, the following function must be called to terminate writing.

``` c
int delete_writer()
```

Return `1` on error, `0` otherwise.



