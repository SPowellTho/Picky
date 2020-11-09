#ifndef NAMEBOX_H
#define NAMEBOX_H

#include <QPushButton>
#include <QLineEdit>

class NameBox: public QFrame
{

public:
    NameBox();

    std::string name;

    void nameToInput();


private:
    QLineEdit* nameInput;
    QPushButton* deleteButton;
    Q_OBJECT

public slots:
    void confirmChange();
    void deleteSelf();
};

#endif // NAMEBOX_H
