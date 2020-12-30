#pragma once
#include "Base.hpp"

#include "Book.hpp"
#include "Vendor.hpp"

#include <QAbstractTableModel>
#include <QTextStream>
#include <optional>
#include <vector>

class Record final {
public:
  Record() = default;

  CRU_DEFAULT_COPY(Record);
  CRU_DEFAULT_MOVE(Record);

  ~Record() = default;

public:
  void WriteTo(QTextStream &stream);
  void ReadFrom(QTextStream &stream);

  std::vector<Book> &GetBooks() { return books_; }
  std::vector<Vendor> &GetVendors() { return vendors_; }

private:
  std::vector<Book> books_;
  std::vector<Vendor> vendors_;
};

class BookModel : public QAbstractTableModel {
public:
  explicit BookModel(Record *record) : record_(record) {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

private:
  Record *record_;
};

class VendorModel : public QAbstractTableModel {
public:
  explicit VendorModel(Record *record) : record_(record) {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex()) override;

private:
  Record *record_;
};
