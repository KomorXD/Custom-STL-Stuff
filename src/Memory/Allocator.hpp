#pragma once

namespace nstd {
	template<typename T>
	class Allocator {
		public:

			// Returns an address of an obj even if the operator& is overloaded
			T* address(T& obj) const {
				return addressof(obj);
			}

			// Returns a const address of an obj even if the operator& is overloaded
			const T* address(const T& obj) const {
				return addressof(obj);
			}

			// Allocates uSize space in memory without initializing it
			// If allocation fails, throws std::bad_alloc
			// If impossible to allocate, throws std::bad_array_new_length
			T* allocate(size_t uSize) {
				T* pPtr = (T*)::operator new(uSize * sizeof(T));

				if (!pPtr)
					throw std::bad_alloc();

				if (std::numeric_limits<size_t>::max() / sizeof(T) < uSize)
					throw std::bad_array_new_length();

				return pPtr;
			}

			// Allocates uSize space in memory, as close to the pHint as possible, without initializing it
			// If allocation fails, throws std::bad_alloc
			// If impossible to allocate, throws std::bad_array_new_length
			T* allocate(size_t uSize, const void* pHint) {
				T* pPtr = (T*)::operator new(uSize * sizeof(T), pHint);

				if (!pPtr)
					throw std::bad_alloc();

				if (std::numeric_limits<size_t>::max() / sizeof(T) < uSize)
					throw std::bad_array_new_length();

				return pPtr;
			}

			// Deallocates memory with given size uSize, at pPtr
			void deallocate(void* pPtr, size_t uSize) {
				::operator delete(pPtr, uSize * sizeof(T));
			}

			// Returns largest supported allocation size
			size_t max_size() const {
				return std::numeric_limits<size_t>::max() / sizeof(T);
			}

			// Construct an object with arg val in-place at an initialized memory location given in pPtr
			void construct(T* pPtr, const T& val) {
				new(pPtr) T(val);
			}
			
			// Construct an object with args in-place at an initialized memory location given in pPtr
			template<typename... Args>
			void construct(T* pPtr, Args&&... args) {
				new(pPtr) T(std::forward<Args>(args)...);
			}

			// Calls the destructor of an object at pPtr
			void destroy(T* pPtr) {
				pPtr->~T();
			}

			// Static methods
			static T* allocate(Allocator& alloc, size_t uSize) {
				return alloc.allocate(uSize);
			}

			static T* allocate(Allocator& alloc, size_t uSize, const void* pHint) {
				return alloc.allocate(uSize, pHint);
			}

			static void deallocate(Allocator& alloc, void* pPtr, size_t uSize) {
				alloc.deallocate(pPtr, uSize);
			}

			static size_t max_size(const Allocator& alloc) {
				return alloc.max_size();
			}

			template<typename... Args>
			static void construct(Allocator& alloc, T* pPtr, Args&&... args) {
				alloc.construct(pPtr, std::forward<Args>(args)...);
			}

			static void destroy(Allocator& alloc, T* pPtr) {
				alloc.destroy(pPtr);
			}
	};
}