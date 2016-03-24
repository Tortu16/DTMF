#include "tono.h"
#include <cmath>


float toneDetectionFunction (float *xn, int fk, float fs){
    float wk_ = 0.0;
    float w1_ = 0.0;
    float w2_ = 0.0;
    float c1_ = 0.0;
    float Xk_ = 0.0; 

    switch (fk){
    case 697:
        c1_ = 1.9901;
        break;
    case 770:
        c1_ = 1.9880;
        break;
    case 852:
        c1_ = 1.9853;
        break;
    case 941:
        c1_ = 1.9821;
        break;
    case 1209:
        c1_ = 1.9704;
        break;
    case 1336:
        c1_ = 1.9639;
        break;
    case 1477:
        c1_ = 1.9559;
        break;
    case 1633:
        c1_ = 1.9461;
        break;
    default:
        c1_ = 0;
    }

    for (int i=0; i< 512; i++){
        w2_ = w1_;
        w1_ = wk_;
        wk_ = xn[i] + c1_*w1_-w2_;
    }

    Xk_ = w1_*w1_ + w2_*w2_ - c1_*w1_*w2_;

    return Xk_;

}



/*
toneDetection::toneDetection()
    : xn_ (0), fk_ (0), fs_(0), Xk_(0), wk_(0), w1_(0), w2_(0){
    }

toneDetection::~toneDetection(){
    delete[] xn_;
}

float toneDetection::Goertzel(float *xn, int fk, float fs){
    wk_ = 0.0;
    w1_ = 0.0;
    w2_ = 0.0;
    xn_ = xn;
    fk_ = fk;
    fs_ = fs; // it is assumed fs = 44100 always.

    switch (fk){
    case 697:
        c1_ = 1.9901;
        break;
    case 770:
        c1_ = 1.9880;
        break;
    case 852:
        c1_ = 1.9853;
        break;
    case 941:
        c1_ = 1.9821;
        break;
    case 1209:
        c1_ = 1.9704;
        break;
    case 1336:
        c1_ = 1.9639;
        break;
    case 1477:
        c1_ = 1.9559;
        break;
    case 1633:
        c1_ = 1.9461;
        break;
    default:
        c1_ = 0;
    }

    for (int i=0; i< 1024; i++){
        w2_ = w1_;
        w1_ = wk_;
        wk_ = xn_[i] + c1_*w1_-w2_;
    }

    Xk_ = w1_*w1_ + w2_*w2_ - c1_*w1_*w2_;

    return Xk_;

}
*/
