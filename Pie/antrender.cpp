#include "antrender.h"

#include "winbgi_qt.h"
#include "Stan.h"
#include "ACom_V.h"
#include "atools.h"


void AntRender::rend(QPainter *painter, const QRectF& boundingRect )
{
  painter->setRenderHints(QPainter::Antialiasing, true);

  QPen pen(Qt::green, 2);
  painter->setPen(pen);
  painter->drawPie(boundingRect, 90 * 16, 290 * 16);


  Station *stan=new Station("");
  QString fn="ste/sta/holoni.ste";

  stan->Open(fn.toStdString().c_str());
  CurrentPicture=LT;
  MOD=ED;

  alib::tools::ProfilerTimer t(__FUNCTION__);
  setAntLibPainter(painter);
  stan->Clear();
  stan->Go();
//  stan->Show();
  return;

  for (int i = 1; i < Units_Size; i++) {
    for (int j = 0; j < stan->POLE[i]->GetArraySize(); j++){
      auto ac=stan->POLE[i]->GetObjPtr(j);
      start_bgi_tracking();
      ac->Show();
      QRect r=stop_bgi_tracking();
      painter->setPen(pen);
//      painter->drawRect(r);
    }
  }


}
