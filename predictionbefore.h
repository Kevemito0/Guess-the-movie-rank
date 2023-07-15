#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "hashT.h"
#include "algorithm"
#include "cmath"

/*
struct info{
    int movie_id;
    double rank;
    int user_id;
};
*/

class predictionbefore{
public:
    bool compareMovies(const info &a, const info &b);
    predictionbefore();
    ~predictionbefore();
    void setuser_length(int user);
    void setmovie_length(int movie);
    int getmovie_length();
    int getuser_length();
    void reading_input(std::string const& file_name);
    void merge(info *array, int p, int q, int r);
    void mergeSort(info *arr, int l, int r);
    void print();
    void print_file();
    void print_rec();
    void finding_rank();
    void predict(std::string const& file_name);
    void print_map();
private:
    info *rank_user;
    info *rank_movie;
    info arr;
    int user_length;
    int movie_length;
    int max_user = 0;
    int max_movie = 0;
    std::unordered_map<int,info> rating_user;
    int hashfunc(int key);
    // int *topUser;
    // int *topMovie;
    int length;
    double** data;
    int **rec;
    hashT information;
    // info rank;
    // info movie_id;
};

void predictionbefore::setuser_length(int user) {
    if(max_user <= user){
        max_user = user;
    }
    user_length = max_user;
}
void predictionbefore::setmovie_length(int movie) {
    if(max_movie <= movie){
        max_movie = movie;
    }
    movie_length = max_movie;
}

int predictionbefore::getmovie_length() {
    return movie_length;
}
int predictionbefore::getuser_length() {
    return user_length;
}

bool predictionbefore::compareMovies(const info &a, const info &b){
    return a.rank < b.rank;
}

void predictionbefore::print_map() {
    information.print_file();
}

void predictionbefore::merge(info* movies, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;
    info temp[right - left + 1];

    while (i <= mid && j <= right) {
        if (compareMovies(movies[i], movies[j])) {
            temp[k++] = movies[i++];
        } else {
            temp[k++] = movies[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = movies[i++];
    }

    while (j <= right) {
        temp[k++] = movies[j++];
    }

    for (int l = 0; l < k; l++) {
        movies[left + l] = temp[l];
    }
}
void predictionbefore::mergeSort(info* movies, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(movies, left, mid);
        mergeSort(movies, mid + 1, right);
        merge(movies, left, mid, right);
    }
}

// right siniri icin sayi degistirebiliriz daha hizli ve sabit olur //
void predictionbefore::finding_rank() {
    for(int i = 0; i < getuser_length() + 1; i++){
        for(int k = 0; k < getmovie_length()+1;k++) {
            if (rec[i][k] == 1){
                rank_movie[k].movie_id = k;
                rank_movie[k].rank += 1;
                rank_user[i].user_id = i;
                rank_user[i].rank += 1;
            }
        }
    }

    mergeSort(rank_movie,0,getmovie_length());
    mergeSort(rank_user,0,getuser_length());

    std::cout << "--------FOR USERS-------------" << std::endl;


    int stop = 0;
    for(int i = user_length; i >=0; i--){
        if(rank_user[i].rank >= 1 && stop != 10){
            std::cout << "User: " << rank_user[i].user_id << " ranked a movie: " << rank_user[i].rank << " times" << std::endl;
            stop++;
        }
    }

    std::cout << "--------FOR MOVIES-------------" << std::endl;


    int stop_movie = 0;
    for(int i = movie_length; i >= 0; i--){
        if(rank_movie[i].rank >= 1 && stop_movie != 10){
            std::cout << "Movie: " << rank_movie[i].movie_id << "  " << rank_movie[i].rank << " times ranked" << std::endl;
            stop_movie++;
        }
    }
}


// oy verenler ile vermeyenleri ayiran arrayin output kontrolu //
void predictionbefore::print_rec() {
    for(int i = 1 ; i < 100000 ; i++) {
        for (int k = 1; k < 10000; k++) {
            if(rec[i][k] == 1){
                std::cout << "User: " << i << " movieID: "<< k << " Rank: ";
                std::cout << data[i][k] << std::endl;
            }
        }
    }
}


predictionbefore::predictionbefore() {
    rank_movie = new info[10000];
    rank_user = new info[100000];
    for(int i = 0; i < 10000; i++){
        rank_movie[i].rank = 0;
    }
    for(int i = 0; i < 100000;i++){
        rank_user[i].rank = 0;
    }
    // topUser = new int[10];
    // topMovie = new int[10];
    rec = new int*[100000];
    for(int i = 0; i < 100000; i++){
        rec[i] = new int[10000];
    }
    data = new double*[100000];
    for(int k = 0; k <100000; ++k){
        data[k] = new double[10000];
    }
}

void predictionbefore::reading_input(std::string const& file_name) {
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
            data[a][b] = c;
            rec[a][b] = 1;
            // burda hash tablea info yükledigimiz icin temp acip rating falan koyup hashe yukluyoruz
            info temp;
            temp.rank = c;
            temp.movie_id = b;
            temp.user_id = a;
            information.insert(a,temp);
            index++;
        }
        input.close();
    }
    length = index;
}
// hash tabli printliyo //
void predictionbefore::print() {
    information.print();
}

predictionbefore::~predictionbefore(){
    // delete topMovie;
    // delete topUser;
    for(int i = 0; i < 10000; ++i) {
        delete [] data[i];
        delete [] rec[i];
    }
    delete rank_movie;
    delete rank_user;
    delete [] data;
    delete [] rec;
}

void predictionbefore::print_file() {
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

void predictionbefore::predict(std::string const& file_name) {
    std::ifstream input;
    input.open(file_name);
    std::string line;
    if(input.is_open()) {
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


            double mul = 0.0;
            double sum1 = 0.0;
            double sum2 = 0.0;
            double similarity[100001];

            for(int i = 1; i < user_length; i++){
                if(i != b){
                    for(int j = 1; j < movie_length; j++){
                        if(j != c){
                            if(rec[i][j] != 0 || rec[b][j] != 0) {
                                mul += data[i][j] * data[b][j];
                                sum1 += pow(data[i][j], 2);
                                sum2 += pow(data[b][j], 2);
                            }
                        }
                    }
                    similarity[i] = abs(1-(mul / (sqrt(sum1)*sqrt(sum2))));

                }
            }

            int mostSimilarUser = 1;

            for(int k = 2; k <= user_length; k++){
                if(k != b){
                    if(similarity[k] > similarity[mostSimilarUser]){
                        if(rec[k][c] == 1){
                            mostSimilarUser = k;
                        }
                    }
                }
            }

            rec[b][c] = rec[mostSimilarUser][c];

            std::cout<<"movie_id: "<<a<<" UserID: "<<b<<" MovieID:"<<c<<" Prediction: "<<data[b][c]<<std::endl;
        }
        input.close();
    }
}
