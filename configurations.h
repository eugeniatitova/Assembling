#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "assembly.h"
#include <QDialog>
namespace Ui {
class Configurations;
}

class Configurations : public QDialog {
  Q_OBJECT

public:
  explicit Configurations(QWidget *parent = 0);
  ~Configurations();

signals:
  void assemblySelected(Assembly assembly);

private:
  void fillList();
  Ui::Configurations *ui;

private slots:
  void selectItemHandler();
  void deleteItemHandler();
  void openAssembly();
};

#endif // CONFIGURATIONS_H
