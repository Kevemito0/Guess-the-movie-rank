#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include "algorithm"
#include "cmath"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>

struct info{
    int ID;
    double rank;
};
struct user{
    int id;
    double similarity;
};

class prediction2{
public:
    bool compareMovies(const info &a, const info &b);
    prediction2();
   // ~prediction2();
    void reading_input(std::string const& file_name);
    void merge_sort(info array[], int const left,int const right);
    void print();
    void print_file();
    void print_rec();
    void finding_rank();
    double pearson_correlation(const std::vector<info>& object1, const std::vector<info>& object2);
    bool searchVector1(std::vector<info>arr,int mov);
    int searchVector2(std::vector<info>arr,int mov);
    bool searchVector3(std::vector<info> arr1, std::vector<info> arr2,int mov);
    int test_search(int user);
    bool compareSimilarity(const user &a,const user &b);
    void predict(std::string const& file_name);
    std::unordered_map<int, std::vector<info>> hash_table;
    double** data;
    std::vector<int> merge_sort(std::vector<int>& vec);

private:
    info *rank_user;
    info *rank_movie;
    int *topUser;
    int *topMovie;
    int length;
    //double** data;
    int **rec;
    info rank;
    info ID;
    //std::unordered_map<int, std::vector<info>> hash_table;

};
double prediction2::pearson_correlation(const std::vector<info> &object1, const std::vector<info> &object2) {
    if (object1.size() != object2.size()) {
        throw std::invalid_argument("object1 and object2 must have the same size");
    }

    int n = object1.size();
    int N = 0;
    double sum_object1 = 0;
    double sum_object2 =0;
    double square_sum1 = 0;
    double square_sum2 = 0;
    double product = 0;
    // Summation over all attributes for both objects
    for(int i = 0; i < n;i++) {
        int l = searchVector2(object2,object1[i].ID);
         if(l != -1) {
             sum_object2 += object2[l].rank;
             sum_object1 += object1[i].rank;
             N++;
         }
    }

    // Sum the squares
    for(int i = 0; i < n; i++) {
        int l = searchVector2(object2,object1[i].ID);
            if(l != -1) {
                square_sum2 += pow(object2[l].rank, 2);
                square_sum1 += pow(object1[i].rank, 2);
            }
    }
    // Add up the products
    for(int i = 0; i < n; i++) {
        int l = searchVector2(object2, object1[i].ID);
        if(l != -1)
        product += object1[i].rank * object2[l].rank;
    }

    // Calculate Pearson Correlation score
    double numerator = product - (sum_object1 * sum_object2 / N);
    double denominator = sqrt((square_sum1 - pow(sum_object1, 2) / N) * (square_sum2 - pow(sum_object2, 2) / N));

    // Can't have division by 0
    if (denominator == 0) {
        return 0;
    }

    double result = numerator / denominator;
    return result;
}

bool prediction2::compareMovies(const info &a, const info &b){
    return a.rank < b.rank;
}

bool prediction2::compareSimilarity(const user &a, const user &b) {
    return a.similarity < b.similarity;
}

void prediction2::merge_sort(info array[], int const left, int const right) {
    if (right >= left) {
        return;
    }

    int mid = (left + right) / 2;

    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);

    // merge the two sorted halves back together
    info* temp = new info[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (array[i].ID < array[j].ID) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    // add any remaining elements from the left or right halves
    while (i <= mid) {
        temp[k++] = array[i++];
    }
    while (j <= left) {
        temp[k++] = array[j++];
    }

    for (int m = 0; m < right - left + 1; m++) {
        array[left + m] = temp[m];
    }
    delete[] temp;
}

void prediction2::finding_rank() {

    info topTenUser[11] = {0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,0,0};
    info topTenMovie[11] = {0,0,0,0,0,0,0,0,0,0,
                           0,0,0,0,0,0,0,0,0,0,0,0};
    int times[36000];
    int k = 0;
    for(int i=1;i < 36000;i++) {
        int a = 0;
        for (info value: hash_table[i]) {
            a += 1;
        }
        times[i] = a;
    }
   for(int i = 1; i < 36000; i++){
       if(times[i] > topTenUser[1].rank){
           for(int j = 9; j > 0; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[1].ID = i;
           topTenUser[1].rank = times[i];
       }
       else if(times[i] >= topTenUser[2].rank){
           for(int j = 9; j > 1; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[2].ID = i;
           topTenUser[2].rank = times[i];

       }else if(times[i] >= topTenUser[3].rank){
           for(int j = 9; j > 2; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[3].ID = i;
           topTenUser[3].rank = times[i];

       }else if(times[i] >= topTenUser[4].rank){
           for(int j = 9; j > 3; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[4].ID = i;
           topTenUser[4].rank = times[i];

       }else if(times[i] >= topTenUser[5].rank){
           for(int j = 9; j > 4; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[5].ID = i;
           topTenUser[5].rank = times[i];

       }else if(times[i] >= topTenUser[6].rank){
           for(int j = 9; j > 5; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[6].ID = i;
           topTenUser[6].rank = times[i];

       }else if(times[i] >= topTenUser[7].rank){
           for(int j = 9; j > 6; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[7].ID = i;
           topTenUser[7].rank = times[i];

       }else if(times[i] >= topTenUser[8].rank){
           for(int j = 9; j > 7; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[8].ID = i;
           topTenUser[8].rank = times[i];

       }else if(times[i] >= topTenUser[9].rank){
           for(int j = 9; j > 8; j--){
               topTenUser[j] = topTenUser[j-1];
           }
           topTenUser[9].ID = i;
           topTenUser[9].rank = times[i];

       }else if(times[i] >= topTenUser[10].rank){

           topTenUser[10].ID = i;
           topTenUser[10].rank = times[i];
       }
   }

    std::cout<<"--------FOR USERS-------------"<<std::endl;
   for(int i = 1; i <= 10; i++){
       std::cout<<"User: "<<topTenUser[i].ID<<" ranked a movie "<<topTenUser[i].rank<<" times"<<std::endl;
   }

   // std::cout << "--------FOR MOVIES-------------" << std::endl;


  /*  int stop_movie = 0;
    for(int i = 10000; i >= 0; i--){
        if(rank_movie[i].rank >= 1 && stop_movie != 10){
            std::cout << "Movie: " << rank_movie[i].ID << "  " << rank_movie[i].rank << " times ranked" << std::endl;
            stop_movie++;
        }
    }*/
}

// oy verenler ile vermeyenleri ayiran arrayin output kontrolu //
void prediction2::print_rec() {
    for(int i = 1 ; i < 100000 ; i++) {
        for (int k = 1; k < 10000; k++) {
            if(rec[i][k] == 1){
                std::cout << "User: " << i << " movieID: "<< k << " Rank: ";
                std::cout << data[i][k] << std::endl;
            }
        }
    }
}

prediction2::prediction2() {
    std::unordered_map<int, std::vector<info>> hash_table;

}

void prediction2::reading_input(std::string const& file_name) {
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
            getline(input, line, ',');
            std::stringstream ss1(line);
            ss1 >> b;
            getline(input, line, '\n');
            std::stringstream ss2(line);
            ss2 >> c;

            info temp;
            temp.ID = b;
            temp.rank = c;

            hash_table[a].push_back(temp);

        }
        input.close();
    }
}

// inputtan aldigimiz raw datayi direkt yazdiriyor kontrol amacli print //
void prediction2::print() {
    std::cout << "UserID " << "ItemID " << "Ratings" << std::endl;
    for(int i=1;i < 36000;i++) {
        for (info value: hash_table[i]) {
            std::cout <<i<<" "<< value.ID << " "<<value.rank<<std::endl;  // Outputs: 1 2 3 4
        }
    }
}

void prediction2::print_file() {
    std::ofstream outfile;
    std::ofstream array1, array2;
    outfile.open("outputTest.txt");
    outfile << "UserID " << "ItemID " << "Ratings" << std::endl;
    for(int userID = 1 ; userID < 100000 ; userID++) {
        for (int movieID = 1; movieID < 10000; movieID++) {
            if(rec[userID][movieID] == 1){
                outfile << userID << " " << movieID << " "<< data[userID][movieID] << std::endl;
            }
        }
    }
}

void prediction2::predict(std::string const& file_name) {
    std::ifstream input;
    input.open(file_name);
    // std::ofstream output;
    // output.open("output_similarity.txt");
    std::string line;
    if (input.is_open()) {
        std::cout << "ID,Predicted" << std::endl;
        while (getline(input, line, ',')) {
            int a, b, c;
            std::stringstream ss(line);
            ss >> a;
            getline(input, line, ',');
            std::stringstream ss1(line);
            ss1 >> b;
            getline(input, line, '\n');
            std::stringstream ss2(line);
            ss2 >> c;
            double similarity[36000];
            double temp = 0;

            for (int i = 0; i < 36000; i++) { //user arama loopu
                if(hash_table[i].size() == hash_table[b].size()){
                    similarity[i] = pearson_correlation(hash_table[b],hash_table[i]);
                }

            }
            std::cout << similarity[a]<< std::endl;
        }
    }
    input.close();
   // output.close();
}


bool prediction2::searchVector1(std::vector<info>arr, int mov) {

    for(int i = 0; i < arr.size(); i++){
        if(arr[i].ID == mov){
            return true;
        }
    }
    return false;
}

bool prediction2::searchVector3(std::vector<info> arr1, std::vector<info> arr2, int mov) {

    return (searchVector1(arr1,mov) && searchVector1(arr2,mov));
}

int prediction2::searchVector2(std::vector<info>arr, int mov) {

    for(int i = 0; i < arr.size(); i++){
        if(arr[i].ID == mov){
            return i;
        }
    }
    return -1;
}
int prediction2::test_search(int user) {

    for(int i = 0; i < hash_table[user].size(); i++){
        if(hash_table[user].at(i).ID){
            return i;
        }
    }
    return -1;
}