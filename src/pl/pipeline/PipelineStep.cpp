//
// Created by Simon Hofmann on 16.11.15.
//

#include "PipelineStep.h"

namespace pl {


PipelineStep::PipelineStep(const cv::Ptr<ConfigContainer> config)
    :
        mConfig(config)
{

}


PipelineStep::~PipelineStep()
{

}


std::string PipelineStep::help()
{
    return mConfig->help();
}


std::string PipelineStep::usage()
{
    return mConfig->usage();
}


cv::Mat PipelineStep::train(const cv::Mat &input,
                            const cv::Mat &param) const
{
    try {
        return this->trainImpl(false, input, param);
    } catch(const pl::ClusterError &e) {
        throw;
    } catch(const pl::DimensionalityReductionError &e) {
        throw;
    } catch(const pl::EncodingError &e) {
        throw;
    } catch(const pl::FeatureExError &e) {
        throw;
    } catch(const pl::IOError &e) {
        throw;
    } catch(const pl::MLError &e) {
        throw;
    } catch(const pl::OCVError &e) {
        throw;
    } catch(const cv::Exception &e) {
        throw;
    }
}


cv::Mat PipelineStep::debugTrain(const cv::Mat &input,
                                 const cv::Mat &param) const
{
    try {
        return this->trainImpl(true, input, param);
    } catch(const pl::ClusterError &e) {
        throw;
    } catch(const pl::DimensionalityReductionError &e) {
        throw;
    } catch(const pl::EncodingError &e) {
        throw;
    } catch(const pl::FeatureExError &e) {
        throw;
    } catch(const pl::IOError &e) {
        throw;
    } catch(const pl::MLError &e) {
        throw;
    } catch(const pl::OCVError &e) {
        throw;
    } catch(const cv::Exception &e) {
        throw;
    }
}


cv::Mat PipelineStep::run(const cv::Mat &input,
                          const cv::Mat &param) const
{
    try {
        return this->runImpl(false, input, param);
    } catch(const pl::ClusterError &e) {
        throw;
    } catch(const pl::DimensionalityReductionError &e) {
        throw;
    } catch(const pl::EncodingError &e) {
        throw;
    } catch(const pl::FeatureExError &e) {
        throw;
    } catch(const pl::IOError &e) {
        throw;
    } catch(const pl::MLError &e) {
        throw;
    } catch(const pl::OCVError &e) {
        throw;
    } catch(const cv::Exception &e) {
        throw;
    }
}


cv::Mat PipelineStep::debugRun(const cv::Mat &input,
                               const cv::Mat &param) const
{
    try {
        return this->runImpl(true, input, param);
    } catch(const pl::ClusterError) {
        throw;
    } catch(const pl::DimensionalityReductionError &e) {
        throw;
    } catch(const pl::EncodingError &e) {
        throw;
    } catch(const pl::FeatureExError &e) {
        throw;
    } catch(const pl::IOError &e) {
        throw;
    } catch(const pl::MLError &e) {
        throw;
    } catch(const pl::OCVError &e) {
        throw;
    } catch(const cv::Exception &e) {
        throw;
    }
}


std::string PipelineStep::info()
{
    return mConfig->identifier();
}


std::string PipelineStep::config() const {
    return mConfig->toString();
}

std::string PipelineStep::identifier() const
{
    return mConfig->identifier();
}

std::string PseudoPipelineStep::info()
{
    return mConfig->identifier();
}

std::string PseudoPipelineStep::help()
{
    return mConfig->help();
}

std::string PseudoPipelineStep::usage()
{
    return mConfig->usage();
}

std::string PseudoPipelineStep::config() const
{
    return mConfig->toString();
}

PseudoPipelineStep::PseudoPipelineStep(const cv::Ptr<ConfigContainer> config)
    :
        mConfig(config)
{

}

PseudoPipelineStep::~PseudoPipelineStep()
{

}


}
