#include "Goertzel.h"
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

float segundaArmonica (float *xn, int fk, float fs){
    float wk_ = 0.0;
    float w1_ = 0.0;
    float w2_ = 0.0;
    float c1_ = 0.0;
    float Xk_ = 0.0; 
//1394     1540     1704     1882     2418     2672     2954     3266
//1.9607   1.9521   1.9413   1.9285   1.8825   1.8568   1.8255   1.7874
    switch (fk){
    case 1394:
        c1_ = 1.9607;
        break;
    case 1540:
        c1_ = 1.9521;
        break;
    case 1704:
        c1_ = 1.9413;
        break;
    case 1882:
        c1_ = 1.9285;
        break;
    case 2418:
        c1_ = 1.8825;
        break;
    case 2672:
        c1_ = 1.8568;
        break;
    case 2954:
        c1_ = 1.8255;
        break;
    case 3266:
        c1_ = 1.7874;
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
