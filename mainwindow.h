#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QFileSystemModel"
#include <iostream>
#include <QXmlStreamWriter>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tree_clicked(const QModelIndex &index);

    void on_processButton_clicked();

    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    void createNetwork(const QModelIndex &index);
    void writeGraph(QXmlStreamWriter *stream, std::vector<std::string> *nodes, QMap<std::string, std::string> *edges);
    void writeNodes(QXmlStreamWriter *stream, std::vector<std::string> *nodes);
    void writeEdges(QXmlStreamWriter *stream, QMap<std::string, std::string> *edges);
    int index_node;

};

#endif // MAINWINDOW_H
