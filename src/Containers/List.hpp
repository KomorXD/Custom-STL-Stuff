#pragma once

#include <memory>
#include <functional>
#include <fstream>

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : input_iterator_tag {};

struct bidirectional_iterator_tag : forward_iterator_tag {};

template<typename List>
class ListIterator
{
	private:
		using node_type = typename List::node_type;

	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type   = typename List::difference_type;
		using value_type		= typename List::value_type;
		using reference			= typename List::reference;
		using pointer			= typename List::pointer;

		explicit ListIterator(std::shared_ptr<node_type> node, std::shared_ptr<node_type> tailPtr)
			: m_Ptr(node), m_TailPtr(tailPtr)
		{}
		
		ListIterator& operator++ ()
		{
			m_Ptr = m_Ptr->next;

			return *this;
		}

		ListIterator& operator++ (int)
		{
			ListIterator temp = *this;

			++(*this);

			return temp;
		}

		ListIterator& operator-- ()
		{
			if(m_Ptr)
				m_Ptr = m_Ptr->prev.lock();
			else
				m_Ptr = m_TailPtr;

			return *this;
		}

		ListIterator& operator-- (int)
		{
			ListIterator temp = *this;

			--(*this);

			return temp;
		}

		reference operator* () const
		{
			return m_Ptr->value;
		}

		pointer operator-> () const
		{
			return &(m_Ptr->value);
		}

		bool operator== (const ListIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!= (const ListIterator& other)
		{
			return m_Ptr != other.m_Ptr;
		}

	private:
		std::shared_ptr<node_type> m_Ptr;
		std::shared_ptr<node_type> m_TailPtr;
};

template<typename List>
class ConstListIterator
{
	private:
		using node_type = typename List::node_type;

	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = typename List::difference_type;
		using value_type = typename List::value_type;
		using const_reference = typename List::const_reference;
		using const_pointer = typename List::const_pointer;

		explicit ConstListIterator(std::shared_ptr<node_type> node, std::shared_ptr<node_type> tailPtr)
			: m_Ptr(node), m_TailPtr(tailPtr)
		{}

		ConstListIterator& operator++ ()
		{
			m_Ptr = m_Ptr->next;

			return *this;
		}

		ConstListIterator& operator++ (int)
		{
			ConstListIterator temp = *this;

			++(*this);

			return temp;
		}

		ConstListIterator& operator-- ()
		{
			if(m_Ptr)
				m_Ptr = m_Ptr->prev.lock();
			else
				m_Ptr = m_TailPtr;

			return *this;
		}

		ConstListIterator& operator-- (int)
		{
			ConstListIterator temp = *this;

			--(*this);

			return temp;
		}

		const_reference operator* () const
		{
			return m_Ptr->value;
		}

		const_pointer operator-> () const
		{
			return &(m_Ptr->value);
		}

		bool operator== (const ConstListIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!= (const ConstListIterator& other)
		{
			return m_Ptr != other.m_Ptr;
		}

	private:
		std::shared_ptr<node_type> m_Ptr;
		std::shared_ptr<node_type> m_TailPtr;
};

template<typename List>
class ReverseListIterator
{
	private:
		using node_type = typename List::node_type;

	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = typename List::difference_type;
		using value_type = typename List::value_type;
		using reference = typename List::reference;
		using pointer = typename List::pointer;

		explicit ReverseListIterator(std::shared_ptr<node_type> node, std::shared_ptr<node_type> headPtr)
			: m_Ptr(node), m_HeadPtr(headPtr)
		{}

		ReverseListIterator& operator++ ()
		{
			m_Ptr = m_Ptr->prev.lock();

			return *this;
		}

		ReverseListIterator& operator++ (int)
		{
			ReverseListIterator temp = *this;

			--(*this);

			return temp;
		}

		ReverseListIterator& operator-- ()
		{
			if(m_Ptr)
				m_Ptr = m_Ptr->next;
			else
				m_Ptr = m_HeadPtr;

			return *this;
		}

		ReverseListIterator& operator-- (int)
		{
			ReverseListIterator temp = *this;

			++(*this);

			return temp;
		}

		reference operator* () const
		{
			return m_Ptr->value;
		}

		pointer operator-> () const
		{
			return &(m_Ptr->value);
		}

		bool operator== (const ReverseListIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!= (const ReverseListIterator& other)
		{
			return m_Ptr != other.m_Ptr;
		}

	private:
		std::shared_ptr<node_type> m_Ptr;
		std::shared_ptr<node_type> m_HeadPtr;
};

template<typename List>
class ConstReverseListIterator
{
	private:
		using node_type = typename List::node_type;

	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = typename List::difference_type;
		using value_type = typename List::value_type;
		using const_reference = typename List::const_reference;
		using const_pointer = typename List::const_pointer;

		explicit ConstReverseListIterator(std::shared_ptr<node_type> node, std::shared_ptr<node_type> headPtr)
			: m_Ptr(node), m_HeadPtr(headPtr)
		{}

		ConstReverseListIterator& operator++ ()
		{
			m_Ptr = m_Ptr->prev.lock();

			return *this;
		}

		ConstReverseListIterator& operator++ (int)
		{
			ConstReverseListIterator temp = *this;

			--(*this);

			return temp;
		}

		ConstReverseListIterator& operator-- ()
		{
			if(m_Ptr)
				m_Ptr = m_Ptr->next;
			else
				m_Ptr = m_HeadPtr;

			return *this;
		}

		ConstReverseListIterator& operator-- (int)
		{
			ConstReverseListIterator temp = *this;

			++(*this);

			return temp;
		}

		const_reference operator* ()
		{
			return m_Ptr->value;
		}

		const_pointer operator-> ()
		{
			return &(m_Ptr->value);
		}

		bool operator== (const ConstReverseListIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!= (const ConstReverseListIterator& other)
		{
			return m_Ptr != other.m_Ptr;
		}

	private:
		std::shared_ptr<node_type> m_Ptr;
		std::shared_ptr<node_type> m_HeadPtr;
};

template<typename T>
class List
{
	private:
		struct ListNode
		{
			T value = T{};

			std::shared_ptr<ListNode> next;
			std::weak_ptr<ListNode>   prev;

			ListNode() = default;

			template<typename... Args>
			explicit ListNode(Args&&... args)
				: value(std::forward<Args>(args)...)
			{}
		};

	public:
		using value_type			 = T;
		using node_type				 = ListNode;
		using size_type				 = size_t;
		using difference_type		 = ptrdiff_t;
		using reference				 = value_type&;
		using const_reference		 = const value_type&;
		using pointer				 = value_type*;
		using const_pointer			 = const value_type*;
		using iterator				 = ListIterator<List<T>>;
		using const_iterator		 = ConstListIterator<List<T>>;
		using reverse_iterator		 = ReverseListIterator<List<T>>;
		using const_reverse_iterator = ConstReverseListIterator<List<T>>;

		explicit List() = default;

		// Invokes = copy operator
		List(const List& other)
		{
			*this = other;
		}

		// Invokes = move operator
		List(List&& other) noexcept
		{
			*this = std::move(other);
		}

		// Invokes = init_list operator
		List(std::initializer_list<T> list)
		{
			*this = list;
		}

		// Clears current container and copies every element of the other one
		List& operator= (const List& other)
		{
			if(this == &other)
				return *this;

			clear();

			std::shared_ptr<ListNode> node = other.m_Head;

			while(node)
			{
				push_back(node->value);
				node = node->next;
			}

			return *this;
		}

		// Clears current container and moves every element from the other one
		List& operator= (List&& other) noexcept
		{
			if(this == &other)
				return *this;

			clear();

			m_Head = std::move(other.m_Head);
			m_Tail = std::move(other.m_Tail);
			m_Size = other.m_Size;

			other.m_Size = 0;

			return *this;
		}

		// Clear current container and copies every element from initializer list
		List& operator= (std::initializer_list<T> list)
		{
			clear();

			for(const T& el : list)
				push_back(el);

			return *this;
		}

		// Clears this container
		~List()
		{
			clear();
		}

		// Returns a reference to the front of the list
		T& front()
		{
			return m_Head->value;
		}

		// Returns a const reference to the front of the list
		const T& front() const
		{
			return m_Head->value;
		}

		// Returns a reference to the back of the list
		T& back()
		{
			return m_Tail->value;
		}

		// Returns a const reference to the back of the list
		const T& back() const
		{
			return m_Tail->value;
		}

		// Returns a reference to the n-th element of the list, might throw if index out of range
		T& get(size_t ind)
		{
			if(ind >= m_Size)
				throw std::out_of_range("Index out of list's range");

			iterator itr = begin();

			while(ind-- && itr != end())
				++itr;

			return *itr;
		}

		// Returns a const reference to the n-th element of the list, might throw if index out of range
		const T& get(size_t ind) const
		{
			if(ind >= m_Size)
				throw std::out_of_range("Index out of list's range");

			const_iterator itr = begin();

			while(ind-- && itr != cend())
				++itr;

			return *itr;
		}

		// Returns a index of the first found occurrence of given val. Returns -1 if none found
		size_t find(const T& val)
		{
			std::shared_ptr<ListNode> itr = m_Head;
			size_t i = 0;

			while(itr)
			{
				if(itr->value == val)
					return i;

				itr = itr->next;
				++i;
			}

			return -1;
		}

		bool empty() const noexcept
		{
			return m_Size == 0;
		}

		size_t size() const noexcept
		{
			return m_Size;
		}

		// Moves each element into head, effectively clearing each and every one, including head
		void clear()
		{
			while(m_Head)
				m_Head = std::move(m_Head->next);

			m_Size = 0;
		}

		// Inserts val at given pos by rearranging pointers in nodes around the pos
		void insert(size_t pos, const T& val)
		{
			if(pos > m_Size)
				throw std::out_of_range("Index out of list's range");

			if(pos == 0)
			{
				push_front(val);

				return;
			}

			if(pos == m_Size)
			{
				push_back(val);

				return;
			}

			std::shared_ptr<ListNode> node = std::make_shared<ListNode>(val);
			std::shared_ptr<ListNode> ptr  = m_Head;

			while(pos--)
				ptr = ptr->next;

			node->next = ptr;
			node->prev = ptr->prev;

			ptr->prev.lock()->next = node;
			ptr->prev = node;

			m_Size++;
		}

		// Same as before, but moves the given val
		void insert(size_t pos, T&& val)
		{
			if(pos > m_Size)
				throw std::out_of_range("Index out of list's range");

			if(pos == 0)
			{
				push_front(val);

				return;
			}

			if(pos == m_Size)
			{
				push_back(val);

				return;
			}

			std::shared_ptr<ListNode> node = std::make_shared<ListNode>(std::move(val));
			std::shared_ptr<ListNode> ptr  = m_Head;

			while(pos--)
				ptr = ptr->next;

			node->next = ptr;
			node->prev = ptr->prev;

			ptr->prev.lock()->next = node;
			ptr->prev = node;

			m_Size++;
		}

		// Inserts element at the front of this list
		void push_front(const T& val)
		{
			if(!m_Size)
			{
				m_Head = m_Tail = std::make_shared<ListNode>(val);

				m_Size++;

				return;
			}

			std::shared_ptr<ListNode> temp = std::make_shared<ListNode>(val);

			temp->next = m_Head;

			m_Head->prev = temp;
			m_Head = temp;

			m_Size++;
		}

		// Moves element to the front of this list
		void push_front(T&& val)
		{
			if(!m_Size)
			{
				m_Head = m_Tail = std::make_shared<ListNode>(std::move(val));

				m_Size++;

				return;
			}

			std::shared_ptr<ListNode> temp = std::make_shared<ListNode>(std::move(val));
			
			temp->next = m_Head;

			m_Head->prev = temp;
			m_Head = temp;

			m_Size++;
		}

		// Constructs element in-place at the start of the list
		template<typename... Args>
		T& emplace_front(Args&&... args)
		{
			std::shared_ptr<ListNode> node = std::make_shared<ListNode>(std::forward<Args>(args)...);

			if(!m_Head)
			{
				m_Head = m_Tail = node;
				m_Size++;

				return m_Head->value;
			}

			m_Head->prev = node;
			node->next = m_Head;
			m_Head = node;

			return m_Head->value;
		}

		// Constructs element in-place at pos
		template<typename... Args>
		T& emplace(size_t pos, Args&&... args)
		{
			if(pos > m_Size)
				throw std::out_of_range("Index out of list's range");

			if(pos == 0)
			{
				emplace_front(std::forward<Args>(args)...);

				return;
			}

			if(pos == m_Size)
			{
				emplace_back(std::forward<Args>(args)...);

				return;
			}

			std::shared_ptr<ListNode> node = std::make_shared<ListNode>(std::forward<Args>(args)...);
			std::shared_ptr<ListNode> ptr = m_Head;

			while(pos--)
				ptr = ptr->next;

			node->next = ptr;
			node->prev = ptr->prev;

			ptr->prev.lock()->next = node;
			ptr->prev = node;

			m_Size++;
		}

		// Pushes element to the back of the list
		void push_back(const T& val)
		{
			if(!m_Size)
			{
				m_Head = m_Tail = std::make_shared<ListNode>(val);

				m_Size++;

				return;
			}

			std::shared_ptr<ListNode> temp = std::make_shared<ListNode>(val);

			temp->prev = m_Tail;

			m_Tail->next = temp;
			m_Tail = temp;

			m_Size++;
		}

		// Moves element to the back of the list
		void push_back(T&& val)
		{
			if(!m_Size)
			{
				m_Head = m_Tail = std::make_shared<ListNode>(std::move(val));

				m_Size++;

				return;
			}

			std::shared_ptr<ListNode> temp = std::make_shared<ListNode>(std::move(val));
			
			temp->prev = m_Tail;

			m_Tail->next = temp;
			m_Tail = temp;

			m_Size++;
		}

		// Constructs element in-place at the back of the list
		template<typename... Args>
		T& emplace_back(Args&&... args)
		{
			std::shared_ptr<ListNode> node = std::make_shared<ListNode>(std::forward<Args>(args)...);

			if(!m_Tail)
			{
				m_Tail = m_Head = node;
				m_Size++;

				return m_Tail->value;
			}

			m_Tail->next = node;
			node->prev = m_Tail;
			m_Tail = node;

			return m_Tail->value;
		}

		// Erases the element at the start of the list
		void pop_front()
		{
			if(!m_Size)
				return;

			m_Head = std::move(m_Head->next);
			m_Size--;
		}

		// Erases the element at the back of the list
		void pop_back()
		{
			if(!m_Size)
				return;

			m_Tail = std::move(m_Tail->prev.lock());
			m_Tail->next = std::shared_ptr<ListNode>(nullptr);
			m_Size--;
		}

		// Erases the element at the given pos
		void erase(size_t pos)
		{
			if(pos >= m_Size)
				throw std::out_of_range("Index out of list's range");

			if(pos == 0)
			{
				pop_front();

				return;
			}

			if(pos == m_Size - 1)
			{
				pop_back();

				return;
			}

			std::shared_ptr<ListNode> node = m_Head;

			while(pos--)
				node = node->next;

			node->prev.lock()->next = node->next;
			node->next->prev = node->prev;
		}

		// Sorts list with given, or default, compaaring funcition using quick sort
		void sort(std::function<bool(const T&, const T&)> comp = [](const T& lhs, const T& rhs) { return lhs <= rhs; })
		{
			QuickSort(m_Head, m_Tail, comp);
		}

		// Swaps two lists
		void swap(List& other) noexcept
		{
			if(this == &other)
				return;

			std::swap(m_Head, other.m_Head);
			std::swap(m_Tail, other.m_Tail);
			std::swap(m_Size, other.m_Size);
		}

		// Reads bytes and loads them as new list elements
		bool read_from_binary_file(const std::string& filename)
		{
			std::fstream file(filename, std::ios::in | std::ios::binary);

			if(!file.good())
				return false;

			T temp;

			while(file.read((char*)&temp, sizeof(T)))
				push_back(std::move(temp));

			file.close();

			return true;
		}

		// Saves list's elements bytes into file
		bool write_to_binary_file(const std::string& filename)
		{
			std::fstream file(filename, std::ios::out | std::ios::binary);

			if(!file.good())
				return false;

			for(const T& el : *this)
				file.write((char*)&el, sizeof(T));

			file.close();

			return true;
		}

		iterator begin() noexcept
		{
			return iterator(m_Head, m_Tail);
		}

		iterator end() noexcept
		{
			return iterator(std::shared_ptr<ListNode>(nullptr), m_Tail);
		}

		const_iterator begin() const noexcept
		{
			return const_iterator(m_Head, m_Tail);
		}

		const_iterator end() const noexcept
		{
			return const_iterator(std::shared_ptr<ListNode>(nullptr), m_Tail);
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(m_Tail, m_Head);
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(std::shared_ptr<ListNode>(nullptr), m_Head);
		}

		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(m_Tail, m_Head);
		}

		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(std::shared_ptr<ListNode>(nullptr), m_Head);
		}
		
		const_iterator cbegin() const noexcept
		{
			return const_iterator(m_Head, m_Tail);
		}

		const_iterator cend() const noexcept
		{
			return const_iterator(std::shared_ptr<ListNode>(nullptr), m_Tail);
		}

		const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(m_Tail, m_Head);
		}

		const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(std::shared_ptr<ListNode>(nullptr), m_Head);
		}

	private:
		std::shared_ptr<ListNode> Partition(std::shared_ptr<ListNode>& left, std::shared_ptr<ListNode>& right, const std::function<bool(const T&, const T&)>& comp)
		{
			T val = right->value;

			std::shared_ptr<ListNode> i = left->prev.lock();

			for(std::shared_ptr<ListNode> j = left; j != right; j = j->next)
			{
				if(comp(j->value, val))
				{
					i = i ? i->next : left;
					std::swap(i->value, j->value);
				}
			}

			i = i ? i->next : left;

			std::swap(i->value, right->value);

			return i;
		}

		void QuickSort(std::shared_ptr<ListNode> left, std::shared_ptr<ListNode> right, const std::function<bool(const T&, const T&)>& comp)
		{
			if(right && left != right && left != right->next)
			{
				std::shared_ptr<ListNode> pivot = Partition(left, right, comp);

				QuickSort(left, pivot->prev.lock(), comp);
				QuickSort(pivot->next, right, comp);
			}
		}
		
		std::shared_ptr<ListNode> m_Head;
		std::shared_ptr<ListNode> m_Tail;

		size_t m_Size = 0;
};
