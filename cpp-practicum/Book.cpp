#include "Book.hpp"

#include <QString>

QTextStream &operator>>(QTextStream &left, Book &right) {
  auto line = left.readLine();

  auto fields = line.split(QChar('|'));

  if (fields.size() != 6) {
    throw SerializationException("The line has not 6 parts.");
  }

  right.SetIsbn(fields[0].toStdU16String());
  right.SetTitle(fields[1].toStdU16String());
  right.SetType(fields[2].toStdU16String());
  right.SetAuthor(fields[3].toStdU16String());
  right.SetPress(fields[4].toStdU16String());

  bool ok;
  auto stock_count = fields[5].toInt(&ok);
  if (!ok) {
    throw SerializationException("Part 6 is not a number.");
  }

  right.SetStockCount(stock_count);

  return left;
}

QTextStream &operator<<(QTextStream &left, const Book &right) {
  left << right.GetIsbn() << '|' << right.GetTitle() << '|' << right.GetType()
       << '|' << right.GetAuthor() << '|' << right.GetPress() << '|'
       << right.GetStockCount();
  return left;
}
