#include "filesummary.h"

namespace pl {

FileSummary::FileSummary(const std::string &fileName, const int width, const int height, const decorationNiveau niv)
    :
      fileName(fileName),
      imageWidth(width),
      imageHeight(height),
      niveau(niv)
{

}

QDomElement FileSummary::toXml()
{
    QDomDocument tmp;
    QDomElement root = tmp.createElement("file");
    root.setAttribute("filename", QString::fromStdString(this->fileName));
    tmp.appendChild(root);

    addXmlEntry(tmp,
                root,
                "width",
                std::to_string(this->imageWidth));

    addXmlEntry(tmp,
                root,
                "height",
                std::to_string(this->imageHeight));

    addXmlEntry(tmp,
                root,
                "niveau",
                std::to_string(this->niveau));

    if(!this->textAreas.empty()) {
        QDomElement text = addXmlEntry(tmp,
                                       root,
                                       "object");

        for(cv::Rect r : this->textAreas) {
            std::stringstream ss;
            ss << r.x << "," << r.y << "," << r.width << "," << r.height;
            addXmlEntry(tmp,
                        text,
                        "bbox",
                        ss.str());
        }
    }

    return tmp.documentElement();
}


QDomElement FileSummary::addXmlEntry(QDomDocument &doc,
                                     QDomNode &node,
                                     const std::string &tag,
                                     const std::string &value)
{
    QDomElement e = doc.createElement(QString::fromStdString(tag));
    node.appendChild(e);
    if(!value.empty()) {
        QDomText t = doc.createTextNode(QString::fromStdString(value));
        e.appendChild(t);
    }

    return e;
}


}
