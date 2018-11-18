#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

int cmpfunc(const void *, const void *);

int main(int argc, char *argv[]) {

    char s[60];
    const char *w[60];
    char wurd[60];
    char c;
    int i;
    int sigma;
    int wcar;
    char **wl;
    int l = 0;
    int k;

    FILE *file; //pointer file to output document
    FILE *cwfile; //count words pointer file
    FILE *rfile; //pointer to input file to be copied and formatted

    //the following declares a wordlist pointer to pointer of strings
    char **wordlist = malloc(sizeof(char *));

    //pointer to properly indented output
    sprintf(s, "%s.out", argv[2]);
    if ((file = fopen(s, "w+")) == NULL) {
        puts("Failed opening file");
    }

    //pointer counts words into file.words
    sprintf(s, "%s.words", argv[2]);
    if ((cwfile = fopen(s, "w+")) == NULL) {
        puts("Failed opening file");
    }

    //open specificed file for reading
    rfile = fopen(argv[2], "r");

    //Verify if input format from user is correct
    if (argc != 3 || !isdigit(*argv[1])) {
        puts("Incorrect number of types");
    }

    /*process the file into the resultant file.out in proper format
     * also, counts the number of occurrences per word*/
    i = 1; //counts the number of words in read file
    wcar = 0; //counts the number of characters per word
    sigma = 0; //counter of word chars which resets when > argv[1]
    while ((c = fgetc(rfile)) != EOF) {
        //word size summation, resets when reaches line limit
        if ((sigma += wcar) > (atoi(argv[1]) + 1)) {
            sigma = wcar;
        }

        //resets word temporary storer and word character counter
        wurd[0] = 0;
        wcar = 0;
        //concatenate one word to string variable
        while ((c != ' ' && c != '\n')) {
            if (c == EOF)
                break;

            //string concatenation can use only an array of chars not a pointer
            strcat(wurd, &c);
            c = fgetc(rfile);
            wcar++;
        }
        wcar++; /*counts for the \n or space*/

        /*parses each line to a limit of argv[1] chars,
         * where 25 <= argv[1] <= 60*/
        if ((sigma + wcar) > (atoi(argv[1]) + 1))
            fprintf(file, "\n");

        //stores each word to file.out
        fprintf(file, "%s ", wurd);
        wordlist[i] = strdup(wurd);
        i++;

        //adds memory for wordlist to store another word
        wordlist = realloc(wordlist, (i + 1) * sizeof(char *));
    }

    //allocates space to store words in run-time
    wl = malloc(sizeof(char *));

    for (int j = 1; j < i; j++) {
        wl[j - 1] = strdup(wordlist[j]);
        wl = realloc(wl, (j + 1) * sizeof(char *));
    }

    //quick sorts the lsit of words in ascending order
    qsort(wl, (size_t) i - 1, sizeof(char *), cmpfunc);

    //prints all the words to count words file in alphabetical order
    k = 1;
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

int cmpfunc(const void *a, const void *b) {
    const char **ia = (const char **) a;
    const char **ib = (const char **) b;
    return strcmp(*ia, *ib);
}