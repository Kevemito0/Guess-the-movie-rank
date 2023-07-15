#ifndef PROJECT_PREDICTION_H
#define PROJECT_PREDICTION_H
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include "algorithm"
class prediction{
public:
    prediction();
    ~prediction();
    void reading_input(std::string const& file_name);
    void print();
    int userAt(int i);
    int itemAt(int i);
    double rating(int i);

private:
    int *users;
    int *matrix;
    int *userID;
    int *itemID;
    double *ratings;
    int length;
};


prediction::prediction() {
    userID = new int[1123400];
    itemID = new int[1123400];
    ratings = new double[1123400];
}

void prediction::reading_input(std::string const& file_name) {
    std::ifstream input;
    input.open(file_name);
    std::string line;
    int index = 0;
    if(input.is_open()) {
        while (getline(input, line, ',')) {
            int a, b;
            double c;
            std::stringstream ss(line);
            ss >> a;
            userID[index] = a;
            getline(input, line, ',');
            std::stringstream ss1(line);
            ss1 >> b;
            itemID[index] = b;
            getline(input, line, '\n');
            std::stringstream ss2(line);
            ss2 >> c;
            ratings[index] = c;
            index++;
        }
        input.close();
    }
    length = index;
}

void prediction::print() {
    std::cout << "UserID " << "ItemID " << "Ratings" << std::endl;
    for(int i = 1; i < length ; i++){
        std::cout << userID[i] << " " << itemID[i] << " "<< ratings[i] << std::endl;
    }
}
int prediction::userAt(int i) {
    return userID[i];
}

int prediction::itemAt(int i) {
    return itemID[i];
}

double prediction::rating(int i) {
    return ratings[i];
}

prediction::~prediction(){
    delete userID;
    delete ratings;
    delete itemID;
}

#endif //PROJECT_PREDICTION_H
