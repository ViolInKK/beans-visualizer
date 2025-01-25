// Hashmap using "Seperate chaining" collision resolving method and FNV1a32 hash function.
/*
 * REFERENCES:
 * https://en.wikipedia.org/wiki/Hash_table#
 * http://burtleburtle.net/bob/hash/evahash.html
 * https://www.partow.net/programming/hashfunctions/
 * https://github.com/rurban/smhasher
*/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

//For strcmp
#include<string.h>

typedef int unsigned u32;

#define MAP_SIZE 128
#define FNV_32_PRIME 0x01000193

typedef struct sListNode {
    char *key;
    u32 value;
    u32 isSet;

    struct sListNode *nextListNode;
} ListNode;

typedef struct sHashMap {
    int size;
    int capacity;

    ListNode mapBuckets[];
} HashMap;

HashMap *InitHashMap(int capacity){
    HashMap *hashMap = malloc(sizeof(*hashMap) + sizeof(ListNode) * capacity);
    if(hashMap == NULL){
        fprintf(stderr, "Couldn't init hashmap.\n");
        exit(1);
    }
    hashMap->size = 0;
    hashMap->capacity = capacity;
    for(int i = 0; i < capacity; i++){
        hashMap->mapBuckets[i].isSet = 0;
    }
    return hashMap;
}

void DeallocHashMap(HashMap *hashMap){
    if(hashMap->size != 0){
        for(int i = 0; i < hashMap->capacity; i++){
            if(!hashMap->mapBuckets[i].isSet){
                continue;
            }
            ListNode *currentNode = hashMap->mapBuckets[i].nextListNode;
            ListNode *nextNode = NULL;
            while(currentNode != NULL){
                nextNode = currentNode->nextListNode;
                free(currentNode);
                currentNode = nextNode;
            }
        }
    }
    free(hashMap);
    return;
}

u32 FNV1aHash(HashMap *hashMap, char *key){
    u32 hval = 0x811c9dc5;
    while(*key){
        hval ^= (u32)*key++;
        hval *= FNV_32_PRIME;
    }
    return hval % hashMap->capacity;
}

void HashMapSet(HashMap *hashMap, char *key, u32 value){
    u32 index = FNV1aHash(hashMap, key);
    //If root listnode in the bucket is empty just put new entry in there.
    if(hashMap->mapBuckets[index].isSet == 0){
        hashMap->mapBuckets[index].key = key;
        hashMap->mapBuckets[index].value = value;
        hashMap->mapBuckets[index].isSet = 1;
        hashMap->mapBuckets[index].nextListNode = NULL;
        hashMap->size++;
        return;
    }
    //Else iterate over bucket nodes checking for the key we need and inserting new node at the end if needed key wasnt found. 
    else{
        ListNode *currentNode = &hashMap->mapBuckets[index];
        ListNode *prevNode = NULL;
        while(currentNode != NULL){
            if(strcmp(currentNode->key, key) == 0 && currentNode->isSet){
                currentNode->value = value;
                return;
            }
            prevNode = currentNode;
            currentNode = currentNode->nextListNode;
        }
        if(hashMap->size >= hashMap->capacity){
            fprintf(stderr, "Hashmap is full.\n");
            return;
        }
        ListNode *newListNode = malloc(sizeof(*newListNode));
        newListNode->key = key;
        newListNode->value = value;
        newListNode->isSet = 1;
        newListNode->nextListNode = NULL;
        prevNode->nextListNode = newListNode;
        hashMap->size++;
        return;
    }
}

//NOTE(ViolinKK):
//      There are probably issues with u32/int typecasting, but Im not sure, and I dont wanna look into it.
u32 HashMapGet(HashMap *hashMap, char *key){
    u32 index = FNV1aHash(hashMap, key);
    ListNode *currentNode = &hashMap->mapBuckets[index];
    if(!currentNode->isSet){
        return -1;
    }
    while(currentNode != NULL){
        if(strcmp(currentNode->key, key) == 0 && currentNode->isSet){
            return currentNode->value;
        }
        currentNode = currentNode->nextListNode;
    }
    return -1;
}
void HashMapDeleteEntry(HashMap *hashMap, char *key){
    u32 index = FNV1aHash(hashMap, key);
    ListNode *currentNode = &hashMap->mapBuckets[index];
    //If bucket is empty.
    if(!currentNode->isSet){
        fprintf(stderr, "No entry with such key.\n");
        return;
    }
    //If target entry is at the root of a bucket.
    if(strcmp(currentNode->key, key) == 0){
        //If bucket only has root.
        if(currentNode->nextListNode == NULL){
            currentNode->isSet = 0;
        }
        //If bucket has more than root, copy next bucket node into root and free that next bucket node.
        else{
            currentNode->key = currentNode->nextListNode->key;
            currentNode->value = currentNode->nextListNode->value;
            currentNode->nextListNode = currentNode->nextListNode->nextListNode;
            free(currentNode->nextListNode);
        }
        hashMap->size--;
        return;
    }
    //Iterate over bucket linked list looking for node to be deleted.
    ListNode *prevNode = currentNode;
    currentNode = currentNode->nextListNode;
    while(currentNode != NULL){
        if(strcmp(currentNode->key, key) == 0 && currentNode->isSet){
            currentNode->isSet = 0;
            prevNode->nextListNode = currentNode->nextListNode;
            free(currentNode);
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->nextListNode;
    }
    fprintf(stderr, "No entry with such key.\n");
    return;
}

int main(void){
    HashMap *hashMap = InitHashMap(MAP_SIZE);

    HashMapSet(hashMap, "key", 10);
    HashMapSet(hashMap, "another key", 25);
    HashMapSet(hashMap, "yet another key", 38);

    //25
    HashMapGet(hashMap, "another key");
    //-1
    HashMapGet(hashMap, "non existing key");

    HashMapDeleteEntry(hashMap,"yet another key");
    //-1
    HashMapGet(hashMap, "yet another key");

    DeallocHashMap(hashMap);
    return 0;
}
