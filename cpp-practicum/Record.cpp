#include "Record.hpp"

void Record::WriteTo(QFile file) {
  file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate);
  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  stream << books_.size() << ' ' << vendors_.size() << '\n';
  for (const auto &book : books_) {
    stream << book << '\n';
  }
  for (const auto &vendor : vendors_) {
    stream << vendor << '\n';
  }
}

void Record::ReadFrom(QFile file) {
  file.open(QFile::ReadOnly | QFile::Text);
  QTextStream stream(&file);
  stream.setCodec("UTF-8");

  books_.clear();
  vendors_.clear();

  int book_count, vendor_count;
  stream >> book_count >> vendor_count;
  stream.skipWhiteSpace();
  for (int i = 0; i < book_count; i++) {
    Book book;
    stream >> book;
    books_.push_back(std::move(book));
  }
  for (int i = 0; i < vendor_count; i++) {
    Vendor vendor;
    stream >> vendor;
    vendors_.push_back(std::move(vendor));
  }
}
