#ifndef ABSTRACT_MATRIX_H
#define ABSTRACT_MATRIX_H

// abstract matrix class
using namespace std;

template <typename T>
class AbstractMatrix {
public:
    int getWidth();
    int getHeight();
    int getArea();

private: 
    void setWidth(int);
    void setHeight(int);
    void setArea(int);
    int width;
    int height;  
    int area;
    
    std::vector<std::vector<T>> data;
};

#endif