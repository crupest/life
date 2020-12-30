#include "qboxlayout.h"
#include "qtableview.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  QWidget window;
  QVBoxLayout window_layout;
  window.setLayout(&window_layout);

  QHBoxLayout top_bar;
  window_layout.addLayout(&top_bar);

  QPushButton import_button(QStringLiteral("导入"));
  QPushButton export_button(QStringLiteral("导出"));
  top_bar.addWidget(&import_button);
  top_bar.addWidget(&export_button);
  top_bar.addStretch(1);

  QHBoxLayout center_area;
  window_layout.addLayout(&center_area);

  QTableView book_view;
  QTableView vendor_view;

  center_area.addWidget(&book_view);
  center_area.addWidget(&vendor_view);

  window.show();

  return application.exec();
}
