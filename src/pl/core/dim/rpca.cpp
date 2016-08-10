#include "rpca.h"


RPCA::RPCA(int _components,
           bool _whiten,
           float _reg)
    : n_components(_components),
      whiten(_whiten),
      reg(_reg)
{}


RPCA::RPCA(const std::string & path)
{
    load(path);
}

void RPCA::fit(const cv::Mat1f & descr)
{
    // make data zero mean
    cv::reduce(descr, mean, 0, CV_REDUCE_AVG);
    cv::Mat1f X(descr.rows, descr.cols);

#ifdef USE_TBB
    tbb::parallel_for(int(0), X.rows, [&](int y) {
        X.row(y) = descr.row(y) - mean;
    }
    );
#else
    for( int y = 0; y < X.rows; y++){
        X.row(y) = descr.row(y) - mean;
    }
#endif

    cv::Mat1f U, S, V;
    cv::SVD::compute(X, S, U, V, cv::SVD::FULL_UV);
    cv::pow(S, 2, variance);
    variance /= X.rows;
    if (n_components <= 0) {
        n_components = X.cols;
    }

    components = V.rowRange(0, n_components);
    if(variance.rows < n_components) {
        whiten = false;
    } else {
        variance = variance.rowRange(0, n_components);
    }

    this->dataLoaded = true;
}

void RPCA::transform(const cv::Mat1f & descr,
                     cv::Mat1f & out) const
{
    if(descr.cols != mean.cols) {
        std::stringstream s;
        s << "Input and mean data missmatch." << std::endl;
        s << "Input: " << descr.size() << " Mean: " << mean.size() << std::endl;
        throw pl::DimensionalityReductionError(s.str(), currentMethod, currentLine);
    } else if(descr.cols != components.cols) {
        std::stringstream s;
        s << "Input and transformation data missmatch." << std::endl;
        s << "Input: " << descr.size() << " Transform: " << components.size() << std::endl;
        throw pl::DimensionalityReductionError(s.str(), currentMethod, currentLine);
    }
    // make data zero-mean
    cv::Mat1f X(descr.rows,descr.cols);
#ifdef USE_TBB
        tbb::parallel_for(int(0), X.rows, [&](int i) {
            X.row(i) = descr.row(i) - mean;
        }
        );
#else
    for( int y = 0; y < X.rows; y++){
        X.row(y) = descr.row(y) - mean;
    }
#endif
    // the actual transformation
    X = X * components.t();

    // whiten the data
    if ( whiten ) {
        cv::Mat1f var_reg = variance.clone();
        var_reg = var_reg.reshape(1, 1);
        if ( reg > 0.0 )
            var_reg += reg;
        cv::sqrt(var_reg, var_reg);
#ifdef USE_TBB
        tbb::parallel_for(int(0), X.rows, [&](int i) {
            cv::Mat1f row = X.row(i);
            row /= var_reg;
        }
        );
#else
        for( int i = 0; i < X.rows; i++ ) {
            cv::Mat1f row = X.row(i);
            row /= var_reg;
        }
#endif
    }
    out = X;
}

void RPCA::dump(const std::string &path)
{
    cv::FileStorage fs(path, cv::FileStorage::WRITE);
    fs << "whiten" << whiten
       << "n_components" << n_components
       << "reg" << reg
       << "mean" << mean
       << "components" << components
       << "variance" << variance;
    fs.release();
}

void RPCA::load(const std::string &path)
{
    cv::FileStorage fs(path, cv::FileStorage::READ);
    if(fs["whiten"].isNone() || fs["whiten"].empty() ||
       fs["n_components"].isNone() || fs["n_components"].empty() ||
       fs["reg"].isNone() || fs["reg"].empty() ||
       fs["mean"].isNone() || fs["mean"].empty() ||
       fs["components"].isNone() || fs["components"].empty() ||
       fs["variance"].isNone() || fs["variance"].empty()) {
        std::stringstream s;
        s << "Unable to load data from file: " << path << std::endl;
        throw pl::DimensionalityReductionError(s.str(), currentMethod, currentLine);
    }

    fs["whiten"] >> whiten;
    fs["n_components"] >> n_components;
    fs["reg"] >> reg;
    fs["mean"] >> mean;
    fs["components"] >> components;
    fs["variance"] >> variance;
    fs.release();
    this->dataLoaded = true;
}
