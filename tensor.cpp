#include <iostream>
#include <string>
#include <random>
#include <math.h>
#include <fstream>

#include "dais_exc.h"
#include "tensor.h"

#define PI 3.141592654
#define FLT_MAX 3.402823466e+38F /* max value */
#define FLT_MIN 1.175494351e-38F /* min positive value */

using namespace std;


/**
 * Random Initialization
 * 
 * Perform a random initialization of the tensor
 * 
 * @param mean The mean
 * @param std  Standard deviation
 */
void Tensor::init_random(float mean, float std){
    if(data){

        std::default_random_engine generator;
        std::normal_distribution<float> distribution(mean,std);

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                for(int k=0;k<d;k++){
                    this->operator()(i,j,k)= distribution(generator);
                }
            }
        }    

    }else{
        throw(tensor_not_initialized());
    }
    
    
}

Tensor Tensor::operator-(const Tensor &rhs)const{
    if(this->r != rhs.r || this->c != rhs.c || this->d != rhs.d){
        throw std::dimension_mismatch("dimensioni diverse");
    }
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z-rhs.data+x*c*d+y*d+z;
            }
        }
    }
    return ris;
}

Tensor Tensor::operator+(const Tensor &rhs)const{
    if(this->r != rhs.r || this->c != rhs.c || this->d != rhs.d){
        throw std::dimension_mismatch("dimensioni diverse");
    }
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z+rhs.data+x*c*d+y*d+z;
                
            }
        }
    }
    return ris;
}

Tensor Tensor::operator*(const Tensor &rhs)const{
    if(this->r != rhs.r || this->c != rhs.c || this->d != rhs.d){
        throw std::dimension_mismatch("dimensioni diverse");
    }
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z*rhs.data+x*c*d+y*d+z;
            }
        }
    }
    return ris;
}

Tensor Tensor::operator/(const Tensor &rhs)const{
    if(this->r != rhs.r || this->c != rhs.c || this->d != rhs.d){
        throw std::dimension_mismatch("dimensioni diverse");
    }
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z/rhs.data+x*c*d+y*d+z;
            }
        }
    }
    return ris;
}

Tensor Tensor::operator-(const float &rhs)const){
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z-rhs;
            }
        }
    }
    return ris;
}

Tensor Tensor::operator+(const float &rhs)const{
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z+rhs;
            }
        }
    }
    return ris;
}

Tensor Tensor::operator*(const float &rhs)const{
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z*rhs;
            }
        }
    }
    return ris;
}

Tensor Tensor::operator/(const float &rhs)const{
    Tensor ris(this->r,this->c,this->d,0.0);
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                ris.data+x*c*d+y*d+z=this.data+x*c*d+y*d+z/rhs;
            }
        }
    }
    return ris;
}

Tensor & Tensor::operator=(const Tensor &other){
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                this.data+x*c*d+y*d+z=other.data+x*c*d+y*d+z;
            }
        }
    }
    return *this;
}

bool Tensor::operator==(const Tensor& rhs)const{
    for(int x=0; x<r; x++){
        for(int y=0; y<c; y++){
            for (int z=0;z<d; z++) {
                if(abs(this.data+x*c*d+y*d+z-rhs.data+x*c*d+y*d+z)>EPSILON){
                    return false;
                }
            }
        }
    }
    return true;
}

float Tensor::operator()(int i, int j, int k) const{
    float ris;
    if(i>r || j>c || k>d || i<0 || j<0 || k<0){
        throw std::index_out_of_bound("valori fuori dal range");
    }
    for(int x=0; x<i; x++){
        for(int y=0; y<j; y++){
            for (int z=0;z<k; z++) {
                if (x==i-1 && y==j-1 && z==k-1) {
                    ris= *(data+x*c*d+y*d+k);
                }
            }
        }
    }
    return ris;
}


