#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

// Insert your code here...

//------definition of struct node element--------//

typedef struct _nodeElement {
    pKey pElement_key; // not sure if needed...
    pElement pData;
    pNode_Element pNext_node;
} node_element;

//--------definition of struct hash table--------//
typedef struct _Hash {
    int hashTable_size;
    pNode_Element* table_head;
    HashFunc pfunc_search;
    PrintFunc pfunc_print;
    CompareFunc pfunc_compare;
    GetKeyFunc pfunc_getKey;
    DestroyFunc pfunc_destroy;
} hashTable;


//-------------------------------------helping functions-----------------------------------//
void malloc_error()
{
    printf("Error Allocating Memory");
    exit (1);
}
//-----------------------------------------------------------------------------------------//

/*********************************************************************************
Function name: HashCreate
Description: constructor
Parameters: size - size of hash table
            pfunc_search - a pointer to an element searching function
            pfunc_print - a pointer to a printing function
            pfunc_compare - a pointer to a comparing elements function
            pfunc_getKey - a pointer to a getter (of element key) function
            pfunc_destroy - a pointer to a destroy function
Return value: pHash - a pointer to the hash table created
**********************************************************************************/
pHash HashCreate (int size, HashFunc pfunc_search, PrintFunc pfunc_print, CompareFunc pfunc_compare,
                  GetKeyFunc pfunc_getKey, DestroyFunc pfunc_destroy)
{
    pHash p_HashTable = NULL;
    pNode_Element pNodeElement = NULL;
    p_HashTable = (pHash)malloc(sizeof(hashTable)); //is this ok? i'm not sure..
    pNodeElement = (pNode_Element)malloc(size*(sizeof(node_element)));
    if (p_HashTable == NULL || pNodeElement == NULL)
    {
        malloc_error();
    }
    p_HashTable->table_head = pNodeElement;
    return p_HashTable;
}

/*********************************************************************************
Function name: HashAdd
Description: inserts the element given to the hash table in it's appropriate place
Parameters: p_HashTable - a pointer to the hash table
            p_element - a pointer to an element
Return value: Result - FAIL if couldn't add to the table, else SUCCESS
**********************************************************************************/
Result HashAdd (pHash p_HashTable, pElement p_element)
{
    pNode_Element pNode_newElem = NULL;
        //create node for new element:
    pNode_newElem = (pNode_Element)malloc(sizeof(node_element));
    if (pNode_newElem == NULL)
    {
        malloc_error();
    }
        //extract element's key:
    pKey newElem_key = p_HashTable->pfunc_getKey(p_element);
        //assign element's info to node:

    int place_in_hashTable = p_HashTable->pfunc_search(newElem_key, p_HashTable->hashTable_size);
}

/*********************************************************************************
Function name: HashFind
Description: the function searches for an element in the table with the key given
Parameters: p_HashTable - a pointer to the hash table
            p_key - a pointer to the key of an element
Return value: pElement - a pointer to the element with the key given
**********************************************************************************/
pElement HashFind (pHash p_HashTable, pKey p_key)
{
    int place_in_hashTable = p_HashTable->pfunc_search(p_key, p_HashTable->hashTable_size);
    pNode_Element current = *(p_HashTable->table_head + place_in_hashTable);
    while (current != NULL)
    {
        if (p_HashTable->pfunc_compare(p_key, current->pElement_key) == SAME)
        {

        }
    }
}

/*********************************************************************************
Function name: HashRemove
Description: the function removes the element with the key given from the table
Parameters: p_HashTable - a pointer to the hash table
            p_key - a pointer to the key of an element
Return value: Result - FAIL if couldn't remove, else SUCCESS
**********************************************************************************/
Result HashRemove (pHash p_HashTable, pKey p_key)
{
    pNode_Element p_elem_found =
}

/*********************************************************************************
Function name: HashPrint
Description: the function prints the elements in the table
Parameters: p_HashTable - a pointer to the hash table
Return value: Result - FAIL if couldn't print, else SUCCESS
**********************************************************************************/
Result HashPrint (pHash p_HashTable);

/*********************************************************************************
Function name: HashDestroy
Description: the function destroys the hash table
Parameters: p_HashTable - a pointer to the hash table
Return value: Result - FAIL if couldn't destroy, else SUCCESS
**********************************************************************************/
Result HashDestroy (pHash p_HashTable);

