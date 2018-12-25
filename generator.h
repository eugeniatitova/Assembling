#ifndef GENERATOR_H
#define GENERATOR_H

#include <QDialog>
#include "componentsdb.h"
namespace Ui {
class Generator;
}

class Generator : public QDialog
{
    Q_OBJECT

public:
    explicit Generator(QWidget *parent = 0);
    ~Generator();

private:
  void initGUI();
    Ui::Generator *ui;
private slots:
    void genTypeChanged();
    void fillAssembliesListView(QList<Assembly> *assembliesList);
    //void ItemHandler(QString currItem);
};

#endif // GENERATOR_H
