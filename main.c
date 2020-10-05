#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

//function declaration
void replaceAll(char *str, const char *oldWord, char* newWord);
char* censoring(int noAsterisks);

int main(void){
    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    char path[100];
    
    char buffer[BUFFER_SIZE];

    printf("Enter path of source file: ");
    scanf("%s", path);

    /*  Open all required files */
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");

   /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        perror("\nUnable to open file.\n");
        perror("Please check whether file exists and you have read/write privilege.\n");
        exit(1);
    }

    /*
     * Read line from source file and write to destination
     * file after replacing given word.
     */

    //char* oldWord;
    char toReplace[20];
    printf("what word do you want to bleep out? ");
    scanf("%s", toReplace);

    char* newWord;
    newWord = (char *)malloc(sizeof(char));
    //int noWords = (255 * numToReplace * sizeof(char))/(sizeof(char) * 255);
    
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
            int noAsterisks = strlen(toReplace);
            //printf("%d \n", noAsterisks);
            newWord = (char *)realloc(newWord, noAsterisks*sizeof(char));
            replaceAll(buffer, toReplace, newWord);
            // After replacing write it to temp file.
            fputs(buffer, fTemp);
            
    }
    free(newWord);

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(path);

    /* Rename temp file as original file */
    rename("replace.tmp", path);
    printf("\nSuccessfully replaced all occurances of %s\n", toReplace);
    return 0;
}

/**
 * Replace all occurrences of a given a word in string.
 */
void replaceAll(char *str, const char *oldWord, char* newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    //to replace the old word with the same amount of asterisks
    owlen = strlen(oldWord);
    for(int i = 0; i < owlen; i++){
	    *(newWord + i) = '*';
    }
    *(newWord + owlen) = '\0';

    /*
     * Repeat till all occurrences are replaced.
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word
        strcat(str, newWord);

        // Concatenate str with remaining words after
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}
