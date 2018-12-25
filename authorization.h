#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog {
  Q_OBJECT

public:
  explicit Authorization(QWidget *parent = 0);
  ~Authorization();

signals:
  void authPass();

private:
  Ui::Authorization *ui;

private slots:
  void authRequest();
};

#endif // AUTHORIZATION_H
