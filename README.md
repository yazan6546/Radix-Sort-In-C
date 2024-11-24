# Radix Sort Program

This repository contains a C program that performs radix sort on a list of strings. The program allows users to load strings from a file, sort them using radix sort, and perform various operations on the list of strings.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Functions](#functions)
6. [File Structure](#file-structure)
7. [Contributing](#contributing)
8. [License](#license)

## Introduction

The radix sort program is designed to sort a list of strings using the radix sort algorithm. It provides a menu-driven interface for users to load strings from a file, sort them, print them, add new strings, delete strings, and save the sorted strings to an output file.

## Features

- Load strings from a file
- Print unsorted strings
- Sort strings using radix sort
- Print sorted strings
- Add a new word to the list of sorted strings
- Delete a word from the sorted strings
- Save sorted strings to an output file
- Exit the program

## Installation

To compile and run the program, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yazan6546/Radix-Sort-In-C.git
    ```
2. Navigate to the repository directory:
    ```sh
    cd Radix-Sort-In-C
    ```
3. Compile the program:
    ```sh
    gcc -o radix_sort main.c
    ```
4. Run the program:
    ```sh
    ./radix_sort
    ```

## Usage

1. Create a file named `input.txt` and store the strings to be sorted in this file, each string on a new line.
2. Run the program:
    ```sh
    ./radix_sort
    ```
3. Upon running the program, a menu will be displayed with the following options:

    1. Load strings from file.
    2. Print strings before sorting.
    3. Sort the strings.
    4. Print the sorted strings.
    5. Add a new word to the list of sorted strings.
    6. Delete a word from the sorted strings.
    7. Save to output file.
    8. Exit.

4. Select an option by entering the corresponding number.

## Functions

The program includes the following functions:

- `void showMenu()`: Displays the main menu of the program.
- `struct node_list* makeEmpty_list(struct node_list* L)`: Creates an empty list.
- `struct node_list* fromArray(char** array, int length)`: Converts an array into a linked list.
- `char** toArray(struct node_list* L)`: Converts a linked list into an array.
- `void deleteList_list(struct node_list* L)`: Deletes a list.
- `int isEmpty_list(struct node_list* L)`: Checks if a list is empty.
- `void printList_list(struct node_list* L)`: Prints the contents of the list.
- `void addLast_list(struct node_list* L, char* data)`: Adds an element at the end of the list.
- `int isLast_list(struct node_list* L, struct node_list* p)`: Returns whether a given node is the last in the list.
- `struct node_list* findPrevious_int(struct node_list* L, char* data)`: Finds the string preceding a given string.
- `struct node_list* remove_string(struct node_list* L, char* data)`: Removes the first node that has a matched string to the supplied one.
- `void deleteNode(struct node_list* p)`: Deletes the given node.
- `struct node_list* loadStrings(FILE* p)`: Loads the strings and saves them in a linked list.
- `int map(char c)`: Maps a given character to an index from 0 to 62.
- `void radixSort(struct node_list** list)`: Performs radix sort on the given list.
- `void deleteArray(char** array, int length)`: Deletes the given array.
- `void emptyList(struct node_list* L)`: Empties the given list.
- `void printToFile(struct node_list* list, FILE* q)`: Prints the contents of the list to the given file.

## File Structure

- [`main.c`](main.c): Contains the implementation of the radix sort program.
- [`README.md`](README.md): Contains the documentation for the project.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.