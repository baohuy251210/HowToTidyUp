#include "endscene02.h"
#include "ui_endscene02.h"

EndScene02::EndScene02(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndScene02)
{
    ui->setupUi(this);
}

EndScene02::~EndScene02()
{
    delete ui;
}
