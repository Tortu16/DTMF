

class cosapprox {
public:
    /*
     * Constructor
     */

    cosapprox();

    /*
     * Destructor
     */

    ~cosapprox();

    /*
     * Init
     *
     * N = number of samples
     * F = frequency
     *
     */
    void init(int N,
              float F);

    /*
     * Return frequency of cosine generated
     */
    float getFreq() const;

    /*
     * Set frequency of cosine to be generated
     */
    void setFreq(float F);

    /*
     * Return internal index of cosine generated
     */
    int getIndex() const;

    /*
     * Set index of cosine to be generated. Can be used to control phase if needed.
     */
    void setIndex(int idx_);

    /*
     * Return Index of cosine generated
     */
    float getSampleNumber() const;

    /*
     * Set Index of cosine to be generated
     */
    void setSampleNumber(int n);

    /*
     * Calculate the cosine of the angle input, based on the index and frequency
     */
    float cosine (int n, float F);

    /*
     * Calculate the tone based on both frequencies.
     */
    void tone (int N, float F1, float F2, float* out);

private:


    /*
     * Number of samples (Buffer size of the audio buffer)
     */
    int N_;

    /*
     * Frequency to generate
     */
    float F_;

    /*
     * Audio Buffer
     */
    float* jackBuffer_;

    /*
     * Polynomial coefficients
     */
    const float c1_ = 0.019238;
    const float c2_ = 2.6469e+09;
    const float c3_ = 1.4574e+07;
    const float c4_ = -4.8565e+04;
    const float c5_ = -360;

    /*
     * Auxiliary variables for sign calculation
     *
     * o turns sample index to angle.
     *
     * Because the algorithm implemented is for half a sine wave, the angle is shifted
     * by 90 degrees to turn the output into the corresponding cosine.
     *
     */
    float o_;
    float o2_;
    float part_;

    float sign_;

    /* handles an internal index to know what was the last "angle" value of the
     * cosine curve that was calculated.
     */
    int idx_;

};
