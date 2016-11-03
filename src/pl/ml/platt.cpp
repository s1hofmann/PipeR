#include "platt.h"
#include <iostream>

#include "../exception/error.h"

namespace pl {


Platt::Platt()
{

}

Platt::~Platt()
{

}

std::pair<double, double> Platt::platt_calibrate(const cv::Mat1d decision,
                                                 const cv::Mat1i labels)
{
    if(decision.rows != labels.rows || decision.cols > 1 || labels.cols > 1) {
        throw MLError("Data missmatch, aborting.");
    }

    double negativeLabel, positiveLabel;
    cv::minMaxIdx(labels, &negativeLabel, &positiveLabel, NULL, NULL);

    unsigned int posPrior = 0;
    unsigned int negPrior = 0; // calculate priors

    for(int i = 0; i < labels.rows; ++i) {
        if(labels.at<int>(i, 0) == static_cast<int>(positiveLabel)) {
            ++posPrior;
        } else {
            ++negPrior;
        }
    }

    // Construct initial values: target support in array t,
    // initial function value in fval
    double hiTarget=(posPrior+1.0)/(posPrior+2.0);
    double loTarget=1/(negPrior+2.0);
    long len = posPrior + negPrior; // Total number of data

    std::vector<double> t;
    double A = 0.0;
    double B = log( (negPrior+1.0 ) / (posPrior+1.0) );
    double fval=0.0;
    for ( int i = 0; i < len; i++ ) {
        if (labels(i,0) > 0)
            t.push_back(hiTarget);
        else
            t.push_back(loTarget);

        double fApB = decision(i,0)*A + B;
        if (fApB >= 0)
            fval += t[i]*fApB + log1p(exp(-fApB));
        else
            fval += (t[i]-1)*fApB + log1p(exp(fApB));
    }

    //Parameter setting
    int maxiter = 100; //Maximum number of iterations
    double minstep = 1e-10; //Minimum step taken in line search
    double sigma = 1e-12; //Set to any value > 0

    for(size_t it = 0; it < maxiter; ++it) {
        //Update Gradient and Hessian (use H' = H + sigma I)
        double h11, h22, h21, g1, g2;
        h11 = h22 = sigma;
        h21 = g1 = g2 = 0.0;
        for ( int i = 0; i < len; i++ ) {
            double fApB = decision(i,0)*A+B;
            double p;
            double q;
            if (fApB >= 0) {
                p = exp(-fApB) / (1.0+exp(-fApB));
                q = 1.0 / (1.0+exp(-fApB));
            }
            else {
                p = 1.0 / (1.0+exp(fApB));
                q = exp(fApB) / (1.0+exp(fApB));
            }
            double d2 = p*q;
            h11 += decision(i,0)*decision(i,0)*d2;
            h22 += d2;
            h21 += decision(i,0)*d2;
            double d1 = t[i]-p;
            g1 += decision(i,0)*d1;
            g2 += d1;
        }
        //Stopping criteria
        if ( std::abs(g1) < 1e-5 && std::abs(g2) < 1e-5 ) {
            break;
        }

        //Compute modified Newton directions
        double det = h11*h22 - h21*h21;
        double dA = -(h22*g1 - h21*g2)/det;
        double dB = -(-h21*g1 + h11*g2)/det;
        double gd = g1*dA + g2*dB;
        double stepsize = 1.0;
        while ( stepsize >= minstep ) { //Line search
            double newA = A + stepsize*dA;
            double newB = B + stepsize*dB;
            double newf = 0.0;

            for ( int i = 0; i < len; i++ ) {
                double fApB = decision(i,0)*newA + newB;
                if (fApB >= 0)
                    newf += t[i]*fApB + log1p(exp(-fApB));
                else
                    newf += (t[i]-1)*fApB + log1p(exp(fApB));
            }

            if ( newf < fval + 0.0001*stepsize*gd ) {
                A = newA;
                B = newB;
                fval = newf;
                break; //Sufficient decrease satisfied
            }
            else {
                stepsize /= 2.0;
            }
        }
        if ( stepsize < minstep ) {
            std::cerr << "Platt: Line search fails" << std::endl;
            break;
        }
        if ( it == maxiter )
            std::cerr << "Platt: Reaching maximum iterations" << std::endl;
    }

    return std::make_pair(A, B);
}

double Platt::sigmoid_predict(double decision_value, double A, double B)
{
    double fApB = decision_value*A+B;
    // 1-p used later; avoid catastrophic cancellation
    if(fApB >= 0) {
        return exp(-fApB)/(1.0+exp(-fApB));
    } else {
        return 1.0/(1+exp(fApB)) ;
    }
}


}
