/*
 * A9: An Educational App
 * Cameron Davie, John Duffy, Nathan Gordon, Eli Hebdon, Huy Tran, Dominic Utter
 * 3 December 2019
 *
 * This class is responsible for the "lightbulb" widget that opens an educational link
 * based on the evidence that's currently selected.
 *
*/

#ifndef EDUCATIONALPOPUP_H
#define EDUCATIONALPOPUP_H

#include "cleaningtoolview.h"
#include "model.h"
#include "iscene.h"
#include <QUrl>
#include <QDesktopServices>

namespace Ui {
class educationalpopup;
}

class educationalpopup : public IScene
{
    Q_OBJECT

signals:

public:
    explicit educationalpopup(QWidget *parent = nullptr);
    ~educationalpopup();
    Ui::educationalpopup *ui;
    void setModel(Model*);
    QString url;

public slots:
    void on_lightbulb_clicked();
    void evidenceClickedURLChange(Evidence* evidence);
    void hideEducationalDialogSlot();

private:
    Model* model;
};

#endif // EDUCATIONALPOPUP_H
