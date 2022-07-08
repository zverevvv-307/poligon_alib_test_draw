#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QPainter>

#include <memory>

#include "Stan.h"

class SmartSta : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
  Q_PROPERTY(bool opened READ opened WRITE setOpened NOTIFY openedChanged)
  Q_PROPERTY(QString key READ key NOTIFY keyChanged)
  Q_PROPERTY(QString name READ name NOTIFY openedChanged)
  QML_ELEMENT

public:
  explicit SmartSta(QObject *parent = nullptr);

  QString key() const;
  QString name() const;
  Q_INVOKABLE void DrawBgiOn(QPainter *painter);

  const QString& path() const { return m_path; }
  void setPath(const QString &newPath);
  Q_SIGNAL void pathChanged();

  bool opened() const{ return sta && m_opened; }
  void setOpened(bool newOpened);
  Q_SIGNAL void openedChanged();

  Q_SIGNAL void keyChanged();
  Q_SIGNAL void needUpdate();

private:

  bool open();
  void close();

  QString m_path;
  bool m_opened = false;

  std::unique_ptr<Station> sta;
};

