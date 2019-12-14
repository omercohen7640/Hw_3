#ifndef _DICT_H_
#define _DICT_H_
#define _DIC_SIZE_  25*26; //dictionary size
#define _MAGIC_NUM_ 26; //number four the hash function
#include "hash.h"

typedef struct _Dic *pDic;
typedef struct _Dic_Def *pDicDef;
//
/*********************************************************************************
Function name: HashWord
Description: hash function
Parameters:
 word - word in the dictionary
 size - size of the hash table
Return value: return the index in the hash array of the word.
**********************************************************************************/
int HashWord(char* word, int size);

/*********************************************************************************
Function name: PrintEntry
Description: print a word and traslation of the dictionary
Parameters:
p_dicidef - pointer to a dictionary definition
Return value: return the index in the hash array of the word.
**********************************************************************************/
Result PrintEntry(pDicDef p_dicdef);

/*********************************************************************************
Function name: CompareWords
Description: compare between two words
Parameters:
word1
word2
Return value:return SAME or DIFFERENT.
**********************************************************************************/
CompResult CompareWords(char* word1, char* word2);

/*********************************************************************************
Function name: GetEntryKey
Description: get a definition and return the word
Parameters:
p_dicdef- pointer to a dictionary definition
Return value: return the word
**********************************************************************************/
char* GetEntryKey(pDicDef p_dicdef);

/*********************************************************************************
Function name: DestroyEntry
Description: get a definition and destroy it
Parameters:
p_dicdef- pointer to a dictionary definition
Return value: return FAILURE if something went wrong and SUCCES otherwise
**********************************************************************************/
Result DestroyEntry(pDicDef p_dicdef);

/*********************************************************************************
Function name: CreateDictionary
Description: create a dictionary
Parameters: no parameters
Return value: return pointer to dictionary.
**********************************************************************************/
pDic CreateDictionary();

/*********************************************************************************
Function name: AddTranslation
Description: add definition to the the dictionary
Parameters:
p_dic - pointer to the dictionary
word - word the user want to add
translation - the word's translation
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result AddTranslation(pDic p_dic, char* word, char* translation);

/*********************************************************************************
Function name: Translate
Description: the function search for a definition and print the definition
Parameters:
p_dic - pointer to the dictionary
word - word the user want to print it's definition
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result Translate(pDic p_dic, char* word);

/*********************************************************************************
Function name: DeleteTranslation
Description: the function search for a definition by a word and deletes it
Parameters:
p_dic - pointer to the dictionary
word - word the user want to delete it's definition
Return value: return SUCCESS or FAILURE.
**********************************************************************************/
Result DeleteTranslation(pDic p_dic, char* word);

// Result PrintD

#endif