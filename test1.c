#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"
//

pHash ReadDictionary () {
    //This function reads a dictionary line by line from the standard input.
    pHash dictionary;
    char entryLine [100] = "";
    char *word, *translation;

    dictionary = CreateDictionary();

    while (scanf ("%s", entryLine) == 1) { // Not EOF
        word = strtok(entryLine, "=");
        translation = strtok(NULL, "=");
        AddTranslation(dictionary, word, translation);
    }

    return dictionary;
}

int main () {
        //read dictionary from input:
    pHash dict = ReadDictionary;
    if (dict == NULL) return -1;
        //print dictionary:
    if (PrintDictionary (dict) == FAIL) return -1;

    if (DeleteTranslation(dict,"dog") == FAIL) return -1;
    if (DeleteTranslation(dict,"cat") == FAIL) return -1;
    if (DeleteTranslation(dict,"astronaut") == FAIL) return -1;

    if (PrintDictionary (dict) == FAIL) return -1;

    if (AddTranslation(dict, "goat", "ez") == FAIL) return -1;
    if (AddTranslation(dict, "cow", "para") == FAIL) return -1;
    if (AddTranslation(dict, "school", "beitsefer") == FAIL) return -1;
    if (AddTranslation(dict, "boy", "yeled") == FAIL) return -1;

    if (PrintDictionary (dict) == FAIL) return -1;

    if (Translate(dict, "flag") == FAIL) return -1;
    if (Translate(dict, "goat") == FAIL) return -1;
    if (Translate(dict, "school") == FAIL) return -1;
    if (Translate(dict, "apple") == FAIL) return -1;

    if (HashDestroy(dict) == FAIL) return -1;
    return 0;
}
