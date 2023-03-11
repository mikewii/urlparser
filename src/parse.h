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
                    const QList<QPair<QString,QString>>& fragmentItems,
                    const QString& scheme,
                    const QString& host,
                    const QString& path,
                    const int port,
                    const QString& authority,
                    const QString& userInfo,
                    const QString& userName,
                    const QString& password) const;

    QList<QPair<QString,QString>> queryItems(void) const {return m_query.queryItems();}
    QList<QPair<QString,QString>> fragmentItems(void) const {return m_fragment.queryItems();}

signals:
    void query_ready();
    void fragment_ready();
    void basic_ready();

private:
    QUrlQuery m_query;
    QUrlQuery m_fragment;
    QUrl::ParsingMode m_parsingMode;
};
