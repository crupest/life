#include "Base.hpp"
#include "StringUtil.hpp"

#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

inline std::u16string_view ToUtf16View(const std::wstring &str) {
  return std::u16string_view(reinterpret_cast<const char16_t *>(str.c_str()),
                             str.size());
}

inline std::wstring_view ToWStringView(std::u16string_view str) {
  return std::wstring_view(reinterpret_cast<const wchar_t *>(str.data()),
                           str.size());
}

class SerializationException : public std::runtime_error {
public:
  using runtime_error::runtime_error;
};

std::vector<std::string_view> SplitByVerticalLine(std::string_view str,
                                                  int field_count) {
  std::vector<std::string_view> fields;
  gsl::index current_position = 0;

  for (int i = 0; i < field_count - 1; i++) {
    auto pos = str.find('|', current_position);
    if (pos == std::string::npos) {
      throw SerializationException("Failed to find next splitter('|').");
    }
    fields.push_back(str.substr(current_position, pos - current_position));
    current_position = pos + 1;
  }
  fields.push_back(str.substr(current_position));

  return fields;
}

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

std::istream &operator>>(std::istream &left, Book &right) {
  std::string line;
  std::getline(left, line);

  std::vector<std::string_view> fields = SplitByVerticalLine(line, 6);

  right.SetIsbn(cru::ToUtf16(fields[0]));
  right.SetTitle(cru::ToUtf16(fields[1]));
  right.SetType(cru::ToUtf16(fields[2]));
  right.SetAuthor(cru::ToUtf16(fields[3]));
  right.SetPress(cru::ToUtf16(fields[4]));
  right.SetStockCount(std::stoi(std::string(fields[5])));

  return left;
}

std::ostream &operator<<(std::ostream &left, const Book &right) {
  left << cru::ToUtf8(right.GetIsbn()) << '|' << cru::ToUtf8(right.GetTitle())
       << '|' << cru::ToUtf8(right.GetType()) << '|'
       << cru::ToUtf8(right.GetAuthor()) << '|' << cru::ToUtf8(right.GetPress())
       << '|' << right.GetStockCount();
  return left;
}

void PrettyPrint(std::wostream &stream, const Book &book) {
  stream << L"ISBN: " << ToWStringView(book.GetIsbn()) << L"\n";
  stream << L"标题: " << ToWStringView(book.GetTitle()) << L"\n";
  stream << L"类型: " << ToWStringView(book.GetType()) << L"\n";
  stream << L"作者: " << ToWStringView(book.GetAuthor()) << L"\n";
  stream << L"出版社: " << ToWStringView(book.GetPress()) << L"\n";
  stream << L"库存: " << book.GetStockCount() << L"\n";
}

class Vendor final {
public:
  Vendor() = default;
  Vendor(int id, std::u16string name, std::u16string type,
         std::u16string address, std::u16string phone)
      : id_(id), name_(std::move(name)), type_(std::move(type)),
        address_(std::move(address)), phone_(std::move(phone)) {}

  CRU_DEFAULT_COPY(Vendor)
  CRU_DEFAULT_MOVE(Vendor)

  ~Vendor() = default;

public:
  int GetId() const { return id_; }
  void SetId(int id) { id_ = id; }

  std::u16string GetName() const { return name_; }
  void SetName(std::u16string name) { name_ = std::move(name); }

  std::u16string GetType() const { return type_; }
  void SetType(std::u16string type) { type_ = std::move(type); }

  std::u16string GetAddress() const { return address_; }
  void SetAddress(std::u16string address) { address_ = std::move(address); }

  std::u16string GetPhone() const { return phone_; }
  void SetPhone(std::u16string phone) { phone_ = std::move(phone); }

private:
  int id_;
  std::u16string name_;
  std::u16string type_;
  std::u16string address_;
  std::u16string phone_;
};

std::istream &operator>>(std::istream &left, Vendor &right) {
  std::string line;
  std::getline(left, line);

  std::vector<std::string_view> fields = SplitByVerticalLine(line, 5);

  right.SetId(std::stoi(std::string(fields[0])));
  right.SetName(cru::ToUtf16(fields[1]));
  right.SetType(cru::ToUtf16(fields[2]));
  right.SetAddress(cru::ToUtf16(fields[3]));
  right.SetPhone(cru::ToUtf16(fields[4]));

  return left;
}

std::ostream &operator<<(std::ostream &left, const Vendor &right) {
  left << right.GetId() << '|' << cru::ToUtf8(right.GetName()) << '|'
       << cru::ToUtf8(right.GetType()) << '|' << cru::ToUtf8(right.GetAddress())
       << '|' << cru::ToUtf8(right.GetPhone());
  return left;
}

class Record final {
public:
  Record();

  CRU_DEFAULT_COPY(Record);
  CRU_DEFAULT_MOVE(Record);

  ~Record() = default;

public:
  void WriteTo(std::ostream &stream);
  void ReadFrom(std::istream &stream);

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

void Record::WriteTo(std::ostream &stream) {
  stream << books_.size() << ' ' << vendors_.size() << '\n';
  for (const auto &book : books_) {
    stream << book << '\n';
  }
  for (const auto &vendor : vendors_) {
    stream << vendor << '\n';
  }
}

void Record::ReadFrom(std::istream &stream) {
  books_.clear();
  vendors_.clear();
  int book_count, vendor_count;
  stream >> book_count >> vendor_count;
  stream >> std::ws;
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

int main() {
  Record record;

  while (true) {
    std::wcout << L"1. 查询 2. 添加 0. 退出\n";
    int choice = 0;
    std::wcin >> choice;
    if (choice == 1) {
      std::wcout
          << L"1. 图书 2. 供应商\n输入数字选择操作，其他任意字符将退出程序。\n";
      choice = 0;
      std::wcin >> choice;
      if (choice == 1) {
        std::wcout << L"请输入图书编号：\n";
        std::wstring isbn;
        std::wcin >> isbn;
        auto find_result = record.FindBookByIsbn(ToUtf16View(isbn));
        if (find_result) {
          PrettyPrint(std::wcout, *find_result);
          std::wcout << L"0. 返回主菜单 1. 修改 2. 删除\n";
          choice = 0;
          std::wcin >> choice;
          if (choice == 1) {
            // TODO: 
          } else if (choice == 2) {
            record.RemoveBookByIsbn(ToUtf16View(isbn));
            std::wcout << L"删除成功。\n";
          }
        } else {
          std::wcout << L"该书不存在。\n";
        }
      } else if (choice == 2) {

      } else {
        return 0;
      }

    } else if (choice == 2) {

    } else {
      return 0;
    }
  }

  return 0;
}
