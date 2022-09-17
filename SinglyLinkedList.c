/*
    Linked Lists -> Singly
    17/09/2022
    Most important functions
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Linked {
    int value;
    struct Linked *next;
} lin;

lin *createList (int);
lin *createNode (int);
int showList (lin *);
int countNodes (lin *);
lin *findPos (lin *,int);
lin *findEnd (lin *);
int insertPos (lin *,int,int);
lin *insertBegin (lin *,int);
void insertEnd (lin *,int);
int modPos (lin *,int,int);
int supPos (lin *,int);
lin *supBegin (lin *);
int supEnd (lin *);
lin *supAll (lin *);


int main (void) {

    lin *list = NULL;

    list = createList(0);
    insertEnd(list,1);
    insertEnd(list,2);
    insertEnd(list,3);
    insertEnd(list,4);
    list = insertBegin(list,90);
    insertPos(list,3,80);
    printf("N nodes = %d\n",countNodes(list));
    showList(list);

    modPos(list,5,70);
    supPos(list,2);
    showList(list);

    supEnd(list);
    list = supBegin(list);
    showList(list);

    list = supAll(list);
    if (-1 == showList(list))
        printf("All have been freed\n");

    return 0;
}


//CREATION
lin *createList (int value) {
    lin *create;

    if (NULL == (create = malloc(sizeof(lin))))
        return NULL;
    
    create->value = value;
    create->next = NULL;

    return create;
}

lin *createNode (int value) {
    lin *newNode;

    if (NULL == (newNode = malloc(sizeof(lin*))))
        return NULL;

    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}


//IMPORTANT FUNCTIONS
int showList (lin *list) {
    lin *ind;
    int count;

    if (list == NULL)
        return -1;

    ind = list;
    count = 0;

    printf("VALUES\n");
    while (ind != NULL) {
        printf ("%d : %d\n",count++,ind->value);
        ind = ind->next;
    }

    return 0;
}

int countNodes (lin *list) {
    lin *ind;
    int count;

    if (list == NULL)
        return -1;
    
    ind = list;
    count = 1;

    while (ind->next != NULL) {
        ind = ind->next;
        count++;
    }

    return count;
}


//SEARCH
lin *findPos (lin *list, int pos) {
    lin *ind;

    if (pos < 0)
        return NULL;

    ind = list;

    for (int i = 0; i < pos; i++)
        if (ind->next == NULL)
            return NULL;
        else
            ind = ind->next;
    
    return ind;
}

lin *findEnd (lin *list) {
    lin *ind = list;

    if (list == NULL)
        return NULL;

    while (ind->next != NULL)
        ind = ind->next;
    return ind;
}


//INSERTION
int insertPos (lin *list, int pos, int value) {
    lin *ind,*aux;

    if (list == NULL)
        return -1;
    else if (pos < 0)
        return -2;
    else if (pos >= countNodes(list)-1)
        return -3;
    
    if (pos == 0)
        insertBegin(list,value);

    ind = findPos(list,pos-1);
    aux = createNode(value);
    aux->next = ind->next;
    ind->next = aux;

    return 0;
}

lin *insertBegin (lin *list, int value) {
    lin *aux;

    aux = createNode(value);

    aux->next = list;
    list = aux;

    return list;
}

void insertEnd (lin *list, int value) {
    lin *ind,*aux;

    if (list == NULL)
        insertBegin(list,value);

    ind = findEnd(list);
    ind->next = (aux = createNode(value));
}


//MODIFY
int modPos (lin *list, int pos, int value) {
    lin *ind;

    if (list == NULL)
        return -1;

    if (NULL == (ind = findPos(list,pos)))
        return -1;

    ind->value = value;

    return 0;
}


//SUPPRESSION
int supPos (lin *list, int pos) {
    lin *ind,*aux;

    if (list == NULL)
        return -1;

    ind = findPos(list,pos-1);
    aux = ind->next;
    ind->next = aux->next;
    free(aux);

    return 0;
}

lin *supBegin (lin *list) {
    lin *ind,*aux;

    if (list == NULL)
        return NULL;
    else if (list->next != NULL) {
        aux = list->next;
        free(list);
        return aux;
    }
    else {
        free(list);
        return (list = NULL);
    }
}

int supEnd (lin *list) {
    lin * ind;
    int tot;
    if (list == NULL)
        return -1;
    if (1 == (tot =countNodes(list))) {
        supAll(list);
    }
    else if (NULL != (ind =  findPos(list,tot-2))) {
        free(ind->next);
        ind->next = NULL;
    }

    return 0;
}

lin *supAll (lin *list) {
    lin *ind;

    do {
        ind = list->next;
        free(list);
        list = ind;
    } while (ind != NULL);

    return NULL;
}
