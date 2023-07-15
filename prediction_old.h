#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "algorithm"
#include "cmath"
#include <algorithm>
struct info{
    int ID;
    double rank;
};
            // KEREM ÇAKILLI 2003611
class prediction_old{
public:
    bool compareMovies(const info &a, const info &b);
    prediction_old();
    ~prediction_old();
    void reading_input(std::string const& file_name);
    void mergeSort(info *movies, int left, int right);
    void merge(info *movies, int left, int mid, int right);
    void finding_rank();
    void setuser_length(int user);
    void setmovie_length(int movie);
    int getmovie_length();
    int getuser_length();
    void predict(std::string const& file_name);

private:
    info *rank_user;
    info *rank_movie;
    int **rec;
    double **dats;
    int user_length;
    int movie_length;
    int max_user = 0;
    int max_movie = 0;

};

int prediction_old::getmovie_length() {
    return movie_length;
}
int prediction_old::getuser_length() {
    return user_length;
}


void prediction_old::setuser_length(int user) {
    if(max_user <= user){
        max_user = user;
    }
    user_length = max_user;
}
void prediction_old::setmovie_length(int movie) {
    if(max_movie <= movie){
        max_movie = movie;
    }
    movie_length = max_movie;
}


bool prediction_old::compareMovies(const info &a, const info &b){
    return a.rank > b.rank;
}


void prediction_old::mergeSort(info *movies, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(movies, left, mid);
        mergeSort(movies, mid + 1, right);
        merge(movies, left, mid, right);
    }
}


void prediction_old::merge(info *movies, int left, int mid, int right) {
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

void prediction_old::finding_rank() {

    mergeSort(rank_movie,0,getmovie_length());
    mergeSort(rank_user,0,getuser_length());

    std::cout << "--------FOR USERS-------------" << std::endl;


    for(int i = 0; i < 10; i++){
        if(rank_user[i].rank >= 1){
            std::cout << "User: " << rank_user[i].ID << " ranked a movie: " << rank_user[i].rank << " times" << std::endl;
        }
    }

    std::cout << "--------FOR MOVIES-------------" << std::endl;


    for(int i = 0; i < 10; i++){
        if(rank_movie[i].rank >= 1){
            std::cout << "Movie: " << rank_movie[i].ID << "  " << rank_movie[i].rank << " times ranked" << std::endl;
        }
    }


}


prediction_old::prediction_old() {
    dats = new double*[36000];
    rec = new int*[36000];
    for(int i = 0; i < 36000; i++){
        rec[i] = new int[8000];
        for(int k = 0; k < 8000; k++){
            rec[i][k] = 0;
        }
    }
    dats = new double*[36000];
    for(int k = 0; k <36000; ++k){
        dats[k] = new double[8000];
    }
    rank_user = new info[36000];
    rank_movie = new info[8000];
    for(int i = 0; i < 8000; i++){
        rank_movie[i].rank = 0;
    }
    for(int i = 0; i < 36000;i++){
        rank_user[i].rank = 0;
    }

}

void prediction_old::reading_input(std::string const& file_name) {
    std::ifstream input;
    input.open(file_name);
    std::string line;
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

            dats[a][b] = c;
            rec[a][b] = 1;
            rank_user[a].rank += 1;
            rank_user[a].ID = a;
            rank_movie[b].rank += 1;
            rank_movie[b].ID = b;
            setmovie_length(b);
            setuser_length(a);
        }
        input.close();
    }
}

void prediction_old::predict(std::string const& file_name) {
    std::ifstream input;
    input.open(file_name);
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
            double sum1 = 0.0;
            double sum2 = 0.0;
            double mul = 0.0;
            int k1 = 0; int k2 = 0; int k3 = 0; int k4 = 0; int k5 = 0;
            double avg = 0;
            double similarity[36000];
            for(int i = 0; i < 36000;i++){
                if(rec[i][c] == 1 && i != b) {
                    for (int k = 0; k < 8000; k++) {
                        if(rec[i][k] == 1 && rec[b][k] == 1){
                            sum1 += pow(dats[i][k],2);
                            sum2 += pow(dats[b][k],2);
                            mul += dats[b][k] * dats[i][k];
                        }
                    }
                    if(sum1 != 0 && sum2 != 0)
                        similarity[i] = mul / (sqrt(sum1)* sqrt(sum2));
                }
            }
            int mostSimilarUser = 42;
            for(int k = 0; k < 36000;k++){
                if(k!= b){
                    if(similarity[k] > similarity[mostSimilarUser] && rec[k][c] == 1) {
                        mostSimilarUser = k;
                    }

                    else if(similarity[k] > similarity[k1] && rec[k1][c] == 1 ){
                        k1 = k;
                    }
                    else if(similarity[k] > similarity[k2] && rec[k][c] == 1){
                        k2 = k;
                    }

                    else if(similarity[k] > similarity[k3] && rec[k][c] == 1){
                        k3 = k;
                    }
                    else if(similarity[k] > similarity[k4] && rec[k][c] == 1){
                        k4 = k;
                    }
                    else if(similarity[k] > similarity[k5] && rec[k][c] == 1){
                        k5 = k;
                    }

                }
            }
            avg = (dats[mostSimilarUser][c] + dats[k1][c] + dats[k2][c]  + dats[k3][c] + dats[k4][c] + dats[k5][c]  ) / 6;
            std::cout << a << ", " << avg << std::endl;
        }
    }
    input.close();
}


prediction_old::~prediction_old() {
    for(int i = 0; i < 8000; ++i) {
        delete [] dats[i];
        delete [] rec[i];
    }
    delete [] dats;
    delete [] rec;
    delete rank_movie;
    delete rank_user;
}