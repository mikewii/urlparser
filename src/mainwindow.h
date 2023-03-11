#pragma once
#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(URL)
QT_FORWARD_DECLARE_CLASS(QTableWidget)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_parse_clicked();
    void on_unparse_clicked();
    void on_addQueryParam_clicked();

    void basic_ready();
    void query_ready();
    void fragment_ready();

    void on_addFragmentParam_clicked();

private:
    Ui::MainWindow *ui;
    URL *m_url;

    void table_AddPair(QTableWidget* tableWidget, const QString& key, const QString& values);
};
