#define _SVID_SOURCE
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

int comparisonFunction(const void *, const void *);

int main(int argc, char *argv[]) {

    char s[60]; //buffer for files
    char tempBuffer[60]; //array of chars for formatted string
    char c; //holds character at a time from input file
    int i = 1; //counts the number of words in read file
    int sigma = 0; //counter of word chars which resets when > argv[1]
    int wordCharCount = 0; //counts the number of characters per word
    char **wl = malloc(sizeof(char *)); //allocates space to store words in run-time
    int l = 0; //used to print last word and occurences in the file
    int k = 1; //count for occurence of each word in file
    int charPerLine = atoi(argv[1]);

    FILE *file; //Pointer to formatted output file
    FILE *cwfile; //Pointer to file that will have counted words.
    FILE *rfile; //Pointer to input file.

    //Will be used as buffer for final output file aka *file
    char **wordlist = malloc(sizeof(char *));

    //pointer to properly indented output
    sprintf(s, "%s.out", argv[2]);
    if ((file = fopen(s, "w+")) == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    //pointer counts words into file.words
    sprintf(s, "%s.words", argv[2]);
    if ((cwfile = fopen(s, "w+")) == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    //open specificed file for reading
    if ((rfile = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    //Input validation
    if (argc != 3 || !isdigit(*argv[1])) {
        fprintf(stderr, "Error! Correct usage: ./WordFormat <character per line> <input_file>\n");
        exit(1);
    }

    /*process the file into the resultant file.out in proper format
     * also, counts the number of occurrences per word*/
    while ((c = (char) fgetc(rfile)) != EOF) {
        //word size summation, resets when reaches line limit
        if ((sigma += wordCharCount) > (charPerLine + 1)) {
            sigma = wordCharCount;
        }

        //resets word temporary storer and word character counter
        tempBuffer[0] = 0;
        wordCharCount = 0;
        //This while loop will concatenate each letter into words and adds to tempBuffer
        while ((c != ' ' && c != '\n')) {
            if (c == EOF)
                break;

            //string concatenation can use only an array of chars not a pointer
            strcat(tempBuffer, &c);
            c = (char) fgetc(rfile);
            wordCharCount++;
        }
        wordCharCount++; /*counts for the \n or space*/

        /*parses each line to a limit of argv[1] chars,
         * where 25 <= argv[1] <= 60*/
        if ((sigma + wordCharCount) > (charPerLine + 1))
            fprintf(file, "\n");

        //stores each word to file.out
        fprintf(file, "%s ", tempBuffer);
        wordlist[i] = strdup(tempBuffer);
        i++;

        //adds memory for wordlist to store another word
        wordlist = realloc(wordlist, (i + 1) * sizeof(char *));
    }


    for (int j = 1; j < i; j++) {
        wl[j - 1] = strdup(wordlist[j]);
        wl = realloc(wl, (j + 1) * sizeof(char *));
    }

    //quick sorts the lsit of words in ascending order
    qsort(wl, (size_t) i - 1, sizeof(char *), comparisonFunction);

    //prints all the words to count words file in alphabetical order
    for (int m = 1; m < i - 1; m++) {
        if (strcmp(wl[m - 1], wl[m]) == 0) {
            k++;
        } else {
            fprintf(cwfile, "%s - %d\n", wl[m - 1], k);
        }
    }

    //prints the last word occurrence
    fprintf(cwfile, "%s - %d\n", wl[l - 1], k);

    fclose(file);
    fclose(cwfile);
    fclose(rfile);

    return 0;
}

int comparisonFunction(const void *a, const void *b) {
    const char **ia = (const char **) a;
    const char **ib = (const char **) b;
    return strcmp(*ia, *ib);
}
