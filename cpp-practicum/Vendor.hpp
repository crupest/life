#pragma once
#include "Base.hpp"

#include <QTextStream>
#include <string>

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

QTextStream &operator>>(QTextStream &left, Vendor &right);
QTextStream &operator<<(QTextStream &left, const Vendor &right);
