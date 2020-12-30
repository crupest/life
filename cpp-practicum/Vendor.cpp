#include "Vendor.hpp"

#include <QString>

QTextStream &operator>>(QTextStream &left, Vendor &right) {
  auto line = left.readLine();

  auto fields = line.split(QChar('|'));

  if (fields.size() != 5) {
    throw SerializationException("Line has not 5 parts.");
  }

  bool ok;
  auto id = fields[0].toInt(&ok);
  if (!ok) {
    throw SerializationException("Part 1 is not a number.");
  }

  right.SetId(id);
  right.SetName(fields[1].toStdU16String());
  right.SetType(fields[2].toStdU16String());
  right.SetAddress(fields[3].toStdU16String());
  right.SetPhone(fields[4].toStdU16String());

  return left;
}

QTextStream &operator<<(QTextStream &left, const Vendor &right) {
  left << right.GetId() << '|' << right.GetName() << '|' << right.GetType()
       << '|' << right.GetAddress() << '|' << right.GetPhone();
  return left;
}
