#include "endscene01.h"
#include "ui_endscene01.h"

EndScene01::EndScene01(QWidget *parent) :
    IScene(parent),
    ui(new Ui::EndScene01)
{
    ui->setupUi(this);
}

EndScene01::~EndScene01()
{
    delete ui;
}
