#ifndef INTROREADER_H
#define INTROREADER_H
#include <QVector>
#include <QJsonDocument>

class IntroReader
{
public:
    IntroReader();
    void readFromFile(QJsonDocument input);
    QVector<QString> paragraphs;
    int paragraphDisplayIndex;
    bool reachEndOfText;
    QString musicFile;
    QString nextText();
};

#endif // INTROREADER_H
