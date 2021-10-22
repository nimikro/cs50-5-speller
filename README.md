# cs50-5-speller
This is a command line application developed in C# that implements a program that spell-checks a file, using a hash table.. This is an exercise for Harvard's CS50 online course.

# Table of contents
1. [Speller](#Speller)
2. [Understanding](#Understanding)
3. [Specification](#Specification)

# Speller
Implements a program that spell-checks a file, a la the below, using a hash table.
```
$ ./speller texts/lalaland.txt
MISSPELLED WORDS

[...]
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT
[...]
Shangri
[...]
fianc
[...]
Sebastian's
[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
```

# Understanding
Theoretically, on input of size n, an algorithm with a running time of n is “asymptotically equivalent,” in terms of O, to an algorithm with a running time of 2n. Indeed, when describing the running time of an algorithm, we typically focus on the dominant (i.e., most impactful) term (i.e., n in this case, since n could be much larger than 2). In the real world, though, the fact of the matter is that 2n feels twice as slow as n.

The challenge ahead of you is to implement the fastest spell checker you can! By “fastest,” though, we’re talking actual “wall-clock,” not asymptotic, time.

In `speller.c`, we’ve put together a program that’s designed to spell-check a file after loading a dictionary of words from disk into memory. That dictionary, meanwhile, is implemented in a file called `dictionary.c`. (It could just be implemented in `speller.c`, but as programs get more complex, it’s often convenient to break them into multiple files.) The prototypes for the functions therein, meanwhile, are defined not in `dictionary.c` itself but in `dictionary.h` instead. That way, both `speller.c` and `dictionary.c` can #include the file.

## `dictionary.h`
Open up `dictionary.h`, and you’ll see a few lines that mention `DICTIONARY_H`. No need to worry about those, but, if curious, those lines just ensure that, even though `dictionary.c` and `speller.c` (which you’ll see in a moment) `#include` this file, `clang` will only compile it once.

Next notice how we #include a file called stdbool.h. That’s the file in which bool itself is defined. You’ve not needed it before, since the CS50 Library used to #include that for you.

Also notice our use of `#define`, a “preprocessor directive” that defines a “constant” called `LENGTH` that has a value of `45`. It’s a constant in the sense that you can’t (accidentally) change it in your own code. In fact, `clang` will replace any mentions of `LENGTH` in your own code with, literally, `45`. In other words, it’s not a variable, just a find-and-replace trick.

Finally, notice the prototypes for five functions: `check`, `hash`, `load`, `size`, and `unload`. Notice how three of those take a pointer as an argument, per the *:
```
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
```
Recall that `char *` is what we used to call `string`. So those three prototypes are essentially just:
```
bool check(const string word);
unsigned int hash(const string word);
bool load(const string dictionary);
```
And `const`, meanwhile, just says that those strings, when passed in as arguments, must remain constant; you won’t be able to change them, accidentally or otherwise!

## `dictionary.c`
Now open up `dictionary.c`. Notice how, atop the file, we’ve defined a `struct` called `node` that represents a node in a hash table. And we’ve declared a global pointer array, `table`, which will represent the hash table we will use to keep track of words in the dictionary. The array contains `N` node pointers.

Next, we’ve implemented `load`, `hash`, `check`, `size`, and `unload`.

## `speller.c`
Okay, next open up `speller.c` and spend some time looking over the code and comments therein. You won’t need to change anything in this file, and you don’t need to understand its entirety, but do try to get a sense of its functionality nonetheless. Notice how, by way of a function called `getrusage`, we’ll be “benchmarking” (i.e., timing the execution of) your implementations of `check`, `load`, `size`, and `unload`. Also notice how we go about passing `check`, word by word, the contents of some file to be spell-checked. Ultimately, we report each misspelling in that file along with a bunch of statistics.

Notice, incidentally, that we have defined the usage of `speller` to be
```
Usage: speller [dictionary] text
```
where `dictionary` is assumed to be a file containing a list of lowercase words, one per line, and `text` is a file to be spell-checked. As the brackets suggest, provision of `dictionary` is optional; if this argument is omitted, `speller` will use `dictionaries/large` by default. In other words, running
```
$ ./speller text
```
will be equivalent to running
```
$ ./speller dictionaries/large text
```
where `text` is the file you wish to spell-check. Suffice it to say, the former is easier to type!

Within the default dictionary, mind you, are 143,091 words, all of which must be loaded into memory! In fact, take a peek at that file to get a sense of its structure and size. Notice that every word in that file appears in lowercase (even, for simplicity, proper nouns and acronyms). From top to bottom, the file is sorted lexicographically, with only one word per line (each of which ends with `\n`). No word is longer than 45 characters, and no word appears more than once.

## `texts/`
So that you can test your implementation of `speller`, we’ve also provided you with a whole bunch of texts, among them the script from La La Land, the text of the Affordable Care Act, three million bytes from Tolstoy, some excerpts from The Federalist Papers and Shakespeare, and more. So that you know what to expect, open and skim each of those files.

Now, as you should know from having read over `speller.c` carefully, the output of speller, if executed with, say,
```
$ ./speller texts/lalaland.txt
```
will eventually resemble the below.

Below’s some of the output you’ll see. For information’s sake, we’ve excerpted some examples of “misspellings.” And lest we spoil the fun, we’ve omitted our own statistics for now.
```
MISSPELLED WORDS

[...]
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT
[...]
Shangri
[...]
fianc
[...]
Sebastian's
[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
```
`TIME IN load` represents the number of seconds that `speller` spends executing your implementation of load. `TIME IN check` represents the number of seconds that `speller` spends, in total, executing your implementation of `check`. `TIME IN size` represents the number of seconds that `speller` spends executing your implementation of `size`. `TIME IN unload` represents the number of seconds that `speller` spends executing your implementation of `unload`. `TIME IN TOTAL` is the sum of those four measurements.

Note that these times may vary somewhat across executions of speller, depending on what else CS50 IDE is doing, even if you don’t change your code.

Incidentally, to be clear, by “misspelled” we simply mean that some word is not in the dictionary provided.

## `Makefile`
And, lastly, recall that `make` automates compilation of your code so that you don’t have to execute `clang` manually along with a whole bunch of switches. However, as your programs grow in size, `make` won’t be able to infer from context anymore how to compile your code; you’ll need to start telling `make` how to compile your program, particularly when they involve multiple source (i.e., `.c`) files, as in the case of this problem. And so we’ll utilize a `Makefile`, a configuration file that tells `make` exactly what to do. Open up `Makefile`, and you should see four lines:

1. The first line tells `make `to execute the subsequent lines whenever you yourself execute `make speller` (or just `make`).
2. The second line tells `make` how to compile `speller.c` into machine code (i.e., `speller.o`).
3. The third line tells `make` how to compile `dictionary.c` into machine code (i.e., `dictionary.o`).
4. The fourth line tells `make` to link `speller.o` and `dictionary.o` in a file called `speller`.

# Specification
We implemented, in order, `load`, `hash`, `size`, `check`, and `unload` as efficiently as possible using a hash table in such a way that `TIME IN load`, `TIME IN check`, `TIME IN size`, and `TIME IN unload` are all minimized. To be sure, it’s not obvious what it even means to be minimized, inasmuch as these benchmarks will certainly vary as you feed `speller` different values for `dictionary` and for `text`. Some specifications from us.

* You may not alter `speller.c`, `dictionary.h`, or `Makefile`.
* You may alter `dictionary.c`, but you may not alter the declarations (i.e., prototypes) of `load`, `hash`, `size`, `check`, or `unload`. You may, though, add new functions and (local or global) variables to `dictionary.c`.
* You may change the value of `N` in `dictionary.c`, so that your hash table can have more buckets.
* The implementation of `check` is case-insensitive. In other words, if `foo` is in dictionary, then check returns true given any capitalization thereof; none of `foo`, `foO`, `fOo`, `fOO`, `fOO`, `Foo`, `FoO`, `FOo`, and `FOO` are considered misspelled.
* Capitalization aside, the implementation of `check` only returns true for words actually in `dictionary`. Beware hard-coding common words (e.g., the), lest we pass your implementation a dictionary without those same words. Moreover, the only possessives allowed are those actually in dictionary. In other words, even if `foo` is in dictionary, `check` returns false given `foo's` if `foo's` is not also in dictionary.
* We assume that any dictionary passed to your program will be structured exactly like ours, alphabetically sorted from top to bottom with one word per line, each of which ends with `\n`. We also assume that `dictionary` will contain at least one word, that no word will be longer than `LENGTH` (a constant defined in dictionary.h) characters, that no word will appear more than once, that each word will contain only lowercase alphabetical characters and possibly apostrophes, and that no word will start with an apostrophe.
* We assume that `check` will only be passed words that contain (uppercase or lowercase) alphabetical characters and possibly apostrophes.
* The spell checker may only take `text` and, optionally, `dictionary` as input. Although you might be inclined (particularly if among those more comfortable) to “pre-process” our default dictionary in order to derive an “ideal hash function” for it, you may not save the output of any such pre-processing to disk in order to load it back into memory on subsequent runs of your spell checker in order to gain an advantage.
* The spell checker does not leak any memory. Be sure to check for leaks with `valgrind`.

