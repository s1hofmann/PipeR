#include <iostream>

#include <opencv2/core/core.hpp>
#include "app/mom/momprocessor.h"


int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cerr << "No application specified. Aborting." << std::endl;
    } else {
        std::string app = argv[1];

        if(!app.compare("mom")) {
            try {
                MomProcessor mp(argc, argv);
                return mp.run();
            } catch(pl::CommandLineError) {
                return MomProcessor::ReturnValues::RETURN_COMMANDLINE_ERROR;
            }
        }
    }
    return 0;
}
