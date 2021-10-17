# SortedSet
an implementation of sorted set class in c++ using singly linked list.

# The following member functions are available in the public interface:

1. 	SortedSet();  //default constructor

2. 	void insert(T const&);  //inserts the data in such a way that the resulting set remains sorted. Duplicate data is not allowed

3. 	void delete_(int const&);  //deletes the data at the given index.

4. 	void union_(SortedSet<T> const&); //takes union of two sets.
  
5.  void intersection(SortedSet<T> const&);  //takes intersection of two sets

6.  void deleteAll();  //deletes all the elements in the set.

7.  bool isEmpty() const; //returns true if the set is empty.

8.  void print() const;   //prints all the elements of the set.

9.  ~SortedSet();  //destructor
  
Note: None of the functions have any nested loop.
