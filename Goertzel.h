#ifndef TONEDETECTION
#define TONEDETECTION


float toneDetectionFunction (float *xn, int fk, float fs);


/*
class toneDetection {
public:
    // Constructor
    toneDetection();

    // Destructor
    ~toneDetection();

    // Calculates power in specified frequency over the audio sample.
    float Goertzel (float* xn, int fk, float fs);


private:

    // audio buffer input. Size of this array determines resolution.
    // This buffer must never have less than 256.
    float* xn_;

    // Frequency where Goerzel coefficient will be calculated.
    int fk_;

    // sampling frequency
    float fs_;

    // Goertzel Coefficient
    float Xk_;

    // Auxiliary variables for recursive part of Goertzel
    float wk_, w1_, w2_, c1_;
};
*/
#endif // TONEDETECTION




