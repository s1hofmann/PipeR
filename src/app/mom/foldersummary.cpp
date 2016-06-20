#include "foldersummary.h"

namespace pl {


FolderSummary::FolderSummary(const std::string &inputFolder)
    :
      input(inputFolder)
{
}


bool FolderSummary::save(const std::string &path, const std::string &filename)
{
    QDir outputDir(QString::fromStdString(path));
    QFileInfo absFile(outputDir, QString::fromStdString(filename));
    QFile outFile(absFile.absoluteFilePath());
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Unable to save file!" << std::endl;
        return false;
    }

    QTextStream outStream(&outFile);
    QDomDocument doc = this->toXml();
    outStream << doc.toString();
    outFile.close();

    return true;
}

QDomDocument FolderSummary::toXml()
{
    QDomDocument doc;
    QDomProcessingInstruction instr = doc.createProcessingInstruction("xml",
                                                                      "version='1.0' encoding='UTF-8'");
    doc.appendChild(instr);

    QDomElement root = doc.createElement("summary");
    root.setAttribute("folder", QString::fromStdString(input));
    doc.appendChild(root);

    for(FileSummary f : this->files) {
        root.appendChild(f.toXml());
    }

    return doc;
}


}
