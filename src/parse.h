#pragma once
#include <QObject>
#include <QUrl>
#include <QUrlQuery>

class URL : public QObject, public QUrl
{
    Q_OBJECT
    Q_DISABLE_COPY(URL)
public:
    explicit URL(QObject *parent = nullptr);

    void parse(const QString& url);
    QString unparse(const QList<QPair<QString,QString>>& queryItems,
                    const QString& scheme,
                    const QString& host,
                    const QString& path,
                    const int port,
                    const QString& authority,
                    const QString& userInfo,
                    const QString& userName,
                    const QString& password) const;

    QList<QPair<QString,QString>> queryItems(void) const {return m_query.queryItems();}

signals:
    void query_ready();
    void basic_ready();

private:
    QUrlQuery m_query;
    QUrl::ParsingMode m_parsingMode;
};
