#include "winning.h"
#include "ui_winning.h"

Winning::Winning(bool Player, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Winning)
{
    /*界面布局*/
    ui->setupUi(this);
    this->resize(400, 200);
    ui->label_win->setGeometry(100, 40, 150, 50);
    //ui->label_win->setText();
    ui->pushButton_OK->setGeometry(100, 120, 80, 30);
    ui->pushButton_Quit->setGeometry(250, 120, 80, 30);

    if (Player==false)
    {
        ui->label_win->setText("AI win!!!");
    }
    else
    {
        ui->label_win->setText("Player win!!!");
    }

    connect(ui->pushButton_OK, SIGNAL(clicked(bool)), this, SLOT(pushOK()));
    connect(ui->pushButton_Quit, SIGNAL(clicked(bool)), this, SLOT(pushQuit()));

}

Winning::~Winning()
{
    delete ui;
}

int Winning::pushOK()
{
    accept();
    return 0;
}
int Winning::pushQuit()
{
    reject();
    return 0;
}


