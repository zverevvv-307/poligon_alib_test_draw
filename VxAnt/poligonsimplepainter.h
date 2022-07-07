#pragma once

#include <QObject>
#include <QQuickItem>
#include <QtQuick/QQuickPaintedItem>
#include "qtmetamacros.h"
#include "smartych.h"
#include "smartsta.h"
//#include "myprop_helpers.h"
#include <QStaticText>


class PoligonSimplePainter : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(SmartYch* ych READ ych WRITE setYch NOTIFY ychChanged);
  Q_PROPERTY(SmartSta* sta READ sta WRITE setSta NOTIFY staChanged);
  QML_ELEMENT


  void paint(QPainter *painter) override;

public:
  explicit PoligonSimplePainter(QQuickItem *parent = nullptr);

  SmartYch* ych() const{ return m_ych; }
  void setYch(SmartYch *newYch);
  Q_SIGNAL void ychChanged();

  SmartSta *sta() const{ return m_sta; }
  void setSta(SmartSta *newSta);
  Q_SIGNAL void staChanged();

private:
  SmartYch *m_ych=nullptr;
  SmartSta *m_sta=nullptr;

  QStaticText m_Label;
};

