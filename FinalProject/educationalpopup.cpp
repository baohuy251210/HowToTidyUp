/*
 * A9: An Educational App
 * Cameron Davie, John Duffy, Nathan Gordon, Eli Hebdon, Huy Tran, Dominic Utter
 * 3 December 2019
 *
 * This class is responsible for the "lightbulb" widget that opens an educational link
 * based on the evidence that's currently selected.
 *
*/

#include "educationalpopup.h"
#include "ui_educationalpopup.h"


//Constructor
educationalpopup::educationalpopup(QWidget *parent) :
    IScene(parent),
    ui(new Ui::educationalpopup)
{
    ui->setupUi(this);
    this->hide();
}

//Destructor
educationalpopup::~educationalpopup()
{
    delete ui;
}

//This function aligns the game's model with this widget
void educationalpopup::setModel(Model * model){
    this->model = model;
}

//This function handles the signal that fires when the "lightbulb" help icon is clicked.
void educationalpopup::on_lightbulb_clicked()
{
    QDesktopServices::openUrl(QUrl(url));
}

//This function handles what happens when a different piece of evidence is clicked in the scene.
void educationalpopup::evidenceClickedURLChange(Evidence* evidence) {

    this->show();
    url = evidence->educationalURL;

}

//This function handles hiding the "lightbulb" icon and is linked to the same signal as the itemDialog.
void educationalpopup::hideEducationalDialogSlot() {
    this->hide();
}
