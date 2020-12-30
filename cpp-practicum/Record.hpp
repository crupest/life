#pragma once
#include "Base.hpp"

#include "Book.hpp"
#include "Vendor.hpp"

#include <QFile>
#include <optional>
#include <vector>

class Record final {
public:
  Record();

  CRU_DEFAULT_COPY(Record);
  CRU_DEFAULT_MOVE(Record);

  ~Record() = default;

public:
  void WriteTo(QFile file);
  void ReadFrom(QFile file);

  const std::vector<Book> &GetBooks() const { return books_; }
  const std::vector<Vendor> &GetVendors() const { return vendors_; }

  // TODO: Implementation
  std::optional<Book> FindBookByIsbn(std::u16string_view isbn);

  // TODO: Implementation
  void RemoveBookByIsbn(std::u16string_view isbn);

private:
  std::vector<Book> books_;
  std::vector<Vendor> vendors_;
};
