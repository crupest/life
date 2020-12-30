#pragma once
#include "Base.hpp"

#include <QTextStream>
#include <string>

class Book final {
public:
  Book() = default;

  Book(std::u16string isbn, std::u16string title, std::u16string type,
       std::u16string author, std::u16string press, int stock_count)
      : isbn_(std::move(isbn)), title_(std::move(title)),
        type_(std::move(type)), author_(std::move(author)),
        press_(std::move(press)), stock_count_(stock_count) {}

  CRU_DEFAULT_COPY(Book)
  CRU_DEFAULT_MOVE(Book)

  ~Book() = default;

public:
  std::u16string GetIsbn() const { return isbn_; }
  void SetIsbn(std::u16string isbn) { isbn_ = std::move(isbn); }

  std::u16string GetTitle() const { return title_; }
  void SetTitle(std::u16string title) { title_ = std::move(title); }

  std::u16string GetType() const { return type_; }
  void SetType(std::u16string type) { type_ = std::move(type); }

  std::u16string GetAuthor() const { return author_; }
  void SetAuthor(std::u16string author) { author_ = std::move(author); }

  std::u16string GetPress() const { return press_; }
  void SetPress(std::u16string press) { press_ = std::move(press); }

  int GetStockCount() const { return stock_count_; }
  void SetStockCount(int stock_count) { stock_count_ = stock_count; }

private:
  std::u16string isbn_;
  std::u16string title_;
  std::u16string type_;
  std::u16string author_;
  std::u16string press_;
  int stock_count_;
};

QTextStream &operator>>(QTextStream &left, Book &right);
QTextStream &operator<<(QTextStream &left, const Book &right);
