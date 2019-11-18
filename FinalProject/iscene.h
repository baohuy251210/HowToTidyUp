#ifndef ISCENE_H
#define ISCENE_H

#include <QWidget>

class IScene : public QWidget
{
    Q_OBJECT
public:
    explicit IScene(QWidget *parent = nullptr);

signals:
    virtual void changeScene(IScene* scene);
public slots:
};

#endif // ISCENE_H
