//
// Created by shaqfa on 2019-12-07.
//

#ifndef C__14_CSV_WRITER_H
#define C__14_CSV_WRITER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "types.h"

class csv_dump{
public:
    csv_dump(std::string&);
    ~csv_dump();

    template<typename T>
    void dump(T&);

    template<typename T>
    void dump(std::vector<T>&);
    void dump(RealVec&);
    void dump(UIntVec&);

    template<typename T>
    void dump(std::vector<std::vector<T>>&);
    void dump(RealMat&);
    void dump(UIntMat&);

private:
    std::string fname;
    std::ofstream new_file;

};
#endif //C__14_CSV_WRITER_H