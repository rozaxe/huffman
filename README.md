# Dynamic Huffman coding

![Version](https://img.shields.io/badge/version-2.1.0-brightgreen.svg)

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
Dynamic Huffman Coding - v2.1.0

Usage: huffman [-h] [ [-s] <output_file> (-c|-u) <input_file> ]
  -c, --compress    Compress specified file
  -u, --uncompress  Uncompress specified file
  -s, --silent      Do not show progression and comparison
  -h, --help        Display this message

```
