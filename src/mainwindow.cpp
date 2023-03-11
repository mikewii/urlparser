#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "parse.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_url(new URL(this))
{
    ui->setupUi(this);

    connect(m_url, &URL::basic_ready,
            this, &MainWindow::basic_ready);
    connect(m_url, &URL::query_ready,
            this, &MainWindow::query_ready);

    ui->queryParams->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->queryParams->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parse_clicked()
{
    m_url->parse(ui->url->text());
}

void MainWindow::on_unparse_clicked()
{
    auto& tableWidget = ui->queryParams;
    QList<QPair<QString,QString>> queryItems;

    for (auto row = 0; row < tableWidget->rowCount(); ++row) {
        QTableWidgetItem *key = tableWidget->item(row, 0);

        if (key->checkState() != Qt::CheckState::Checked)
            continue;

        QTableWidgetItem *values = tableWidget->item(row, 1);

        queryItems.append({key->text(), values->text()});
    }

    auto unparsed = m_url->unparse(
                queryItems,
                ui->scheme->text(),
                ui->host->text(),
                ui->path->text(),
                ui->port->value(),
                ui->authority->text(),
                ui->userInfo->text(),
                ui->userName->text(),
                ui->password->text());

    ui->unparsedUrl->setText(unparsed);
}

void MainWindow::basic_ready()
{
    ui->queryParams->setRowCount(0);

    auto scheme = m_url->scheme();
    auto host = m_url->host();
    auto path = m_url->path();
    auto port = m_url->port();
    auto authority = m_url->authority();
    auto userInfo = m_url->userInfo();
    auto userName = m_url->userName();
    auto password = m_url->password();

    ui->scheme->setText(scheme);
    ui->host->setText(host);
    ui->path->setText(path);

    if (port != -1)
        ui->port->setValue(port);

    ui->authority->setText(authority);
    ui->userInfo->setText(userInfo);
    ui->userName->setText(userName);
    ui->password->setText(password);
}

void MainWindow::query_ready()
{
    const auto& query = m_url->queryItems();

    for (const auto& params : qAsConst(query))
        tableWidget_AddQueryParameter(params.first, params.second);
}

void MainWindow::tableWidget_AddQueryParameter(const QString &key, const QString &values)
{
    if (key.isEmpty()) {
        ui->statusbar->showMessage("Key cant be empty!");
        return;
    }

    auto& tableWidget = ui->queryParams;

    QTableWidgetItem *itemKey = new QTableWidgetItem(key);
    itemKey->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    itemKey->setCheckState(Qt::Checked);

    QTableWidgetItem *itemValues = new QTableWidgetItem(values);
    itemValues->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);

    tableWidget->insertRow(tableWidget->rowCount());

    tableWidget->setItem(tableWidget->rowCount() - 1, 0, itemKey);
    tableWidget->setItem(tableWidget->rowCount() - 1, 1, itemValues);
}

void MainWindow::on_addQueryParam_clicked()
{
    const auto& key = ui->queryParamKey->text();
    const auto& values = ui->queryParamValues->text();

    tableWidget_AddQueryParameter(key, values);
}
