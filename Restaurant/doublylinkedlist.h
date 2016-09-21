/**
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Sean McDonald
 * @date 1/1/16
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {

 public:
   DoublyLinkedList();
   ~DoublyLinkedList();
   void append(T* data);
   bool empty() const { return (head == nullptr); }
   T* remove();
   T* first();
   T* next();

 private:
   class Node {
    public:
      Node();
      Node(T* data);
      Node* next;
      Node* prev;
      T* data;
   };
   Node* head;
   Node* tail;
   Node* current;
};

/**
 * @brief   Node constructor.
 */
template <class T>
DoublyLinkedList<T>::Node::Node() {
 next=prev=NULL;

}

/**
 * @brief   DoublyLinkedList constructor.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {

   head=NULL;
   tail=NULL;
   current=NULL;

}

/**
 * @brief   DoublyLinkedList destructor.
 */
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
   while (head!=nullptr) {
      Node* temp=new Node();
      temp=head;
      head=head->next;
      delete temp;
      temp=head;
      }
      
   }

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */
template <class T>
void DoublyLinkedList<T>::append(T* data) {
   Node* temp= new Node();
   temp->data=data;
   if (head==nullptr) {
      head=temp;
      tail=head;
      tail->next=nullptr;
   }
   else {
   tail->next=temp;
   temp->prev=tail;
   tail=temp;
   tail->next=nullptr;
   }
  // temp=tail->next;
  // tail=temp;
  // tail->data=data;
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */
template <class T>
T* DoublyLinkedList<T>::first() {


   if(head==nullptr) {
      return nullptr;
   }
   current=head;
//    Node* temp=new Node;
//   return temp->data;
return head->data;

}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::next() {
 if(head==nullptr) {
     return nullptr;
  }
  else if(current==tail) {
      return nullptr;
   }
   else if(current->next==nullptr){
      return nullptr;
   }
   else {
   current=current->next;
   return current->data;
}
}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */
template <class T>
T* DoublyLinkedList<T>::remove() {
   if (head==nullptr){
      return nullptr;
   }
   if(head==tail){
      delete head;
      head=nullptr;
      return nullptr;
   }
   if(current==head) {
      current=head->next;
      delete head;
      head=current;
      return current->data;
   }
   else if (current==tail){
      Node* node=new Node();
      node=tail;
      tail=tail->prev;
      delete node;
      return nullptr;
   }
      Node* node=new Node();
      node=current;
      current=current->next;
      current->prev=node->prev;
      current=node->prev;
      current->next=node->next;
      current=node->next;
      delete node;
      return current->data;
}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
