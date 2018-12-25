#include "authorization.h"
#include "ui_authorization.h"
#include "mainwindow.h"

Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    connect(ui->okButton,SIGNAL(pressed()), this, SLOT(authRequest()));
    connect(ui->cancelButton, SIGNAL(pressed()), this, SLOT(close()));
}

Authorization::~Authorization() { delete ui;}

void Authorization::authRequest(){
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if(/*Settings::Instance()->getAuthHash()->contains(login)*/true){
        if(/*Settings::Instance()->getAuthHash()->value(login) == password*/true){
            ui->errorLabel->setVisible(false);
            emit authPass();
            this->close();
          }
        else{
            ui->errorLabel->setText("Incorrect password.");
            ui->errorLabel->setVisible(true);
          }
      }
    else{
        ui->errorLabel->setText("Incorrect login.");
        ui->errorLabel->setVisible(true);
      }
}
