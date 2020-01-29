//
// Created by shaqfa on 2019-12-07.
//

#include "csv_writer.h"

csv_dump::csv_dump(std::string& file_name): fname(file_name) {
    file_name+=".csv";
    new_file.open(file_name);
}

csv_dump::~csv_dump() {new_file.close();}

template <class T>
void csv_dump::dump(T& dumped_value) {
    new_file << dumped_value<<"\n";
}

template <class T>
void csv_dump::dump(std::vector<T>& dumped_vector) {
    for(auto&& v: dumped_vector)
        new_file << v <<"\n";
}

void csv_dump::dump(RealVec& dumped_vector) {
    for(auto&& v: dumped_vector)
        new_file << v <<"\n";
}

void csv_dump::dump(UIntVec& dumped_vector) {
    for(auto&& v: dumped_vector)
        new_file << v <<"\n";
}

template<typename T>
void csv_dump::dump(std::vector<std::vector<T>>& dumped_matrix) {
    UInt Id_cols = 0, Id_rows = 0;
    for (auto& row : dumped_matrix) {
        Id_cols = 0;
        for (auto col : row){
            new_file << col;
            if (Id_cols < (dumped_matrix[0].size() - 1))
                new_file <<",";
            Id_cols++;
        }
        if (Id_rows < (dumped_matrix.size() - 1))
            new_file << std::endl;
    }
}

void csv_dump::dump(RealMat& dumped_matrix) {
    UInt Id_cols = 0, Id_rows = 0;
    for (auto& row : dumped_matrix) {
        Id_cols = 0;
        for (auto col : row){
            new_file << col;
            if (Id_cols < (dumped_matrix[0].size() - 1))
                new_file <<",";
            Id_cols++;
        }
        if (Id_rows < (dumped_matrix.size() - 1))
            new_file << std::endl;
    }
}

void csv_dump::dump(UIntMat& dumped_matrix) {
    UInt Id_cols = 0, Id_rows = 0;
    for (auto& row : dumped_matrix) {
        Id_cols = 0;
        for (auto col : row){
            new_file << col;
            if (Id_cols < (dumped_matrix[0].size() - 1))
                new_file <<",";
            Id_cols++;
        }
        if (Id_rows < (dumped_matrix.size() - 1))
            new_file << std::endl;
    }
}