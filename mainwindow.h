#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "authorization.h"
#include "configurations.h"
#include "generator.h"
#include "administrator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
    void initGUI();
    void refreshGUI(bool checkParts);
    void chooseParts(Parts parts);
    void fillAssemblyTable();
    void fillPartBaseInfo(Component baseInfo, QString toolTip);
    void fillAssemblyTableRow(Component baseInfo, int row, int count, bool useSpinBox);
    void assembleTableRowPainting(int row, QString stylesheet);
    void processAssemblyCheck();

    bool administratorAccept = false;
    Assembly currentAssembly;
    Ui::MainWindow *ui;
    Administrator *admDialog;
    Authorization *authDialog;
    Configurations *configDialog;
    Generator *generatorDialog;
private slots:
    void authPassed();
    void authorizationMenuClicked();
    void administratorMenuClicked();
    void assembliesMenuClicked();
    void generatorMenuClicked();
    void catalogTableDoubleClickHandler();
    void assembleTableDoubleClickHandler();
    void partsTableChanged();
    void openAssembly(Assembly a);
    void clearButtonPressed();
    void getReportButtonPressed();
    void saveButtonPressed();

    void assemblyNumOfRamChanged(int value);
    void assemblyNumOfGpuChanged(int value);
    void assemblyNumOfDataStoragesChanged(int value);
};

#endif // MAINWINDOW_H
