#include "introreader.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QColor>
#include <QTextStream>
#include <QPainter>
#include <math.h>
#include <iostream>
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
    QJsonArray delaysArr = jsonObj["delays"].toArray();
    for (int i = 0; i < delaysArr.size(); i++){
        delays.push_back(delaysArr[i].toInt());
    }
    paragraphDisplayIndex= 0;
    delayDisplayIndex = 0;

}
QString IntroReader::nextText(){
    if (paragraphDisplayIndex < paragraphs.size())
        return paragraphs[paragraphDisplayIndex++];
    else{
        return "";
    }
}
int IntroReader::nextMsDelay(){
    if (delayDisplayIndex< delays.size())
        return delays[delayDisplayIndex++];
    else{
        return 0;
    }
}

bool IntroReader::reachEndOfText(){
    return paragraphDisplayIndex == paragraphs.size();
}
