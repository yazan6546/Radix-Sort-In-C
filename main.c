
/*
 * name :
 * id :
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * doubly linked list structure
 */
struct node_list {
    int length;
    char *data;
    struct node_list* next;
    struct node_list *previous;
};

void showMenu ();


/*
 * Set of functions whose purpose is to supply the library of linked list
 */
struct node_list* makeEmpty_list(struct node_list* L);  //create an empty list
struct node_list* fromArray(char** array, int length); //convert an array into a linked list
char ** toArray (struct node_list *L); //convert a linked list into an array
void deleteList_list(struct node_list* L); //delete a list
int isEmpty_list(struct node_list* L); //check if a list is empty
void printList_list(struct node_list* L); //print the contents of the list
void addLast_list(struct node_list* L, char* data); //add an element at the end of the list
int isLast_list(struct node_list* L, struct node_list* p); //return whether a given node is the last in the list
struct node_list* findPrevious_int (struct node_list* L, char* data); //find the string preceding a given string
struct node_list* remove_string (struct node_list* L, char* data); //remove the first node that has a matched string to the supplied one
void deleteNode (struct node_list* p); //delete the given node

struct node_list* loadStrings (FILE *p); //load the strings and save them in a linked list
int map (char c); //mapped a given character to an index from 0 to 52
void radixSort (struct node_list **list); //perform radix sort on the given list
void deleteArray (char **array, int length); //delete the given array
void emptyList(struct node_list* L); //empty the given list
void printToFile (struct node_list *list, FILE *q); //print the contents of the list to the given file


int main () {

    int number;
    FILE *p = fopen("in put.txt", "r");
    struct node_list* temp1;
    if (p == NULL) {
        perror("FILE");
        exit(1);
    }
    struct node_list *strings_unsorted;
    struct node_list *strings_sorted;

    //loop that controls the menu
    for (;;) {

        showMenu(); //display the main menu

        scanf("%d", &number); //controls the operation chosen.

        switch (number) {

            //Option 1 : loads the strings from input.txt into a linked list of strings
            case 1: {
                printf("Loading strings...\n");
                strings_unsorted = loadStrings(p);      //loads the strings into this list
                fclose(p);
                p = fopen("input.txt", "r");
                strings_sorted = loadStrings(p);
                printf("The strings have been loaded from input.txt\n\n");
                break;
            }

                //Option 2 : Print the strings before sorting
            case 2 : {
                printf("Unsorted strings : \n");
                printList_list(strings_unsorted);
                printf("\n");
                break;
            }
            //Option 3 : Sort the strings using radix sort
            case 3 : {
                printf("Sorting strings...\n");
                radixSort(&strings_sorted);
                printf("Strings have been sorted\n\n");
                break;
            }

            //Option 4 : print the sorted strings
            case 4: {
                printf("Sorted strings : \n");
                printList_list(strings_sorted);
                printf("\n\n");
                break;
            }

            //Option 5 : add a new word to the list of sorted strings and sort
            case 5 : {
                char *string = calloc(31, 1);
                if (string == NULL) {
                    printf("out of memory!\n");
                    exit(1);
                }
                printf("Enter the word that you want to add: \n");
                scanf("%s", string);
                printf("Sorting in progress...\n");
                addLast_list(strings_sorted, string);
                addLast_list(strings_unsorted, string);
                radixSort(&strings_sorted);
                printf("Sorted successfully...\n");
                printList_list(strings_sorted);
                break;

            }

                //Option 6 : delete a word from the list
            case 6 : {
                printf("Enter the word that you want to delete : \n");
                char string[31];

                scanf("%s", string);
                printf("press 1 if you want to delete all occurrences\n"
                              "2 if only the first occurrence\n");
                scanf("%d", &number);
                if (number == 2) {          //remove only the first occurrence of the string from the list
                    temp1 =  remove_string(strings_sorted, string);
                    remove_string(strings_unsorted, string);

                    if (temp1 == NULL) {
                        printf("This string does not exist.\n\n");
                    }
                }
                else if (number == 1) {     //remove all occurrences of the string
                    temp1 = remove_string(strings_sorted, string);
                    remove_string(strings_unsorted, string);

                    if (temp1 == NULL) {
                        printf("This string does not exist.\n\n");
                    }

                    while (temp1 != NULL) {
                        remove_string(strings_sorted, string);
                        remove_string(strings_unsorted, string);
                        temp1 = temp1->next;
                    }

                }
                else {
                    printf("invalid option\n\n");
                }
                break;

            }

            //Option 7 : save the strings to an output file
            case 7 : {
                FILE *output = fopen("output.txt", "w");
                printf("Printing to output.txt...\n");
                printToFile(strings_sorted, output);
                printf("Output printed.\n\n");
                fclose(output);
                break;
            }

                //Option 8 : exit program
            case 8 : {

                printf("Terminating program...");
                deleteList_list(strings_unsorted);
                deleteList_list(strings_sorted);
                fclose(p);
                exit(0);
            }
            default: {
                printf("Invalid input.\n\n");
            }
        }


    }


}


/*
 * Function that displays the main menu of the program
 */

void showMenu () {

    printf("******* Radix sort program *******\n\n");
    printf("1- Load strings from file.\n");
    printf("2- Print strings before sorting.\n");
    printf("3- Sort the strings\n");
    printf("4- Print the sorted strings.\n");
    printf("5- Add a new word to the list of sorted strings.\n");
    printf("6- Delete a word from the sorted strings.\n");
    printf("7- Save to output file.\n");
    printf("8- Exit.\n");

    printf("Choose one of the options above:\n");

}
/*
 * Function that creates an empty list given a list pointer
 */
struct node_list* makeEmpty_list(struct node_list* L) {     //makeEmpty_list

    if (L != NULL) {        //L points to some head node_list
        deleteList_list(L);
    }
    L = malloc(sizeof(struct node_list));
    L->length = 0;

    if (L == NULL) { //if malloc fails
        printf("out of memory!\n");
        exit(1);
    }

    L -> next = NULL;
    L->previous = NULL;
    return L;
}


/*
 * Function that converts an array of strings into a list of strings. Parameter :
 * an array of pointer to characters that represents the array of strings, length of the array
 */

struct node_list* fromArray(char** array, int length) {

    struct node_list* L = NULL;
    L = makeEmpty_list(L);          //create an empty list

    for (int i = 0;i<length;i++) {          //traverse the array
        char *temp = calloc(31, 1);
        if (temp == NULL) {
            printf("malloc failed.\n");
            exit(1);
        }
        strcpy(temp, array[i]);     //copy the string from the array into the linked list (should
                                                //use strcpy just to avoid dangling pointers
        addLast_list(L, temp);
    }

    return L;
}

/*
 * Function that converts a list of strings into an of strings. Parameter :
 * a list pointer that does not point to an allocated memory location.
 */
char ** toArray (struct node_list *L) {
    int index = 0;

    char **array = malloc(L->length * sizeof(char*));       //allocate n pointer to char where n is the length of the list
    if (array == NULL) {
        printf("malloc failed.\n");
        exit(1);
    }

    struct node_list *p = L->next;
    if (isEmpty_list(L)) {
        printf("The list is empty.\n");
        return NULL;
    }
    while (p != NULL) {
        char *data = calloc(31, 1);     //allocate a string of 31 characters for each pointer
        if (data == NULL) {
            printf("malloc failed.\n");
            exit(1);
        }
        strcpy(data, p->data);
        array[index] = data;
        index++;
        p = p->next;

    }
    return array; //return the allocated array of strings
}

/*
 * Function that takes a linked list and deletes it from memory
 */
void deleteList_list(struct node_list* L) {

    struct node_list* p;
    p = L -> next;
    L -> next = NULL;
    free(L); //delete the head

    while (p!=NULL) { //delete each node in the list
        struct node_list* temp = p->next;
        deleteNode(p);
        p = temp;
    }
}

/*
 * Function that returns whether a given list is empty or not
 */
int isEmpty_list(struct node_list* L) {
    return L->next == NULL;
}



/*
 * Function that takes a list and a string, and adds that string to the
 * end of the list
 */

void addLast_list(struct node_list* L, char* data) {

    struct node_list* newNode = malloc(sizeof(struct node_list));

    if (newNode == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    struct node_list* p = L;
    while (!isLast_list(L, p)) {
        p = p->next;
    }

    char *temp = calloc(31, 1);

    strcpy(temp, data);

    p->next = newNode;
    newNode -> next = NULL;
    newNode->previous = p;
    newNode -> data = temp;
    L->length++;
    newNode->length = 0;
}

/*
 * Function that prints the contents of the list
 */
void printList_list(struct node_list* L) {

    for (struct node_list* p = L->next; p != NULL; p = p->next) {
        printf("%s ", p->data);
    }
    printf("\n");
}
/*
 * Function that returns whether a given node is the last
 * node in the list or not
 */
int isLast_list(struct node_list* L, struct node_list* p) {

    return (p->next == NULL);
}

/*
 * Function that removes the first occurrence of this string from the last. Returns
 * the head node if successful, NULL otherwise
 */
struct node_list* remove_string (struct node_list* L, char* data) {

    struct node_list* prev = findPrevious_int(L, data);

    if (prev == NULL) {
        return NULL;
    }
    struct node_list *temp = prev -> next;
    prev -> next = temp -> next;

    L->length--;
    deleteNode(temp);
    return L;
}
/*
 * Function that takes a node and frees it from memory
 */
void deleteNode (struct node_list* p) {
    free(p->data);
    free(p);
}

/*
 * Function that returns the node preceding the node pointing to
 * the first occurrence of the string
 */
struct node_list* findPrevious_int (struct node_list* L, char* data) {

    struct node_list* p = L;
    int flag = 0;

    while (p -> next != NULL) {                      //continue executing until p is the last node
        if (strcmp(p->next->data, data) == 0) {     //check if the next node contains an identical string
            flag = 1;
            break;
        }
        p = p->next;
    }

    return flag? p : NULL; //return the node if found, NULL otherwise
}


/*
 * Function that takes a file pointer and returns a
 * linked list containing all the strings contained
 * in that file
 */
struct node_list* loadStrings (FILE *p) {

    struct node_list *L = NULL;
    L = makeEmpty_list(L); //create an empty list


    char *string = calloc(31, 1);                //allocate 31 characters for each string
    while((fscanf(p, "%s", string)) != EOF) {               //continue reading strings until reaching the end of file
        addLast_list(L, string);                                      //add the scanned string to the end of the list
    }
    return L;
}

/*
 * Function that takes a pointer to a list and returns a sorted list of strings by means
 * of radix sort. Works by first creating a temporary array that contains the different stages of sorting, wherein
 * in the ith stage the strings are loaded index-wise into the array of linked lists (with each index determined by the map function of
 * each the 31 - ith character of the string), and then loaded into the temporary array in the ascending order of indices. This
 * operation will take O(n*K) where n is the number of letters of the string, and K is the number of strings
 */
void radixSort (struct node_list **list) {

    char **array = toArray(*list);                   //create a temporary array
    int pointer_array = 0, length = (*list)->length;
    struct node_list* index [63];                         //create an array of linked lists
    for (int i = 0; i<63;i++) {                        //initialize all linked lists
        index[i] = NULL;
        index[i] = makeEmpty_list(index[i]);
    }

    /*
     * pick each character of the strings. Each iteration of the outer loop represents
     * the j th letter of the string, so when j = 30, we are comparing the 30th letter
     * and because the maximum length is 30, we can assume that all strings are 30 letters long
     */
    for (int j = 30;j>=0;j--) {

        /*
         * Pick each string and add to an array of linked lists. The jth letter determines
         * what index it will be added to, for example, if the string is ahmad, and we are at the fifth letter
         * then ahmad will be added to the linked list of index map('d') which is 23.
         */
        for (int i = 0; i < length; i++) {
            char *string = array[i];                                //get the ith string in the array to be sorted
            int mapped_value = map(string[j]);                    //get the index of the array using map function
            addLast_list(index[mapped_value], string);      //add the string to the linked list at the index determined by map
        }
        /*
         * Get the strings added to the array of linked lists and add them one by one to the temp array
         */
        for (int i = 0;i<63;i++) {

            if (!isEmpty_list(index[i])) {
                struct node_list *p = index[i]->next;       //iterate on each index of the array of linked lists

                while (p != NULL) {         //continue executing until getting all elements of each linked list
                    strcpy(array[pointer_array++], p->data);
                    p = p->next;
                }
                emptyList(index[i]);
            }
        }
        pointer_array = 0;


    }
    deleteList_list(*list);
    *list = fromArray(array, length);
    deleteArray(array, length);

    for (int i = 0;i<63;i++) {
        deleteList_list(index[i]);
    }

}

/*
 * Function that takes a letter and maps it to a value between 0 and 62. The null character takes value 0
 * uppercase letters take from 11-36, and lowercase from 37 to 62, in  alphabetic order, so A = 11, B = 12 and so on
 */

int map (char c) {

    if (isupper(c)) {
        return c - 'A' + 1 + 10;             //adding 1 to make index 0 for null char
    }
    else if (islower(c)) {
        return c - 'a' + 1 + 26 + 10;       //adding 1 to make index 0 for null char
    }
    else if (isdigit(c)) {
        return c - '0' + 1;
    }
    else if (c == '\0') {
        return 0;
    }

}

/*
 * Function that takes a dynamically allocated array of strings and deletes it
 * along with its contents
 */
void deleteArray (char **array, int length) {
    for (int i = 0;i<length;i++) {      //free each string of this array
        free(array[i]);
    }
    free(array);
}
/*
 * Function that takes a list and deletes all of its nodes
 */
void emptyList(struct node_list* L) {
    struct node_list* p;
    p = L -> next;
    L -> next = NULL;

    while (p!=NULL) {
        struct node_list* temp = p->next;
        deleteNode(p);
        p = temp;
    }
}
/*
 * Function that takes a list along with a file pointer and prints
 * the contents of such array to an output file vertically
 */
void printToFile (struct node_list *list, FILE *q) {
    struct node_list *temp = list->next;
    while (temp != NULL) {
        fprintf(q, "%s\n", temp->data);
        temp = temp->next;
    }
}