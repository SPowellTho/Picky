#include "namebox.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QFont>

NameBox::NameBox()
{
    setFrameStyle(QFrame::Box);
    setLineWidth(1);
    setMaximumHeight(50);
    setMinimumHeight(50);

    nameInput = new QLineEdit();
    deleteButton = new QPushButton(this);

    nameInput->setFrame(1);

    QFont font;//Create font for Name Input box
    font.setWeight(20);
    font.setPointSize(14);
    font.setFamily("Cooper Black");
    nameInput->setFont(font);

    QHBoxLayout* layout = new QHBoxLayout;//Format the inside of Object
    layout->addWidget(nameInput);
    layout->addWidget(deleteButton);
    setLayout(layout);

    QIcon *ico = new QIcon();
        ico->addPixmap(QPixmap(":/res/images/Delete.png"),QIcon::Normal,QIcon::On);
        ico->addPixmap(QPixmap(":/res/images/delete-click.png"),QIcon::Active,QIcon::On);
        deleteButton->setIcon(*ico);
        deleteButton->setIconSize(QSize(deleteButton->width(),deleteButton->height()));
        deleteButton->setFlat(1);

    connect(nameInput, SIGNAL(editingFinished()),
        this, SLOT(confirmChange()));
    connect(deleteButton, SIGNAL(clicked()),
        this, SLOT(deleteSelf()));

    setFocus();
}


void NameBox::confirmChange()
{
    nameInput->setFrame(0);
    name = nameInput->text().toStdString();
}

void NameBox::nameToInput()
{
    nameInput->setText(QString::fromStdString(name));
    nameInput->setFrame(0);
}

void NameBox::deleteSelf()
{
    delete this;
}
