#include "poligonsimplepainter.h"

PoligonSimplePainter::PoligonSimplePainter(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_Label("No data.")
{
}

void PoligonSimplePainter::paint(QPainter *painter)
{
  painter->setRenderHints(QPainter::Antialiasing, true);

  if(m_ych){
    m_ych->DrawBgiOn(painter);
  }
  else if (m_sta) {
    m_sta->DrawBgiOn(painter);
  }

  {
//    QPen pen(Qt::gray, 6);
//    painter->setPen(pen);
//    auto rect = boundingRect().adjusted(3, 3, -3, -3);
//    painter->drawRect(rect);


    QFont font = painter->font();
    font.setPixelSize(24);
    painter->setFont(font);
    painter->drawStaticText(10, 10, m_Label );
  }
}

void PoligonSimplePainter::setYch(SmartYch *newYch)
{
  if (m_ych == newYch)
    return;
  m_ych = newYch;
  m_Label.setText( m_ych->key() );
  emit ychChanged();
  update();
}

void PoligonSimplePainter::setSta(SmartSta *newSta)
{
  if (m_sta == newSta)
    return;
  m_sta = newSta;
  m_Label.setText( m_sta->key() );
  emit staChanged();
  update();
}
