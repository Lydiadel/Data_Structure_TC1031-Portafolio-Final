#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next; 
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

  if(!l1){
    return l2;
  }
  if(!l2){
    return l1;
  }
  /*Check which list has the smallest first value and set it to a ListNode to return called "head"
  Necesitamos hacer esta operacion para saber cual sera
  el nodo con el cual iniciaremos nuestro while, pudiendo
  tener la referencia a la cabeza de nuestra lista, dejando 
  como apuntador el siguiente valor de la lista en la cual se tiene el valor de la cabeza
  */
  ListNode* head = l1;
  if(l1->val > l2->val){
    head = l2;
    l2 = l2->next;
  }else{
    l1 = l1->next;
  }

  /*Create new ListNode with head's value.
  This new list will be acquiring the sorted values from both lists */
  ListNode* current = head;
  while(l1 && l2){
    /*"current" has the the lowest first value (head), now it picks the list
    with the lowest first value, sets the result to the next node on current,
    and advances each picked list so it has a new first value.*/
    if(l1->val < l2->val){
      //In case l1.val is lower than l2.val we set the "current" next value as l1 (The lowest in the comparison)
      current->next = l1;
      l1 = l1->next;
      // In case l2 is lower than l1's value we set the "current" next as l2 (The lower in comparison)
    }else{
      current->next = l2;
      l2 = l2->next;
    }
    /*With the next value created we can keep moving forward with the comparison*/
    current = current->next;
  }

  //In case the value 
  if(!l1){
    current->next = l2;
  }else{
    current->next = l1;
  }

  return head;
}