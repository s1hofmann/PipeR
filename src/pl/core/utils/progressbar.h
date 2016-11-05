#pragma once

#include "terminfo.h"
#include <string>
#include <sstream>
#include <cmath>

template <typename T>
class ProgressBar
{
public:
    ProgressBar(const T totalElements) {
        this->mCurrentProgress = -1;
        this->mCurrentProgressPercent = 0.0;
        this->setDimensions();
        this->mTotalElements = totalElements;
        this->mCurrentElement = 0;
        this->initialize();
        this->drawProgressBar();
    }

    void reset(const T totalElements) {
        this->mCurrentProgress = -1;
        this->mCurrentProgressPercent = 0.0;
        this->setDimensions();
        this->mTotalElements = totalElements;
        this->mCurrentElement = 0;
        this->initialize();
        this->drawProgressBar();
    }

    ProgressBar(const T totalElements, const std::string &label) {
        this->mCurrentProgress = -1;
        this->mCurrentProgressPercent = 0.0;
        this->setDimensions();
        this->mTotalElements = totalElements;
        this->mCurrentElement = 0;
        this->mLabel = label;
        this->initialize();
        this->drawLabel();
        this->drawProgressBar();
    }

    void reset(const T totalElements, const std::string &label) {
        this->mCurrentProgress = -1;
        this->mCurrentProgressPercent = 0.0;
        this->setDimensions();
        this->mTotalElements = totalElements;
        this->mCurrentElement = 0;
        this->mLabel = label;
        this->initialize();
        this->drawLabel();
        this->drawProgressBar();
    }

    void setLabel(const std::string &label) {
        this->mLabel = label;
    }

    void rescale(const T newSize) {
        this->mTotalElements = newSize;

        this->mProgressBarBuffer.str(std::string());
        this->mProgressBarBuffer.clear();

        this->mProgressBarBuffer << "[";

        float_t percent = this->mCurrentElement/(float_t)this->mTotalElements;
        this->mCurrentProgressPercent = std::ceil(100*percent);
        this->mCurrentProgress = percent * this->mProgressBarWidth;
        for(int32_t i = 0; i < this->mCurrentProgress; ++i) {
            this->mProgressBarBuffer << "#";
        }
        for(int32_t i = mCurrentProgress; i < this->mProgressBarWidth; ++i) {
            this->mProgressBarBuffer << " ";
        }
        this->mProgressBarBuffer << "]";

        this->mProgressBar = this->mProgressBarBuffer.str();

        this->mProgressBarBuffer.str(std::string());
        this->mProgressBarBuffer.clear();
        this->mProgressBarBuffer << " " << this->mCurrentProgressPercent << "%";
        this->mProgressBarPercent = this->mProgressBarBuffer.str();

        this->mProgressBarBuffer >> this->mProgressBarPercent;

        this->drawProgressBar();
        this->setDimensions();
        --this->mCurrentProgress;
    }

    std::string getLabel() {
        return this->mLabel;
    }

    void update() {
        float_t percent = this->mCurrentElement/(float_t)this->mTotalElements;
        this->mCurrentProgressPercent = 100*percent;
        int32_t progress = percent * this->mProgressBarWidth;
        if(progress > this->mCurrentProgress) {
            ++this->mCurrentProgress;
            if(progress < this->mProgressBarWidth) {
                this->mProgressBar.replace(progress + 1, 1, "#");
            }

            this->mProgressBarBuffer.str(std::string());
            this->mProgressBarBuffer.clear();
            this->mProgressBarBuffer << " " << this->mCurrentProgressPercent << "%";

            this->mProgressBarBuffer >> this->mProgressBarPercent;

            this->drawProgressBar();
            this->setDimensions();
        }
        ++this->mCurrentElement;
    }

private:
    void drawProgressBar() {
        std::cout << "\r" << this->mProgressBar << " " << this->mProgressBarPercent << std::flush;
    }

    void initialize() {
        this->mProgressBarBuffer.str(std::string());
        this->mProgressBarBuffer.clear();

        this->mProgressBarBuffer << "[";
        for(int32_t i = 0; i < this->mProgressBarWidth; ++i) {
            this->mProgressBarBuffer << " ";
        }
        this->mProgressBarBuffer << "]";

        this->mProgressBar = this->mProgressBarBuffer.str();

        this->mProgressBarBuffer.str(std::string());
        this->mProgressBarBuffer.clear();
        this->mProgressBarBuffer << " 0%";
        this->mProgressBarPercent = this->mProgressBarBuffer.str();
    }

    void drawLabel() {
        if(!this->mLabel.empty()) {
            std::cout << this->mLabel << std::endl;
            for(int32_t i = 0; i < this->mLabel.size(); ++i) {
                std::cout << "=";
            }
            std::cout << std::endl;
        }
    }

    void setDimensions() {
        this->mTotalWidth = this->mTermInfo.getCols();
        this->mProgressBarWidth = this->mTotalWidth - 7;
    }

    int32_t getProgressBarWidth() {
        return this->mProgressBarWidth;
    }

    int32_t getTerminalWidth() {
        return this->mTotalWidth;
    }


//
// DATA
//
    TermInfo mTermInfo;

    T mTotalElements;
    T mCurrentElement;

    std::string mLabel;
    std::string mProgressBar;
    std::string mProgressBarPercent;
    std::stringstream mProgressBarBuffer;

    int32_t mProgressBarWidth;
    int32_t mTotalWidth;

    int32_t mCurrentProgressPercent;
    int32_t mCurrentProgress;
};
