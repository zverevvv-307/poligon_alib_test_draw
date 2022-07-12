//#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFileInfo>
#include <QSettings>


int main(int argc, char *argv[])
{
//  QApplication app(argc, argv);
  QGuiApplication app(argc, argv);

  app.setOrganizationName("Gtss");
  app.setApplicationName(QFileInfo(app.applicationFilePath()).baseName());
  QSettings::setDefaultFormat(QSettings::IniFormat);
  QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, "./" );
  QSettings settings;
  qDebug()<<"Ini file:"<<settings.fileName();

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/poligon/main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
      &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      }, Qt::QueuedConnection);


//  engine.addImportPath(QStringLiteral(":/"));
//  engine.addImportPath(".");
//  engine.addImportPath("..");
  engine.load(url);

  return app.exec();
}
