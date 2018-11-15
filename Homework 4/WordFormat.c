#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cmpfunc(const void *a, const void *b) {
    const char **ia = (const char **) a;
    const char **ib = (const char **) b;
    return strcmp(*ia, *ib);
    /* strcmp functions works exactly as expected from
     *    comparison function */
}

int main(int argc, char *argv[]) {
    FILE *file; /*pointer file to output document*/
    FILE *cwfile;  /*count words pointer file*/
    FILE *rfile;   /*pointer to input file to be copied and formatted*/

    //Imported from dot.h file
    char s[60];
    /*const char *w[60];*/
    char wurd[60];
    char c;
    int i;
    int sigma;
    int wcar;
    char **wl;
    int l;
    int k;


    typedef struct {
        int count;
        char car;
        enum flop {
            OFF, ON
        } flip;
    } hash;

    /*the following declares a wordlist pointer to pointer of strings*/
    char **wordlist = malloc(sizeof(char *));

    /*pointer to properly indented output*/
    sprintf(s, "%s.out", argv[2]);
    if ((file = fopen(s, "w+")) == NULL)
        puts("Failed opening file");

    /*pointer counts words into file.words*/
    sprintf(s, "%s.words", argv[2]);
    if ((cwfile = fopen(s, "w+")) == NULL)
        puts("Failed opening file");

    /*open specified file for reading*/
    rfile = fopen(argv[2], "r");

    /*Verify if input format from user is correct*/
    if (argc != 3 || !isdigit(*argv[1]))
        puts("Incorrect number or types");


    /*process the file into the resultant file.out in proper format
     * also, counts the number of ocurrences per word*/
    i = 1;  /*counts the number of words in read file*/
    wcar = 0;  /*counts the number of characters per word*/
    sigma = 0; /*counter of word chars which resets when > argv [ 1 ]*/
    while ((c = (char) fgetc(rfile)) != EOF) {
        /*word size summation, resets when reaches line limit*/
        if ((sigma += wcar) > (atoi(argv[1]) + 1))
            sigma = wcar;


        /*resets word temporary storer and word character counter*/
        wurd[0] = 0;
        wcar = 0;
        /*concatenate one word to string variable*/
        while ((c != ' ' && c != '\n')) {
            if (c == EOF)
                break;

            /*string concatenation can use only an array of chars not a pointer*/
            strcat(wurd, &c);
            c = (char) fgetc(rfile);
            wcar++;
        }
        wcar++; /*counts for the \n or space*/

        /*parses each line to a limit of argv [ 1 ] chars,
         * where 25 <= argv [ 1 ] <= 60*/
        if ((sigma + wcar) > (atoi(argv[1]) + 1))
            fprintf(file, "\n");


        /*stores each word to file.out*/
        fprintf(file, "%s ", wurd);
        wordlist[i] = strdup(wurd);
        i++;

        /*adds memory for wordlist to store another word*/
        wordlist = realloc(wordlist, (i + 1) * sizeof(char *));
    }

    /*allocates space to store words in run-time*/
    wl = malloc(sizeof(char *));

    for (l = 1; l < i; l++) {
        wl[l - 1] = strdup(wordlist[l]);
        wl = realloc(wl, (l + 1) * sizeof(char *));
    }

    /*quick sorts the list of words in ascending order*/
    qsort(wl, (size_t) (i - 1), sizeof(char *), cmpfunc);

    /*prints all the words to count words file in alphabetical order*/
    k = 1;
    for (l = 1; l < i - 1; l++) {
        if (strcmp(wl[l - 1], wl[l]) == 0) {
            k++;
        } else {
            fprintf(cwfile, "%s - %d\n", wl[l - 1], k);
            k = 1;
        }
    }
    /*prints the last word occurrence*/
    fprintf(cwfile, "%s - %d\n", wl[l - 1], k);

    fclose(file);
    fclose(cwfile);
    fclose(rfile);
    return 0;
}
