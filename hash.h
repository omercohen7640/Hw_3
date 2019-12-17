#ifndef _HASH_H_
#define _HASH_H_

typedef enum {FAIL = 0, SUCCESS} Result;
typedef enum {SAME = 0, DIFFERENT} CompResult;

typedef struct _Hash *pHash;

typedef void* pElement;
typedef void* pKey;

typedef int (*HashFunc) (pKey key, int size);
typedef Result (*PrintFunc) (pElement element);
typedef CompResult (*CompareFunc) (pKey key1, pKey key2);
typedef pKey (*GetKeyFunc) (pElement element);
typedef void (*DestroyFunc)(pElement element); // should return Result value?

// definition of node in linked list
typedef struct _nodeElement *pNode_Element;

// Add your declarations here...
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
                  GetKeyFunc pfunc_getKey, DestroyFunc pfunc_destroy);

/*********************************************************************************
Function name: HashAdd
Description: inserts the element given to the hash table in it's appropriate place
Parameters: p_HashTable - a pointer to the hash table
            p_element - a pointer to an element
Return value: Result - FAIL if couldn't add to the table, else SUCCESS
**********************************************************************************/
Result HashAdd (pHash p_HashTable, pElement p_element);

/*********************************************************************************
Function name: HashFind
Description: the function searches for an element in the table with the key given
Parameters: p_HashTable - a pointer to the hash table
            p_key - a pointer to the key of an element
Return value: pElement - a pointer to the element with the key given
**********************************************************************************/
pElement HashFind (pHash p_HashTable, pKey p_key);

/*********************************************************************************
Function name: HashRemove
Description: the function removes the element with the key given from the table
Parameters: p_HashTable - a pointer to the hash table
            p_key - a pointer to the key of an element
Return value: Result - FAIL if couldn't remove, else SUCCESS
**********************************************************************************/
Result HashRemove (pHash p_HashTable, pKey p_key);

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

#endif
