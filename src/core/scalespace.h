#pragma once


#include <vector>
#include <opencv2/core/core.hpp>


namespace pipe {


class ScaleSpace {

public:
    ScaleSpace(int _n_ocataves,
               int _n_sublevels)
        : n_octaves(_n_ocataves),
          n_sublevels(_n_sublevels) {}

    virtual ~ScaleSpace(){}

    virtual void compute(const cv::Mat & img,
                         std::vector<cv::Mat> & scales) = 0;

//protected:
    double getScaleFactor(int o, int s) const {
        return std::pow(2, o + (float) s / (float) n_sublevels );
    }

protected:
    int n_octaves;
    int n_sublevels;

};

class LinearScaleSpace : public ScaleSpace
{
public:
    LinearScaleSpace(int _n_octaves = 2,
                     int _n_sublevels = 3)
        : ScaleSpace(_n_octaves, _n_sublevels) {}
    void compute(const cv::Mat & img,
                 std::vector<cv::Mat> & scales);
};

class GaussianScaleSpace : public ScaleSpace
{
public:
    GaussianScaleSpace(int _n_octaves = 4,
                       int _n_sublevels = 3,
                       double _sigma_base = 1.6,
                       bool _scale_octave = true,
                       bool _scale_sublevel = false)
        : ScaleSpace(_n_octaves, _n_sublevels),
          sigma_base(_sigma_base),
          scale_octave(_scale_octave),
          scale_sublevel(_scale_sublevel)
    {}
    void compute(const cv::Mat & img,
                 std::vector<cv::Mat> & scales);

private:
    double sigma_base;
    bool scale_octave;
    bool scale_sublevel;
};


}
