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
    connect(m_url, &URL::fragment_ready,
            this, &MainWindow::fragment_ready);

    ui->queryParams->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->queryParams->horizontalHeader()->setStretchLastSection(true);

    ui->fragmentParams->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->fragmentParams->horizontalHeader()->setStretchLastSection(true);
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
    QList<QPair<QString,QString>> queryItems;
    QList<QPair<QString,QString>> fragmentItems;

    auto collect = [&](const QTableWidget* table, QList<QPair<QString,QString>>& container)
    {
        for (auto row = 0; row < table->rowCount(); ++row) {
            QTableWidgetItem *key = table->item(row, 0);

            if (key->checkState() != Qt::CheckState::Checked)
                continue;

            QTableWidgetItem *values = table->item(row, 1);

            container.append({key->text(), values->text()});
        }
    };

    collect(ui->queryParams, queryItems);
    collect(ui->fragmentParams, fragmentItems);

    auto unparsed = m_url->unparse(
                queryItems,
                fragmentItems,
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
    ui->fragmentParams->setRowCount(0);
    updateQueryParamsCount();
    updateFragmentParamsCount();

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
        table_AddPair(ui->queryParams, params.first, params.second);


}

void MainWindow::fragment_ready()
{
    const auto& fragment = m_url->fragmentItems();

    for (const auto& params : qAsConst(fragment))
        table_AddPair(ui->fragmentParams, params.first, params.second);

    updateFragmentParamsCount();
}

void MainWindow::table_AddPair(QTableWidget* tableWidget, const QString& key, const QString& values)
{
    if (key.isEmpty()) {
        ui->statusbar->showMessage("Key cant be empty!");
        return;
    }

    QTableWidgetItem *itemKey = new QTableWidgetItem(key);
    itemKey->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    itemKey->setCheckState(Qt::Checked);

    QTableWidgetItem *itemValues = new QTableWidgetItem(values);
    itemValues->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);

    tableWidget->insertRow(tableWidget->rowCount());

    tableWidget->setItem(tableWidget->rowCount() - 1, 0, itemKey);
    tableWidget->setItem(tableWidget->rowCount() - 1, 1, itemValues);
}

void MainWindow::updateQueryParamsCount(void)
{
    ui->mainTab->setTabText(ui->mainTab->indexOf(ui->queryTab), QString("Query (%1)").arg(ui->queryParams->rowCount()));
}

void MainWindow::updateFragmentParamsCount(void)
{
    ui->mainTab->setTabText(ui->mainTab->indexOf(ui->fragmentTab), QString("Fragment (%1)").arg(ui->fragmentParams->rowCount()));
}

void MainWindow::on_addQueryParam_clicked()
{
    const auto& key = ui->queryParamKey->text();
    const auto& values = ui->queryParamValues->text();

    table_AddPair(ui->queryParams, key, values);
    updateQueryParamsCount();
}

void MainWindow::on_addFragmentParam_clicked()
{
    const auto& key = ui->fragmentParamKey->text();
    const auto& values = ui->fragmentParamValues->text();

    table_AddPair(ui->fragmentParams, key, values);
    updateFragmentParamsCount();
}
