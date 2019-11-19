#include "introreader.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QColor>
#include <QTextStream>
#include <QPainter>
#include <math.h>
#include <iostream>
#include <QDebug>
IntroReader::IntroReader()
{
}

void IntroReader::readFromFile(QJsonDocument input){
    paragraphs.clear();
    if (input.isEmpty()){
        return;
    }
    QJsonObject jsonObj = input.object();
    QJsonArray jsonArray = jsonObj["paragraphs"].toArray();

    for (int i = 0; i < jsonArray.size(); i++){
        paragraphs.push_back(jsonArray[i].toString());
    }
    paragraphDisplayIndex= 0;
}
QString IntroReader::nextText(){
    if (paragraphDisplayIndex < paragraphs.size())
        return paragraphs[paragraphDisplayIndex++];
    else{
        return "";
    }
}

bool IntroReader::reachEndOfText(){
    return paragraphDisplayIndex == paragraphs.size();
}