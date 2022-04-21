#include <gtest/gtest.h>
#include <set>

#include "my_containers.h"
#include "my_containersplus.h"

using namespace s21;

TEST(Array, default_construct) {
  Array<int, 0> myArr;
  ASSERT_EQ(myArr.size(), 0);
}

TEST(Array, eq_and_not_eq) {
  Array<int, 4> myArr = {1, 2, 3, 4};
  Array<int, 4>::ArrayIterator iter = myArr.begin(), other = myArr.begin();
  ASSERT_EQ(true, other == iter);
  ASSERT_EQ(false, other != iter);
}

TEST(Array, initializer_list_construct) {
  Array<int, 4> myArr = {1, 2, 3, 4};
  ASSERT_EQ(myArr.size(), 4);

  Array<int, 4>::ArrayIterator iter = myArr.begin();
  ASSERT_EQ(1, *iter);
  ASSERT_EQ(2, *(++iter));
  ASSERT_EQ(3, *(++iter));
  ASSERT_EQ(4, *(++iter));
}
TEST(Array, copy_construct) {
  Array<int, 4> myArr = {1, 2, 3, 4};
  Array<int, 4> other = myArr;
  ASSERT_EQ(other[0], 1);
  ASSERT_EQ(other[1], 2);
  ASSERT_EQ(other[2], 3);
  ASSERT_EQ(other[3], 4);
}

TEST(Array, move_construct_and_equating) {
  Array<int, 4> myArr = {1, 2, 3, 4};
  Array<int, 4> move = std::move(myArr);
  Array<int, 4>::ArrayIterator iter = move.begin();
  ASSERT_EQ(true, myArr.empty());
  ASSERT_EQ(1, *iter);
  ASSERT_EQ(2, *(++iter));
  ASSERT_EQ(3, *(++iter));
  ASSERT_EQ(4, *(++iter));

  Array<int, 4> move1;
  move1 = std::move(move);
  iter = move1.begin();
  ASSERT_EQ(true, move.empty());
  ASSERT_EQ(1, *iter);
  ASSERT_EQ(2, *(++iter));
  ASSERT_EQ(3, *(++iter));
  ASSERT_EQ(4, *(++iter));
}

TEST(Array, front_back) {
  Array<int, 4> myArr = {1, 2, 3, 4};
  ASSERT_EQ(1, myArr.front());
  ASSERT_EQ(4, myArr.back());
}

TEST(Array, at) {
  Array<int, 4> myArr = {1, 2, 3, 4};
  ASSERT_EQ(1, myArr.at(0));
  ASSERT_EQ(2, myArr.at(1));
  ASSERT_EQ(3, myArr.at(2));
  ASSERT_EQ(4, myArr.at(3));
}

TEST(Array, fill) {
  Array<double, 5> myArr;
  myArr.fill(0.5);
  Array<double, 5>::ArrayIterator iter = myArr.begin();
  ASSERT_EQ(0.5, *iter);
  ASSERT_EQ(0.5, *(++iter));
  ASSERT_EQ(0.5, *(++iter));
  ASSERT_EQ(0.5, *(++iter));
  ASSERT_EQ(0.5, *(++iter));
}

TEST(Array, swap) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5> arr10 = {10, 20, 30, 40, 50, 60};
  arr1.swap(arr10);
  Array<int, 5>::ArrayIterator iter1 = arr10.begin(), iter10 = arr1.begin();
  ASSERT_EQ(1, *iter1);
  ASSERT_EQ(2, *(++iter1));
  ASSERT_EQ(3, *(++iter1));
  ASSERT_EQ(4, *(++iter1));
  ASSERT_EQ(5, *(++iter1));
  ASSERT_EQ(10, *iter10);
  ASSERT_EQ(20, *(++iter10));
  ASSERT_EQ(30, *(++iter10));
  ASSERT_EQ(40, *(++iter10));
  ASSERT_EQ(50, *(++iter10));
}

TEST(Array_iters, plus_plus) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5>::ArrayIterator iter = arr1.begin();
  ASSERT_EQ(1, *iter);
  ASSERT_EQ(2, *(iter++));
  ASSERT_EQ(3, *(++iter));
}

TEST(Array_iters, plus) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5>::ArrayIterator iter = arr1.begin();
  iter = iter + 1;
  ASSERT_EQ(2, *iter);
  iter = iter + 2;
  ASSERT_EQ(4, *iter);
}

TEST(Array, operator_minusminus) {
  Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  Array<int, 5>::ArrayIterator iter = arr1.end();
  iter--;
  ASSERT_EQ(5, *iter);
  --iter;
  ASSERT_EQ(4, *iter);
}

TEST(List, simple_constructor) {
  List<double> empty;
  ASSERT_EQ(true, empty.empty());
}

TEST(List, push) {
  List<double> test1;
  test1.push_back(0.5);
  ASSERT_EQ(0.5, test1.front());
  test1.push_back(0.7);
  ASSERT_EQ(0.7, test1.back());
  test1.push_front(0.1);
  ASSERT_EQ(0.1, test1.front());
}

TEST(List, iterators_construct) {
  List<char> symbols = {'a', 'b', 'c', 'd'};
  List<char>::ListIterator iter = symbols.begin();
  ASSERT_EQ('a', *iter);
  iter = symbols.end();
  --iter;
  ASSERT_EQ('d', *iter);
}

TEST(List, iterator_list_loop_plus) {
  List<char> symbols = {'a', 'b', 'c', 'd'};
  List<char>::ListIterator iter = symbols.begin();
  ASSERT_EQ('a', *iter);
  ASSERT_EQ('b', *(++iter));
  ASSERT_EQ('c', *(++iter));
  ASSERT_EQ('d', *(++iter));
  ASSERT_EQ(true, (++iter) == symbols.end());
}
TEST(List, iterator_list_loop_minus) {
  List<char> symbols = {'a', 'b', 'c', 'd'};
  List<char>::ListIterator iter = symbols.end();
  ASSERT_EQ('d', *(--iter));
  ASSERT_EQ('c', *(--iter));
  ASSERT_EQ('b', *(--iter));
  ASSERT_EQ('a', *(--iter));
  ASSERT_EQ(true, iter == symbols.begin());
}

TEST(List, constructors) {
  List<char> symbols = {'1', '2', '3', '4'};
  List<char>::ListIterator charIter = symbols.begin();
  ASSERT_EQ('1', *charIter);
  ASSERT_EQ('2', *(++charIter));
  ASSERT_EQ('3', *(++charIter));
  ASSERT_EQ('4', *(++charIter));
  List<char> symbols_copy(symbols);
  List<char>::ListIterator charIter1 = symbols_copy.begin();
  ASSERT_EQ('1', *charIter1);
  ASSERT_EQ('2', *(++charIter1));
  ASSERT_EQ('3', *(++charIter1));
  ASSERT_EQ('4', *(++charIter1));
  List<char> symbols_move = std::move(symbols_copy);
  List<char>::ListIterator charIter2 = symbols_move.begin();
  ASSERT_EQ('1', *charIter2);
  ASSERT_EQ('2', *(++charIter2));
  ASSERT_EQ('3', *(++charIter2));
  ASSERT_EQ('4', *(++charIter2));
  ASSERT_EQ(true, symbols_copy.empty());
  List<int> constrWithSize(5);
  ASSERT_EQ(5, constrWithSize.size());
}

TEST(List, insert) {
  List<char> symbols = {'a', 'b', 'c', 'd'};
  List<char>::ListIterator iter = symbols.begin();
  List<char>::ListIterator iter1 = symbols.insert(iter, 'n');
  ASSERT_EQ('n', *(symbols.begin()));
  ASSERT_EQ('n', symbols.front());
  ASSERT_EQ('n', *iter1);

  iter = iter + 3;
  iter1 = symbols.insert(iter, 'l');

  ASSERT_EQ('l', *iter1);
}

TEST(List, erase) {
  List<char> symbols = {'a', 'b', 'c', 'd'};
  List<char>::ListIterator iter = symbols.begin();
  symbols.erase(iter);
  ASSERT_EQ('b', symbols.front());
  ASSERT_EQ(3, symbols.size());
  iter = symbols.begin();

  symbols.erase(iter + 1);
  ASSERT_EQ('b', *(iter));
  ASSERT_EQ('d', *(iter + 1));
  ASSERT_EQ(2, symbols.size());
  symbols.erase(symbols.begin());
  symbols.erase(symbols.begin());
  ASSERT_EQ(0, symbols.size());
}

TEST(List, pop) {
  List<char> numbers = {'-', '0', '1', '2', '3', '4', '5', '6', '7'};
  numbers.pop_back();
  ASSERT_EQ('6', numbers.back());
  numbers.pop_back();
  ASSERT_EQ('5', numbers.back());
  List<char>::ListIterator k = numbers.end();
  --k;
  numbers.pop_front();
  ASSERT_EQ('0', numbers.front());
  ASSERT_EQ('5', *k);
}

TEST(List, merge) {
  List<int> elems1 = {1, 2, 3, 4};
  List<int> elems2 = {5, 6, 7, 8};
  elems1.merge(elems2);
  List<int>::ListIterator iter = elems1.begin(), end = elems1.end();
  int sum = 0;
  for (; iter != end; ++iter) {
    sum += *iter;
  }
  ASSERT_EQ(36, sum);
}

TEST(List, reverse) {
  List<int> normal = {1, 2, 3, 4, 5};
  List<int> reverse = {5, 4, 3, 2, 1};
  normal.reverse();
  List<int>::ListIterator iter = normal.begin(), iterCheck = reverse.begin();
  List<int>::ListIterator end = reverse.end();
  for (; iterCheck != end; ++iterCheck, ++iter) {
    ASSERT_EQ(*iter, *iterCheck);
  }
}

TEST(List, unique1) {
  List<int> myList = {1, 1, 1, 1, 1, 1};
  myList.unique();
  List<int>::ListIterator iter = myList.begin();
  ASSERT_EQ(*iter, 1);
  ASSERT_EQ(myList.size(), 1);
}

TEST(List, unique2) {
  List<int> myList = {1, 1, 2, 2, 3, 3, 4, 4};
  myList.unique();
  List<int>::ListIterator iter = myList.begin();
  ASSERT_EQ(*iter, 1);
  ASSERT_EQ(*(++iter), 2);
  ASSERT_EQ(*(++iter), 3);
  ASSERT_EQ(*(++iter), 4);
  ASSERT_EQ(myList.size(), 4);
}

TEST(List, splice) {
  List<int> myList = {1, 2, 3};
  List<int> otherList = {4, 5, 6};
  List<int>::ListIterator iter = myList.begin();
  myList.splice(iter, otherList);
  iter = myList.begin();
  ASSERT_EQ(*iter, 4);
  ASSERT_EQ(*(++iter), 5);
  ASSERT_EQ(*(++iter), 6);
  ASSERT_EQ(*(++iter), 1);
  ASSERT_EQ(*(++iter), 2);
  ASSERT_EQ(*(++iter), 3);
  ASSERT_EQ(myList.size(), 6);
}

TEST(List, emplace) {
  List<int> myList = {1, 2, 3};
  List<int> checkList = {1, 4, 5, 6, 2, 3};
  List<int>::ListIterator iter = myList.begin(), end = myList.end(),
                          iterCheck = checkList.begin();
  myList.emplace(iter + 1, 4, 5, 6);
  for (; iter != end; iter++, iterCheck++) {
    ASSERT_EQ(*iter, *iterCheck);
  }
}

TEST(List, emplace_back) {
  List<int> myList = {1, 2, 3};
  List<int> checkList = {1, 2, 3, 4, 5, 6};
  List<int>::ListIterator iter = myList.begin(), end,
                          iterCheck = checkList.begin();
  myList.emplace_back(4, 5, 6);
  end = myList.end();
  for (; iter != end; iter++, iterCheck++) {
    ASSERT_EQ(*iter, *iterCheck);
  }
}

TEST(List, emplace_front) {
  List<int> myList = {1, 2, 3};
  List<int> checkList = {4, 5, 6, 1, 2, 3};
  List<int>::ListIterator iter = myList.begin(), end,
                          iterCheck = checkList.begin();
  myList.emplace_front(4, 5, 6);
  end = myList.end();
  iter = myList.begin();
  for (; iter != end; iter++, iterCheck++) {
    ASSERT_EQ(*iter, *iterCheck);
  }
}

TEST(List, operator_minus) {
  List<int> myList = {1, 2, 3};
  List<int>::ListIterator iter = myList.end();
  iter = iter - 1;
  ASSERT_EQ(*iter, 3);
}

TEST(Map, basic) {
  Map<int, int> Kala;

//  Emptiness check

ASSERT_EQ(Kala.size(), 0);
ASSERT_EQ(Kala.max_size(), 0);
ASSERT_TRUE(Kala.empty());

//  Pairs initialization
auto pair_1 = std::make_pair(15, 6);
auto pair_2 = std::make_pair(1, 2);
auto pair_3 = std::make_pair(6, 546);
auto pair_4 = std::make_pair(32, 1);
auto pair_5 = std::make_pair(2, 5);
auto pair_6 = std::make_pair(14, 8);
auto pair_7 = std::make_pair(3, 93);
auto pair_8 = std::make_pair(16, 7);

//  Insert check

auto insert_iter_pair = Kala.insert(pair_1);

Map<int, int>::iterator iter;
iter = Kala.end();
auto check_pair = *iter;
ASSERT_EQ(check_pair.first, 15);
ASSERT_EQ(check_pair.second, 6);
ASSERT_EQ(pair_1, *insert_iter_pair.first);

Kala.insert(pair_2);

iter = Kala.end();
check_pair = *iter;
ASSERT_EQ(check_pair.first, 15);
ASSERT_EQ(check_pair.second, 6);

iter = Kala.begin();
check_pair = *iter;
ASSERT_EQ(check_pair.first, 1);
ASSERT_EQ(check_pair.second, 2);

iter = Kala.insert(pair_3).first;

check_pair = *iter;
ASSERT_EQ(check_pair.first, 6);
ASSERT_EQ(check_pair.second, 546);

--iter;
check_pair = *iter;
ASSERT_EQ(check_pair.first, 1);
ASSERT_EQ(check_pair.second, 2);

ASSERT_TRUE(Kala.contains(1));

//  Copy constructor check

Map<int, int> KalaCopied(Kala);

iter = KalaCopied.begin();
check_pair = *iter;
ASSERT_EQ(check_pair.first, 1);
ASSERT_EQ(check_pair.second, 2);

++iter;
check_pair = *iter;
ASSERT_EQ(check_pair.first, 6);
ASSERT_EQ(check_pair.second, 546);

++iter;
check_pair = *iter;
ASSERT_EQ(check_pair.first, 15);
ASSERT_EQ(check_pair.second, 6);

ASSERT_TRUE(KalaCopied.contains(6));

--iter;
check_pair = *iter;

KalaCopied.erase(iter);

ASSERT_FALSE(KalaCopied.contains(6));


//  Initialize constructor check

Map<int, int> KalaSorted = {pair_2, pair_5, pair_7, pair_3, pair_6, pair_1, pair_8, pair_4};

ASSERT_EQ(KalaSorted.size(), 8);
ASSERT_EQ(KalaSorted.max_size(), 8);

Map<int, int>::iterator sortIterB(KalaSorted.begin());
Map<int, int>::iterator sortIterE(KalaSorted.end());

bool sorted{true};
auto tmp_pair = *sortIterB;


while (sortIterB <= sortIterE && sorted) {
  check_pair = *sortIterB;
  if (check_pair.first < tmp_pair.first) {
    sorted = false;
  }
  tmp_pair = check_pair;
  ++sortIterB;
}

ASSERT_TRUE(sorted);

KalaSorted.clear();

ASSERT_EQ(KalaSorted.size(), 0);
ASSERT_EQ(KalaSorted.max_size(), 0);
ASSERT_TRUE(KalaSorted.empty());

Map<int, int> KalaInit = {pair_1, pair_2, pair_3, pair_4, pair_5, pair_6, pair_7, pair_8};

ASSERT_EQ(KalaInit.size(), 8);
ASSERT_EQ(KalaInit.max_size(), 8);

Map<int, int>::iterator sortItersB(KalaInit.begin());
Map<int, int>::iterator sortItersE(KalaInit.end());

sorted = true;
tmp_pair = *sortItersB;

while (sortItersB <= sortItersE && sorted) {
  check_pair = *sortItersB;
  if (check_pair.first < tmp_pair.first) {
    sorted = false;
  }
  tmp_pair = check_pair;
  ++sortItersB;
}

ASSERT_TRUE(sorted);

ASSERT_EQ(KalaInit.at(1), 2);

KalaInit.insert_or_assign(std::make_pair(1, 6));

ASSERT_EQ(KalaInit.at(1), 6);

pair_1 = std::make_pair(102, 6);
pair_2 = std::make_pair(23, 2);
pair_3 = std::make_pair(76, 546);
pair_4 = std::make_pair(50, 1);
pair_5 = std::make_pair(150, 5);

Map<int, int> KalaToMerge = {pair_1, pair_2, pair_3, pair_4, pair_5};

KalaInit.merge(KalaToMerge);

ASSERT_EQ(KalaInit.size(), 13);
ASSERT_EQ(KalaInit.max_size(), 13);

ASSERT_TRUE(KalaSorted.empty());

Vector<std::pair<Map<int, int>::MapIterator, bool>> Kod(KalaSorted.emplace_back(pair_2, pair_1, pair_3));

auto iterMap = KalaSorted.begin();
auto iterVector = Kod.begin();
auto iter_iter = *iterVector;

ASSERT_EQ(pair_2, *iterMap);
ASSERT_EQ(*iterMap, *iter_iter.first);

++iterMap;
++iterVector;
++iterVector;

iter_iter = *iterVector;

ASSERT_EQ(pair_3, *iterMap);
ASSERT_EQ(*iterMap, *iter_iter.first);

++iterMap;
--iterVector;

iter_iter = *iterVector;

ASSERT_EQ(pair_1, *iterMap);
ASSERT_EQ(*iterMap, *iter_iter.first);
}

TEST(Queue, basic) {
Queue<int> Kala;
int k = 5;

//  empty and size test

ASSERT_EQ(true, Kala.empty());
ASSERT_EQ(0, Kala.size());

//  push and top test

Kala.push(k);
ASSERT_EQ(k, Kala.back());
k = 6;
Kala.push(k);
ASSERT_EQ(k, Kala.back());

Kala.back() = 11;
ASSERT_EQ(11, Kala.back());

int& c = Kala.back();
c = 3;

ASSERT_EQ(c, Kala.back());

ASSERT_EQ(5, Kala.front());

Kala.front() = 11;
ASSERT_EQ(11, Kala.front());

int& d = Kala.front();
d = 4;

ASSERT_EQ(d, Kala.front());

//  pop test
ASSERT_EQ(3, Kala.back());
Kala.pop();
ASSERT_EQ(3, Kala.front());
ASSERT_EQ(3, Kala.back());


//  memory test allocation test

k = 4;

Kala.push(k);
Kala.push(k);
Kala.push(k);
Kala.push(k);
Kala.push(k);
Kala.push(k);



//  empty and size test

ASSERT_EQ(false, Kala.empty());
ASSERT_EQ(7, Kala.size());

//  swap test
Queue<int> Kala1;
Kala1.swap(Kala);

ASSERT_EQ(false, Kala1.empty());
ASSERT_EQ(7, Kala1.size());
ASSERT_EQ(4, Kala1.back());

ASSERT_EQ(true, Kala.empty());
ASSERT_EQ(0, Kala.size());

//  move constructor test

Queue<int> Kala2(std::move(Kala1));

ASSERT_EQ(false, Kala2.empty());
ASSERT_EQ(7, Kala2.size());
ASSERT_EQ(4, Kala2.back());

ASSERT_EQ(true, Kala1.empty());
ASSERT_EQ(0, Kala1.size());

//  copy constructor test

Queue<int> Kala4(Kala2);

ASSERT_EQ(false, Kala4.empty());
ASSERT_EQ(7, Kala4.size());
ASSERT_EQ(4, Kala4.back());

//  initialize constructor test

Queue<int> KalaInit = {1, 2, 4, 5};
ASSERT_EQ(false, KalaInit.empty());
ASSERT_EQ(4, KalaInit.size());
ASSERT_EQ(5, KalaInit.back());
ASSERT_EQ(1, KalaInit.front());

Queue<int> KalaBad = {};
ASSERT_EQ(true, KalaBad.empty());
ASSERT_EQ(0, KalaBad.size());

//  emplace methods

KalaBad.emplace_back(6, 4, 3, 2);

ASSERT_EQ(2, KalaBad.back());
ASSERT_EQ(6, KalaBad.front());


//  Operator = test

Queue<int> Moved(std::move(KalaInit));

ASSERT_EQ(false, Moved.empty());
ASSERT_EQ(4, Moved.size());
ASSERT_EQ(5, Moved.back());
ASSERT_EQ(1, Moved.front());

}

TEST(Test, IterBegin) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 15, 14};
  s21::set<int> mySet(list);
  std::set<int> origSet(list);
  s21::set<int>::iterator myIter;
  std::set<int>::iterator origIter;
  myIter = mySet.begin();
  origIter = origSet.begin();
  ASSERT_EQ(*myIter, *origIter);
}

TEST(Test, FromBeginToEnd) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  s21::set<int> mySet(list);
  std::set<int> origSet(list);
  auto iter1 = mySet.begin();
  auto iter2 = origSet.begin();
  while (iter1 != mySet.end() && iter2 != origSet.end()) {
    ASSERT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, string) {
  std::initializer_list<std::string> list{"2321",   "fgdgf",          "a",
                                          "dfdsf4", "d2ueu3eg32e3d2", "......"};
  s21::set<std::string> mySet(list);
  std::set<std::string> origSet(list);
  auto iter1 = mySet.begin();
  auto iter2 = origSet.begin();
  while (iter1 != mySet.end() && iter2 != origSet.end()) {
    EXPECT_TRUE(*iter1 == *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, insert) {
  std::initializer_list<double> list{11.3, -4.1, 3231.2, 2.33, 0.9,
                                     1.10, 2.5,  7.25,   6.3,  8.0,
                                     -132, 12.3, 13.4,   -5.15};
  s21::set<double> mySet(list);
  std::set<double> origSet(list);
  auto iter1 = mySet.begin();
  auto iter2 = origSet.begin();
  mySet.insert(666.777);
  origSet.insert(666.777);
  while (iter1 != mySet.end() && iter2 != origSet.end()) {
    ASSERT_DOUBLE_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, erase) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  s21::set<int> mySet(list);
  std::set<int> origSet(list);
  auto iter1 = mySet.begin();
  auto iter2 = origSet.begin();
  auto rmIter1 = mySet.begin();
  auto rmIter2 = origSet.begin();
  ++rmIter1;
  ++rmIter2;
  mySet.erase(rmIter1);
  origSet.erase(rmIter2);
  while (iter1 != mySet.end() && iter2 != origSet.end()) {
    ASSERT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, erase2) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  s21::set<int> mySet(list);
  std::set<int> origSet(list);
  auto iter1 = mySet.begin();
  auto rmIter1 = mySet.begin();
  auto rmIter2 = origSet.begin();
  ++rmIter1;
  ++rmIter2;
  mySet.erase(rmIter1);
  origSet.erase(rmIter2);
  auto rmIter11 = mySet.begin();
  auto rmIter22 = origSet.begin();
  mySet.erase(rmIter11);
  origSet.erase(rmIter22);
  iter1 = mySet.begin();
  auto iter22 = origSet.begin();
  while (iter1 != mySet.end() && iter22 != origSet.end()) {
    ASSERT_EQ(*iter1, *iter22);
    ++iter1;
    ++iter22;
  }
}

TEST(Test, emptyTrue) {
  std::set<char> oSet;
  s21::set<char> mSet;
  EXPECT_TRUE(oSet.empty());
  EXPECT_TRUE(mSet.empty());
}

TEST(Test, emptyFlase) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  std::set<int> oSet(list);
  s21::set<int> mSet(list);
  EXPECT_FALSE(oSet.empty());
  EXPECT_FALSE(mSet.empty());
}

TEST(Test, clear) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  std::set<int> oSet(list);
  s21::set<int> mSet(list);
  oSet.clear();
  mSet.clear();
  EXPECT_TRUE(oSet.empty());
  EXPECT_TRUE(mSet.empty());
  oSet.clear();
  mSet.clear();
  EXPECT_TRUE(oSet.empty());
  EXPECT_TRUE(mSet.empty());
}

TEST(Test, swap) {
  std::initializer_list<long double> list{11.3, -4.1, 3231.2, 2.33, 0.9,
                                          1.10, 2.5,  7.25,   6.3,  8.0,
                                          -132, 12.3, 13.4,   -5.15};
  std::set<long double> oSet1(list);
  std::set<long double> oSet2;
  s21::set<long double> mSet1(list);
  s21::set<long double> mSet2;
  oSet1.swap(oSet2);
  mSet1.swap(mSet2);
  EXPECT_TRUE(oSet1.empty());
  EXPECT_FALSE(oSet2.empty());
  EXPECT_TRUE(mSet1.empty());
  EXPECT_FALSE(mSet2.empty());
}

// Если компилить с 20 стандартом
TEST(Test, merge1) {
  std::initializer_list<int> list1{11, 4, 2, 3,  9,  10, 5,
                                   7,  6, 8, 13, 12, 14, 15};
  std::initializer_list<int> list2{-4, -5, 28, 39};
  std::set<int> oSet1(list1);
  std::set<int> oSet2(list2);
  oSet1.merge(oSet2);
  s21::set<int> mSet1(list1);
  s21::set<int> mSet2(list2);
  mSet1.merge(mSet2);
  std::set<int>::iterator oIt = oSet1.begin();
  s21::set<int>::iterator mIt = mSet1.begin();
  while (oIt != oSet1.end() && mIt != mSet1.end()) {
    ASSERT_EQ(*oIt, *mIt);
    ++oIt;
    ++mIt;
  }
  EXPECT_TRUE(oSet2.empty() && mSet2.empty());
}

TEST(Test, merge2) {
  std::set<int> oSet;
  s21::set<int> mSet;
  oSet.merge(oSet);
  mSet.merge(mSet);
  EXPECT_TRUE(oSet.empty() && mSet.empty());
}

TEST(Test, find1) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  std::set<int> oSet(list);
  s21::set<int> mSet(list);
  std::set<int>::iterator oIter = oSet.find(13);
  s21::set<int>::iterator mIter = mSet.find(13);
  ASSERT_EQ(*oIter, *mIter);
  ++oIter;
  ++mIter;
  ASSERT_EQ(*oIter, *mIter);
}

TEST(Test, find2) {
  s21::set<char> Set;
  s21::set<char>::iterator it;
  it = Set.find('f');
  EXPECT_TRUE(it == Set.end());
}

TEST(Test, contains1) {
  s21::set<char> Set;
  EXPECT_FALSE(Set.contains('f'));
}

TEST(Test, contains2) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  s21::set<int> Set(list);
  EXPECT_TRUE(Set.contains(10));
  EXPECT_TRUE(Set.contains(13));
  EXPECT_TRUE(Set.contains(12));
  EXPECT_FALSE(Set.contains(-7));
}

TEST(Test, size1) {
  std::initializer_list<int> list{6,        9,      -2,     43,
                                  21432432, 234324, 412342, 12321};
  s21::set<int> mSet(list);
  std::set<int> oSet(list);
  ASSERT_EQ(mSet.size(), oSet.size());
}

TEST(Test, size2) {
  std::set<int> oSet;
  s21::set<int> mSet;
  ASSERT_EQ(oSet.size(), mSet.size());
}

TEST(Test, move_constructor) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  std::set<int> oSet1(list);
  std::set<int> oSet2(std::move(oSet1));
  s21::set<int> mSet1(list);
  s21::set<int> mSet2(std::move(mSet1));
  EXPECT_TRUE(oSet1.empty() == mSet1.empty());
  EXPECT_TRUE(oSet2.empty() == mSet2.empty());
}

TEST(Test, copy_constructor) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  s21::set<int> mSet1(list);
  s21::set<int> mSet2(mSet1);
  s21::set<int>::iterator it1 = mSet1.begin();
  s21::set<int>::iterator it2 = mSet2.begin();
  while (it1 != mSet1.end() || it2 != mSet2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, move_operator) {
  std::initializer_list<int> list{11, 4, 2, 3,  9,  10, 5,
                                  7,  6, 8, 13, 12, 14, 15};
  s21::set<int> mSet1(list);
  s21::set<int> mSet2 = std::move(mSet1);
  ASSERT_TRUE(mSet1.empty());
  ASSERT_FALSE(mSet2.empty());
}

TEST(Test, max_size) {
  s21::set<int> mSet;
  ASSERT_EQ(2305843009213693951, mSet.max_size());
}

TEST(Test, multi_fromStartToEnd) {
  s21::multiset<int> mMulti;
  std::multiset<int> oMulti;
  mMulti.insert(1);
  oMulti.insert(1);
  mMulti.insert(1);
  oMulti.insert(1);
  mMulti.insert(2);
  oMulti.insert(2);
  mMulti.insert(3);
  oMulti.insert(3);
  mMulti.insert(3);
  oMulti.insert(3);
  auto it1 = mMulti.begin();
  auto it2 = oMulti.begin();
  while (it1 != mMulti.end() && it2 != oMulti.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, multi_initlist) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti(list);
  std::multiset<int> oMulti(list);
  auto it1 = mMulti.begin();
  auto it2 = oMulti.begin();
  while (it1 != mMulti.end() && it2 != oMulti.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, multi_copy) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti1(list);
  std::multiset<int> oMulti1(list);
  s21::multiset<int> mMulti2(mMulti1);
  std::multiset<int> oMulti2(oMulti1);
  auto it1 = mMulti2.begin();
  auto it2 = oMulti2.begin();
  while (it1 != mMulti2.end() && it2 != oMulti2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, multi_move) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti1(list);
  std::multiset<int> oMulti1(list);
  s21::multiset<int> mMulti2(std::move(mMulti1));
  std::multiset<int> oMulti2(std::move(oMulti1));
  EXPECT_TRUE(mMulti1.empty());
  EXPECT_TRUE(oMulti1.empty());
  auto it1 = mMulti2.begin();
  auto it2 = oMulti2.begin();
  while (it1 != mMulti2.end() && it2 != oMulti2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, multi_eq) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti1(list);
  std::multiset<int> oMulti1(list);
  s21::multiset<int> mMulti2 = std::move(mMulti1);
  std::multiset<int> oMulti2 = std::move(oMulti1);
  EXPECT_TRUE(mMulti1.empty());
  EXPECT_TRUE(oMulti1.empty());
  auto it1 = mMulti2.begin();
  auto it2 = oMulti2.begin();
  while (it1 != mMulti2.end() && it2 != oMulti2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, size) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti2(list);
  std::multiset<int> oMulti2(list);
  auto it1 = mMulti2.begin();
  auto it2 = oMulti2.begin();
  while (it1 != mMulti2.end() && it2 != oMulti2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  ASSERT_EQ(mMulti2.size(), oMulti2.size());
}

TEST(Test, max_size_int) {
  s21::multiset<int> mMulti;
  ASSERT_EQ(2305843009213693951, mMulti.max_size());
}

TEST(Test, multi_clear) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti(list);
  mMulti.clear();
  ASSERT_TRUE(mMulti.empty());
}

TEST(Test, multi_erase) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti2(list);
  std::multiset<int> oMulti2(list);
  auto rit1 = mMulti2.begin();
  auto rit2 = oMulti2.begin();
  ++rit2;
  ++rit1;
  mMulti2.erase(rit1);
  oMulti2.erase(rit2);
  auto it1 = mMulti2.begin();
  auto it2 = oMulti2.begin();
  while (it1 != mMulti2.end() && it2 != oMulti2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  ASSERT_EQ(mMulti2.size(), oMulti2.size());
}

TEST(Test, multi_erase2) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti2(list);
  std::multiset<int> oMulti2(list);
  auto rit1 = mMulti2.begin();
  auto rit2 = oMulti2.begin();
  mMulti2.erase(rit1);
  oMulti2.erase(rit2);
  auto it1 = mMulti2.begin();
  auto it2 = oMulti2.begin();
  while (it1 != mMulti2.end() && it2 != oMulti2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  ASSERT_EQ(mMulti2.size(), oMulti2.size());
}

TEST(Test, multi_swap) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti1(list);
  s21::multiset<int> mMulti2;
  mMulti1.swap(std::move(mMulti2));
  EXPECT_TRUE(mMulti1.empty());
  EXPECT_FALSE(mMulti2.empty());
}

TEST(Test, multi_merge) {
  std::initializer_list<int> list = {1, 2, 3, 3, 4, 5, 5, 6};
  s21::multiset<int> mMulti1(list);
  s21::multiset<int> mMulti2(list);
  std::multiset<int> oMulti1(list);
  std::multiset<int> oMulti2(list);
  mMulti1.merge(mMulti2);
  oMulti1.merge(oMulti2);
  EXPECT_TRUE(oMulti2.empty());
  EXPECT_TRUE(mMulti2.empty());
  auto it1 = mMulti1.begin();
  auto it2 = oMulti1.begin();
  while (it1 != mMulti1.end() || it2 != oMulti1.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, find) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti(list);
  std::multiset<int> oMulti(list);
  auto it1 = mMulti.find(3);
  auto it2 = oMulti.find(3);
  ASSERT_EQ(*it1, *it2);
  ++it1;
  ++it2;
  ASSERT_EQ(*it1, *it2);
  while (it1 != mMulti.end() || it2 != oMulti.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, contains) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  s21::multiset<int> mMulti(list);
  EXPECT_TRUE(mMulti.contains(-3));
  EXPECT_FALSE(mMulti.contains(-10));
}

TEST(Test, count) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2, 3,  3, 5,
                                     6, -1, -1, 6, 7, 9, 22, 0, -3};
  std::multiset<int> oMulti(list);
  s21::multiset<int> mMulti(list);
  ASSERT_EQ(oMulti.count(1), mMulti.count(1));
  ASSERT_EQ(oMulti.count(2), mMulti.count(2));
  ASSERT_EQ(oMulti.count(0), mMulti.count(0));
  ASSERT_EQ(oMulti.count(73), mMulti.count(73));
}

TEST(Test, lower1) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2,  3, 3, 5,
                                     6, -1, -1, 6, 7, 22, 9, 0, -3};
  std::multiset<int> oMulti(list);
  s21::multiset<int> mMulti(list);
  ASSERT_EQ(*mMulti.lower_bound(77), *oMulti.lower_bound(77));
  auto it1 = mMulti.lower_bound(1);
  auto it2 = oMulti.lower_bound(1);
  while (it1 != mMulti.end() || it2 != oMulti.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, upper) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2,  3, 3, 5,
                                     6, -1, -1, 6, 7, 22, 9, 0, -3};
  std::multiset<int> oMulti(list);
  s21::multiset<int> mMulti(list);
  ASSERT_EQ(*mMulti.upper_bound(22), *oMulti.upper_bound(22));
  auto it1 = mMulti.upper_bound(1);
  auto it2 = oMulti.upper_bound(1);
  while (it1 != mMulti.end() || it2 != oMulti.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(Test, xtreme_upANDlow) {
  std::initializer_list<double> list = {22.3, 17.9, 323.2};
  std::multiset<double> oSet(list);
  s21::multiset<double> mSet(list);
  ASSERT_DOUBLE_EQ(*oSet.upper_bound(1.3), *mSet.upper_bound(1.3));
  ASSERT_DOUBLE_EQ(*oSet.lower_bound(1.3), *mSet.lower_bound(1.3));
}

TEST(Test, range) {
  std::initializer_list<int> list = {1, 1,  1,  2, 2, 2,  3, 3, 5,
                                     6, -1, -1, 6, 7, 22, 9, 0, -3};
  std::multiset<int> oSet(list);
  s21::multiset<int> mSet(list);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> p1;
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> p2;
  p1 = oSet.equal_range(2);
  p2 = mSet.equal_range(2);
  ASSERT_EQ(*p1.first, *p2.first);
  ASSERT_EQ(*p1.second, *p2.second);
}

TEST(Tets, set_emplace) {
  std::initializer_list<double> list = {1.2, 3.7, 3.14, 8.9};
  std::set<double> set1(list);
  s21::set<double> set2(list);
  set1.emplace(1.2);
  set1.emplace(3.7);
  set1.emplace(9.9);
  auto v2 = set2.emplace(1.2, 3.7, 9.9);
  auto it2 = v2.begin();
  for (int i = 0; i < 3; i++, ++it2) {
    if (i == 2) {
      ASSERT_TRUE((*it2).second);
    } else {
      ASSERT_FALSE((*it2).second);
    }
  }
  auto iter1 = set1.begin();
  auto iter2 = set2.begin();
  while (iter1 != set1.end() || iter2 != set2.end()) {
    ASSERT_DOUBLE_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, set_emplace_empty) {
  std::initializer_list<int> list = {1, 3, 3, 8, 17};
  s21::set<int> set1(list);
  std::set<int> set2(list);
  auto v1 = set1.emplace();
  auto it1 = v1.begin();
  ASSERT_EQ(*(*it1).first, 0);
  ASSERT_FALSE((*it1).second);
  auto iter1 = set1.begin();
  auto iter2 = set2.begin();
  while (iter1 != set1.end() || iter2 != set2.end()) {
    ASSERT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, multi_emplace) {
  std::initializer_list<double> list = {1.2, 3.7, 3.14, 8.9};
  std::multiset<double> set1(list);
  s21::multiset<double> set2(list);
  set1.emplace(1.2);
  set1.emplace(3.7);
  set1.emplace(9.9);
  auto v2 = set2.emplace(1.2, 3.7, 9.9);
  auto it2 = v2.begin();
  for (int i = 0; i < 3; i++, ++it2) {
    ASSERT_TRUE((*it2).second);
  }
  auto iter1 = set1.begin();
  auto iter2 = set2.begin();
  while (iter1 != set1.end() || iter2 != set2.end()) {
    ASSERT_DOUBLE_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Test, multi_emplce_empty) {
  std::initializer_list<int> list = {1, 3, 3, 8, 17};
  s21::multiset<int> set1(list);
  std::multiset<int> set2(list);
  auto v1 = set1.emplace();
  auto it1 = v1.begin();
  ASSERT_EQ(*(*it1).first, 0);
  ASSERT_FALSE((*it1).second);
  auto iter1 = set1.begin();
  auto iter2 = set2.begin();
  while (iter1 != set1.end() || iter2 != set2.end()) {
    ASSERT_EQ(*iter1, *iter2);
    ++iter1;
    ++iter2;
  }
}

TEST(Stack, basic) {
Stack<int> Kala;
int k = 5;

//  empty and size test

ASSERT_EQ(true, Kala.empty());
ASSERT_EQ(0, Kala.size());

//  push and top test

Kala.push(k);
ASSERT_EQ(k, Kala.top());
k = 6;
Kala.push(k);
ASSERT_EQ(k, Kala.top());

Kala.top() = 11;
ASSERT_EQ(11, Kala.top());

int& c = Kala.top();
c = 3;

ASSERT_EQ(c, Kala.top());

//  pop test

Kala.pop();
ASSERT_EQ(5, Kala.top());


//  memory test allocation test

k = 3;
Kala.push(k);
Kala.push(k);
Kala.push(k);
Kala.push(k);
Kala.push(k);
Kala.push(k);



//  empty and size test

ASSERT_EQ(false, Kala.empty());
ASSERT_EQ(7, Kala.size());

//  swap test
Stack<int> Kala1;
Kala1.swap(Kala);

ASSERT_EQ(false, Kala1.empty());
ASSERT_EQ(7, Kala1.size());
ASSERT_EQ(3, Kala1.top());

ASSERT_EQ(true, Kala.empty());
ASSERT_EQ(0, Kala.size());

//  move constructor test

Stack<int> Kala2(std::move(Kala1));

ASSERT_EQ(false, Kala2.empty());
ASSERT_EQ(7, Kala2.size());
ASSERT_EQ(3, Kala2.top());

ASSERT_EQ(true, Kala1.empty());
ASSERT_EQ(0, Kala1.size());

//  copy constructor test

Stack<int> Kala4(Kala2);

ASSERT_EQ(false, Kala4.empty());
ASSERT_EQ(7, Kala4.size());
ASSERT_EQ(3, Kala4.top());

//  initialize constructor test

Stack<int> KalaInit = {1, 5, 4, 3};
ASSERT_EQ(false, KalaInit.empty());
ASSERT_EQ(4, KalaInit.size());
ASSERT_EQ(3, KalaInit.top());

Stack<int> KalaBad = {};
ASSERT_EQ(true, KalaBad.empty());
ASSERT_EQ(0, KalaBad.size());

//  Operator = test

Stack<int> Moved(std::move(KalaInit));

ASSERT_EQ(false, Moved.empty());
ASSERT_EQ(4, Moved.size());
ASSERT_EQ(3, Moved.top());

Moved.emplace_front(1, 6, 8, 1, 4);

ASSERT_EQ(9, Moved.size());
ASSERT_EQ(4, Moved.top());

}

TEST(Vector, basic) {
  Vector<int> Kala;

  //  Emptiness check

ASSERT_EQ(Kala.size(), 0);
ASSERT_EQ(Kala.max_size(), 0);
ASSERT_TRUE(Kala.empty());

//ASSERT_EQ(Kala.front(), 0);
//ASSERT_EQ(Kala.back(), 0);

//  Push check

Kala.push_back(3);

ASSERT_EQ(Kala.front(), 3);
ASSERT_EQ(Kala.back(), 3);

Kala.push_back(5);

ASSERT_EQ(Kala.front(), 3);
ASSERT_EQ(Kala.back(), 5);

//  Pop check

Kala.pop_back();

ASSERT_EQ(Kala.front(), 3);
ASSERT_EQ(Kala.back(), 3);

//  Memory allocation check

Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);
Kala.push_back(3);

ASSERT_EQ(Kala.size(), 10);
ASSERT_EQ(Kala.max_size(), 10);

//  Shrink_to_fit_check

Kala.pop_back();
Kala.pop_back();
Kala.pop_back();
Kala.pop_back();

ASSERT_EQ(Kala.size(), 6);
ASSERT_EQ(Kala.max_size(), 10);
ASSERT_EQ(Kala.capacity(), 4);

Kala.push_back(3);
ASSERT_EQ(Kala.size(), 7);
ASSERT_EQ(Kala.max_size(), 10);
ASSERT_EQ(Kala.capacity(), 3);

Kala.shrink_to_fit();

ASSERT_EQ(Kala.size(), 7);
ASSERT_EQ(Kala.max_size(), 7);

//  Reserve check

Kala.reserve(50);

ASSERT_EQ(Kala.size(), 7);
ASSERT_EQ(Kala.max_size(), 57);

Kala.push_back(9);
ASSERT_EQ(Kala.size(), 8);
ASSERT_EQ(Kala.max_size(), 57);
ASSERT_EQ(Kala.capacity(), 49);
ASSERT_EQ(Kala.back(), 9);

//  Parametrized size constructor check

Vector<int> KalaSize(15);

ASSERT_EQ(KalaSize.size(), 0);
ASSERT_EQ(KalaSize.max_size(), 15);

KalaSize.push_back(3);
KalaSize.push_back(6);
KalaSize.push_back(7);

ASSERT_EQ(KalaSize.front(), 3);
ASSERT_EQ(KalaSize.back(), 7);

Vector<int> KalaEmpty;

KalaSize.swap(KalaEmpty);

ASSERT_EQ(KalaEmpty.size(), 3);
ASSERT_EQ(KalaEmpty.max_size(), 15);
ASSERT_EQ(KalaEmpty.front(), 3);
ASSERT_EQ(KalaEmpty.back(), 7);

ASSERT_EQ(KalaSize.size(), 0);
ASSERT_EQ(KalaSize.max_size(), 0);

//  Copy constructor check

Vector<int> KalaCopied(KalaEmpty);

ASSERT_EQ(KalaCopied.size(), 3);
ASSERT_EQ(KalaCopied.max_size(), 15);
ASSERT_EQ(KalaCopied.front(), 3);
ASSERT_EQ(KalaCopied.back(), 7);


//  Initialize constructor check

Vector<int> KalaInit = {1, 7, 2, 8, 9};

ASSERT_EQ(KalaInit.size(), 5);
ASSERT_EQ(KalaInit.max_size(), 5);
ASSERT_EQ(KalaInit.front(), 1);
ASSERT_EQ(KalaInit.back(), 9);

//  Move constructor check

Vector<int> KalaMoved(std::move(KalaInit));

ASSERT_EQ(KalaMoved.size(), 5);
ASSERT_EQ(KalaMoved.max_size(), 5);
ASSERT_EQ(KalaMoved.front(), 1);
ASSERT_EQ(KalaMoved.back(), 9);

ASSERT_EQ(KalaInit.size(), 0);
ASSERT_EQ(KalaInit.max_size(), 0);
ASSERT_TRUE(KalaInit.empty());

//ASSERT_EQ(KalaInit.front(), 0);
//ASSERT_EQ(KalaInit.back(), 0);

//  Erase check

Vector<int>::VectorIterator iter(KalaMoved.begin());

ASSERT_EQ(KalaMoved.at(2), 2);
ASSERT_EQ(KalaMoved[1], 7);

KalaMoved.erase(iter);

ASSERT_EQ(KalaMoved.at(2), 8);
ASSERT_EQ(KalaMoved[1], 2);

iter.Advance(2);


ASSERT_EQ(iter.GetPosition(), 2);
ASSERT_EQ(*iter, 8);

KalaMoved.erase(iter);

ASSERT_EQ(*iter, 9);
ASSERT_EQ(KalaMoved.size(), 3);
ASSERT_EQ(KalaMoved.max_size(), 5);
ASSERT_EQ(KalaMoved.front(), 7);
ASSERT_EQ(KalaMoved.back(), 9);

//  Insert check

int ins = 8;
iter = KalaMoved.insert(iter, ins);
ASSERT_EQ(iter.GetPosition(), 2);
ASSERT_EQ(*iter, 8);

ASSERT_EQ(KalaMoved.size(), 4);
ASSERT_EQ(KalaMoved.max_size(), 5);
ASSERT_EQ(KalaMoved.front(), 7);
ASSERT_EQ(KalaMoved.back(), 9);


//  Clear check

KalaCopied.clear();

ASSERT_EQ(KalaCopied.size(), 0);
ASSERT_EQ(KalaCopied.max_size(), 0);

KalaCopied.emplace_back(6, 7, 15, 3);

ASSERT_EQ(KalaCopied.front(), 6);
ASSERT_EQ(KalaCopied.back(), 3);

auto it = KalaCopied.begin();

it.Advance(2);

ASSERT_EQ(*it, 15);

auto new_it = KalaCopied.emplace(it, 5, 13);

auto check_it = KalaCopied.begin();

check_it.Advance(2);

ASSERT_EQ(*check_it, 13);

check_it.Advance(1);

ASSERT_EQ(*check_it, 5);

check_it.Advance(1);

ASSERT_EQ(*check_it, 15);

ASSERT_EQ(*new_it, 13);

Vector<int[5]> ooo{};

}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}