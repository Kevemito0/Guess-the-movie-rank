#ifndef H_orderedListType
#define H_orderedListType
#include "algorithm"
//***********************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement the basic
// properties of an ordered linked list. This class is
// derived from the class linkedListType. 
//***********************************************************


struct info{
    int ID;
    double rank;
};

struct node{
    info data;
    node *link;
};


class orderedLinkedList
{
public:
    bool search(const int& searchItem) const;
      //Function to determine whether searchItem is in the list.
      //Postcondition: Returns true if searchItem is in the list, 
      //               otherwise the value false is returned.

    int get_item(const int& item) const;
    int size();

    void insert(const info& newItem);
      //Function to insert newItem in the list.
      //Postcondition: first points to the new list, newItem 
      //               is inserted at the proper place in the
      //               list, and count is incremented by 1.

    void insertFirst(const info& newItem);
      //Function to insert newItem at the beginning of the list.
      //Postcondition: first points to the new list, newItem is
      //               inserted at the beginning of the list,
      //               last points to the last node in the  
      //               list, and count is incremented by 1.

    void insertLast(const info& newItem);
      //Function to insert newItem at the end of the list.
      //Postcondition: first points to the new list, newItem 
      //               is inserted at the end of the list,
      //               last points to the last node in the 
      //               list, and count is incremented by 1.
    double similarity(orderedLinkedList &item1, orderedLinkedList& item2,int size);
    void destroylist();
    ~orderedLinkedList();
    orderedLinkedList();
    bool getCurrent();
    void print();

private:
    int count;   //variable to store the number of
    //elements in the list
    node *first; //pointer to the first node of the list
    node *last;  //pointer to the last node of the list

};

double orderedLinkedList::similarity(orderedLinkedList  &item1, orderedLinkedList &item2,int size) {
    double sum = 0.0;
    double sum2 = 0.0;
    double mul = 0.0;
    double similarity = 0;
    node *current1;
    node *current2;

    current1 = item1.first;
    current2 = item2.first;
    while(current1 != NULL){
        if(item2.search(current1->data.ID)) {
            sum2 += pow(get_item(current2->data.rank), 2);
            sum += pow(get_item(current1->data.rank),2);
            mul += (current1 -> data.rank) * (current2 -> data.rank);
            current1 = current1 -> link;
        }
        else
        current2 = current2 -> link;
    }
    similarity = abs(1- (mul / (sqrt(sum2) * sqrt(sum))));

    return similarity;

}


int orderedLinkedList::size() {
    node *current;
    current = first;
    int size = 0;
    while(current!= NULL){
        current = current-> link;
        size++;
    }
    return size;
}

int orderedLinkedList::get_item(const int &item) const {
    if(search(item)){
        return item;
    }
}

bool orderedLinkedList::getCurrent() {
    node *current;
    current = first;
    return current != NULL;
}
void orderedLinkedList::print() {
    node *current;
    current = first;
    while(current != NULL){
        std::cout << "movieID: " << current -> data.ID << " ";
        std::cout << "Rate: " << current -> data.rank << " ";
        current = current -> link;
        std::cout << std::endl;
    }
}
bool orderedLinkedList::search(const int& searchItem) const
{
    bool found = false;
    node *current; //pointer to traverse the list

    current = first;  //start the search at the first node

    while (current != NULL && !found)
        if (current->data.ID >= searchItem)
            found = true;
        else
            current = current->link;
 
    if (found)
       found = (current->data.ID == searchItem); //test for equality

    return found;
}//end search


void orderedLinkedList::insert(const info& newItem)
{
    node *current; //pointer to traverse the list
    node *trailCurrent; //pointer just before current
    node *newNode;  //pointer to create a node

    bool  found;

    newNode = new node; //create the node
    newNode->data = newItem;   //store newItem in the node
    newNode->link = NULL;      //set the link field of the node
                               //to NULL

    if (first == NULL)  //Case 1
    {
        first = newNode;
        last = newNode;
        count++;
    }
    else
    {
        current = first;
        found = false;

        while (current != NULL && !found) //search the list
           if (current->data.ID >= newItem.ID)
               found = true;
           else
           {
               trailCurrent = current;
               current = current->link;
           }
 
        if (current == first)      //Case 2
        {
            newNode->link = first;
            first = newNode;
            count++;
        }
        else                       //Case 3
        {
            trailCurrent->link = newNode;
            newNode->link = current;

            if (current == NULL)
                last = newNode;

            count++;
        }
    }//end else
}//end insert

void orderedLinkedList::insertFirst(const info& newItem)
{
    insert(newItem);
}//end insertFirst


void orderedLinkedList::insertLast(const info& newItem)
{
    insert(newItem);
}//end insertLast

void orderedLinkedList::destroylist(){
    node *temp;
    while(first != NULL){
        temp = first;
        first = first -> link;
        delete temp;
    }
    last = NULL;
    count = 0;
}
orderedLinkedList::orderedLinkedList(){
    first = NULL;
    last = NULL;
    count = 0;
}
orderedLinkedList::~orderedLinkedList(){
    destroylist();
}

#endif