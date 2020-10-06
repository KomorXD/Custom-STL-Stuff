#pragma once

#include <stdexcept>
#include <initializer_list>

namespace nstd {
	template<typename Array>
	class ArrayIterator {
		public:
			using ValueType = typename Array::ValueType;

		public:
			ArrayIterator(ValueType* ptr)
				: m_Ptr(ptr) { }

			ArrayIterator& operator ++() {
				m_Ptr++;

				return *this;
			}

			ArrayIterator operator ++(int) {
				ArrayIterator itr = *this;

				++(*this);

				return itr;
			}

			ArrayIterator& operator --() {
				m_Ptr--;

				return *this;
			}

			ArrayIterator operator --(int) {
				ArrayIterator itr = *this;

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

			size_t operator +(const ArrayIterator& other) {
				return m_Ptr + other;
			}

			size_t operator -(const ArrayIterator& other) {
				return m_Ptr - other.m_Ptr;
			}

			ArrayIterator operator +(size_t uOffset) {
				return ArrayIterator(m_Ptr + uOffset);
			}

			ArrayIterator operator -(size_t uOffset) {
				return ArrayIterator(m_Ptr - uOffset);
			}

			ArrayIterator& operator +=(const ArrayIterator& other) {
				m_Ptr += other.m_Ptr;

				return *this;
			}

			ArrayIterator& operator -=(const ArrayIterator& other) {
				m_Ptr -= other.m_Ptr;

				return *this;
			}

			ArrayIterator& operator +=(size_t uOffset) {
				m_Ptr += uOffset;

				return *this;
			}

			ArrayIterator& operator -=(size_t uOffset) {
				m_Ptr -= uOffset;

				return *this;
			}

			bool operator ==(const ArrayIterator& other) {
				return m_Ptr == other.m_Ptr;
			}

			bool operator !=(const ArrayIterator& other) {
				return m_Ptr != other.m_Ptr;
			}

			bool operator <(const ArrayIterator& other) {
				return m_Ptr < other.m_Ptr;
			}

			bool operator <=(const ArrayIterator& other) {
				return m_Ptr <= other.m_Ptr;
			}

			bool operator >(const ArrayIterator& other) {
				return m_Ptr > other.m_Ptr;
			}

			bool operator >=(const ArrayIterator& other) {
				return m_Ptr >= other.m_Ptr;
			}

		private:
			ValueType* m_Ptr;
	};
	
	template<typename Array>
	class ConstArrayIterator {
		public:
			using ValueType = typename Array::ValueType;

		public:
			ConstArrayIterator(ValueType* ptr)
				: m_Ptr(ptr) { }

			ConstArrayIterator& operator ++() {
				m_Ptr++;

				return *this;
			}

			ConstArrayIterator operator ++(int) {
				ConstArrayIterator itr = *this;

				++(*this);

				return itr;
			}

			ConstArrayIterator& operator --() {
				m_Ptr--;

				return *this;
			}

			ConstArrayIterator operator --(int) {
				ConstArrayIterator itr = *this;

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

			size_t operator +(const ConstArrayIterator& other) {
				return m_Ptr + other;
			}

			size_t operator -(const ConstArrayIterator& other) {
				return m_Ptr - other.m_Ptr;
			}

			ConstArrayIterator operator +(size_t uOffset) {
				return ConstArrayIterator(m_Ptr + uOffset);
			}

			ConstArrayIterator operator -(size_t uOffset) {
				return ConstArrayIterator(m_Ptr - uOffset);
			}

			ConstArrayIterator& operator +=(const ConstArrayIterator& other) {
				m_Ptr += other.m_Ptr;

				return *this;
			}

			ConstArrayIterator& operator -=(const ConstArrayIterator& other) {
				m_Ptr -= other.m_Ptr;

				return *this;
			}

			ConstArrayIterator& operator +=(size_t uOffset) {
				m_Ptr += uOffset;

				return *this;
			}

			ConstArrayIterator& operator -=(size_t uOffset) {
				m_Ptr -= uOffset;
				
				return *this;
			}

			bool operator ==(const ConstArrayIterator& other) {
				return m_Ptr == other.m_Ptr;
			}

			bool operator !=(const ConstArrayIterator& other) {
				return m_Ptr != other.m_Ptr;
			}

			bool operator <(const ConstArrayIterator& other) {
				return m_Ptr < other.m_Ptr;
			}

			bool operator <=(const ConstArrayIterator& other) {
				return m_Ptr <= other.m_Ptr;
			}

			bool operator >(const ConstArrayIterator& other) {
				return m_Ptr > other.m_Ptr;
			}

			bool operator >=(const ConstArrayIterator& other) {
				return m_Ptr >= other.m_Ptr;
			}

		private:
			ValueType* m_Ptr;
	};
}

namespace nstd {
	template<typename T, size_t _Size>
	class Array {
		public:
			using ValueType		= T;
			using Iterator		= ArrayIterator<Array<T, _Size>>;
			using ConstIterator = ConstArrayIterator<Array<T, _Size>>;
			
		public:
			Array() {
				for (size_t i = 0; i < _Size; ++i)
					m_Data[i] = T{};
			}

			Array(const Array<T, _Size>& other) {
				*this = other;
			}

			Array(Array<T, _Size>&& other) {
				*this = std::move(other);
			}

			Array(std::initializer_list<T> list) {
				*this = list;
			}

			~Array() {
				for (size_t i = 0; i < _Size; ++i)
					m_Data[i].~T();
			}

			Array<T, _Size>& operator =(const Array<T, _Size>& other) {
				if (this != &other) {
					for (size_t i = 0; i < _Size; ++i)
						m_Data[i] = other.m_Data[i];
				}

				return *this;
			}

			Array<T, _Size>& operator =(Array<T, _Size>&& other) {
				if (this != &other) {
					for (size_t i = 0; i < _Size; ++i)
						m_Data[i] = other.m_Data[i];
				}

				return *this;
			}

			Array<T, _Size>& operator =(std::initializer_list<T> list) {
				size_t i = 0;

				for (auto it = list.begin(); it != list.end() && i < _Size; ++i, ++it)
					m_Data[i] = *it;

				for (i; i < _Size; ++i)
					m_Data[i] = T{};

				return *this;
			}

			T& at(size_t uIndex) {
				if (uIndex >= _Size)
					throw std::out_of_range("Invalid index");

				return m_Data[uIndex];
			}

			const T& at(size_t uIndex) const {
				if (uIndex >= _Size)
					throw std::out_of_range("Invalid index");

				return m_Data[uIndex];
			}

			T& operator [](size_t uIndex) {
				return m_Data[uIndex];
			}

			const T& operator [](size_t uIndex) const {
				return m_Data[uIndex];
			}

			T& front() {
				return m_Data[0];
			}

			const T& front() const {
				return m_Data[0];
			}

			T& back() {
				return m_Data[_Size - 1];
			}

			const T& back() const {
				return m_Data[_Size - 1];
			}

			T* data() {
				return m_Data;
			}

			const T* data() const {
				return m_Data;
			}

			bool empty() const {
				return _Size == 0;
			}

			size_t size() const {
				return _Size;
			}

			size_t max_size() const {
				return _Size;
			}

			void fill(const T& value) {
				for (size_t i = 0; i < _Size; ++i)
					m_Data[i] = value;
			}

			void swap(Array<T, _Size>& other) {
				if (this != &other)
					std::swap(m_Data, other.m_Data);
			}

			Iterator begin() {
				return Iterator(m_Data);
			}

			Iterator end() {
				return Iterator(m_Data + _Size);
			}

			Iterator rbegin() {
				return Iterator(m_Data - 1);
			}

			Iterator rend() {
				return Iterator(m_Data + _Size - 1);
			}

			ConstIterator cbegin() {
				return ConstIterator(m_Data);
			}

			ConstIterator cend() {
				return ConstIterator(m_Data + _Size);
			}

			ConstIterator crbegin() {
				return ConstIterator(m_Data - 1);
			}

			ConstIterator crend() {
				return ConstIterator(m_Data + _Size - 1);
			}

		private:
			T m_Data[_Size];
	};
}

template<typename T, size_t _Size>
bool operator ==(const nstd::Array<T, _Size>& lhs, const nstd::Array<T, _Size>& rhs) {
	for (size_t i = 0; i < _Size; ++i) {
		if (lhs[i] != rhs[i])
			return false;
	}

	return true;
}

template<typename T, size_t _Size>
bool operator !=(const nstd::Array<T, _Size>& lhs, const nstd::Array<T, _Size>& rhs) {
	for (size_t i = 0; i < _Size; ++i) {
		if (lhs[i] != rhs[i])
			return true;
	}

	return false;
}

template<typename T, size_t _Size>
bool operator <(const nstd::Array<T, _Size>& lhs, const nstd::Array<T, _Size>& rhs) {
	for (size_t i = 0; i < _Size; ++i) {
		if (lhs[i] < rhs[i])
			return true;

		if (lhs[i] > rhs[i])
			return false;
	}

	return false;
}

template<typename T, size_t _Size>
bool operator <=(const nstd::Array<T, _Size>& lhs, const nstd::Array<T, _Size>& rhs) {
	for (size_t i = 0; i < _Size; ++i) {
		if (lhs[i] < rhs[i])
			return true;

		if (lhs[i] > rhs[i])
			return false;
	}

	return true;
}

template<typename T, size_t _Size>
bool operator >(const nstd::Array<T, _Size>& lhs, const nstd::Array<T, _Size>& rhs) {
	for (size_t i = 0; i < _Size; ++i) {
		if (lhs[i] > rhs[i])
			return true;

		if (lhs[i] < rhs[i])
			return false;
	}

	return false;
}

template<typename T, size_t _Size>
bool operator >=(const nstd::Array<T, _Size>& lhs, const nstd::Array<T, _Size>& rhs) {
	for (size_t i = 0; i < _Size; ++i) {
		if (lhs[i] > rhs[i])
			return true;

		if (lhs[i] < rhs[i])
			return false;
	}

	return true;
}

namespace std {
	template<typename T, size_t _Size>
	void swap(nstd::Array<T, _Size>& lhs, nstd::Array<T, _Size>& rhs) noexcept {
		lhs.swap(rhs);
	}

	template<size_t _Index, typename T, size_t _Size>
	T& get(nstd::Array<T, _Size>& arr) {
		return arr.at(_Index);
	}

	template<size_t _Index, typename T, size_t _Size>
	const T& get(const nstd::Array<T, _Size>& arr) {
		return arr.at(_Index);
	}

	template<size_t _Index, typename T, size_t _Size>
	T&& get(nstd::Array<T, _Size>&& arr) {
		return arr.at(_Index);
	}

	template<size_t _Index, typename T, size_t _Size>
	const T&& get(const nstd::Array<T, _Size>&& arr) {
		return arr.at(_Index);
	}
}
