#include "evidence.h"

#include <QVector>
#include <QString>

Evidence::Evidence(QVector<QString> correctTools, QVector<QString> usedTools, QString description)
    : correctTools(correctTools), usedTools(usedTools), description(description)
{

}
