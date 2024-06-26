#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "lz77.h"
#include "lz78.h"
#include "enthropy.h"
#include "treevisualizer.h"
#include "fanotree.h"

#include "cryptvisualizer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu m;

    ui->lineEdit->setEnabled(false);


    auto tree = new FanoTree();
    tree->create("уплощенно-пинакоидально-ромбоэдрический");
    auto tv = new TreeVisualizer(tree);

    tv->drawTree();
    ui->tab_4->layout()->addWidget(tv);

    auto cr = new CryptVisualizer();
    cr->draw();
    ui->tab_6->layout()->addWidget(cr);


    connect(this->ui->comboBox, &QComboBox::currentIndexChanged, this, [this](int index)
    {
        currentAlgorithm = LZFactory::LZAlgorithm(index);
    });



    connect(this->ui->enthropyButton, &QPushButton::clicked, this, [this]()
    {

        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);

        auto str = ui->enthropyTextEdit->toPlainText();

        Enthropy e;

        auto res = e.calculate(str);
        auto vString = e.makeStringFraction();

        ui->label->setText("E = " + vString + QString::number(res.enthropy));
        ui->label_2->setText("H0 = " + QString::number(res.capacity));
        ui->label_3->setText("R = " + QString::number(res.redundancy));
        ui->label_4->setText("r = " + QString::number(res.relativeRedundancy));


        auto v = e.visualize();

        int index = 0;

        ui->tableWidget->setColumnCount(2);

        for(const auto& i : v)
        {
            ui->tableWidget->insertRow(index);
            ui->tableWidget->setItem(index, 0, new QTableWidgetItem(i.first));
            ui->tableWidget->setItem(index, 1, new QTableWidgetItem(i.second));

            index++;
        }

    });

    connect(this->ui->codeButton, &QPushButton::clicked, this, [this]()
    {

        this->ui->decodeTextEdit->clear();
        this->ui->visualizationList->clear();
        this->ui->indexList->clear();
        this->ui->dictList->clear();


        auto str = ui->codeTextEdit->toPlainText();
        preprocessString(str, option, true);

        auto lz = LZFactory().create(currentAlgorithm);
        qDebug() << str;
        lz->compress(str);
        auto v = lz->visualize();

        for(auto i : v)
        {
            ui->indexList->addItem(std::get<0>(i));
            ui->dictList->addItem(std::get<1>(i));
            ui->visualizationList->addItem(std::get<2>(i));
            ui->decodeTextEdit->insertPlainText(std::get<2>(i));
        }

        lz->parseEncoded(ui->decodeTextEdit->toPlainText());
    } );

    connect(this->ui->LZ77CodeButton, &QPushButton::clicked, this, [this]()
    {
        this->ui->LZ77Code->clear();
        this->ui->LZ77Buf->clear();
        this->ui->LZ77Dict->clear();

        auto str = ui->LZ77CodeEdit->toPlainText();

        auto lz = LZFactory().create(currentAlgorithm);
        qDebug() << str;
        lz->compress(str);
        auto v = lz->visualize();

        for(auto i : v)
        {
            ui->LZ77Dict->addItem(std::get<0>(i));
            ui->LZ77Buf->addItem(std::get<1>(i));
            ui->LZ77Code->addItem(std::get<2>(i));
            ui->LZ77DecodeEdit->insertPlainText(std::get<2>(i));
        }

        //lz.parseEncoded(ui->LZ77DecodeEdit->toPlainText());

    });


    connect(this->ui->decodeButton, &QPushButton::clicked, this, [this]()
    {
        this->ui->visualizationList->clear();
        this->ui->indexList->clear();
        this->ui->dictList->clear();

        auto str = ui->decodeTextEdit->toPlainText();

        preprocessString(str, option,false);

        auto lz = LZFactory().create(currentAlgorithm);
        lz->parseEncoded(str);
        auto d = lz->decompress();
        qDebug() << d;

        auto v = lz->visualize();

        for(auto i : v)
        {
            ui->indexList->addItem(std::get<0>(i));
            ui->dictList->addItem(std::get<1>(i));
            ui->visualizationList->addItem(std::get<2>(i));
        }

        this->ui->codeTextEdit->setPlainText(d);
    });

    connect(this->ui->checkBox, &QCheckBox::stateChanged, this, [this](int state){
        if(state == Qt::Unchecked)
        {
            ui->lineEdit->setEnabled(false);
            deleteFlag(Options::CHANGE_SPACE);
        }
        else
        {
            ui->lineEdit->setEnabled(true);
            addFlag(Options::CHANGE_SPACE);
        }
    });

    connect(this-> ui->checkBox_2, &QCheckBox::stateChanged, this, [this](int state) {
        if(state == Qt::Unchecked)
        {
            deleteFlag(Options::NO_REGISTER);
        }
        else
        {
            addFlag(Options::NO_REGISTER);
        }
    });

    connect(this->ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString& str){
        if(!str.isEmpty())
            replaceSymbol = str[0];
    });

    connect(this->ui->pushButton, &QPushButton::clicked, this, [this](){
        this->ui->visualizationList->clear();
        this->ui->indexList->clear();
        this->ui->dictList->clear();
        this->ui->codeTextEdit->clear();
        this->ui->decodeTextEdit->clear();
    });
}

void MainWindow::preprocessString(QString& str, MainWindow::Options params, bool isCoding)
{
    if((params & Options::CHANGE_SPACE) && isCoding == false)
        str.replace(QRegularExpression("'[\\s]'"), QString('\'' + replaceSymbol + '\''));


    if((params & Options::CHANGE_SPACE) && isCoding == true)
        str.replace(QRegularExpression("[\\s]"), QString(replaceSymbol));


    if(params & Options::NO_REGISTER)
        str = std::move(str.toLower());

}

MainWindow::Options operator|(MainWindow::Options a, MainWindow::Options b) {
    return static_cast<MainWindow::Options>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

bool operator &(MainWindow::Options a, MainWindow::Options b)
{
    return static_cast<bool>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}


MainWindow::~MainWindow()
{
    delete ui;
}



