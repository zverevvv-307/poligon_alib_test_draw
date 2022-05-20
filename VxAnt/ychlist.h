#pragma once

#include <QObject>
#include <QStringList>
#include <QQmlEngine>
#include <QJsonDocument>
#include <QJsonObject>


class YchList : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
  Q_PROPERTY(QString json READ json NOTIFY jsonChanged)
  QML_ELEMENT

public:
  explicit YchList(QObject *parent = nullptr);

  const QString& path() const { return m_path; }
  void setPath(const QString &newPath);
  Q_SIGNAL void pathChanged();

  QString json() const { return m_json; }
  Q_SIGNAL void jsonChanged(const QString& );


private:

  void open();
  void close();
  QString m_path;
  QString m_json;

};

