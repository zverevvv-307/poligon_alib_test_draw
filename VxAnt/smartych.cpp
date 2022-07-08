#include "smartych.h"
#include "qtmetamacros.h"

#include <QDebug>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

#include "Polig.h"
#include "Stan.h"
#include "atools.h"
#include "winbgi_qt.h"
#include "linuxcasetransformpathfunction.h"

void SmartYch::setPath(const QString &newPath) {
  if (m_path == newPath)
    return;
  m_path = newPath;
  Q_EMIT pathChanged();
  Q_EMIT keyChanged();

  if(m_path.isEmpty()){
    this->setOpened( false );
    return;
  }

  if(this->opened())
    this->setOpened( false );
  this->setOpened( true );
}

void SmartYch::setOpened(bool newOpened) {
  if (m_opened == newOpened)
    return;

  if(newOpened)
    open();
  else
    close();

  if (m_opened == newOpened)
    Q_EMIT openedChanged();
}

bool SmartYch::open() {
  alib::tools::ProfilerTimer t(__PRETTY_FUNCTION__);
  close();

  LinuxCaseTransformPathFunction::set_root( m_path.toStdString() );

  MOD = RD;
  CurrentPicture = BG;
  CurrentStation = 0;

  try {
    ych.reset(new Poligon());
    if (ych->Open( m_path.toStdString().c_str() ) < 0)
      return false;
  } catch (const std::exception& e) {
    std::clog << "std::exception: " << e.what() << std::endl;
    return false;
  }
  m_opened = true;;
  needUpdate();
  return m_opened;

}

void SmartYch::close() {
  if(ych){
    ych->Close();
    ych.reset();
    needUpdate();
  }
  m_opened = false;
}

SmartYch::SmartYch(QObject *parent)
    :QObject(parent)
{
}

QString SmartYch::key() const {
  return QString::fromStdString( fs::path( m_path.toStdString() ).filename().u8string() ).toLower();
}

QString SmartYch::name() const
{
  return ych ? ych->Name().asQString() : "No Data";
}


QString SmartYch::current_sta() const {

  Station *pStan = nullptr;
  if(ych){
    if (this->CurrentPicture != BG)
      pStan = ych->STB[this->CurrentStation];
    else
      pStan = ych->ST[this->CurrentStation];
  }

  std::string sta;
  if(pStan)
    sta = fs::path(pStan->filename.c_str()).filename().u8string();

  return QString::fromStdString(sta);
}

void SmartYch::DrawBgiOn(QPainter *painter) {
  alib::tools::ProfilerTimer t(__PRETTY_FUNCTION__);
  if (! this->opened())
    return;

  try {
    bool s = false;
//    MOD=ED;
    ::CurrentPicture = this->CurrentPicture;
    ::CurrentStation = this->CurrentStation;
    setAntLibPainter(painter);
    if (this->CurrentPicture == BG) {
      if (s) {
        ych->Clear();
        ych->Show();
      } else {
        ych->Clear();
        ych->Go();
      }
    } else {
      Station *pStan = ych->STB[this->CurrentStation];
      if (pStan == 0)
        return;

      if (s) {
        pStan->Clear();
        pStan->Show();
      } else {
        pStan->Clear();
        pStan->Go();
      }
    }
  }
  catch (...)  {
    std::clog << "ERROR on SmartYch::DrawBgiOn." << std::endl;
  }

}

