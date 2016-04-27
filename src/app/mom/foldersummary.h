#pragma once

#include <QDomDocument>
#include <vector>
#include <iostream>

#include "filesummary.h"

namespace pl {


class FolderSummary
{
public:
    FolderSummary(const std::string &inputFolder);

    inline void addFile(const FileSummary &file) { files.push_back(file); }

    bool save(const std::string &path, const std::string &filename);

private:
    QDomDocument toXml();

private:
    std::string input;
    std::vector<FileSummary> files;
};


}
