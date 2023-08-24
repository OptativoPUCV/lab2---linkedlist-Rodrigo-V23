#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new -> data = data;
    new -> prev = NULL;
    new -> next = NULL;
    return new;
}
List * createList()
{
  List *nueva_lista = (List *) malloc(sizeof(List));
  if(nueva_lista == NULL)
  {
    exit(EXIT_FAILURE);
  }
  nueva_lista -> head = NULL;
  nueva_lista -> tail = NULL;
  nueva_lista -> current = NULL;
  return nueva_lista;
}
void * firstList(List * list)
{
  if(list->head != NULL)
  {
    list->current = list->head;
    return list->current->data;
  }
  return NULL;
}
void * nextList(List * list)
{
  if(list -> current != NULL && list -> current -> next != NULL)
  {
    list -> current = list -> current -> next;
    return list -> current -> data;
  } 
  return NULL;
}
void * lastList(List * list)
{
  if(list -> tail != NULL)
  {
    list -> current = list -> tail;
    return list -> current -> data;
  }
  return NULL;
}
void * prevList(List * list)
{
  if(list -> current != NULL && list -> current -> prev != NULL)
  {
    list -> current = list -> current -> prev;
    return list -> current -> data;
  }
  return NULL;
}
void pushFront(List * list, void * data)
{
  if(list)
  {
    Node *nuevo_nodo = createNode(data);
    if(nuevo_nodo)
    {
      nuevo_nodo -> next = list->head;
      if (list -> head)
      {
        list -> head -> prev = nuevo_nodo;
      } 
      else
      {
        list -> tail = nuevo_nodo;
      }
      list -> head = nuevo_nodo;
    }
  }
}
void pushBack(List * list, void * data)
{
  list -> current = list -> tail;
  pushCurrent(list,data);
}
void pushCurrent(List * list, void * data)
{
  if(list -> current != NULL)
  {
    Node *nuevo_nodo = createNode(data);
    if(nuevo_nodo)
    {
      nuevo_nodo -> next = list -> current->next;
      if(list -> current -> next)
      {
        list -> current -> next->prev = nuevo_nodo;
      }
      else
      {
        list->tail = nuevo_nodo;
      }
      nuevo_nodo -> prev = list -> current;
      list -> current -> next = nuevo_nodo;
    }
  }
}
void * popFront(List * list)
{
  list -> current = list -> head;
  return popCurrent(list);
}
void * popBack(List * list)
{
  list -> current = list->tail;
  return popCurrent(list);
}
void * popCurrent(List * list)
{
  if(list->current != NULL)
  {
    void *data = list->current->data;
    Node *temp = list->current;
    if(list->current->prev)
    {
      list->current->prev->next = list->current->next;
    }
    else
    {
      list->head = list->current->next;
    }
    if(list->current->next)
    {
      list->current->next->prev = list->current->prev;
    }
    else
    {
      list->tail = list->current->prev;
    }
    list->current = list->current->next;
    free(temp);
    return data;
  }
return NULL;
}
void cleanList(List * list)
{
  while (list->head != NULL)
  {
    popFront(list);
  }
}