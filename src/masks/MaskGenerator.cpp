//
// Created by Simon Hofmann on 11.12.15.
//

#include "MaskGenerator.h"

namespace pl {

MaskGenerator::MaskGenerator(const std::string &name)
    :
        mIdentifier(name)
{

}

Json::Value MaskGenerator::readJSON(const std::__cxx11::string &file)
{
    Json::Reader reader;
    Json::Value root;

    std::ifstream ifs;
    ifs.open(file, std::ifstream::in);

    bool parsingSuccessfull = reader.parse(ifs, root);

    if(parsingSuccessfull) {
        ifs.close();
        return root;
    } else {
        return Json::Value();
    }
}


MaskGenerator::~MaskGenerator() {

}


}
