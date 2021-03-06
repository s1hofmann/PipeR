#include <iostream>

#include <opencv2/core/core.hpp>

#include "app/mom/momprocessor.h"
#include "app/train/trainingprocessor.h"
#include "app/optimize/optimizationprocessor.h"
#include "app/predict/predictor.h"

#ifdef ENABLE_UI
#include <QApplication>
#include "ui/pipelineconfigwindow.h"
#endif

int32_t main(int32_t argc, char *argv[]) {
#ifdef ENABLE_UI
    QApplication appl(argc, argv);
    PipelineConfigWindow a;
    a.show();
    return appl.exec();
#else
    std::string app;
    // TODO: Let cmake take care of this list of enabled apps
    std::vector<std::string> apps = {"mom", "train", "optimize"};

    if(argc < 2) {
        std::cerr << "No application specified. Aborting." << std::endl;
        std::cerr << "Known applications:" << std::endl;
        for(std::string a : apps) {
            std::cout << a << std::endl;
        }
        return -1;
    } else {
        app = argv[1];
    }

#ifdef APP_MOM
    if(!app.compare("mom") || !app.compare("MOM")) {
        try {
            MomProcessor mp(argc, argv);
            return mp.run();
        } catch(pl::CommandLineError) {
            return MomProcessor::ReturnValues::RETURN_COMMANDLINE_ERROR;
        }
    }
#endif
#ifdef APP_TRAIN
    if(!app.compare("train") || !app.compare("TRAIN")) {
        try {
            TrainingProcessor tp(argc, argv);
            return tp.run();
        } catch(pl::CommandLineError) {
            return TrainingProcessor::ReturnValues::RETURN_COMMANDLINE_ERROR;
        }
    }
#endif
#ifdef APP_OPT
    if(!app.compare("optimize") || !app.compare("OPTIMIZE")) {
        try {
            OptimizationProcessor op(argc, argv);
            return op.run();
        } catch(pl::CommandLineError) {
            return OptimizationProcessor::ReturnValues::RETURN_COMMANDLINE_ERROR;
        }
    }
#endif
#ifdef APP_PREDICT
    if(!app.compare("predict") || !app.compare("PREDICT")) {
        try {
            Predictor p(argc, argv);
            return p.run();
        } catch(pl::CommandLineError) {
            return OptimizationProcessor::ReturnValues::RETURN_COMMANDLINE_ERROR;
        }
    }
#endif

    std::cerr << "Unknow application '" << app << "'. Maybe it's disabled?" << std::endl;
    return -1;
#endif
}
