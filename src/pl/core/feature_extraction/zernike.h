#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>


class ZernikePolyImpl;

template <typename T>
class ZernikeFeature {
public:
    ZernikeFeature() {
        static_assert(std::is_base_of<ZernikePolyImpl, T>::value, "ZernikePolyImpl type needed.");
    }

    virtual ~ZernikeFeature() {

    }

    cv::Mat compute(cv::Mat &input,
                    std::vector<cv::KeyPoint> &keypoints) {
        return cv::Mat();
    }
};


class ZernikePolyImpl {
public:
    ZernikePolyImpl();

    virtual ~ZernikePolyImpl();

    /**
     * @brief compute Computes a Zernike feature descriptor for a single keypoint
     * @param image Image to extract feature from
     * @param keypoint Feature keypoint
     * @return Keypoint descriptor
     */
    virtual cv::Mat compute(cv::Mat &image,
                            cv::KeyPoint &keypoint) const;

protected:
    /**
     * @brief fak Faculty helper method
     * @param n Degree of faculty
     * @return Faculty of n
     */
    unsigned long long fak(uint32_t n) const {
        if(n < 17) {
            return mFakLookUp[n];
        }
        unsigned long long fak = mFakLookUp[16];
        for(size_t i = 17; i <= n; ++i) {
            fak *= i;
        }
        return fak;
    }

private:
    /**
     * @brief poly Method to compute Zernike polynomial, either real or pseudo
     * @param m
     * @param n
     * @param rho
     * @return
     */
    virtual double poly(int32_t m, int32_t n, double rho) const = 0;

    /**
      * Small faculty lookup table
      */
    constexpr const static unsigned long long mFakLookUp[] = {
        1,
        1, 2, 6, 24,
        120, 720, 5040, 40320,
        362880, 3628800, 39916800, 479001600,
        6227020800, 87178291200, 1307674368000, 20922789888000
    };
};


class ZernikePoly : public ZernikePolyImpl {
public:
    ZernikePoly();

    virtual ~ZernikePoly();

    // ZernikePolyImpl interface
    virtual cv::Mat compute(cv::Mat &image,
                            cv::KeyPoint &keypoint) const override {

    }

private:
    // ZernikePolyImpl interface
    virtual double poly(int32_t m, int32_t n, double rho) const override {
        double r = 0.0;
        for(int32_t s = 0; s <= static_cast<int32_t>((n - m) / 2); ++s) {
            r += (std::pow(-1.0,static_cast<double>(s)) * fak(n-s) * std::pow(static_cast<double>(rho), static_cast<double>(n-2*s)))
                    / (fak(s) * fak((n+m)/2-s) * fak((n-m)/2-s));
        }
        return r;
    }
};


class PseudoZernikePoly : public ZernikePolyImpl {
public:
    PseudoZernikePoly();

    virtual ~PseudoZernikePoly();

    // ZernikePolyImpl interface
    virtual cv::Mat compute(cv::Mat &image,
                            cv::KeyPoint &keypoint) const override {

    }

private:
    // ZernikePolyImpl interface
    virtual double poly(int32_t m, int32_t n, double rho) const override {

    }
};
