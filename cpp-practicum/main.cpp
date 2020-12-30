#include "Record.hpp"

#include <QApplication>
#include <QHBoxLayout>
#include <QHeaderView>
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
  QPushButton add_book_button(QStringLiteral("添加书"));

  top_bar.addWidget(&import_button);
  top_bar.addWidget(&export_button);
  top_bar.addStretch(1);
  top_bar.addWidget(&add_book_button);

  QHBoxLayout center_area;
  window_layout.addLayout(&center_area);

  QTableView book_view;
  book_view.verticalHeader()->hide();
  book_view.setSelectionBehavior(QAbstractItemView::SelectRows);
  book_view.setEditTriggers(QAbstractItemView::DoubleClicked);
  book_view.setSelectionMode(QAbstractItemView::SingleSelection);
  QTableView vendor_view;

  center_area.addWidget(&book_view);
  center_area.addWidget(&vendor_view);

  Record record;
  BookModel book_model(&record);

  book_view.setModel(&book_model);

  QObject::connect(&add_book_button, &QPushButton::clicked, [&book_model]() {
    book_model.insertRow(book_model.rowCount());
  });

  window.show();

  return application.exec();
}
