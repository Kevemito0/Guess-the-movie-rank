#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include "algorithm"

struct info{
    int movie_id;
    int rank;
};

class prediction3{
public:
    bool compareMovies(const info &a, const info &b);
    prediction3();
    ~prediction3();
    void prediction();
    void reading_input(std::string const& file_name);
    void heapify(int *arr, int n, int i);
    void heap_sort(int *arr,int n);
    void merge(info* movies, int left, int mid, int right);
    void mergeSort(info* movies, int left, int right);
    void print();
    void print_file();
    void topTenMovies();
    void topTenUsers();
    void print_rec();
    void finding_rank();
private:
    info *rank_user;
    info *rank_movie;
    int length;
    double** data;
    int **rec;
};

void prediction3::prediction() {

}

bool prediction3::compareMovies(const info &a, const info &b){
    return a.rank < b.rank;
}

void prediction3::merge(info* movies, int left, int mid, int right) {
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
void prediction3::mergeSort(info* movies, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(movies, left, mid);
        mergeSort(movies, mid + 1, right);
        merge(movies, left, mid, right);
    }
}

// right siniri icin sayi degistirebiliriz daha hizli ve sabit olur //
void prediction3::finding_rank() {
    for(int i = 1; i < 100000; i++){
        for(int k = 1; k < 10000;k++) {
            if (rec[i][k] == 1){
                rank_movie[k].movie_id = k;
                rank_movie[k].rank += 1;
                rank_user[i].movie_id = i;
                rank_user[i].rank += 1;
            }
        }
    }

    //burdaki 10000 - 1 yerine //
     mergeSort(rank_movie,0,10000-1);
     mergeSort(rank_user,0,100000-1);

    //top10 user ve movie icin ayri bi array acilip icine atilabilir boylece bosuna 100k aramamis olur//
    int stop = 0;
    for(int i = 100000; i >=0; i--){
        if(rank_user[i].rank >= 1 && stop != 10){
            std::cout << "User: " << rank_user[i].movie_id << " ranked a movie: " << rank_user[i].rank << " times" << std::endl;
            stop++;
        }
    }

    std::cout << "--------FOR MOVIES-------------" << std::endl;


    int stop_movie = 0;
    for(int i = 10000; i >= 0; i--){
        if(rank_movie[i].rank >= 1 && stop_movie != 10){
            std::cout << "Movie: " << rank_movie[i].movie_id << "  " << rank_movie[i].rank << " times ranked" << std::endl;
            stop_movie++;
        }
    }
}

    // oy verenler ile vermeyenleri ayiran arrayin output kontrolu //
void prediction3::print_rec() {
    for(int i = 1 ; i < 100000 ; i++) {
        for (int k = 1; k < 10000; k++) {
            if(rec[i][k] == 1){
                std::cout << "User: " << i << " movieID: "<< k << " Rank: ";
                std::cout << data[i][k] << std::endl;
            }
        }
    }
}


void prediction3::heapify(int *arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void prediction3::heap_sort(int *arr, int n) {
// Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

prediction3::prediction3() {
    rank_movie = new info[10000];
    rank_user = new info[100000];
    length = 0;
    rec = new int*[100000];
    for(int i = 0; i < 100000; i++){
        rec[i] = new int[10000];
    }
    data = new double*[100000];
    for(int k = 0; k <100000; ++k){
        data[k] = new double[10000];
    }
}

void prediction3::reading_input(std::string const& file_name) {
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
            index++;
        }
        input.close();
    }
    length = index;
}
 // inputtan aldigimiz raw datayi direkt yazdiriyor kontrol amacli print //
void prediction3::print() {
    std::cout << "UserID " << "ItemID " << "Ratings" << std::endl;
    for(int userID = 1 ; userID < 100000 ; userID++) {
            for (int movieID = 1; movieID < 10000; movieID++) {
                if(rec[userID][movieID] == 1){
                    std::cout << userID << " " << movieID << " "<< data[userID][movieID] << std::endl;
                }
            }
    }
}

void prediction3::topTenMovies() {
    double ratingOrder[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int movieOrder[11] = {0,0,0,0,0,0,0,0,0,0,0};;

    double temp = 0;

    for(int i = 1; i < 7000; i++){
        for(int j = 1; j < 100000; j++){
            temp += data[j][i];
        }

        if(ratingOrder[1] <= temp){
            for(int q = 9; q > 0; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[1] = temp;
            movieOrder[1] = i;

        }else if(ratingOrder[2] <= temp){
            for(int q = 9; q > 1; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[2] = temp;
            movieOrder[2] = i;


        }else if(ratingOrder[3] <= temp){
            for(int q = 9; q > 2; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[3] = temp;
            movieOrder[3] = i;


        }else if(ratingOrder[4] <= temp){
            for(int q = 9; q > 3; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[4] = temp;
            movieOrder[4] = i;


        }else if(ratingOrder[5] <= temp){
            for(int q = 9; q > 4; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[5] = temp;
            movieOrder[5] = i;


        }else if(ratingOrder[6] <= temp){
            for(int q = 9; q > 5; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[6] = temp;
            movieOrder[6] = i;


        }else if(ratingOrder[7] <= temp){
            for(int q = 9; q > 6; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[7] = temp;
            movieOrder[7] = i;


        }else if(ratingOrder[8] <= temp){
            for(int q = 9; q > 7; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[8] = temp;
            movieOrder[8] = i;


        }else if(ratingOrder[9] <= temp){
            for(int q = 9; q > 8; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                movieOrder[q + 1] = movieOrder[q];
            }
            ratingOrder[9] = temp;
            movieOrder[9] = i;


        }else if(ratingOrder[10] <= temp){
            ratingOrder[10] = temp;
            movieOrder[10] = i;

        }

        temp = 0;
    }
    std::cout<<"--------TOP 10 MOVIES-------"<<std::endl;
    for(int i = 1; i < 11; i++){
        std::cout<<"MovieID "<<movieOrder[i]<<"  Rating "<<ratingOrder[i]<<std::endl;
    }
}

void prediction3::topTenUsers() {
    double ratingOrder[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int userOrder[11] = {0,0,0,0,0,0,0,0,0,0,0};

    double temp = 0;

    for(int i = 1; i < 7000; i++){
        for(int j = 1; j < 100000; j++){
            temp += data[j][i];
        }

        if(ratingOrder[1] <= temp){
            for(int q = 9; q > 0; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[1] = temp;
            userOrder[1] = i;

        }else if(ratingOrder[2] <= temp){
            for(int q = 9; q > 1; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[2] = temp;
            userOrder[2] = i;


        }else if(ratingOrder[3] <= temp){
            for(int q = 9; q > 2; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[3] = temp;
            userOrder[3] = i;


        }else if(ratingOrder[4] <= temp){
            for(int q = 9; q > 3; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[4] = temp;
            userOrder[4] = i;


        }else if(ratingOrder[5] <= temp){
            for(int q = 9; q > 4; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[5] = temp;
            userOrder[5] = i;


        }else if(ratingOrder[6] <= temp){
            for(int q = 9; q > 5; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[6] = temp;
            userOrder[6] = i;


        }else if(ratingOrder[7] <= temp){
            for(int q = 9; q > 6; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[7] = temp;
            userOrder[7] = i;


        }else if(ratingOrder[8] <= temp){
            for(int q = 9; q > 7; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[8] = temp;
            userOrder[8] = i;


        }else if(ratingOrder[9] <= temp){
            for(int q = 9; q > 8; q--){
                ratingOrder[q + 1] = ratingOrder[q];
                userOrder[q + 1] = userOrder[q];
            }
            ratingOrder[9] = temp;
            userOrder[9] = i;


        }else if(ratingOrder[10] <= temp){
            ratingOrder[10] = temp;
            userOrder[10] = i;

        }

        temp = 0;
    }
    std::cout<<"--------TOP 10 USER-------"<<std::endl;
    for(int i = 1; i < 11; i++){
        std::cout<<"UserID "<<userOrder[i]<<"  Rating "<<ratingOrder[i]<<std::endl;
    }
}


prediction3::~prediction3(){
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

void prediction3::print_file() {
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