#include <QGuiApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

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
