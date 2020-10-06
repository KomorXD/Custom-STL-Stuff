#pragma once

#include <stdexcept>
#include <initializer_list>

namespace nstd {
	template<typename Vector>
	class VectorIterator {
		public:
			using ValueType = typename Vector::ValueType;

		public:
			VectorIterator(ValueType* ptr)
				: m_Ptr(ptr) { }

			VectorIterator& operator ++() {
				m_Ptr++;

				return *this;
			}
			
			VectorIterator operator ++(int) {
				VectorIterator itr = *this;

				++(*this);

				return itr;
			}

			VectorIterator& operator --() {
				m_Ptr--;

				return *this;
			}

			VectorIterator operator --(int) {
				VectorIterator itr = *this;

				--(*this);

				return itr;
			}

			ValueType& operator [](size_t uIndex) {
				return *(m_Ptr + uIndex);
			}

			ValueType* operator ->() {
				return m_Ptr;
			}

			ValueType& operator *() {
				return *m_Ptr;
			}

			size_t operator +(const VectorIterator& other) {
				return m_Ptr + other;
			}

			size_t operator -(const VectorIterator& other) {
				return m_Ptr - other.m_Ptr;
			}

			VectorIterator operator +(size_t uOffset) {
				return VectorIterator(m_Ptr + uOffset);
			}

			VectorIterator operator -(size_t uOffset) {
				return VectorIterator(m_Ptr - uOffset);
			}

			VectorIterator& operator +=(const VectorIterator& other) {
				m_Ptr += other.m_Ptr;

				return *this;
			}

			VectorIterator& operator -=(const VectorIterator& other) {
				m_Ptr -= other.m_Ptr;

				return *this;
			}

			VectorIterator& operator +=(size_t uOffset) {
				m_Ptr += uOffset;

				return *this;
			}

			VectorIterator& operator -=(size_t uOffset) {
				m_Ptr -= uOffset;

				return *this;
			}

			bool operator ==(const VectorIterator& other) {
				return m_Ptr == other.m_Ptr;
			}

			bool operator !=(const VectorIterator& other) {
				return m_Ptr != other.m_Ptr;
			}

			bool operator <(const VectorIterator& other) {
				return m_Ptr < other.m_Ptr;
			}

			bool operator <=(const VectorIterator& other) {
				return m_Ptr <= other.m_Ptr;
			}

			bool operator >(const VectorIterator& other) {
				return m_Ptr > other.m_Ptr;
			}

			bool operator >=(const VectorIterator& other) {
				return m_Ptr >= other.m_Ptr;
			}

		private:
			ValueType* m_Ptr;
	};

	template<typename Vector>
	class ConstVectorIterator {
		public:
			using ValueType = typename Vector::ValueType;

		public:
			ConstVectorIterator(ValueType* ptr)
				: m_Ptr(ptr) { }

			ConstVectorIterator& operator ++() {
				m_Ptr++;

				return *this;
			}

			ConstVectorIterator operator ++(int) {
				ConstVectorIterator itr = *this;

				++(*this);

				return itr;
			}

			ConstVectorIterator& operator --() {
				m_Ptr--;

				return *this;
			}

			ConstVectorIterator operator --(int) {
				ConstVectorIterator itr = *this;

				--(*this);

				return itr;
			}

			const ValueType& operator [](size_t uIndex) const {
				return *(m_Ptr + uIndex);
			}

			const ValueType* operator ->() const {
				return m_Ptr;
			}

			const ValueType& operator *() const {
				return *m_Ptr;
			}

			size_t operator +(const ConstVectorIterator& other) {
				return m_Ptr + other;
			}

			size_t operator -(const ConstVectorIterator& other) {
				return m_Ptr - other.m_Ptr;
			}

			ConstVectorIterator operator +(size_t uOffset) {
				return ConstVectorIterator(m_Ptr + uOffset);
			}

			ConstVectorIterator operator -(size_t uOffset) {
				return ConstVectorIterator(m_Ptr - uOffset);
			}

			ConstVectorIterator& operator +=(const ConstVectorIterator& other) {
				m_Ptr += other.m_Ptr;

				return *this;
			}

			ConstVectorIterator& operator -=(const ConstVectorIterator& other) {
				m_Ptr -= other.m_Ptr;

				return *this;
			}

			ConstVectorIterator& operator +=(size_t uOffset) {
				m_Ptr += uOffset;

				return *this;
			}

			ConstVectorIterator& operator -=(size_t uOffset) {
				m_Ptr -= uOffset;

				return *this;
			}

			bool operator ==(const ConstVectorIterator& other) {
				return m_Ptr == other.m_Ptr;
			}

			bool operator !=(const ConstVectorIterator& other) {
				return m_Ptr != other.m_Ptr;
			}

			bool operator <(const ConstVectorIterator& other) {
				return m_Ptr < other.m_Ptr;
			}

			bool operator <=(const ConstVectorIterator& other) {
				return m_Ptr <= other.m_Ptr;
			}

			bool operator >(const ConstVectorIterator& other) {
				return m_Ptr > other.m_Ptr;
			}

			bool operator >=(const ConstVectorIterator& other) {
				return m_Ptr >= other.m_Ptr;
			}

		private:
			ValueType* m_Ptr;
	};
}

namespace nstd {
	template<typename T>
	class Vector {
		public:
			using ValueType		= T;
			using Iterator		= VectorIterator<Vector<T>>;
			using ConstIterator = ConstVectorIterator<Vector<T>>;
			
		public:
			//Default constructor, allocates 2 * sizeof(T) bytes of memory on the heap
			Vector() {
				ReAlloc(2);
			}

			//Allocates uSize number of elements and assigns them a value of 'value'
			Vector(size_t uSize, const T& value) {
				ReAlloc(uSize);

				for (size_t i = 0; i < uSize; ++i)
					m_pData[i] = value;
			}

			//Allocates uSize number of elements and assigns them a default value
			Vector(size_t uSize) {
				ReAlloc(uSize);

				for (size_t i = 0; i < uSize; ++i)
					m_pData[i] = T{};
			}

			//Allocates enough memory to fit the [first; last) range and constructs a vector based on the iterators
			template<typename InputItr>
			Vector(InputItr first, InputItr last) {
				if (first > last)
					throw std::out_of_range("The 'first' iterator is bigger than the 'last' iterator");

				size_t uSize = last - first;
				size_t i = 0;

				ReAlloc(uSize);
				m_uSize = uSize;

				for (auto it = first; it != last; ++it, ++i)
					m_pData[i] = *it;
			}

			//Copy constructor
			Vector(const Vector& other) {
				*this = other;
			}

			//Move constructor
			Vector(Vector&& other) {
				*this = std::move(other);
			}

			//Init list contructor
			Vector(std::initializer_list<T> list) {
				*this = list;
			}

			//Destructor, frees used space on the heap
			~Vector() {
				::operator delete(m_pData, m_uCapacity * sizeof(T));
			}

			//Clears the current vector, copies other vector into this one
			Vector& operator =(const Vector& other) {
				if (this == &other)
					return *this;

				clear();
				ReAlloc(other.m_uCapacity);

				for (size_t i = 0; i < other.m_uSize; ++i)
					m_pData[i] = other.m_pData[i];

				m_uSize = other.m_uSize;

				return *this;
			}

			//Clears the current vector, moves other vector into this one and leaves a hollow object
			Vector& operator =(Vector&& other) noexcept {
				if (this == &other)
					return *this;

				clear();

				m_pData		= other.m_pData;
				m_uSize		= other.m_uSize;
				m_uCapacity = other.m_uCapacity;

				other.m_pData	  = nullptr;
				other.m_uSize	  = 0;
				other.m_uCapacity = 0;

				return *this;
			}

			//Clears the current vector, allocates memory for list.size() elements and copies them from the list
			Vector& operator =(std::initializer_list<T> list) {
				for (size_t i = 0; i < m_uSize; ++i)
					m_pData[i].~T();

				ReAlloc(list.size());
				m_uSize = list.size();

				size_t i = 0;

				for (auto it = list.begin(); it != list.end(), i < m_uSize; ++it, ++i)
					m_pData[i] = *it;

				return *this;
			}

			//Clears the vector, reallocates enough memory for 'count' elements and assigns vector elements to 'value's
			void assign(size_t count, const T& value) {
				clear();
				ReAlloc(m_uSize);

				for (size_t i = 0; i < m_uSize; ++i)
					m_pData[i] = value;
			}

			//Clears the vector, reallocates enough memory to fit the [first, last) range and assigns vector elements baes on iterators
			template<typename InputItr>
			void assign(InputItr first, InputItr last) {
				if (first > last)
					throw std::out_of_range("The 'first' iterator is bigger than the 'last' iterator");

				clear();

				size_t uSize = last - first;
				size_t i = 0;

				ReAlloc(uSize);
				m_uSize = uSize;

				for (auto it = first; it != last; ++it, ++i)
					m_pData[i] = *it;
			}

			//Look for: Vector& operator =(std::initializer_list<T> list)
			void assign(std::initializer_list<T> list) {
				*this = list;
			}

			//Accesses m_pData[uIndex] and returns a reference. If uIndex is invalid, throws an exception
			T& at(size_t uIndex) {
				if (uIndex >= m_uSize)
					throw std::out_of_range("Invalid index");

				return m_pData[uIndex];
			}

			//Accesses m_pData[uIndex] and returns a const reference. If uIndex is invalid, throws an exception
			const T& at(size_t uIndex) const {
				if (uIndex >= m_uSize)
					throw std::out_of_range("Invalid index");

				return m_pData[uIndex];
			}

			//Accesses m_pData[uIndex] and returns a reference
			T& operator [](size_t uIndex) {
				return m_pData[uIndex];
			}

			//Accesses m_pData[uIndex] and returns a const reference
			const T& operator [](size_t uIndex) const {
				return m_pData[uIndex];
			}

			//Returns a reference to the first element. If there are no elements, throws an exception
			T& front() {
				if (m_uSize == 0)
					throw std::out_of_range("No elements in the container");

				return m_pData[0];
			}

			//Returns a const reference to the first element. If there are no elements, throws an exception
			const T& front() const {
				if (m_uSize == 0)
					throw std::out_of_range("No elements in the container");

				return m_pData[0];
			}

			//Returns a reference to the last element. If there are no elements, throws an exception
			T& back() {
				if (m_uSize == 0)
					throw std::out_of_range("No elements in the container");

				return m_pData[m_uSize - 1];
			}

			//Returns a const reference to the last element. If there are no elements, throws an exception
			const T& back() const {
				if (m_uSize == 0)
					throw std::out_of_range("No elements in the container");

				return m_pData[m_uSize - 1];
			}

			//Returns the pointer to the underlying container
			T* data() {
				return m_pData;
			}

			//Returns the const pointer to the underlying container
			const T* data() const {
				return m_pData;
			}

			//Returns an iterator to the beginning of a vector
			Iterator begin() {
				return Iterator(m_pData);
			}

			//Returns an iterator to the element past the end of a vector
			Iterator end() {
				return Iterator(m_pData + m_uSize);
			}

			//Returns an iterator to the element before the beginning of a vector
			Iterator rbegin() {
				return Iterator(m_pData - 1);
			}

			//Returns an iterator to the end of a vector
			Iterator rend() {
				return Iterator(m_pData + m_uSize - 1);
			}

			//Returns an const iterator to the beginning of a vector
			ConstIterator cbegin() {
				return ConstIterator(m_pData);
			}

			//Returns an const iterator to the element past the end of a vector
			ConstIterator cend() {
				return ConstIterator(m_pData + m_uSize);
			}

			//Returns an const iterator to the element before the beginning of a vector
			ConstIterator crbegin() {
				return ConstIterator(m_pData - 1);
			}

			//Returns an const iterator to the end of a vector
			ConstIterator crend() {
				return ConstIterator(m_pData + m_uSize - 1);
			}
			
			//Returns true if this vector is empty, false otherwise
			bool empty() const {
				return m_uSize == 0;
			}

			//Returns a size of a vector
			size_t size() const {
				return m_uSize;
			}

			//Returns the capacity of a vector
			size_t capacity() const {
				return m_uCapacity;
			}

			//If uNewSize if greater than the current capacity, reallocates the memory to be exactly uNewCap in size
			void reserve(size_t uNewCap) {
				if (uNewCap > m_uCapacity)
					ReAlloc(uNewCap);
			}

			//If current size is smaller than capacity, which it should be, reallocates the memory to be exactly m_uSize in size
			void shrink_to_fit() {
				if (m_uSize < m_uCapacity)
					ReAlloc(m_uSize);
			}

			//Explicitly calls destructor of every element and sets the m_uSize to 0, therefore cleaning the container
			void clear() {
				for (size_t i = 0; i < m_uSize; ++i)
					m_pData[i].~T();

				m_uSize = 0;
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for a 'value' and copies it
			Iterator insert(Iterator pos, const T& value) {
				size_t len = pos - begin();

				if (m_uSize >= m_uCapacity)
					ReAlloc(m_uCapacity + m_uCapacity / 2);

				memmove_s(m_pData + len + 1,
						  m_uCapacity * sizeof(T) - (len + 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));

				m_pData[len] = value;
				m_uSize++;

				return Iterator(m_pData + len);
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for a 'value' and moves it
			Iterator insert(Iterator pos, T&& value) {
				size_t len = pos - begin();

				if (m_uSize >= m_uCapacity)
					ReAlloc(m_uCapacity + m_uCapacity / 2);

				memmove_s(m_pData + len + 1,
						  m_uCapacity * sizeof(T) - (len + 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));

				m_pData[len] = std::move(value);
				m_uSize++;

				return Iterator(m_pData + len);
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for a range of [pos; pos + uCount) and copies it
			Iterator insert(Iterator pos, size_t uCount, const T& value) {
				size_t len = pos - begin();

				if (m_uSize + uCount - 1 >= m_uCapacity)
					ReAlloc( m_uSize + uCount > m_uCapacity + m_uCapacity / 2 ? m_uSize + uCount : m_uCapacity + m_uCapacity / 2 );

				memmove_s(m_pData + len + uCount,
						  m_uCapacity * sizeof(T) - (len + uCount - 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));

				for (size_t i = len; i < len + uCount; ++i)
					m_pData[i] = value;

				m_uSize += uCount;

				return Iterator(m_pData + len);
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for a range of [pos; pos + uCount) and moves it
			Iterator insert(Iterator pos, size_t uCount, T&& value) {
				size_t len = pos - begin();

				if (m_uSize + uCount - 1 >= m_uCapacity)
					ReAlloc( m_uSize + uCount > m_uCapacity + m_uCapacity / 2 ? m_uSize + uCount : m_uCapacity + m_uCapacity / 2 );

				memmove_s(m_pData + len + uCount,
						  m_uCapacity * sizeof(T) - (len + uCount - 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));

				for (size_t i = len; i < len + uCount; ++i)
					m_pData[i] = std::move(value);

				m_uSize += uCount;

				return Iterator(m_pData + len);
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for a range of [first; last) and copies it
			Iterator insert(Iterator pos, Iterator first, Iterator last) {
				size_t len  = pos - begin();
				size_t size = last - first;

				if (m_uSize + size >= m_uCapacity)
					ReAlloc(m_uSize + size > m_uCapacity + m_uCapacity / 2 ? m_uSize + size : m_uCapacity + m_uCapacity / 2);

				memmove_s(m_pData + len + size,
						  m_uCapacity * sizeof(T) - (len + size - 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));

				size_t i = len;

				for (auto it = first; it != last; ++it, ++i)
					m_pData[i] = *it;

				m_uSize += size;

				return Iterator(m_pData + len);
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for a list and copies it
			Iterator insert(Iterator pos, std::initializer_list<T> list) {
				size_t len = pos - begin();
				size_t size = list.end() - list.begin();

				if (m_uSize + size >= m_uCapacity)
					ReAlloc(m_uSize + size > m_uCapacity + m_uCapacity / 2 ? m_uSize + size : m_uCapacity + m_uCapacity / 2);

				memmove_s(m_pData + len + size,
						  m_uCapacity * sizeof(T) - (len + size - 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));
				
				size_t i = len;

				for (auto it = list.begin(); it != list.end(); ++it, ++i)
					m_pData[i] = std::move(*it);

				m_uSize += size;

				return Iterator(m_pData + len);
			}

			//Reallocates the memory block if necessary and shifts a part of it to make a space for an emplacement with given args
			template<typename... Args>
			Iterator emplace(Iterator pos, Args&&... args) {
				size_t len = pos - begin();

				if (m_uSize >= m_uCapacity)
					ReAlloc(m_uCapacity + m_uCapacity / 2);

				memmove_s(m_pData + len + 1,
						  m_uCapacity * sizeof(T) - (len + 1) * sizeof(T),
						  m_pData + len,
						  (m_uSize - len) * sizeof(T));

				new(m_pData + len) T(std::forward<Args>(args)...);
				m_uSize++;

				return Iterator(m_pData + len);
			}

			//Erases an element at the position that pos point to
			Iterator erase(Iterator pos) {
				if (pos < begin() || pos >= end())
					return Iterator(nullptr);

				size_t len = pos - begin();

				(*pos).~T();
				memmove_s(m_pData + len,
						  (m_uCapacity - len) * sizeof(T),
						  m_pData + len + 1,
						  (m_uSize - len) * sizeof(T));

				m_uSize--;

				return Iterator(m_pData + len);
			}

			Iterator erase(Iterator first, Iterator last) {
				if (first > last || first < begin() || last > end())
					return Iterator(nullptr);

				size_t len  = first - begin();
				size_t size = last - first;

				for (auto it = first; it != last; ++it)
					(*it).~T();

				memmove_s(m_pData + len,
						  (m_uCapacity - len) * sizeof(T),
						  m_pData + len + size,
						  (m_uSize - len) * sizeof(T));

				m_uSize -= size;

				return Iterator(m_pData + len);
			}

			//Copies the given value and puts it on the end of the container. Reallocates the entire block if necessary
			void push_back(const T& value) {
				if (m_uSize >= m_uCapacity)
					ReAlloc(m_uCapacity + m_uCapacity / 2);

				m_pData[m_uSize] = value;
				m_uSize++;
			}

			//Moves the given value and puts it on the end of the container. Reallocates the entire block if necessary
			void push_back(T&& value) {
				if (m_uSize >= m_uCapacity)
					ReAlloc(m_uCapacity + m_uCapacity / 2);

				m_pData[m_uSize] = std::move(value);
				m_uSize++;
			}

			//Construct a T instance with given arguments in place of the next free space in the memory block
			template<typename... Args>
			T& emplace_back(Args&&... args) {
				if (m_uSize >= m_uCapacity)
					ReAlloc(m_uCapacity + m_uCapacity / 2);

				new(m_pData + m_uSize) T(std::forward<Args>(args)...);

				return m_pData[m_uSize++];
			}

			//If there are any elements, calls a destructor of the last element and decrements the size of a container
			void pop_back() {
				if (m_uSize > 0)
					m_pData[m_uSize--].~T();
			}

			//Resizes the container. If necessary, will reallocate the memory block to a proper size
			void resize(size_t uNewSize, const T& value = T{}) {
				if (uNewSize < m_uSize) {
					while (m_uSize != uNewSize)
						pop_back();
				}
				else if (uNewSize > m_uSize) {
					if (uNewSize > m_uCapacity)
						ReAlloc(uNewSize);

					for (size_t i = m_uSize; i < uNewSize; ++i)
						m_pData[i] = value;
				}
			}

			//Swaps with the given container, not invoking any copy, move or swap operations
			void swap(Vector<T>& other) {
				if (this == &other)
					return;

				std::swap(m_pData,	   other.m_pData);
				std::swap(m_uSize,	   other.m_uSize);
				std::swap(m_uCapacity, other.m_uCapacity);
			}

		private:
			//Creates a new block of memory, moves/copies the m_pData block into it, deletes m_pData
			//and assigns m_pData to the new block, m_uCapacity to the uNewCap
			void ReAlloc(size_t uNewCap) {
				T* pNewBlock = (T*)::operator new(uNewCap * sizeof(T));

				for (size_t i = 0; i < m_uSize; ++i)
					pNewBlock[i] = std::move(m_pData[i]);

				::operator delete(m_pData, m_uCapacity * sizeof(T));
				m_pData = pNewBlock;
				m_uCapacity = uNewCap;
			}

		private:
			T*	   m_pData;
			size_t m_uSize	   = 0;
			size_t m_uCapacity = 0;
	};
}

template<typename T>
bool operator ==(const nstd::Vector<T>& lhs, const nstd::Vector<T>& rhs) {
	if (lhs.size() != rhs.size())
		return false;

	for (size_t i = 0; i < lhs.size(); ++i)
		if (lhs[i] != rhs[i])
			return false;

	return true;
}

template<typename T>
bool operator !=(const nstd::Vector<T>& lhs, const nstd::Vector<T>& rhs) {
	if (lhs.size() != rhs.size())
		return true;

	for (size_t i = 0; i < lhs.size(); ++i)
		if (lhs[i] != rhs[i])
			return true;

	return false;
}

template<typename T>
bool operator <(const nstd::Vector<T>& lhs, const nstd::Vector<T>& rhs) {
	if (lhs.size() < rhs.size())
		return true;

	if (lhs.size() > rhs.size())
		return false;

	for (size_t i = 0; i < lhs.size(); ++i) {
		if (lhs[i] < rhs[i])
			return true;

		if (lhs[i] > rhs[i])
			return false;
	}

	return false;
}

template<typename T>
bool operator <=(const nstd::Vector<T>& lhs, const nstd::Vector<T>& rhs) {
	if (lhs.size() < rhs.size())
		return true;

	if (lhs.size() > rhs.size())
		return false;

	for (size_t i = 0; i < lhs.size(); ++i) {
		if (lhs[i] < rhs[i])
			return true;

		if (lhs[i] > rhs[i])
			return false;
	}

	return true;
}

template<typename T>
bool operator >(const nstd::Vector<T>& lhs, const nstd::Vector<T>& rhs) {
	if (lhs.size() > rhs.size())
		return true;

	if (lhs.size() < rhs.size())
		return false;

	for (size_t i = 0; i < lhs.size(); ++i) {
		if (lhs[i] > rhs[i])
			return true;

		if (lhs[i] < rhs[i])
			return false;
	}

	return false;
}

template<typename T>
bool operator >=(const nstd::Vector<T>& lhs, const nstd::Vector<T>& rhs) {
	if (lhs.size() > rhs.size())
		return true;

	if (lhs.size() < rhs.size())
		return false;

	for (size_t i = 0; i < lhs.size(); ++i) {
		if (lhs[i] > rhs[i])
			return true;

		if (lhs[i] < rhs[i])
			return false;
	}

	return true;
}

namespace std {
	template<typename T>
	void swap(nstd::Vector<T>& lhs, nstd::Vector<T>& rhs) {
		lhs.swap(rhs);
	}
}