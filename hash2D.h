#ifndef TERM_HASH2D_H
#define TERM_HASH2D_H
#include <iostream>
#include <cassert>
#include <string>
struct rating{
    int user_id;
    int movie_id;
    double rating;
};

class hash2D{
public:
private:
    int **hashTable;
    int **hashIndexStatus;
};

#endif //TERM_HASH2D_H
