#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QColorDialog>
#include <QValidator>
QStringList strlist;
QRegExpValidator *validatorHEX = new QRegExpValidator();
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    darkTheme();
    qApp->installEventFilter(this);
    this->setFixedSize(400,400);
    this->setCentralWidget(Window);
    this->chosenColor = Qt::black;
    this->LeHEX->setText("000000");
    this->storage.setHEX("000000");
    QRegExp hexcol("[0-9A-Fa-f]{6}");
    validatorHEX->setRegExp(hexcol);
    this->LeHEX->setValidator(validatorHEX);
    this->lbChosenColor->setAutoFillBackground(true);
    this->lbChosenColor->setFixedSize(100,100);
    this->PbColor->setFixedSize(130,40);
    this->LeHEX->setFixedSize(120,25);
    groupBoxesSettings();
    setDataInputLayout();
    spinBoxSliderSettings();
    this->CbColorModels->setFixedSize(130,25);
    strlist << "RGB ↔ LAB ↔ CMYK" << "RGB ↔ CMYK ↔ HSL" << "RGB ↔ XYZ ↔ LAB" << "RGB ↔ HSV ↔ LAB" << "CMYK ↔ LAB ↔ HSV" << "CMYK ↔ RGB ↔ HSL"
            << "CMYK ↔ RGB ↔ HSV" << "RGB ↔ XYZ ↔ HSV" << "HSV ↔ XYZ ↔ LAB" << "CMYK ↔ LAB ↔ RGB" << "XYZ ↔ LAB ↔ HSL" << "RGB ↔ XYZ ↔ HSL "
            << "RGB ↔ XYZ ↔ CMYK" << "CMYK ↔ LAB ↔ XYZ" << "RGB ↔ CMYK ↔ HSV" << "CMYK ↔ HSL ↔ XYZ" << "RGB ↔ HSL ↔ LAB" << "CMYK ↔ XYZ ↔ RGB";
    this->CbColorModels->addItems(strlist);

    connect(this->PbColor,SIGNAL(clicked()),SLOT(ChooseColor()));
    connect(this->CbColorModels,SIGNAL(activated(int)),SLOT(ChooseModels(int)));
    allConnect();
    ChooseModels(0);
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
    darkPalette.setColor(QPalette::AlternateBase, QColor(253, 53, 53));
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
    QHBoxLayout* labbox = new QHBoxLayout;
    QLabel *lbresh = new QLabel("#");
    lbresh->setFixedSize(10,25);
    lbresh->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignCenter);
    labbox->addWidget(lbresh);
    labbox->addWidget(this->LeHEX);
    labbox->setSpacing(0);
    VBoxUp->addLayout(labbox);
    HBoxUp->addLayout(VBoxUp);
    QVBoxLayout* colmodbox = new QVBoxLayout;
    colmodbox->addSpacerItem(new QSpacerItem(1,63));
    colmodbox->addWidget(CbColorModels);
    HBoxUp->addLayout(colmodbox);
    HBoxUp->setAlignment(Qt::AlignmentFlag::AlignLeft);
    HBoxDown->setSpacing(5);
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
    QString s =this->chosenColor.name();
    s.remove(0,1);
    this->LeHEX->setText(s);
}
void MainWindow::ChooseModels(int i)
{

    for(int j = 0; j < this->HBoxDown->count(); ++j)
    {

         QLayoutItem* item = this->HBoxDown->itemAt(j);
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
    for(int j = 0; j < 3; j++)
    {
        CurrentGBMass[j]->hide();
    }
    switch(i)
    {
    case 0:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[5];
        CurrentGBMass[2]=GroupBoxMass[1];
        break;
    case 1:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[1];
        CurrentGBMass[2]=GroupBoxMass[3];
        break;
    case 2:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[4];
        CurrentGBMass[2]=GroupBoxMass[5];
        break;
    case 3:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[2];
        CurrentGBMass[2]=GroupBoxMass[5];
        break;
    case 4:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[5];
        CurrentGBMass[2]=GroupBoxMass[2];
        break;
    case 5:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[0];
        CurrentGBMass[2]=GroupBoxMass[3];
        break;
    case 6:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[0];
        CurrentGBMass[2]=GroupBoxMass[2];
        break;
    case 7:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[4];
        CurrentGBMass[2]=GroupBoxMass[2];
        break;
    case 8:
        CurrentGBMass[0]=GroupBoxMass[2];
        CurrentGBMass[1]=GroupBoxMass[4];
        CurrentGBMass[2]=GroupBoxMass[5];
        break;
    case 9:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[5];
        CurrentGBMass[2]=GroupBoxMass[0];
        break;
    case 10:
        CurrentGBMass[0]=GroupBoxMass[4];
        CurrentGBMass[1]=GroupBoxMass[5];
        CurrentGBMass[2]=GroupBoxMass[3];
        break;
    case 11:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[4];
        CurrentGBMass[2]=GroupBoxMass[3];
        break;
    case 12:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[4];
        CurrentGBMass[2]=GroupBoxMass[1];
        break;
    case 13:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[5];
        CurrentGBMass[2]=GroupBoxMass[4];
        break;
    case 14:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[1];
        CurrentGBMass[2]=GroupBoxMass[2];
        break;
    case 15:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[3];
        CurrentGBMass[2]=GroupBoxMass[4];
        break;
    case 16:
        CurrentGBMass[0]=GroupBoxMass[0];
        CurrentGBMass[1]=GroupBoxMass[3];
        CurrentGBMass[2]=GroupBoxMass[5];
        break;
    case 17:
        CurrentGBMass[0]=GroupBoxMass[1];
        CurrentGBMass[1]=GroupBoxMass[4];
        CurrentGBMass[2]=GroupBoxMass[0];
        break;
    }
    for(int j = 0; j < 3; j++)
    {
        this->HBoxDown->addWidget(CurrentGBMass[j]);
        CurrentGBMass[j]->show();
    }
}
void MainWindow::groupBoxesSettings()
{
    //=================================================== RGB
    this->GroupBoxMass[0]->setTitle("RGB");
    QVBoxLayout *vboxRGB = new QVBoxLayout;
    QHBoxLayout *hbox1 = new QHBoxLayout;
    QHBoxLayout *hbox2 = new QHBoxLayout;
    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox1->addWidget(new QLabel("R:"));
    hbox1->addWidget(this->sbRGBMass[0]);
    hbox2->addWidget(new QLabel("G:"));
    hbox2->addWidget(this->sbRGBMass[1]);
    hbox3->addWidget(new QLabel("B:"));
    hbox3->addWidget(this->sbRGBMass[2]);
    vboxRGB->addLayout(hbox1);
    vboxRGB->addWidget(this->sliderRGBMass[0]);
    vboxRGB->addLayout(hbox2);
    vboxRGB->addWidget(this->sliderRGBMass[1]);
    vboxRGB->addLayout(hbox3);
    vboxRGB->addWidget(this->sliderRGBMass[2]);
    this->GroupBoxMass[0]->setLayout(vboxRGB);

    //=================================================== CMYK
    this->GroupBoxMass[1]->setTitle("CMYK");
    QVBoxLayout *vboxCMYK = new QVBoxLayout;
    QHBoxLayout *hbox4 = new QHBoxLayout;
    QHBoxLayout *hbox5 = new QHBoxLayout;
    QHBoxLayout *hbox6 = new QHBoxLayout;
    QHBoxLayout *hbox6k = new QHBoxLayout;
    hbox4->addWidget(new QLabel("C:"));
    hbox4->addWidget(this->sbCMYKMass[0]);
    hbox4->addWidget(new QLabel("%"));
    hbox5->addWidget(new QLabel("M:"));
    hbox5->addWidget(this->sbCMYKMass[1]);
    hbox5->addWidget(new QLabel("%"));
    hbox6->addWidget(new QLabel("Y:"));
    hbox6->addWidget(this->sbCMYKMass[2]);
    hbox6->addWidget(new QLabel("%"));
    hbox6k->addWidget(new QLabel("K:"));
    hbox6k->addWidget(this->sbCMYKMass[3]);
    hbox6k->addWidget(new QLabel("%"));
    vboxCMYK->addLayout(hbox4);
    vboxCMYK->addWidget(this->sliderCMYKMass[0]);
    vboxCMYK->addLayout(hbox5);
    vboxCMYK->addWidget(this->sliderCMYKMass[1]);
    vboxCMYK->addLayout(hbox6);
    vboxCMYK->addWidget(this->sliderCMYKMass[2]);
    vboxCMYK->addLayout(hbox6k);
    vboxCMYK->addWidget(this->sliderCMYKMass[3]);
    this->GroupBoxMass[1]->setLayout(vboxCMYK);
    //=================================================== HSV
    this->GroupBoxMass[2]->setTitle("HSV");
    QVBoxLayout *vboxHSV = new QVBoxLayout;
    QHBoxLayout *hbox7 = new QHBoxLayout;
    QHBoxLayout *hbox8 = new QHBoxLayout;
    QHBoxLayout *hbox9 = new QHBoxLayout;
    hbox7->addWidget(new QLabel("H:"));
    hbox7->addWidget(this->sbHSVMass[0]);
    hbox8->addWidget(new QLabel("S:"));
    hbox8->addWidget(this->sbHSVMass[1]);
    hbox9->addWidget(new QLabel("V:"));
    hbox9->addWidget(this->sbHSVMass[2]);
    vboxHSV->addLayout(hbox7);
    vboxHSV->addWidget(this->sliderHSVMass[0]);
    vboxHSV->addLayout(hbox8);
    vboxHSV->addWidget(this->sliderHSVMass[1]);
    vboxHSV->addLayout(hbox9);
    vboxHSV->addWidget(this->sliderHSVMass[2]);
    this->GroupBoxMass[2]->setLayout(vboxHSV);

    //=================================================== HSL
    this->GroupBoxMass[3]->setTitle("HSL");
    QVBoxLayout *vboxHLS = new QVBoxLayout;
    QHBoxLayout *hbox10 = new QHBoxLayout;
    QHBoxLayout *hbox11 = new QHBoxLayout;
    QHBoxLayout *hbox12 = new QHBoxLayout;
    hbox10->addWidget(new QLabel("H:"));
    hbox10->addWidget(this->sbHSLMass[0]);
    hbox11->addWidget(new QLabel("S:"));
    hbox11->addWidget(this->sbHSLMass[1]);
    hbox12->addWidget(new QLabel("L:"));
    hbox12->addWidget(this->sbHSLMass[2]);
    vboxHLS->addLayout(hbox10);
    vboxHLS->addWidget(this->sliderHSLMass[0]);
    vboxHLS->addLayout(hbox11);
    vboxHLS->addWidget(this->sliderHSLMass[1]);
    vboxHLS->addLayout(hbox12);
    vboxHLS->addWidget(this->sliderHSLMass[2]);
    this->GroupBoxMass[3]->setLayout(vboxHLS);

    //=================================================== XYZ
    this->GroupBoxMass[4]->setTitle("XYZ");
    QVBoxLayout *vboxXYZ = new QVBoxLayout;
    QHBoxLayout *hbox13 = new QHBoxLayout;
    QHBoxLayout *hbox14 = new QHBoxLayout;
    QHBoxLayout *hbox15 = new QHBoxLayout;
    hbox13->addWidget(new QLabel("X:"));
    hbox13->addWidget(this->sbXYZMass[0]);
    hbox14->addWidget(new QLabel("Y:"));
    hbox14->addWidget(this->sbXYZMass[1]);
    hbox15->addWidget(new QLabel("Z:"));
    hbox15->addWidget(this->sbXYZMass[2]);
    vboxXYZ->addLayout(hbox13);
    vboxXYZ->addWidget(this->sliderXYZMass[0]);
    vboxXYZ->addLayout(hbox14);
    vboxXYZ->addWidget(this->sliderXYZMass[1]);
    vboxXYZ->addLayout(hbox15);
    vboxXYZ->addWidget(this->sliderXYZMass[2]);
    this->GroupBoxMass[4]->setLayout(vboxXYZ);

    //=================================================== LAB
    this->GroupBoxMass[5]->setTitle("LAB");
    QVBoxLayout *vboxLAB = new QVBoxLayout;
    QHBoxLayout *hbox16 = new QHBoxLayout;
    QHBoxLayout *hbox17 = new QHBoxLayout;
    QHBoxLayout *hbox18 = new QHBoxLayout;
    hbox16->addWidget(new QLabel("L:"));
    hbox16->addWidget(this->sbLABMass[0]);
    hbox17->addWidget(new QLabel("A:"));
    hbox17->addWidget(this->sbLABMass[1]);
    hbox18->addWidget(new QLabel("B:"));
    hbox18->addWidget(this->sbLABMass[2]);
    vboxLAB->addLayout(hbox16);
    vboxLAB->addWidget(this->sliderLABMass[0]);
    vboxLAB->addLayout(hbox17);
    vboxLAB->addWidget(this->sliderLABMass[1]);
    vboxLAB->addLayout(hbox18);
    vboxLAB->addWidget(this->sliderLABMass[2]);
    this->GroupBoxMass[5]->setLayout(vboxLAB);

    this->CurrentGBMass[0]=GroupBoxMass[0];
    this->CurrentGBMass[1]=GroupBoxMass[1];
    this->CurrentGBMass[2]=GroupBoxMass[2];
    for (int i = 0 ; i < 6 ; i ++)
    {
        this->GroupBoxMass[i]->setFixedSize(130,220);
    }
}

void MainWindow::updateInfoFromHEX()
{
    allDisconnect();
    QString hex = this->LeHEX->text();
    storage.setHEX(hex);
    updateInfo();
}
void MainWindow::updateInfoFromRGB()
{
    allDisconnect();
    int r = this->sbRGBMass[0]->value();
    int g = this->sbRGBMass[1]->value();
    int b = this->sbRGBMass[2]->value();
    storage.setRGB(r, g, b);
    updateInfo();
}
void MainWindow::updateInfoFromCMYK()
{
    allDisconnect();
    double c = this->sbCMYKMass[0]->value();
    double m = this->sbCMYKMass[1]->value();
    double y = this->sbCMYKMass[2]->value();
    double k = this->sbCMYKMass[3]->value();
    storage.setCMYK(c, m, y, k);
    updateInfo();
}
void MainWindow::updateInfoFromHSV()
{
    allDisconnect();
    double h = this->sbHSVMass[0]->value();
    double s = this->sbHSVMass[1]->value();
    double v = this->sbHSVMass[2]->value();
    storage.setHSV(h, s, v);
    updateInfo();
}
void MainWindow::updateInfoFromHSL()
{
    allDisconnect();
    double h = this->sbHSLMass[0]->value();
    double s = this->sbHSLMass[1]->value();
    double l = this->sbHSLMass[2]->value();
    storage.setHSL(h, s, l);
    updateInfo();
}
void MainWindow::updateInfoFromXYZ()
{
    allDisconnect();
    double x = this->sbXYZMass[0]->value();
    double y = this->sbXYZMass[1]->value();
    double z = this->sbXYZMass[2]->value();
    storage.setXYZ(x, y, z);
    updateInfo();
}
void MainWindow::updateInfoFromLAB()
{
    allDisconnect();
    double l = this->sbLABMass[0]->value();
    double a = this->sbLABMass[1]->value();
    double b = this->sbLABMass[2]->value();
    storage.setLAB(l, a, b);
    updateInfo();
}

void MainWindow::updateInfoFromRGBSlider()
{
    allDisconnect();
    int r = this->sliderRGBMass[0]->value();
    int g = this->sliderRGBMass[1]->value();
    int b = this->sliderRGBMass[2]->value();
    storage.setRGB(r, g, b);
    updateInfo();
}
void MainWindow::updateInfoFromCMYKSlider()
{
    allDisconnect();
    double c = double(this->sliderCMYKMass[0]->value());
    double m = double(this->sliderCMYKMass[1]->value());
    double y = double(this->sliderCMYKMass[2]->value());
    double k = double(this->sliderCMYKMass[3]->value());
    storage.setCMYK(c, m, y, k);
    updateInfo();
}
void MainWindow::updateInfoFromHSVSlider()
{
    allDisconnect();
    double h = double(this->sliderHSVMass[0]->value());
    double s = double(this->sliderHSVMass[1]->value());
    double v = double(this->sliderHSVMass[2]->value());
    storage.setHSV(h, s, v);
    updateInfo();
}
void MainWindow::updateInfoFromHSLSlider()
{
    allDisconnect();
    double h = double(this->sliderHSLMass[0]->value());
    double s = double(this->sliderHSLMass[1]->value());
    double l = double(this->sliderHSLMass[2]->value());
    storage.setHSL(h, s, l);
    updateInfo();
}
void MainWindow::updateInfoFromXYZSlider()
{
    allDisconnect();
    double x = double(this->sliderXYZMass[0]->value());
    double y = double(this->sliderXYZMass[1]->value());
    double z = double(this->sliderXYZMass[2]->value());
    storage.setXYZ(x, y, z);
    updateInfo();
}
void MainWindow::updateInfoFromLABSlider()
{
    allDisconnect();
    double l = double(this->sliderLABMass[0]->value());
    double a = double(this->sliderLABMass[1]->value());
    double b = double(this->sliderLABMass[2]->value());
    storage.setLAB(l, a, b);
    updateInfo();
}


void MainWindow::updateInfo()
{
    this->LeHEX->setText(storage.getHEX());
    this->sbRGBMass[0]->setValue(storage.getR_rgb());
    this->sbRGBMass[1]->setValue(storage.getG_rgb());
    this->sbRGBMass[2]->setValue(storage.getB_rgb());
    this->sliderRGBMass[0]->setValue(storage.getR_rgb());
    this->sliderRGBMass[1]->setValue(storage.getG_rgb());
    this->sliderRGBMass[2]->setValue(storage.getB_rgb());

    this->sbCMYKMass[0]->setValue(storage.getC_cmyk());
    this->sbCMYKMass[1]->setValue(storage.getM_cmyk());
    this->sbCMYKMass[2]->setValue(storage.getY_cmyk());
    this->sbCMYKMass[3]->setValue(storage.getK_cmyk());
    this->sliderCMYKMass[0]->setValue(storage.getC_cmyk());
    this->sliderCMYKMass[1]->setValue(storage.getM_cmyk());
    this->sliderCMYKMass[2]->setValue(storage.getY_cmyk());
    this->sliderCMYKMass[3]->setValue(storage.getK_cmyk());

    this->sbHSVMass[0]->setValue(storage.getH_hsv());
    this->sbHSVMass[1]->setValue(storage.getS_hsv());
    this->sbHSVMass[2]->setValue(storage.getV_hsv());
    this->sliderHSVMass[0]->setValue(storage.getH_hsv());
    this->sliderHSVMass[1]->setValue(storage.getS_hsv());
    this->sliderHSVMass[2]->setValue(storage.getV_hsv());

    this->sbHSLMass[0]->setValue(storage.getH_hsl());
    this->sbHSLMass[1]->setValue(storage.getS_hsl());
    this->sbHSLMass[2]->setValue(storage.getL_hsl());
    this->sliderHSLMass[0]->setValue(storage.getH_hsl());
    this->sliderHSLMass[1]->setValue(storage.getS_hsl());
    this->sliderHSLMass[2]->setValue(storage.getL_hsl());

    this->sbXYZMass[0]->setValue(storage.getX_xyz());
    this->sbXYZMass[1]->setValue(storage.getY_xyz());
    this->sbXYZMass[2]->setValue(storage.getZ_xyz());
    this->sliderXYZMass[0]->setValue(storage.getX_xyz());
    this->sliderXYZMass[1]->setValue(storage.getY_xyz());
    this->sliderXYZMass[2]->setValue(storage.getZ_xyz());

    this->sbLABMass[0]->setValue(storage.getL_lab());
    this->sbLABMass[1]->setValue(storage.getA_lab());
    this->sbLABMass[2]->setValue(storage.getB_lab());
    this->sliderLABMass[0]->setValue(storage.getL_lab());
    this->sliderLABMass[1]->setValue(storage.getA_lab());
    this->sliderLABMass[2]->setValue(storage.getB_lab());

    this->chosenColor.setNamedColor("#"+this->LeHEX->text());
    allConnect();
}

void MainWindow::spinBoxSliderSettings()
{
    for (int i = 0; i < 3; i++)
    {
        this->sbRGBMass[i]->setRange(0,255);
        this->sbHSVMass[i]->setSingleStep(1);
        this->sbHSLMass[i]->setSingleStep(1);
        this->sbXYZMass[i]->setSingleStep(1);
        this->sbLABMass[i]->setSingleStep(1);
        this->sbHSVMass[i]->setDecimals(3);
        this->sbHSLMass[i]->setDecimals(3);
        this->sbHSLMass[i]->setDecimals(3);
        this->sbXYZMass[i]->setDecimals(3);
        this->sbLABMass[i]->setDecimals(3);
        this->sbRGBMass[i]->setFixedWidth(60);
        this->sbHSVMass[i]->setFixedWidth(60);
        this->sbHSLMass[i]->setFixedWidth(60);
        this->sbXYZMass[i]->setFixedWidth(60);
        this->sbLABMass[i]->setFixedWidth(60);
    }
    for (int i = 0; i < 4; i++)
    {
        this->sbCMYKMass[i]->setRange(0,100);
        this->sbCMYKMass[i]->setSingleStep(1);
        this->sbCMYKMass[i]->setDecimals(3);
    }
    this->sbHSVMass[0]->setRange(0,360);
    this->sbHSVMass[1]->setRange(0,100);
    this->sbHSVMass[2]->setRange(0,100);
    this->sbHSLMass[0]->setRange(0,360);
    this->sbHSLMass[1]->setRange(0,100);
    this->sbHSLMass[2]->setRange(0,100);
    this->sbXYZMass[0]->setRange(0,95.047);
    this->sbXYZMass[1]->setRange(0,100);
    this->sbXYZMass[2]->setRange(0,108.883);
    this->sbLABMass[0]->setRange(0,100);
    this->sbLABMass[1]->setRange(-128,128);
    this->sbLABMass[2]->setRange(-128,128);
    for (int i = 0; i < 3; i++)
    {
        this->sliderRGBMass[i]->setRange(0,255);
    }
    for (int i = 0; i < 4; i++)
    {
        this->sliderCMYKMass[i]->setRange(0,100);
    }
    this->sliderHSVMass[0]->setRange(0,360);
    this->sliderHSVMass[1]->setRange(0,100);
    this->sliderHSVMass[2]->setRange(0,100);
    this->sliderHSLMass[0]->setRange(0,360);
    this->sliderHSLMass[1]->setRange(0,100);
    this->sliderHSLMass[2]->setRange(0,100);
    this->sliderXYZMass[0]->setRange(0,96);
    this->sliderXYZMass[1]->setRange(0,100);
    this->sliderXYZMass[2]->setRange(0,109);
    this->sliderLABMass[0]->setRange(0,100);
    this->sliderLABMass[1]->setRange(-128,128);
    this->sliderLABMass[2]->setRange(-128,128);
}

void MainWindow::allConnect()
{
    for (int i = 0; i < 3; i++)
    {
        connect(this->sbRGBMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromRGB()));
        connect(this->sbCMYKMass[i],SIGNAL(valueChanged(double)),SLOT(updateInfoFromCMYK()));
        connect(this->sbHSLMass[i],SIGNAL(valueChanged(double)),SLOT(updateInfoFromHSL()));
        connect(this->sbHSVMass[i],SIGNAL(valueChanged(double)),SLOT(updateInfoFromHSV()));
        connect(this->sbXYZMass[i],SIGNAL(valueChanged(double)),SLOT(updateInfoFromXYZ()));
        connect(this->sbLABMass[i],SIGNAL(valueChanged(double)),SLOT(updateInfoFromLAB()));
        connect(this->sliderRGBMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromRGBSlider()));
        connect(this->sliderCMYKMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromCMYKSlider()));
        connect(this->sliderHSLMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromHSLSlider()));
        connect(this->sliderHSVMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromHSVSlider()));
        connect(this->sliderXYZMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromXYZSlider()));
        connect(this->sliderLABMass[i],SIGNAL(valueChanged(int)),SLOT(updateInfoFromLABSlider()));
    }
    connect(this->sbCMYKMass[3],SIGNAL(valueChanged(double)),SLOT(updateInfoFromCMYK()));
    connect(this->sliderCMYKMass[3],SIGNAL(valueChanged(int)),SLOT(updateInfoFromCMYKSlider()));
    connect(this->LeHEX,SIGNAL(textChanged(QString)),SLOT(updateInfoFromHEX()));
}
void MainWindow::allDisconnect()
{
    for (int i = 0; i < 3; i++)
    {
        disconnect(this->sbRGBMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromRGB()));
        disconnect(this->sbCMYKMass[i],SIGNAL(valueChanged(double)),this,SLOT(updateInfoFromCMYK()));
        disconnect(this->sbHSLMass[i],SIGNAL(valueChanged(double)),this,SLOT(updateInfoFromHSL()));
        disconnect(this->sbHSVMass[i],SIGNAL(valueChanged(double)),this,SLOT(updateInfoFromHSV()));
        disconnect(this->sbXYZMass[i],SIGNAL(valueChanged(double)),this,SLOT(updateInfoFromXYZ()));
        disconnect(this->sbLABMass[i],SIGNAL(valueChanged(double)),this,SLOT(updateInfoFromLAB()));

        disconnect(this->sliderRGBMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromRGBSlider()));
        disconnect(this->sliderCMYKMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromCMYKSlider()));
        disconnect(this->sliderHSLMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromHSLSlider()));
        disconnect(this->sliderHSVMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromHSVSlider()));
        disconnect(this->sliderXYZMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromXYZSlider()));
        disconnect(this->sliderLABMass[i],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromLABSlider()));
    }
    disconnect(this->sbCMYKMass[3],SIGNAL(valueChanged(double)),this,SLOT(updateInfoFromCMYK()));
    disconnect(this->sliderCMYKMass[3],SIGNAL(valueChanged(int)),this,SLOT(updateInfoFromCMYKSlider()));
    disconnect(this->LeHEX,SIGNAL(textChanged(QString)),this,SLOT(updateInfoFromHEX()));
}
