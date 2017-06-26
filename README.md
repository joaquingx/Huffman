# Huffman Encoding and Decoding
![Bugs](https://img.shields.io/badge/Bugs-Free*-green.svg)

An implementation in C++ that use the [Huffman Algorithm](https://en.wikipedia.org/wiki/Huffman_coding) for compress and decompress data.
### How to build
Follow this steps carefully!(because some paths are hardcoded)
```sh
  $ git clone https://github.com/joaquingx/Huffman-Encoding-Decoding.git
  $ cd Huffman-Encoding-Decoding
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
```

### Usage

```sh
Usage:  ./Huffman OPTIONS input-file [output-file]

OPTIONS
        -e
                Encode.
        -d
                Decode.
        -t
                Print the Conversion table used.
        -b
                Print the output in Binary Representation, Tree and Text Enconding.
        -h
                Print how the tree is enconded.

EXAMPLES
        ./Huffman -ctb Text.txt
                  Encode the file Text.txt to compress.huffman, prints the conversion table
                  and the binary representation of the output .
        ./Huffman -d compress.huffman decompress.bmp
                  Decode the file compress.huffman to decompress.bmp .
        ./Huffman -cp Image.bmp EncodingImage.ll
                  Encode the file Image.bmp to EncodingImage.ll and shows the progress .
```




