#include "Record.hpp"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

int main(int argc, char *argv[]) {
  QApplication application(argc, argv);

  Record record;

  QDir app_dir(application.applicationDirPath());
  QFile data_file = app_dir.filePath("data.txt");
  std::unique_ptr<QTextStream> stream;
  if (data_file.exists()) {
    data_file.open(QFile::ReadWrite);
    stream.reset(new QTextStream(&data_file));
    stream->setCodec("UTF-8");
    try {
      record.ReadFrom(*stream);
    } catch (...) {
    }
  } else {
    data_file.open(QFile::ReadWrite);
    stream.reset(new QTextStream(&data_file));
    stream->setCodec("UTF-8");
  }

  QWidget window;
  QVBoxLayout window_layout;
  window.setLayout(&window_layout);

  QHBoxLayout center_area;
  window_layout.addLayout(&center_area);

  QVBoxLayout book_area;
  QVBoxLayout vendor_area;
  center_area.addLayout(&book_area);
  center_area.addLayout(&vendor_area);

  QHBoxLayout book_top_area;
  QHBoxLayout vendor_top_area;
  book_area.addLayout(&book_top_area);
  vendor_area.addLayout(&vendor_top_area);

  QPushButton book_add_button(QStringLiteral("添加"));
  QPushButton book_remove_button(QStringLiteral("删除"));

  book_top_area.addStretch(1);
  book_top_area.addWidget(&book_add_button);
  book_top_area.addWidget(&book_remove_button);

  QPushButton vendor_add_button(QStringLiteral("添加"));
  QPushButton vendor_remove_button(QStringLiteral("删除"));

  vendor_top_area.addStretch(1);
  vendor_top_area.addWidget(&vendor_add_button);
  vendor_top_area.addWidget(&vendor_remove_button);

  QTableView book_view;
  book_view.verticalHeader()->hide();
  book_view.setSelectionBehavior(QAbstractItemView::SelectRows);
  book_view.setEditTriggers(QAbstractItemView::DoubleClicked);
  book_view.setSelectionMode(QAbstractItemView::SingleSelection);
  book_view.setSortingEnabled(true);

  QTableView vendor_view;
  vendor_view.verticalHeader()->hide();
  vendor_view.setSelectionBehavior(QAbstractItemView::SelectRows);
  vendor_view.setEditTriggers(QAbstractItemView::DoubleClicked);
  vendor_view.setSelectionMode(QAbstractItemView::SingleSelection);

  book_area.addWidget(&book_view, 1);
  vendor_area.addWidget(&vendor_view, 1);

  BookModel book_model(&record);
  VendorModel vendor_model(&record);

  book_view.setModel(&book_model);
  vendor_view.setModel(&vendor_model);

  QObject::connect(&book_add_button, &QPushButton::clicked, [&book_model]() {
    book_model.insertRow(book_model.rowCount());
  });

  QObject::connect(
      &book_remove_button, &QPushButton::clicked, [&book_view, &book_model]() {
        auto selected_rows = book_view.selectionModel()->selectedRows();
        for (const auto &row : selected_rows) {
          book_model.removeRow(row.row());
        }
      });

  QObject::connect(
      &vendor_add_button, &QPushButton::clicked,
      [&vendor_model]() { vendor_model.insertRow(vendor_model.rowCount()); });

  QObject::connect(&vendor_remove_button, &QPushButton::clicked,
                   [&vendor_view, &vendor_model]() {
                     auto selected_rows =
                         vendor_view.selectionModel()->selectedRows();
                     for (const auto &row : selected_rows) {
                       vendor_model.removeRow(row.row());
                     }
                   });

  window.show();

  int result = application.exec();

  record.WriteTo(*stream);

  return result;
}
