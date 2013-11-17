#include "EditorWindow.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  EditorWindow window;
  window.show();
  return app.exec();
}
