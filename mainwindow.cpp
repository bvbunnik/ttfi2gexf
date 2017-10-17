#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "Csv.h"
#include <fstream>

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    //os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        //os << *ii;
        os << "," << *ii;
    }
    //os << " ]";
    return os;
}

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<std::vector<T> >& v)
{
    for (typename std::vector<std::vector<T> >::const_iterator i = v.begin(); i != v.end(); ++i){
    os << "[";
        for (typename std::vector<T>::const_iterator ii = i->begin(); ii != i->end(); ++ii)
        {
            os << "," << *ii;
        }
        os << " ]\n";
    }
    return os;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    dirModel->setRootPath(QDir::currentPath());
    ui->tree->setModel(dirModel);
    ui->tree->sortByColumn(0);
    ui->tree->hideColumn(1);
    ui->tree->hideColumn(2);
    ui->tree->hideColumn(3);

    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(QDir::currentPath());
    ui->listView->setModel(fileModel);
    QStringList filefilter;
    filefilter << "*.csv";
    fileModel->setNameFilters(filefilter);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tree_clicked(const QModelIndex &index)
{
    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fileModel->setRootPath(sPath));
}

void MainWindow::on_processButton_clicked()
{
    QModelIndexList templatelist = ui->listView->selectionModel()->selectedIndexes();
    QString dir = dirModel->fileInfo(ui->tree->currentIndex()).absoluteFilePath();
    foreach (const QModelIndex &index, templatelist)
    {
        createNetwork(index);
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
   QStringList filefilter;
   filefilter = ui->lineEdit->text().split(',', QString::SkipEmptyParts);
   for(auto& str : filefilter){
       str = str.trimmed();
   }
   qDebug() << filefilter;
   fileModel->setNameFilters(filefilter);
}

void MainWindow::createNetwork(const QModelIndex &index)
{
    std::string inputfile  = dirModel->fileInfo(index).filePath().toStdString();
    std::ifstream input(inputfile);
    Csv ttfi(input, ",", true);
    std::vector<std::vector<std::string> > data;
    ttfi.getall(data);
    data.erase(data.begin());
    std::vector<std::string> nodes;
    for (int i=0;i<data.size(); ++i){
        nodes.push_back(data.at(i).at(0));
    }
    QMap<std::string, std::string> edges;
    for (int i=0;i<data.size(); ++i){
        if(data.at(i).at(3).compare("0") != 0 && data.at(i).at(3).compare("-1") != 0){
            edges[data.at(i).at(0)] = data.at(i).at(3);
        }
    }
    QString gexf_file = dirModel->fileName(index);
    gexf_file.chop(4);
    gexf_file.append(".gexf");
    QFile output("/tmp/networks/" + gexf_file);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeDefaultNamespace("http://www.gexf.net/1.2draft");
    stream.writeStartElement("gexf");
        stream.writeAttribute("xmlns:viz","http://www.gexf.net/1.2draft/viz");
        stream.writeAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
        stream.writeAttribute("xsi:schemaLocation","http://www.gexf.net/1.2draft http://www.gexf.net/1.2draft/gexf.xsd");
        stream.writeAttribute("version", "1.2");
        stream.writeStartElement("meta");
            stream.writeAttribute("lastmodifieddate", "2017-10-16");
            stream.writeTextElement("creator", "B. van Bunnik");
            stream.writeTextElement("description", "Parse a TTFI file to GEXF format");
        stream.writeEndElement();
        writeGraph(&stream, &nodes, &edges);
    stream.writeEndElement();
//! [finish stream]
    stream.writeEndDocument();
//! [finish stream]
//! [write output]
    output.close();
    qDebug() << "All done...";
}


void MainWindow::writeGraph(QXmlStreamWriter *stream, std::vector<std::string> *nodes, QMap<std::string, std::string> *edges)
{
    stream->writeStartElement("graph");
        stream->writeAttribute("mode", "static");
        stream->writeAttribute("defaultedgetype", "directed");
        writeNodes(stream, nodes);
        writeEdges(stream, edges);
    stream->writeEndElement();
}

void MainWindow::writeNodes(QXmlStreamWriter *stream, std::vector<std::string> *nodes)
{
    stream->writeStartElement("nodes");
        std::vector<std::string>::iterator itt = nodes->begin();
        while (itt != nodes->cend()){
            stream->writeStartElement("node");
                stream->writeAttribute("id", QString::fromStdString(*itt));
                stream->writeAttribute("label", QString::fromStdString(*itt));
            stream->writeEndElement();
            ++itt;
        }
    stream->writeEndElement();
}

void MainWindow::writeEdges(QXmlStreamWriter *stream, QMap<std::string, std::string> *edges)
{

    stream->writeStartElement("edges");

        QMap<std::string, std::string>::const_iterator i = edges->constBegin();
        int id = 0;
        while (i != edges->constEnd()) {
            stream->writeStartElement("edge");
                stream->writeAttribute("id", QString::number(id));
                stream->writeAttribute("source", QString::fromStdString(i.key()));
                stream->writeAttribute("target", QString::fromStdString(i.value()));
            stream->writeEndElement();
            ++i;
            ++id;
        }
    stream->writeEndElement();
}
