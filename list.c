#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
};

struct List {
    int size;
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;


Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;

    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List* )malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    list->current = list->current->next;
    if (list->current == NULL) return NULL;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->current == NULL) return NULL;
    while (list->current->next != NULL){
        list->current = list->current->next;
    }
    list->tail = list->current;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if (list == NULL) {
        return;
      }
      Node *newNode = (Node *)malloc(sizeof(Node));
      if (newNode == NULL) {
        return;
      }
      newNode->data = data;
      newNode->next = list->head;
      list->head = newNode;
      if (list->tail == NULL) {
        list->tail = newNode;
      }
      list->size++;
}

void pushBack(List * list, void * data) {
    if (list == NULL) {
        return;
      }
      Node *newNode = (Node *)malloc(sizeof(Node));
      if (newNode == NULL) {
        return; 
      }
      newNode->data = data;
      newNode->next = NULL;
      if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
      } else {
        list->tail->next = newNode;
        list->tail = newNode;
      }
      list->size++;
}

void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL) {
        return; 
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return; 
    }
    newNode->data = data;
    newNode->next = list->current->next;
    list->current->next = newNode;
    if (list->current == list->tail) {
        list->tail = newNode; 
    }
    list->size++;
}

void * popFront(List * list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    Node *temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    void *data = temp->data;
    free(temp);
    list->size--;
    return data;
    }

void * popBack(List * list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
      }
      if (list->head == list->tail) { 
        return popFront(list);
      }
      Node *current = list->head;
      while (current->next != list->tail) {
        current = current->next;
      }
      void *data = list->tail->data;
      free(list->tail);
      current->next = NULL;
      list->tail = current;
      list->size--;
      return data;
    }

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) {
        return NULL; 
      }
      if (list->current == list->head) {
        return popFront(list);
      }
      Node *temp = list->head;
      while (temp != NULL && temp->next != list->current) {
        temp = temp->next;
      }
    
      temp->next = list->current->next;
      if (list->current == list->tail) {
        list->tail = temp; 
      }
      void *data = list->current->data;
      free(list->current);
      list->current = temp->next;
      list->size--;
      return data;
    }

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}

void sortedInsert(List *list, void *data, int (*lower_than)(void *data1, void *data2)) {
if (list == NULL) {
return;
}
if (list->head == NULL || lower_than(data, list->head->data)) {
pushFront(list, data);
return;
}
Node *current = list->head;
while (current->next != NULL && !lower_than(data, current->next->data)) {
current = current->next;
}

list->current = current;


pushCurrent(list, data);
}