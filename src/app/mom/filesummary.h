#pragma once

#include <vector>
#include <opencv2/core/core.hpp>
#include <QtXml>

namespace pl {


enum decorationNiveau {
    NIVEAU_GRAPHICAL = 1,
    NIVEAU_RICH = 2,
    NIVEAU_STANDARD = 3,
    NIVEAU_NONE = 4
};


class FileSummary
{
public:
    FileSummary(const std::string &fileName = std::string(),
                const int width = -1,
                const int height = -1,
                const decorationNiveau niv = decorationNiveau::NIVEAU_NONE);

    ~FileSummary() { }

    inline std::string getFileName() const { return fileName; }
    inline void setFileName(const std::string &file) { fileName = file; }

    inline int getImageWidth() const { return imageWidth; }
    inline void setImageWidth(const int width) { imageWidth = width; }

    inline int getImageHeight() const { return imageHeight; }
    inline void setImageHeight(const int height) { imageHeight = height; }

    inline decorationNiveau getDecorationNiveau() const { return niveau; }
    inline void setDecorationNiveau(const decorationNiveau niv) { niveau = niv; }

    inline int hasTextAreas() const { return textAreas.size(); }
    inline std::vector<cv::Rect> getTextAreas() const { textAreas; }
    inline void addTextArea(const cv::Rect &area) { textAreas.push_back(area); }

    QDomElement toXml();

private:
    QDomElement addXmlEntry(QDomDocument &doc,
                            QDomNode &node,
                            const std::string &tag,
                            const std::string &value = std::string());

private:
    std::vector<cv::Rect> textAreas;

    decorationNiveau niveau;

    std::string fileName;

    int imageWidth;
    int imageHeight;
};


}
