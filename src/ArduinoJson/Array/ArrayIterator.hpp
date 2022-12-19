// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2022, Benoit BLANCHON
// MIT License

#pragma once

#include <ArduinoJson/Variant/SlotFunctions.hpp>
#include <ArduinoJson/Variant/VariantRef.hpp>

namespace ARDUINOJSON_NAMESPACE {

class VariantPtr {
 public:
  VariantPtr(MemoryPool* pool, VariantData* data) : _variant(pool, data) {}

  VariantRef* operator->() {
    return &_variant;
  }

  VariantRef& operator*() {
    return _variant;
  }

 private:
  VariantRef _variant;
};

class ArrayIterator {
  friend class JsonArray;

 public:
  ArrayIterator() : _slot(0) {}
  explicit ArrayIterator(MemoryPool* pool, VariantSlot* slot)
      : _pool(pool), _slot(slot) {}

  VariantRef operator*() const {
    return VariantRef(_pool, _slot->data());
  }
  VariantPtr operator->() {
    return VariantPtr(_pool, _slot->data());
  }

  bool operator==(const ArrayIterator& other) const {
    return _slot == other._slot;
  }

  bool operator!=(const ArrayIterator& other) const {
    return _slot != other._slot;
  }

  ArrayIterator& operator++() {
    _slot = _slot->next();
    return *this;
  }

  ArrayIterator& operator+=(size_t distance) {
    _slot = _slot->next(distance);
    return *this;
  }

 private:
  MemoryPool* _pool;
  VariantSlot* _slot;
};

class VariantConstPtr {
 public:
  VariantConstPtr(const VariantData* data) : _variant(data) {}

  VariantConstRef* operator->() {
    return &_variant;
  }

  VariantConstRef& operator*() {
    return _variant;
  }

 private:
  VariantConstRef _variant;
};

class JsonArrayConstIterator {
  friend class JsonArray;

 public:
  JsonArrayConstIterator() : _slot(0) {}
  explicit JsonArrayConstIterator(const VariantSlot* slot) : _slot(slot) {}

  VariantConstRef operator*() const {
    return VariantConstRef(_slot->data());
  }
  VariantConstPtr operator->() {
    return VariantConstPtr(_slot->data());
  }

  bool operator==(const JsonArrayConstIterator& other) const {
    return _slot == other._slot;
  }

  bool operator!=(const JsonArrayConstIterator& other) const {
    return _slot != other._slot;
  }

  JsonArrayConstIterator& operator++() {
    _slot = _slot->next();
    return *this;
  }

  JsonArrayConstIterator& operator+=(size_t distance) {
    _slot = _slot->next(distance);
    return *this;
  }

 private:
  const VariantSlot* _slot;
};
}  // namespace ARDUINOJSON_NAMESPACE
