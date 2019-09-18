# libataxx
A C++ library for the board game [Ataxx](https://en.wikipedia.org/wiki/Ataxx) written using [bitboards](https://en.wikipedia.org/wiki/Bitboard). Capable of FEN parsing, move generation, board printing, and other things.

## Build
```bash
git clone https://github.com/kz04px/libataxx
cd libataxx
make
```

## Header only
A header only version of libataxx can be found in the 'header_only' folder. This version should be functionally identical.

## Performance
A mid range Intel i5 processor is capable of processing several hundred million nodes per second.

## Limitations
Libataxx is specifically designed for Ataxx on a 7x7 board, as such, it does not support any other board size.

## Usage
Some of the bit twiddling required for bitboards has been abstracted away, but at least a passing knowledge of [bitwise operators](https://en.wikipedia.org/wiki/Bitwise_operation) is recommended. The 'examples' folder contains some basic examples.
