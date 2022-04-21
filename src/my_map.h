#ifndef MY_MAP_H
#define MY_MAP_H

#include <iostream>
#include <string>
#include <memory>
#include "my_vector.h"

namespace s21 {
template<typename Key, typename T>
class Map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair<key_type, mapped_type> value_type;
  typedef value_type &reference;
  typedef size_t size_type;

 public:
  class MapIterator {
   public:

    MapIterator() {}

    MapIterator(const MapIterator &other) {
      pointer = other.pointer;
      position = other.position;
    }

    void SetIterator(std::shared_ptr<value_type[]> newPointer) {pointer = newPointer;}

    value_type& operator*() {return pointer[position];}

    void operator++() {position += 1;}

    void operator--(){position -= 1;}

    size_type GetPosition() {return position;}

    bool operator==(const MapIterator other) {return position == other.position;}

    bool operator!=(const MapIterator other) {return position != other.position;}

    bool operator>=(const MapIterator other) {return position >= other.position;}

    bool operator<=(const MapIterator other) {return position <= other.position;}

    void Advance(size_t repeat) {position += repeat;}

    void Decrease(size_t repeat) {position -= repeat;}

    void swap(MapIterator &other) {
      pointer.swap(other.pointer);
      std::swap(position, other.position);
    }

    void copy(const MapIterator other) {position = other.position;}

   private:
    std::shared_ptr<value_type[]> pointer;
    size_type position{};
  };

  typedef MapIterator iterator;
  typedef std::pair<iterator, bool> isInserted;
  typedef std::pair<size_type, bool> isFound;

  Map() {
    EndIterator.SetIterator(Store);
    BeginIterator.SetIterator(Store);
  }

  Map(std::initializer_list<value_type> const &items) {
    Store.reset(new value_type [MapMaxSize]{});
    BeginIterator.SetIterator(Store);
    EndIterator.SetIterator(Store);
    for (auto iter{items.begin()}; iter != items.end(); iter++) {
      insert(*iter);
    }
  }

  Map(const Map &other) {
    MapSize = other.MapSize;
    MapMaxSize = other.MapMaxSize;
    Store.reset(new value_type [MapMaxSize]{});
    for (int i{0}; i < MapSize; i++) {
      Store[i] = other.Store[i];
    }
    BeginIterator.SetIterator(Store);
    BeginIterator.copy(other.BeginIterator);
    EndIterator.SetIterator(Store);
    EndIterator.copy(other.EndIterator);
  }

  Map(Map &&other) {swap(other);}

  void operator=(Map &&other);

  isInserted insert(const value_type& value);

  isInserted insert(const Key& key, const T& obj);

  isInserted insert_or_assign(const value_type& value);

  void clear();

  void erase(iterator position);

  void swap(Map& other);

  void merge(Map& other);

  bool empty() {return MapSize == 0;}

  size_type size() {return MapSize;}

  size_type max_size() {return MapMaxSize;}

  iterator begin() {return BeginIterator;}

  iterator end() {return EndIterator;}

  bool contains(const key_type& key) {return FindPosition(key).second;}

  isFound FindPosition(const key_type& key);

  mapped_type& at(const key_type& key);

  mapped_type& operator[](const key_type& key);

  void emplace_back() {}
  template <class Type, class... Args>
  Vector<std::pair<iterator, bool>> emplace_back(Type data, Args... args) {
    Vector<std::pair<iterator, bool>> res{};
    std::initializer_list<Type> List{args...};
    res.push_back(insert(data));
    for (auto iter = List.begin(); iter < List.end(); iter++) {
      res.push_back(insert(*iter));
    }
    return res;
  }

 private:
  size_type MapSize{};
  size_type MapMaxSize{};
  std::shared_ptr<value_type[]> Store{new value_type[0]};
  iterator EndIterator;
  iterator BeginIterator;

  void IncreaseStoreAllocation(const Map &old);

  void DecreaseStoreAllocation(const Map &old);

  void CheckEmptyToIncreaseIterator();

  void IncreaseSizeForInsert();

  bool InsertToEmptyCase(const value_type& value);

  void StoreReset(std::shared_ptr<value_type[]> newStore);
};

template<typename Key, typename T>
void Map<Key, T>::StoreReset(std::shared_ptr<value_type[]> newStore) {
  Store = std::move(newStore);
  EndIterator.SetIterator(Store);
  BeginIterator.SetIterator(Store);
}

template<typename Key, typename T>
bool Map<Key, T>::InsertToEmptyCase(const value_type& value) {
  bool inserted{false};
  if (empty()) {
    MapSize += 1;
    if (MapSize >= MapMaxSize) {
      MapMaxSize += 1;
    }
    IncreaseStoreAllocation(*this);
    Store[0] = value;
    inserted = true;
  }
  return inserted;
}

template<typename Key, typename T>
void Map<Key, T>::IncreaseSizeForInsert() {
      MapSize += 1;
      if (MapSize >= MapMaxSize) {
        MapMaxSize += 1;
      }
}

template<typename Key, typename T>
void Map<Key, T>::DecreaseStoreAllocation(const Map &old) {
      std::shared_ptr<value_type []> store{new value_type [MapMaxSize]{}};
      for (size_t i{0}; i < MapSize; i++) {
        store[i] = old.Store[i];
      }
      Store = std::move(store);
}

    template<typename Key, typename T>
void Map<Key, T>::IncreaseStoreAllocation(const Map &old) {
      std::shared_ptr<value_type []> store{new value_type [MapMaxSize]{}};
      for (size_t i{0}; i < MapSize; i++) {
        store[i] = old.Store[i];
      }
      Store = std::move(store);
      BeginIterator.SetIterator(Store);
      EndIterator.SetIterator(Store);
}

    template<typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
      MapIterator left(other.begin()), right(other.end());
      while (left <= right) {
        insert(*left);
        ++left;
      }
      other.clear();
}

    template<typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
      Store.swap(other.Store);
      std::swap(MapSize, other.MapSize);
      std::swap(MapMaxSize, other.MapMaxSize);
      BeginIterator.swap(other.BeginIterator);
      EndIterator.swap(other.EndIterator);
    }

    template<typename Key, typename T>
void Map<Key, T>::erase(iterator position) {
      *position = std::make_pair(0, 0);
      --EndIterator;
      for (size_t i{0}, j{0}; i < MapSize; i++, j++) {
        if (i == position.GetPosition()) {
          j++;
        }
        Store[i] = Store[j];
      }
      MapSize -= 1;
    }

    template<typename Key, typename T>
void Map<Key, T>::clear() {
      while (MapSize != 0) {
        *EndIterator = std::make_pair(0, 0);;
        --EndIterator;
        MapSize--;
      }
      Store.reset(new value_type[0]{});
      MapMaxSize = 0;
      EndIterator.SetIterator(Store);
      BeginIterator.SetIterator(Store);
    }

    template<typename Key, typename T>
void Map<Key, T>::operator=(Map &&other ) {
      MapSize = other.MapSize;
      MapMaxSize = other.MapMaxSize;
      Store.reset(new value_type [MapMaxSize]{});
      for (int i{0}; i < MapSize; i++) {
        Store[i] = other.Store[i];
      }
      BeginIterator.SetIterator(Store);
      BeginIterator.copy(other.BeginIterator);
      EndIterator.SetIterator(Store);
      EndIterator.copy(other.EndIterator);
    }

template<typename Key, typename T>
void Map<Key, T>::CheckEmptyToIncreaseIterator() {
  if (!empty()) {
    ++EndIterator;
  }
}

template<typename Key, typename T>
typename Map<Key, T>::isInserted Map<Key, T>:: insert(const value_type& value) {
  iterator positionIterator;
  bool inserted = InsertToEmptyCase(value);
  positionIterator.SetIterator(Store);
  if (!inserted) {
    inserted = contains(value.first);
  }
  if (!inserted) {
    size_type insertedPosition{};
    IncreaseSizeForInsert();
    std::shared_ptr < value_type[] > newStore{new value_type[MapMaxSize]};
    for (size_type i{0}, j{0}; i < MapSize - 1; i++, j++) {
      if (!inserted && value.first < Store[i].first) {
        newStore[j] = value;
        inserted = true;
        ++EndIterator;
        insertedPosition = j;
        j++;
      }
      newStore[j] = Store[i];
    }
    if (!inserted) {
      newStore[MapSize - 1] = value;
      insertedPosition += 1;
      ++EndIterator;
      inserted = true;
    }
    StoreReset(newStore);
    positionIterator.SetIterator(Store);
    positionIterator.Advance(insertedPosition);
  }
  isInserted result = std::make_pair(positionIterator, inserted);
  return result;
}

template<typename Key, typename T>
typename Map<Key, T>::isInserted Map<Key, T>::insert(const Key& key, const T& obj) {
  isInserted result = insert(std::make_pair(key, obj));
  return result;
}

template<typename Key, typename T>
typename Map<Key, T>::isInserted Map<Key, T>::insert_or_assign(const value_type& value) {
  isInserted result;
  isFound found = FindPosition(value.first);
  if (found.second) {
    Store[found.first].second = value.second;
    iterator positionIterator;
    positionIterator.SetIterator(Store);
    positionIterator.Advance(found.first);
    result = std::make_pair(positionIterator, true);
  } else {
    result = insert(value);
  }
  return result;
}

template<typename Key, typename T>
typename Map<Key, T>::isFound Map<Key, T>::FindPosition(const key_type& key) {
  bool found{false};
  int left{}, right = EndIterator.GetPosition(), middle{0};
  while (left <= right && !found) {
    middle = left + (right - left) / 2;
    if (Store[middle].first == key) {
      found = true;
    } else if (Store[middle].first < key) {
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }
  return std::make_pair(middle, found);
}

template<typename Key, typename T>
typename Map<Key, T>::mapped_type& Map<Key, T>::at(const key_type& key) {
  isFound result = FindPosition(key);
  if (!result.second) {
    throw std::out_of_range("Не туда воююешь");
  }
  return Store[result.first].second;
}

template<typename Key, typename T>
typename Map<Key, T>::mapped_type& Map<Key, T>::operator[](const key_type& key) {
  isFound result = FindPosition(key);
  return Store[result.first].second;
}


}

#endif // MY_MAP_H
