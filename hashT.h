#ifndef H_Htable
#define H_Htable

//****************************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement a hash table as
// an ADT. It uses quadratic probing to resolve collisions.
//****************************************************************

#include <iostream>
#include <cassert>

using namespace std;
struct info{
    int movie_id;
    double rank;
    int user_id;
};

struct node{
    info node1;
    info *link;
};

class hashT
{
public:
    void insert(int hashIndex, info& rec);
    //Function to insert an item in the hash table. The first
    //parameter specifies the initial hash index of the item to
    //be inserted. The item to be inserted is specified by the
    //parameter rec.
    //Postcondition: If an empty position is found in the hash
    //   table, rec is inserted and the length is incremented by
    //   one; otherwise, an appropriate error message is
    //   displayed.

    void search(int& hashIndex, info& rec, bool& found) const;
    //Function to determine whether the item specified by the
    //parameter rec is in the hash table. The parameter hashIndex
    //specifies the initial hash index of rec.
    //Postcondition: If rec is found, found is set to true and
    //   hashIndex specifies the position where rec is found;
    //   otherwise, found is set to false.

    bool isItemAtEqual(int hashIndex, info& rec) const;
    //Function to determine whether the item specified by the
    //parameter rec is the same as the item in the hash table
    //at position hashIndex.
    //Postcondition: Returns true if HTable[hashIndex] == rec;
    //   otherwise, returns false.

    void retrieve(int hashIndex, info& rec) const;
    //Function to retrieve the item at position hashIndex.
    //Postcondition: If the table has an item at position
    //   hashIndex, it is copied into rec.

    void remove(int hashIndex,  info& rec);
    //Function to remove an item from the hash table.
    //Postcondition: Given the initial hashIndex, if rec is found
    //   in the table it is removed; otherwise, an appropriate
    //   error message is displayed.
    void print_file();

    void print() const;
    //Function to output the data.

    hashT(int size = 1000000);
    //constructor
    //Postcondition: Create the arrays HTTable and indexStatusList;
    //   initialize the array indexStatusList to 0; length = 0;
    //   HTSize = size; and the default array size is 101.

    ~hashT();
    //destructor
    //Postcondition: Array HTable and indexStatusList are deleted.
private:
    info *HTable;   //pointer to the hash table
    int *indexStatusList;  //pointer to the array indicating the
    //status of a position in the hash table
    int length;    //number of items in the hash table
    int HTSize;    //maximum size of the hash table

};

void hashT::insert(int hashIndex,  info& rec)
{
    int pCount;
    int inc;

    pCount = 0;
    inc = 1;

    while (indexStatusList[hashIndex] == 1
           && HTable[hashIndex].user_id != rec.user_id)
    {
        pCount++;
        hashIndex = (hashIndex + inc ) % HTSize;
        inc = inc + 2;
    }

    if (indexStatusList[hashIndex] != 1)
    {
        HTable[hashIndex] = rec;
        indexStatusList[hashIndex] = 1;
        length++;
    }
    if(HTable[hashIndex].user_id == rec.user_id){
        node *newNode;
        newNode = new node;
        newNode -> node1 = rec;
        newNode -> link = &HTable[hashIndex];
    }
}

void hashT::print_file() {
    std::ofstream map;
    map.open("Map_test.txt");
    map << "UserID," << "MovieID," << "Rate" << std::endl;
    int row_number = 0;
    for (int i = 1; i < HTSize; i++){
        row_number = i;
        if (indexStatusList[i] != 0) {
            map << i << "," << HTable[i].movie_id << "," << HTable[i].rank  << std::endl;
            }
        }
    map.close();
    std::cout << row_number << std::endl;
}

void hashT::search(int& hashIndex, info& rec, bool& found) const
{
    int pCount;
    int inc;

    pCount = 0;
    inc = 1;

    while (indexStatusList[hashIndex] != 0
           && HTable[hashIndex].movie_id != rec.movie_id)
    {
        pCount++;
        hashIndex = (hashIndex + inc ) % HTSize;
        inc = inc + 2;
    }

    if (indexStatusList[hashIndex] == 1 && HTable[hashIndex].movie_id == rec.movie_id )
    {
        hashIndex = hashIndex;
        found = true;
    }
    else
        found = false;
}


bool hashT::isItemAtEqual(int hashIndex, info& rec) const
{
    return(HTable[hashIndex].movie_id == rec.movie_id);
}


void hashT::retrieve(int hashIndex, info& rec) const
{
    if (indexStatusList[hashIndex] == 1)
        rec = HTable[hashIndex];
}


void hashT::remove(int hashIndex,info& rec)
{
    bool found;

    search(hashIndex, rec, found);

    if (found)
    {
        indexStatusList[hashIndex] = -1;
        length--;
    }
    else
        cerr << "The item to be deleted is not in the list."
             << endl;
}


void hashT::print() const
{
    for (int i = 0; i < HTSize; i++)
        if (indexStatusList[i] != 0)
            cout <<"User id: "  << HTable[i].user_id
                 << " movieID: " << HTable[i].movie_id << " Rate: " << HTable[i].rank << endl;
}


hashT::hashT(int size)
{

    HTable = new info[size];
    indexStatusList = new int[size];
    length = 0;
    HTSize = size;

    for (int i = 0; i < size; i++)
        indexStatusList[i] = 0;
}


hashT::~hashT()
{
    delete [] HTable;
    delete [] indexStatusList;
}

#endif
