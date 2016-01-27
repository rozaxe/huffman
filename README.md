# Dynamic Huffman coding

![Version](https://img.shields.io/badge/version-1.0.1-brightgreen.svg)

This program aims to compress file using *dynamic Huffman coding*.

## Usage

To **compress** a file : 

``` shell
$ huffman compressed.bin -c original.txt
```

To **uncompress** a file :

``` shell
$ huffman original.bin -u compressed.bin
```

## Syntax

``` shell
$ huffman --help
Dynamic Huffman Coding - v1.0.1

Usage: huffman (-h | <output_file> (-c|-u) <input_file>)
  -c, --compress    Compress specified file
  -u, --uncompress  Uncompress specified file
  -h, --help        Display this message

```

