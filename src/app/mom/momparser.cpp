#include "momparser.h"

namespace pl {


MOMParser::MOMParser()
{

}


std::vector<EvaluationObject> MOMParser::parse(const std::string &fileName) const
{
    QFile annotationFileNode(QString::fromStdString(fileName));

    if(!annotationFileNode.open(QIODevice::ReadOnly)) {
        std::cerr << "Unable to read annotation file. Exiting!" << std::endl;
        exit(-1);
    }

    QDomDocument doc;
    if(doc.setContent(&annotationFileNode)) {
        annotationFileNode.close();
    } else {
        std::cerr << "Unable to parse XML. Exiting!" << std::endl;
        exit(1);
    }

    QDomNodeList fileNodeList = doc.documentElement().elementsByTagName("file");

    std::cout << "Found " << fileNodeList.size() << " elements." << std::endl;
    std::vector<EvaluationObject> evaluationObjects;

    for(size_t idx = 0; idx < fileNodeList.size(); ++idx) {
        QDomNode currentNode = fileNodeList.at(idx);
        std::string fileName = currentNode.attributes().namedItem("filename").nodeValue().toStdString();

        QDomElement currentElement = currentNode.toElement();
        QDomNodeList objectNodeList = currentElement.elementsByTagName("object");

        std::vector<cv::Rect> boundingBoxes;
        std::vector<std::vector<cv::Point>> contours;

        for(size_t oIdx = 0; oIdx < objectNodeList.size(); ++oIdx) {
            QDomElement objectElement = objectNodeList.at(oIdx).toElement();
            QDomNodeList boxList = objectElement.elementsByTagName("bbox");
            QDomNodeList contourList = objectElement.elementsByTagName("fixpoints");

            for(size_t bIdx = 0; bIdx < boxList.size(); ++bIdx) {
                QDomElement bbox = boxList.at(bIdx).toElement();
                boundingBoxes.push_back(createBoundingBox(bbox.text().toStdString()));
            }

            for(size_t cIdx = 0; cIdx < contourList.size(); ++cIdx) {
                QDomElement contour = contourList.at(cIdx).toElement();
                contours.push_back(createContour(contour.text().toStdString()));
            }
        }

        if(boundingBoxes.size() > 0) {
            evaluationObjects.push_back(EvaluationObject(fileName,
                                                         boundingBoxes,
                                                         contours));
        } else {
            std::cout << "No annotations given, skipping." << std::endl;
        }
    }

    std::cout << "Parsed " << evaluationObjects.size() << " items." << std::endl;

    return evaluationObjects;
}


cv::Rect MOMParser::createBoundingBox(const std::string &annotation) const
{
    std::vector<std::string> strCoords = split(annotation, ',');

    return cv::Rect(std::stoi(strCoords[0]),
                    std::stoi(strCoords[1]),
                    std::stoi(strCoords[2]),
                    std::stoi(strCoords[3]));
}


std::vector<cv::Point> MOMParser::createContour(const std::string &annotation) const
{
    std::vector<std::string> strPoints = split(annotation, ',');

    std::vector<cv::Point> contour;
    for(size_t idx = 0; idx < strPoints.size(); idx += 2) {
        contour.push_back(cv::Point(std::stoi(strPoints[idx]), std::stoi(strPoints[idx+1])));
    }

    return contour;
}


}
