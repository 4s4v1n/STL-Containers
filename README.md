# STL-Containers

![containers](./images/containers.png)

## Content
This project provides an implementation of the Standard Template Library (STL) containers and their main methods.
All containers are in the `s21` namespace.
Each container has an iterator in the form of an internal class of the container. Standard operations are implemented on iterators:
 1) `++iter`
 2) `--iter`
 3) `iter1 == iter2`
 4) `iter1 != iter2`
 5) `iter1 = iter2`
 6) `*iter`
The project is divided into 2 parts, namely `my_containers.h` , `my_containers_plus.h`.

`my_containets.h`
 1) `queue` (my_containerAdaptor.h)
 2) `stack` (my_containerAdaptor.h)
 3) `list` (my_list.h)
 4) `map` (my_map.h)
 5) `set` (my_set.h)
 6) `vector` (my_vector.h)

`my_containers_plus.h`:
 1) `array` (my_array.h)
 2) `multiset` (my_multiset)
For each of the container, the constructors and destructor are essentially the same:

 1) `container()` is the base constructor.
 2) `container(std::initializer_list<value_type> const& items)` - constructor with initialization list.
 3) `container(const container& other)` - copy constructor.
 4) `container(container&& other)` - move constructor.
 5) `operator=(container&& other)` - move operator.
 6) `~container()` - destructor.
 
## Queue

`queue` - a container, from one end of which elements can be added, and from the other - removed.

### queue methods

 1) `const_reference front()` - returns a reference to the first element.
 2) `const_reference back()` - returns a reference to the last element.
 3) `bool empty()` - checks for the presence of elements.
 4) `size_type size()` - returns the number of elements.
 5) `void push(const_reference value)` - adds an element to the end.
 6) `void pop()` - removes the first element.
 7) `void swap(queue& other)` - swaps two objects.

## Stack

`stack` is a container in which elements are added and removed from one end.

### stack methods

 1) `const_reference top()` - returns the reference of the element at the top of the element.
 2) `bool empty()` - checks for the presence of elements.
 3) `size_type size()` - returns the number of elements.
 4) `void push(const_reference value)` - adds an element to the top.
 5) `void pop()` - remove the element at the top.
 6) `void swap(stack& other)` - swaps two objects.

## List

`list` is a doubly linked list whose elements are stored in arbitrary chunks of memory.

### list methods

 1) `const_reference front()` - returns a reference to the first element.
 2) `const_reference back()` - returns a reference to the last element.
 3) `iterator begin()` - returns an iterator to the beginning.
 4) `iterator end()` - returns an iterator to the end.
 5) `bool empty()` - checks for the presence of elements.
 6) `size_type size()` - returns the number of elements.
 7) `size_type max_size()` - returns the maximum number of possible elements.
 8) `void clear()` - clearing.
 9) `iterator insert(iterator pos, const_reference value)` - inserting an element by iterator, returns the position of the iterator where the element was inserted.
 10) `void erase(iterator pos)` - delete element by iterator
 11) `void push_back(const_reference value)` - adding an element to the end.
 12) `void pop_back()` - delete the element at the end.
 13) `void push_front(const_reference value)` - adding an element to the front.
 14) `void pop_front()` - remove element at the beginning.
 15) `void swap(list& other)` - swaps two objects.
 16) `void merge(list& other)` - merges the passed object with the current one.
 17) `void splice(const_iterator pos, list& other)` - transfers elements from another object starting from the position of the iterator.
 18) `void reverse()` - reverses the order of accessing elements.
 19) `void unique()` - removes consecutive duplicate elements.
 20) `void sort()` - sorts all elements.

## Map

`map` is an ordered associative array of pairs of elements consisting of keys and their corresponding values. Keys must be unique.

### map methods

 1) `T& at(const Key& key)` - returns a reference to the element with bounds checking.
 2) `T& operator[](const Key& key)` - returns a reference to the element.
 3) `iterator begin()` - returns an iterator to the beginning.
 4) `iterator end()` - returns an iterator to the end.
 5) `bool empty()` - checks for the presence of elements.
 6) `size_type size()` - returns the number of elements.
 7) `size_type max_size()` - returns the maximum number of possible elements.
 8) `void clear()` - clearing.
 9) `std::pair<iterator, bool> insert(const value_type& value)` - inserts an element by value and returns the pair, iterator position and whether the insert succeeded.
 10) `std::pair<iterator, bool> insert(const Key& key, const T& obj)` - inserts an element by key and returns the pair, iterator position and whether the insert succeeded.
 11) `std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj)` - inserts an element or assigns a value to an element by key, if such a key already exists.
 12) `void erase(iterator pos)` - removes the element at the position of the iterator.
 13) `void swap(map& other)` - swaps two objects.
 14) `void merge(map& other)` - merges the passed object with the current one.
 15) `bool contains(const Key& key)` - checks if an element exists with the given key.

## Set

`set` - an ordered set of unique elements.

### set methods

 1) `iterator begin()` - returns an iterator to the beginning.
 2) `iterator end()` - returns an iterator to the end.
 3) `bool empty()` - checks for the presence of elements.
 4) `size_type size()` - returns the number of elements.
 5) `size_type max_size()` - returns the maximum number of possible elements.
 6) `void clear()` - clearing.
 7) `std::pair<iterator, bool> insert(const value_type& value)` - element insertion, returns a pair, the position of the iterator where the element was inserted and whether the insert succeeded.
 8) `void erase(iterator pos)` - delete element by iterator position.
 9) `void swap(set& other)` - swaps two objects.
 10) `void merge(set& other)` - merges the passed object with the current one.
 11) `iterator find(const Key& key)` - returns an iterator to the element with the specified key.
 12) `bool contains(const Key& key)` - checks if there is an element with the specified key.

## Vector

`vetor` - C-like dynamic random access array with automatic resizing when element is added/removed.

### vector methods

 1) `reference at(size_type pos)` - returns a reference to the element with bounds checking.
 2) `reference operator[](size_type pos)` - returns a reference to the element.
 3) `const_reference front()` - returns a reference to the first element.
 4) `const_reference back()` - returns a reference to the last element.
 5) `iterator data()` - direct access to the underlying array.
 6) `iterator begin()` - returns an iterator to the beginning.
 7) `iterator end()` - returns an iterator to the end.
 8) `bool empty()` - checks for the presence of elements.
 9) `size_type size()` - returns the number of elements.
 10) `size_type max_size()` - returns the maximum number of possible.11) `void reserve(size_type size)` - allocates additional memory for elements and copies existing elements into it.
 12) `size_type capacity()` - returns the number of possible elements to store at the moment.
 13) `void shrink_to_fit()` - releases unused memory.
 14) `void clear()` - clearing.
 15) `iterator insert(iterator pos, const_reference value)` - insert element at iterator position.
 16) `void erase(iterator pos)` - delete an element about the iterator.
 17) `void push_back(const_reference value)` - insert an element at the end.
 18) `void pop_back()` - remove the last element.
 19) `void swap(vector& other)` - swaps two objects.

## Array

`array` is a sequential container that encapsulates a static array.

### array methods

 1) `reference at(size_type pos)` - returns a reference to the element with bounds checking.
 2) `reference operator[](size_type pos)` - returns a reference to the element.
 3) `const_reference front()` - returns a reference to the first element.
 4) `const_reference back()` - returns a reference to the last element.
 5) `iterator data()` - direct access to the underlying array.
 6) `iterator begin()` - returns an iterator to the beginning.
 7) `iterator end()` - returns an iterator to the end.
 8) `bool empty()` - checks for the presence of elements.
 9) `size_type size()` - returns the number of elements.
 10) `size_type max_size()` - returns the maximum number of possible elements.
 11) `void swap(array& other)` - swaps two objects.
 12) `void fill(const_reference value)` - assigns the specified value to all elements in the container.

## Multiset

`multiset` is the same as set but allows you to store duplicate elements.

### multiset methods

 1) `iterator begin()` - returns an iterator to the beginning.
 2) `iterator end()` - returns an iterator to the end.
 3) `bool empty()` - checks for the presence of elements.
 4) `size_type size()` - returns the number of elements.
 5) `size_type max_size()` - returns the maximum number of possible elements.
 6) `void clear()` - clearing.
 7) `iterator insert(const value_type& value)` - inserting an element, returns an iterator to the position where the element was inserted.
 8) `void erase(iterator pos)` - delete element by iterator position.
 9) `void swap(multiset& other)` - swaps two objects.
 10) `void merge(multiset& other)` - merges the passed object with the current one.
 11) `iterator find(const Key& key)` - returns an iterator to the element with the specified key.
 12) `bool contains(const Key& key)` - checks if there is an element with the specified key.
 13) `size_type count(const Key& key)` - returns the number of elements in the container equal to the given one.
 14) `iterator find(const Key& key)` - returns an iterator to the element with the desired value.
 15) `bool contains(const Key& key)` - check if the given element contains.
 16) `std::pair<iterator,iterator> equal_range(const Key& key)` - returns an iterator to the beginning and end of the set of elements that match the given value.
 17) `iterator lower_bound(const Key& key)` - returns an iterator to the first element not less than the passed value.
 18) `iterator upper_bound(const Key& key)` - returns an iterator to the first element greater than the passed value.

The project is built using g++ 9.4.0 and a makefile on Linux. The tests are written in google test.