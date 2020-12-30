#include "qboxlayout.h"
#include "qnamespace.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QMainWindow main_window;

  QWidget centeral_area;
  QVBoxLayout central_area_layout;
  centeral_area.setLayout(&central_area_layout);

  main_window.setCentralWidget(&centeral_area);

  QWidget top_bar;
  QHBoxLayout top_bar_layout;
  top_bar.setLayout(&top_bar_layout);
  central_area_layout.addWidget(&top_bar);

  QPushButton import_button(QStringLiteral("导入"));
  QPushButton export_button(QStringLiteral("导出"));
  top_bar_layout.addWidget(&import_button);
  top_bar_layout.addWidget(&export_button);

  main_window.show();

  return application.exec();
}
