#include "smartsta.h"
#include "qnamespace.h"

#include <QDebug>

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

#include "Polig.h"
#include "Stan.h"
#include "atools.h"
#include "winbgi_qt.h"

void SmartSta::setPath(const QString &newPath) {
  if (m_path == newPath)
    return;
  m_path = newPath;
  emit pathChanged();
  emit keyChanged();

  if(m_path.isEmpty()){
    this->setOpened( false );
    return;
  }

  if(this->opened())
    this->setOpened( false );
  this->setOpened( true );
}

void SmartSta::setOpened(bool newOpened) {
  if (m_opened == newOpened)
    return;

  if(newOpened)
    open();
  else
    close();

  if (m_opened == newOpened)
    emit openedChanged();
}

bool SmartSta::open() {
  alib::tools::ProfilerTimer t(__PRETTY_FUNCTION__);
  try {
    close();
    MOD = RD;
    CurrentPicture = BG;
    CurrentStation = 0;
    sta.reset(new Station());
    if (sta->Open( m_path.toStdString().c_str() ) < 0)
      return false;
    m_opened = true;
  } catch (const std::exception& e) {
    std::clog << "std::exception: " << e.what() << std::endl;
  }
  needUpdate();
  return m_opened;
}

void SmartSta::close() {
  if(sta) {
    sta->Close();
    sta.reset();
    needUpdate();
  }
  m_opened = false;
}

SmartSta::SmartSta(QObject *parent)
    :QObject(parent)
{
}

QString SmartSta::key() const {
  return QString::fromStdString( fs::path( m_path.toStdString() ).filename().u8string() ).toLower();
}

QString SmartSta::name() const
{
  return sta ? sta->Name().asQString() : "No Data";
}

void SmartSta::DrawBgiOn(QPainter *painter) {
  alib::tools::ProfilerTimer t(__PRETTY_FUNCTION__);

  if ( !this->opened() )
    return;
  try {
    bool s = false;
    ::CurrentPicture = LT;
    setAntLibPainter(painter);

    if (s) {
      sta->Clear();
      sta->Show();
    } else {
      sta->Clear();
      sta->Go();
    }
  }
  catch (...)  {
    std::clog << "ERROR on SmartSta::DrawBgiOn." << std::endl;
  }

}

