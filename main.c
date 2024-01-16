#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char array[30000];
char* ptr = array;

int find_closing_brace(char* instructions, int length, int opening_brace) {
    // given instructions, length of instructions and index of opening brace, return index of corresponding closing brace
    // return -1 if corresponding brace not found

    int tofind = 0; // number of additional opening braces encountered
    for (int i = opening_brace; i < length; i++) {
        char chr = instructions[i];
        if (chr == "["[0]) {
            tofind++; // Will always run at least once for the provided opening brace
        } else if (chr == "]"[0]) {
            tofind--;
        }
        if (tofind == 0) {
            return i;
        }
    }
    return -1;
}


int find_opening_brace(char* instructions, int length, int closing_brace) {
    // given instructions, length of instructions and index of closing brace, return index of corresponding opening brace
    // return -1 if corresponding brace not found

    int tofind = 0;
    for (int i = closing_brace; i >= 0; i--) {
        char chr = instructions[i];
        if (chr == "]"[0]) {
            tofind++; // Will always run at least once for the provided closing brace.
        } else if (chr == "["[0]) {
            tofind--;
        }
        if (tofind == 0) {
            return i;
        }
    }
    return -1;
}


int parse_instructions(char* instructions) {
    char inpt;
    int length = strlen(instructions);
    int i = 0; // position in instructions
    while (i < length) {
        int next_i = i + 1;
        char chr = instructions[i];

        // Simple instructions
        if (chr == "+"[0]) {
            (*ptr)++;
        } else if (chr == "-"[0]) {
            (*ptr)--;
        } else if (chr == "."[0]) {
            printf("%c", *ptr);
        } else if (chr == ","[0]) {
            scanf("%c", &inpt);

        // Moving pointer
        } else if (chr == ">"[0]) {
            if (ptr + 1 >= array + 30000) {
                printf("ERROR: trying to access memory outside of allocated array (offset: %d)\n", ptr + 1 - array);
                return -1;
            } else {
                ptr++;                
            }
        } else if (chr == "<"[0]) {
            if (ptr - 1 < array) {
                printf("ERROR: trying to access memory outside of allocated array. (offset: %d)\n", ptr - 1 - array);
                return -1;
            } else {
                ptr--;
            }

        // Looping instructions
        } else if (chr == "["[0]) {
            if (*ptr == 0) {
                int closing_brace = find_closing_brace(instructions, length, i);
                if (closing_brace == -1) {
                    printf("ERROR: No closing brace found for opening brace at %d\n", i);
                    return -1;
                }
                next_i = closing_brace + 1; // add 1 to prevent infinite looping
            }
        } else if (chr == "]"[0]) {
            int opening_brace = find_opening_brace(instructions, length, i);
            if (opening_brace == -1) {
                printf("ERROR: No opening brace found for closing brace at %d\n", i);
            }
            next_i = opening_brace;
        }

        i = next_i;
    }
    return 0;
}


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("%s\n", "ERROR: main must have ONE argument: (./main <input>)");
        exit(0);
    }
    char* user_input = argv[1];
    parse_instructions(user_input);
    exit(0);
}