#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QPainter>

#include <memory>

#include "Polig.h"

class SmartYch : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
  Q_PROPERTY(bool opened READ opened WRITE setOpened NOTIFY openedChanged)
  Q_PROPERTY(QString key READ key NOTIFY keyChanged)
  Q_PROPERTY(QString current_sta READ current_sta)
  QML_ELEMENT

public:

  explicit SmartYch(QObject *parent = nullptr);

  QString key() const;

  const QString& path() const { return m_path; }
  void setPath(const QString &newPath);
  Q_SIGNAL void pathChanged();

  bool opened() const{ return ych && m_opened; }
  void setOpened(bool newOpened);
  Q_SIGNAL void openedChanged();

  Q_INVOKABLE void DrawBgiOn(QPainter *painter);
  QString current_sta() const;

  Q_SIGNAL void keyChanged();

  Q_SIGNAL void needUpdate();

private:

  bool open();
  void close();


  QString m_path;
  bool m_opened = false;

  //Polig
  std::unique_ptr<Poligon> ych;
  int CurrentStation=0;
  int CurrentPicture=0;
};

