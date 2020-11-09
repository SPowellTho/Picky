#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "namebox.h"
#include <list>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMenu>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setting up Buttons
    connect(ui->addButton, SIGNAL(clicked()),
        this, SLOT(addEntry()));

    connect(ui->pickButton, SIGNAL(clicked()),
        this, SLOT(makeChoice()));

    connect(ui->pickButton, SIGNAL(released()),
        this, SLOT(setFocus()));

    connect(ui->addButton, SIGNAL(released()),
        this, SLOT(setFocus()));

    //Create Layout
    QBoxLayout* lay = ui->listLayout;
    ui->scrollArea->setLayout(lay);

    //Format Button Icons
    QIcon *ico = new QIcon(); //add button
        ico->addPixmap(QPixmap(":/res/images/Add.png"),QIcon::Normal,QIcon::Off);
        ico->addPixmap(QPixmap(":/res/images/add-click.png"),QIcon::Active,QIcon::Off);

        ui->addButton->setIcon(*ico);
        ui->addButton->setFlat(1);
        QFont font;
        font.setWeight(50);
        font.setPointSize(14);
        font.setFamily("Cooper Black");
        ui->addButton->setFont(font);

    QIcon *ico2 = new QIcon(); //pick button
        ico2->addPixmap(QPixmap(":/res/images/pick.png"),QIcon::Normal,QIcon::Off);
        ico2->addPixmap(QPixmap(":/res/images/pick-click.png"),QIcon::Active,QIcon::Off);
        ui->pickButton->setIcon(*ico2);
        ui->pickButton->setFlat(1);
        ui->pickButton->setIconSize(QSize(ui->pickButton->width(),ui->pickButton->height()));

        setFocus(); //Draws Focus to Central Widget, Allowing Buttons to load correctly
        createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addEntry(){
    NameBox* newWid = new NameBox();
    entryList.push_back(newWid); //adds object to list

    connect(newWid, SIGNAL(destroyed(QObject*)),
        this, SLOT(removeEntry(QObject*)));

    ui->listLayout->addWidget(newWid); //add new object to UI Layout
    ui->listLayout->setAlignment(Qt::AlignTop);
}

void MainWindow::removeEntry(QObject *n){
    std::vector<NameBox*>::iterator it;
    it = std::find(entryList.begin(), entryList.end(), n);

    entryList.erase(it);
}

void MainWindow::makeChoice(){
    if (!entryList.empty())
    {
        int num;
        std::string message;

        num = rand() % entryList.size();
        message = "I chose " + entryList[num]->name + " for you!";

        QMessageBox messageBox;
        messageBox.setText(QString::fromStdString(message) );
        messageBox.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        messageBox.setStyleSheet("color:black; background-color: rgb(255, 197, 147); ");
        messageBox.exec();
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setText(QString("Uh Oh! You should probably enter something first!") );
        messageBox.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        messageBox.setStyleSheet("color:black; background-color: rgb(255, 197, 147); ");
        messageBox.exec();
    }
}

void MainWindow::createMenus()
{
    newAct = new QAction(tr("&New..."), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Open);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
}

//File IO Methods
void MainWindow::newFile()
{
    unsigned long long sizeNum = entryList.size();
    for (unsigned long long i = 0; i < sizeNum; i++)//Empty Vector of Objects
    {
        delete entryList[0];
    }
}

void MainWindow::openFile()
{
    newFile();
    QString fileName = QFileDialog::getOpenFileName(this,"Select a File","","Text Files(*.txt);;Other()");
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return;


    QTextStream fileText(&file);
    unsigned long long num; QString tempString;
    tempString = fileText.readLine();
    num = tempString.toInt();

    for (unsigned long long i = 0; i < num; i++)//Read File then Write to list
    {
        addEntry();

        tempString = fileText.readLine();
        entryList[i]->name = tempString.toStdString();
        entryList[i]->nameToInput();
    }

    QString text = fileText.readAll();
    //ui->textEdit->setText(text);
    file.close();
    //changeTitle();
}

void MainWindow::saveFile()
{
    QString fileName;

    fileName = QFileDialog::getSaveFileName(this,"Select a File","","Text Files(*.txt);;Other()");

    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
        return;

    QTextStream out(&file);
    //out.setVersion(QDataStream::Qt_4_5);
    unsigned long long sizeNum = entryList.size();

    out << sizeNum << '\n';

    for (unsigned long long i = 0; i < sizeNum; i++)//Write to File
    {
        QString nem = QString::fromStdString(entryList[i]->name);
        out << nem << '\n';
    }

    file.flush();
    file.close();
}
