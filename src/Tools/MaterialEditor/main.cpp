#include "EditorWindow.hpp"
#include <QApplication>

#ifdef _WIN32
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
#ifdef _WIN32
  int argc = 1;
  char* argv[1] = { lpCmdLine };
#endif
  QApplication app(argc, argv);
  EditorWindow window;
  window.show();
  return app.exec();
}
