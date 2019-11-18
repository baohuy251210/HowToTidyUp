#ifndef ENDSCENE01_H
#define ENDSCENE01_H

#include <QWidget>
#include <iscene.h>

namespace Ui {
class EndScene01;
}

class EndScene01 : public IScene
{
    Q_OBJECT

public:
    explicit EndScene01(QWidget *parent = nullptr);
    ~EndScene01();

private:
    Ui::EndScene01 *ui;
};

#endif // ENDSCENE01_H
