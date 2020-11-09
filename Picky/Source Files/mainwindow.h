#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <namebox.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<NameBox*> entryList;

    QMenu *fileMenu = nullptr;
    QAction *newAct = nullptr;
    QAction *openAct = nullptr;
    QAction *saveAct = nullptr;

    void createMenus();
    void newFile();
    void openFile();
    void saveFile();

public slots:
    void addEntry();
    void makeChoice();
    void removeEntry(QObject *n);
};
#endif // MAINWINDOW_H
