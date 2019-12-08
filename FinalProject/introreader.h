#ifndef INTROREADER_H
#define INTROREADER_H
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class IntroReader
{
public:
    IntroReader();
    void readFromFile(QJsonDocument input);
    QVector<QString> paragraphs;
    QVector<int> delays;
    int paragraphDisplayIndex;
    int delayDisplayIndex;
    bool reachEndOfText();
    QString musicFile;
    QString nextText();
    int nextMsDelay();
};

#endif // INTROREADER_H
