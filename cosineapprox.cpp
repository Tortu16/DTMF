#include "cosineapprox.h"
#include <cmath>
#include <cstring>

/*
 * Constructor
 */
cosapprox::cosapprox()
    : N_ (0), F_ (0.0f), o_(0.0f), o2_(0.0f), part_(0.0f), sign_(0.0f) {
}
/*
 * Destructor
 */

cosapprox::~cosapprox(){
    delete[] jackBuffer_;
    idx_ = 0;
}

void cosapprox::init(int N, float F){

    F_= F;
    N_ = N;

    delete[] jackBuffer_;
    jackBuffer_ = new float[N_];
    memset(jackBuffer_,0,sizeof(float)*N_); // initial conditions: 0

}


float cosapprox::cosine(int n, float F){
    o_ = n*360*F + 90.0;
    o2_ = fmod(o_, 360.0);
    o_ = fmod(o_ , 180.0);
    o2_ = o_ - o2_;
    sign_ = std::signbit(o2_);
    sign_ = 2*sign_ + 1;
    o2_ = 180 - o_;

    part_ = c2_+c3_*o_+c4_*o_*o_+c5_*o_*o_*o_+o_*o_*o_*o_;
    return sign_*part_*c1_*o_*o2_;

}

void cosapprox::tone(int N, float F1, float F2,
                       float*out){
    for (int n = 0; n < N; n++){
        jackBuffer_[idx_] = out[n] = (cosine(idx_, F1) + cosine(idx_, F2))/524880000000.0;
        idx_ = idx_ + 1;
        idx_ = idx_ % 44100; // setting a limit to avoid overflow
    }
}

