#include "poligonsimplepainter.h"

PoligonSimplePainter::PoligonSimplePainter(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void PoligonSimplePainter::paint(QPainter *painter)
{
  painter->setRenderHints(QPainter::Antialiasing, true);

  QString name{"No data."};

  if(m_ych){
    m_ych->DrawBgiOn(painter);
    name = m_ych->key();
  }
  else if (m_sta) {
    m_sta->DrawBgiOn(painter);
    name = m_sta->key();
  }

  {
    QPen pen(Qt::gray, 6);
    painter->setPen(pen);
    auto rect = boundingRect().adjusted(3, 3, -3, -3);
    painter->drawRect(rect);
    painter->drawText( rect, Qt::AlignCenter, name );
  }
}

void PoligonSimplePainter::setYch(SmartYch *newYch)
{
  if (m_ych == newYch)
    return;
  m_ych = newYch;
  emit ychChanged();
}

void PoligonSimplePainter::setSta(SmartSta *newSta)
{
  if (m_sta == newSta)
    return;
  m_sta = newSta;
  emit staChanged();
}
