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
    if (size < 1 || pfunc_search == NULL || pfunc_print == NULL || pfunc_compare == NULL || pfunc_getKey == NULL ||
        pfunc_destroy == NULL) exit (1);
    pHash p_HashTable = NULL;
    pNode_Element pNodeElement = NULL;
    p_HashTable = (pHash)malloc(sizeof(hashTable)); //is this ok? i'm not sure..
    pNodeElement = (pNode_Element)malloc(size*(sizeof(node_element)));
    if (p_HashTable == NULL || pNodeElement == NULL)
    {
        malloc_error();
    }
    p_HashTable->hashTable_size = size;
    p_HashTable->table_head = &pNodeElement;
    p_HashTable->pfunc_search = pfunc_search;
    p_HashTable->pfunc_print = pfunc_print;
    p_HashTable->pfunc_compare = pfunc_compare;
    p_HashTable->pfunc_getKey = pfunc_getKey;
    p_HashTable->pfunc_destroy = pfunc_destroy;
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
    if (p_HashTable == NULL || p_element == NULL) return FAIL;
    pNode_Element pNode_newElem = NULL;
        //create node for new element:
    pNode_newElem = (pNode_Element)malloc(sizeof(node_element));
    if (pNode_newElem == NULL)
    {
        malloc_error();
    }
        //extract element's key:
    pNode_newElem->pElement_key = p_HashTable->pfunc_getKey(p_element);
        //assign element's info to node:
    pNode_newElem->pData = p_element;
    int place_in_hashTable = p_HashTable->pfunc_search(pNode_newElem->pElement_key, p_HashTable->hashTable_size);
    pNode_Element current = *(p_HashTable->table_head + place_in_hashTable);
        //new element will point on first element in linked list:
    pNode_newElem->pNext_node = current;
        //new element will now be head of linked list:
    *(p_HashTable->table_head + place_in_hashTable) = pNode_newElem;
    return SUCCESS;
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
    if (p_HashTable == NULL || p_key == NULL) return NULL;
    int place_in_hashTable = p_HashTable->pfunc_search(p_key, p_HashTable->hashTable_size);
    pNode_Element current = *(p_HashTable->table_head + place_in_hashTable);
    while (current != NULL)
    {
            //check if current element's key is same as key given:
        if (p_HashTable->pfunc_compare(p_key, current->pElement_key) == SAME)
        {
            return current->pData;
        }
        current = current->pNext_node;
    }
    //if key not found, return NULL:
    return NULL;
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
    if (p_HashTable == NULL || p_key == NULL) return FAIL;
    int place_in_hashTable = p_HashTable->pfunc_search(p_key, p_HashTable->hashTable_size);
    pNode_Element p_elem_to_delete = *(p_HashTable->table_head + place_in_hashTable);
    while (p_elem_to_delete != NULL)
    {
        if (p_HashTable->pfunc_compare(p_key, p_elem_to_delete->pElement_key) == SAME)
        {
                //free element:
            p_HashTable->pfunc_destroy(p_elem_to_delete->pData);
                //free element's node:
            free(p_elem_to_delete);
            return SUCCESS;
        }
        p_elem_to_delete = p_elem_to_delete->pNext_node;
    }
    //if element wasn't found return fail:
    return FAIL;
}

/*********************************************************************************
Function name: HashPrint
Description: the function prints the elements in the table
Parameters: p_HashTable - a pointer to the hash table
Return value: Result - FAIL if couldn't print, else SUCCESS
**********************************************************************************/
Result HashPrint (pHash p_HashTable){
    if (p_HashTable == NULL) return FAIL;
    pNode_Element* arrey = p_HashTable->table_head;
    pNode_Element current;
    int i = 0;
    while (i < p_HashTable->hashTable_size)
    {
            current = *(arrey + i);
            while (current != NULL)
            {
                p_HashTable->pfunc_print(current->pData);
                current = current->pNext_node;
            }
        i++;
    }
}

/*********************************************************************************
Function name: HashDestroy
Description: the function destroys the hash table
Parameters: p_HashTable - a pointer to the hash table
Return value: Result - FAIL if couldn't destroy, else SUCCESS
**********************************************************************************/
Result HashDestroy(pHash p_HashTable)
{
    if (p_HashTable == NULL) return FAIL;
    pNode_Element* arrey = p_HashTable->table_head;
    pNode_Element current,help_to_delete;
    int i = 0;
    while (i < p_HashTable->hashTable_size)
    {
        current = *(arrey + i);
        while (current != NULL)
        {
            help_to_delete = current;
            current = current->pNext_node;
            p_HashTable->pfunc_destroy(help_to_delete->pData);
            free(help_to_delete);
        }
        i++;
    }
}