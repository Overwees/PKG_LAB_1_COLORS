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
#include <QDoubleSpinBox>
#include <QSpacerItem>
#include <colormath.h>
#include <QSlider>
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
    void updateInfoFromHEX();
    void updateInfoFromRGB();
    void updateInfoFromCMYK();
    void updateInfoFromHSV();
    void updateInfoFromHSL();
    void updateInfoFromXYZ();
    void updateInfoFromLAB();

    void updateInfoFromRGBSlider();
    void updateInfoFromCMYKSlider();
    void updateInfoFromHSVSlider();
    void updateInfoFromHSLSlider();
    void updateInfoFromXYZSlider();
    void updateInfoFromLABSlider();
private:
    Ui::MainWindow *ui;
    QHBoxLayout *HBoxUp = new QHBoxLayout;
    QHBoxLayout *HBoxDown = new QHBoxLayout;
    QLabel* lbChosenColor = new QLabel(this);
    QWidget *Window = new QWidget();
    QPushButton *PbColor = new QPushButton("Выберите цвет");
    QLineEdit *LeHEX = new QLineEdit;
    QSpinBox* sbRGBMass[3]{new QSpinBox,new QSpinBox,new QSpinBox};
    QDoubleSpinBox* sbCMYKMass[4]{new QDoubleSpinBox,new QDoubleSpinBox,new QDoubleSpinBox,new QDoubleSpinBox};
    QDoubleSpinBox* sbHSVMass[3]{new QDoubleSpinBox,new QDoubleSpinBox,new QDoubleSpinBox};
    QDoubleSpinBox* sbHSLMass[3]{new QDoubleSpinBox,new QDoubleSpinBox,new QDoubleSpinBox};
    QDoubleSpinBox* sbXYZMass[3]{new QDoubleSpinBox,new QDoubleSpinBox,new QDoubleSpinBox};
    QDoubleSpinBox* sbLABMass[3]{new QDoubleSpinBox,new QDoubleSpinBox,new QDoubleSpinBox};
    QGroupBox* GroupBoxMass[6]{new QGroupBox,new QGroupBox,new QGroupBox,new QGroupBox,new QGroupBox,new QGroupBox};   
    QGroupBox* CurrentGBMass[3];
    QComboBox* CbColorModels = new QComboBox(this);

    QSlider* sliderRGBMass[3]{new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal)};
    QSlider* sliderXYZMass[3]{new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal)};
    QSlider* sliderHSLMass[3]{new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal)};
    QSlider* sliderHSVMass[3]{new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal)};
    QSlider* sliderLABMass[3]{new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal)};
    QSlider* sliderCMYKMass[4]{new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal),new QSlider(Qt::Orientation::Horizontal)};

    void paintEvent(QPaintEvent*);
    bool eventFilter(QObject *obj, QEvent *event);
    void setDataInputLayout();
    void groupBoxesSettings();
    void darkTheme();
    void updateInfo();
    void spinBoxSliderSettings();
    void allConnect();
    void allDisconnect();
    QColor chosenColor;
    colorMath storage;
};
#endif // MAINWINDOW_H
