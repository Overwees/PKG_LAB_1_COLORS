#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QVector>
#include <QMouseEvent>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void ChooseColor();
    void ChooseModels(int);
private:
    Ui::MainWindow *ui;
    QHBoxLayout *HBoxUp = new QHBoxLayout;
    QHBoxLayout *HBoxDown = new QHBoxLayout;
    QLabel* lbChosenColor = new QLabel(this);
    QWidget *Window = new QWidget();
    QPushButton *PbColor = new QPushButton("Выберите цвет");
    QLineEdit *LeHEX = new QLineEdit;
    QLineEdit* leRGBMass[3]{new QLineEdit,new QLineEdit,new QLineEdit};
    QLineEdit* leCMYKMass[4]{new QLineEdit,new QLineEdit,new QLineEdit,new QLineEdit};
    QLineEdit* leHSVMass[3]{new QLineEdit,new QLineEdit,new QLineEdit};
    QLineEdit* leHLSMass[3]{new QLineEdit,new QLineEdit,new QLineEdit};
    QLineEdit* leXYZMass[3]{new QLineEdit,new QLineEdit,new QLineEdit};
    QLineEdit* leLABMass[3]{new QLineEdit,new QLineEdit,new QLineEdit};
    QGroupBox* GroupBoxMass[6]{new QGroupBox,new QGroupBox,new QGroupBox,new QGroupBox,new QGroupBox,new QGroupBox};
    QComboBox *CbColorModels = new QComboBox(this);
    QGroupBox *CurrentGBMass[3];
    void paintEvent(QPaintEvent*);
    bool eventFilter(QObject *obj, QEvent *event);
    void setDataInputLayout();
    void groupBoxesSettings();
    void darkTheme();
    QColor chosenColor;
};
#endif // MAINWINDOW_H
