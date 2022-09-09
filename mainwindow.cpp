#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColorDialog>
#include <colormath.h>
QStringList strlist;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    darkTheme();
    qApp->installEventFilter(this);
    this->setCentralWidget(Window);
    this->chosenColor = Qt::white;
    this->LeHEX->setText("#ffffff");
    this->lbChosenColor->setAutoFillBackground(true);
    this->lbChosenColor->setFixedSize(100,100);
    this->PbColor->setFixedSize(120,40);
    this->LeHEX->setFixedSize(120,25);
    groupBoxesSettings();
    setDataInputLayout();
    this->CbColorModels->setFixedSize(130,25);
    strlist << "RGB ↔ LAB ↔ CMYK" << "RGB ↔ CMYK ↔ HLS";
    this->CbColorModels->addItems(strlist);
//    ChooseModels(0);
    connect(this->PbColor,SIGNAL(clicked()),SLOT(ChooseColor()));
    connect(this->CbColorModels,SIGNAL(activated(int)),SLOT(ChooseModels(int)));
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPalette pall;
    pall.setColor(lbChosenColor->backgroundRole(),this->chosenColor);
    lbChosenColor->setPalette(pall);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::darkTheme()
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
}

void MainWindow::setDataInputLayout()
{
    QVBoxLayout *VBox = new QVBoxLayout;
    QVBoxLayout *VBoxUp = new QVBoxLayout;
    HBoxUp->addWidget(lbChosenColor);
    VBoxUp->addWidget(this->PbColor);
    VBoxUp->addWidget(this->LeHEX);
    HBoxUp->addLayout(VBoxUp);
    HBoxUp->addWidget(CbColorModels);
    HBoxUp->setAlignment(Qt::AlignmentFlag::AlignLeft);
//    HBoxDown->addWidget(this->CurrentGBMass[0]);
//    HBoxDown->addWidget(this->CurrentGBMass[1]);
//    HBoxDown->addWidget(this->CurrentGBMass[2]);
    VBox->addLayout(HBoxUp);
    VBox->addLayout(HBoxDown);
    Window->setLayout(VBox);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress && obj == this->lbChosenColor)
    {
        ChooseColor();
        return true;
    }
    return false;
}

void MainWindow::ChooseColor()
{
    QColorDialog *RGB = new QColorDialog;
    this->chosenColor = RGB->getColor();
    this->LeHEX->setText(this->chosenColor.name());
}

void MainWindow::ChooseModels(int i)
{

    for(int i = 0; i < this->HBoxDown->count(); ++i)
    {

         QLayoutItem* item = this->HBoxDown->itemAt(i);
         if(item)
         {
             while((item = this->HBoxDown->itemAt(0)))
             {
                  this->HBoxDown->removeItem(item);
                  this->HBoxDown->removeWidget(item->widget());
                  delete item;
             }
         }
    }
    for(int i = 0; i < 3; i++)
    {
        CurrentGBMass[i]->hide();
    }
    switch(i)
    {
    case 0:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[5];
        CurrentGBMass[2]=GroupBoxMass[1];
        this->HBoxDown->addWidget(CurrentGBMass[0]);
        this->HBoxDown->addWidget(CurrentGBMass[1]);
        this->HBoxDown->addWidget(CurrentGBMass[2]);
        break;
    case 1:
//        this->HBoxDown->removeWidget(CurrentGBMass[2]);
//        this->HBoxDown->removeWidget(CurrentGBMass[1]);
//        this->HBoxDown->removeWidget(CurrentGBMass[0]);
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[1];
        CurrentGBMass[2]=GroupBoxMass[3];
        this->HBoxDown->addWidget(CurrentGBMass[0]);
        this->HBoxDown->addWidget(CurrentGBMass[1]);
        this->HBoxDown->addWidget(CurrentGBMass[2]);
        break;
    }
    for(int i = 0; i < 3; i++)
    {
        CurrentGBMass[i]->show();
    }
}

void MainWindow::groupBoxesSettings()
{
    //=================================================== RGB
        QVBoxLayout *vboxRGB = new QVBoxLayout;
        QHBoxLayout *hbox1 = new QHBoxLayout;
        QHBoxLayout *hbox2 = new QHBoxLayout;
        QHBoxLayout *hbox3 = new QHBoxLayout;
        hbox1->addWidget(new QLabel("R:"));
        hbox1->addWidget(this->leRGBMass[0]);
        hbox2->addWidget(new QLabel("G:"));
        hbox2->addWidget(this->leRGBMass[1]);
        hbox3->addWidget(new QLabel("B:"));
        hbox3->addWidget(this->leRGBMass[2]);
        vboxRGB->addLayout(hbox1);
        vboxRGB->addLayout(hbox2);
        vboxRGB->addLayout(hbox3);
        this->GroupBoxMass[0]->setLayout(vboxRGB);

    //=================================================== CMYK
        QVBoxLayout *vboxCMYK = new QVBoxLayout;
        QHBoxLayout *hbox4 = new QHBoxLayout;
        QHBoxLayout *hbox5 = new QHBoxLayout;
        QHBoxLayout *hbox6 = new QHBoxLayout;
        QHBoxLayout *hbox6k = new QHBoxLayout;
        hbox4->addWidget(new QLabel("C:"));
        hbox4->addWidget(this->leCMYKMass[0]);
        hbox4->addWidget(new QLabel("%"));
        hbox5->addWidget(new QLabel("M:"));
        hbox5->addWidget(this->leCMYKMass[1]);
        hbox5->addWidget(new QLabel("%"));
        hbox6->addWidget(new QLabel("Y:"));
        hbox6->addWidget(this->leCMYKMass[2]);
        hbox6->addWidget(new QLabel("%"));
        hbox6k->addWidget(new QLabel("K:"));
        hbox6k->addWidget(this->leCMYKMass[3]);
        hbox6k->addWidget(new QLabel("%"));
        vboxCMYK->addLayout(hbox4);
        vboxCMYK->addLayout(hbox5);
        vboxCMYK->addLayout(hbox6);
        vboxCMYK->addLayout(hbox6k);
        this->GroupBoxMass[1]->setLayout(vboxCMYK);
    //=================================================== HSV

    QVBoxLayout *vboxHSV = new QVBoxLayout;
    QHBoxLayout *hbox7 = new QHBoxLayout;
    QHBoxLayout *hbox8 = new QHBoxLayout;
    QHBoxLayout *hbox9 = new QHBoxLayout;
    hbox7->addWidget(new QLabel("H:"));
    hbox7->addWidget(this->leHSVMass[0]);
    hbox8->addWidget(new QLabel("S:"));
    hbox8->addWidget(this->leHSVMass[1]);
    hbox9->addWidget(new QLabel("V:"));
    hbox9->addWidget(this->leHSVMass[2]);
    vboxHSV->addLayout(hbox7);
    vboxHSV->addLayout(hbox8);
    vboxHSV->addLayout(hbox9);
    this->GroupBoxMass[2]->setLayout(vboxHSV);

    //=================================================== HLS
    QVBoxLayout *vboxHLS = new QVBoxLayout;
    QHBoxLayout *hbox10 = new QHBoxLayout;
    QHBoxLayout *hbox11 = new QHBoxLayout;
    QHBoxLayout *hbox12 = new QHBoxLayout;
    hbox10->addWidget(new QLabel("H:"));
    hbox10->addWidget(this->leHLSMass[0]);
    hbox11->addWidget(new QLabel("L:"));
    hbox11->addWidget(this->leHLSMass[1]);
    hbox12->addWidget(new QLabel("S:"));
    hbox12->addWidget(this->leHLSMass[2]);
    vboxHLS->addLayout(hbox10);
    vboxHLS->addLayout(hbox11);
    vboxHLS->addLayout(hbox12);
    this->GroupBoxMass[3]->setLayout(vboxHLS);

    //=================================================== XYZ
    QVBoxLayout *vboxXYZ = new QVBoxLayout;
    QHBoxLayout *hbox13 = new QHBoxLayout;
    QHBoxLayout *hbox14 = new QHBoxLayout;
    QHBoxLayout *hbox15 = new QHBoxLayout;
    hbox13->addWidget(new QLabel("X:"));
    hbox13->addWidget(this->leXYZMass[0]);
    hbox14->addWidget(new QLabel("Y:"));
    hbox14->addWidget(this->leXYZMass[1]);
    hbox15->addWidget(new QLabel("Z:"));
    hbox15->addWidget(this->leXYZMass[2]);
    vboxXYZ->addLayout(hbox13);
    vboxXYZ->addLayout(hbox14);
    vboxXYZ->addLayout(hbox15);
    this->GroupBoxMass[4]->setLayout(vboxXYZ);

    //=================================================== LAB
    QVBoxLayout *vboxLAB = new QVBoxLayout;
    QHBoxLayout *hbox16 = new QHBoxLayout;
    QHBoxLayout *hbox17 = new QHBoxLayout;
    QHBoxLayout *hbox18 = new QHBoxLayout;
    hbox16->addWidget(new QLabel("L:"));
    hbox16->addWidget(this->leLABMass[0]);
    hbox17->addWidget(new QLabel("A:"));
    hbox17->addWidget(this->leLABMass[1]);
    hbox18->addWidget(new QLabel("B:"));
    hbox18->addWidget(this->leLABMass[2]);
    vboxLAB->addLayout(hbox16);
    vboxLAB->addLayout(hbox17);
    vboxLAB->addLayout(hbox18);
    this->GroupBoxMass[5]->setLayout(vboxLAB);

    this->CurrentGBMass[0]=GroupBoxMass[0];
    this->CurrentGBMass[1]=GroupBoxMass[1];
    this->CurrentGBMass[2]=GroupBoxMass[2];
}
