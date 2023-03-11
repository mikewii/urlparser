#include "parse.h"
#include <QDebug>

URL::URL(QObject *parent)
    : QObject(parent)
    , m_parsingMode(QUrl::ParsingMode::TolerantMode)
{
}

void URL::parse(const QString &url)
{
    QUrl::clear();
    m_query.clear();
    m_fragment.clear();

    QUrl::setUrl(url);

    if (!QUrl::isValid() || QUrl::isEmpty()) {
        qDebug() << QUrl::errorString();
        return;
    }

    emit basic_ready();

    if (QUrl::hasFragment()) {
        m_fragment.setQuery(QUrl::fragment());
        emit fragment_ready();
    }

    if (QUrl::hasQuery()) {
        m_query.setQuery(QUrl::query());
        emit query_ready();
    }
}

QString URL::unparse(const QList<QPair<QString,QString>>& queryItems,
                     const QList<QPair<QString,QString>>& fragmentItems,
                     const QString& scheme,
                     const QString& host,
                     const QString& path,
                     const int port,
                     const QString& authority,
                     const QString& userInfo,
                     const QString& userName,
                     const QString& password) const
{
#define setIfNotEmpty(var, fun) \
    if (!var.isEmpty()) \
        fun(var) \

    QUrl url;
    QUrlQuery query;
    QUrlQuery fragment;

    setIfNotEmpty(scheme, url.setScheme);
    setIfNotEmpty(host, url.setHost);
    setIfNotEmpty(path, url.setPath);
    setIfNotEmpty(authority, url.setAuthority);
    setIfNotEmpty(userInfo, url.setUserInfo);
    setIfNotEmpty(userName, url.setUserName);
    setIfNotEmpty(password, url.setPassword);

    setIfNotEmpty(queryItems, query.setQueryItems);
    setIfNotEmpty(query, url.setQuery);

    setIfNotEmpty(fragmentItems, fragment.setQueryItems);
    setIfNotEmpty(fragment.toString(), url.setFragment);

    if (port != -1)
        url.setPort(port);

    return url.toString();
}
