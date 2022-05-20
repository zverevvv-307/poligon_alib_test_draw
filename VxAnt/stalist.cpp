#include "stalist.h"

#include <QDebug>
#include <QJsonArray>

#include <memory>
#include <map>
#include <filesystem>

#include "atools.h"
#include "qdebug.h"
#include "qglobal.h"
#include "utils.h"

namespace fs = std::filesystem;

StaList::StaList(QObject *parent)
    : QObject{parent}
{
}

void StaList::setPath(const QString &newPath)
{
  if (m_path == newPath)
    return;
  m_path = newPath;
  emit pathChanged();
  this->close();
  this->open();
}


auto is_sta_file = [](const fs::path& path) {
  std::string ex = alib::to_lower( path.extension() );
  return ex == ".sta" || ex == ".ste";
};

void StaList::open()
{
  alib::tools::ProfilerTimer t(__FUNCTION__);

  fs::path path = m_path.toStdString();
  if ( is_sta_file(path) )
    path  = path.remove_filename();

  QJsonArray list;
  for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{path}) {
    if( not dir_entry.is_directory() ){
      //if( dir_entry.is_regular_file() ){
      std::string key = alib::to_lower( dir_entry.path().filename().u8string() );
      if( not is_sta_file(dir_entry) )
        continue;
      QJsonObject o {
          {"key",  QString::fromStdString(key)},
          {"type", QString::fromStdString(dir_entry.path().extension()).toLower()},
          {"path", QString::fromStdString(dir_entry.path().lexically_normal().u8string())}
      };
      list.append(o);
      std::cout << key << " -> " << dir_entry << std::endl;
    }
  }

  QJsonObject js;
  js["items"]= list;
  m_json = QJsonDocument(js).toJson(QJsonDocument::Compact);
  emit jsonChanged( m_json );
//  qDebug() << m_json;
}

void StaList::close()
{
  if( m_json.size() ){
    m_json = {};
    emit jsonChanged( m_json );
  }
}

