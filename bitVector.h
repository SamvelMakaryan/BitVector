#include <cstddef>
#include <iostream>
class bitVector {
	public:

		struct bits {
			bool zero : 1;
			bool one : 1;
			bool two : 1;
			bool three : 1;
			bool four : 1;
			bool five : 1;
			bool six : 1;
			bool seven : 1;
		};

	public:
		
		bitVector() : m_size(0), m_cap(0), m_buf(nullptr) {}

		bitVector(size_t n) : m_size(n), m_cap(n / 8 + 1) {
			m_buf = new bits [m_cap];
		}

		bitVector(size_t n, bool val) : m_size(n), m_cap(n / 8 + 1) {

			m_buf = new bits [m_cap];
			for (int i = 0; i < m_size / 8; ++i) {
				m_buf[i].zero = m_buf[i].one = m_buf[i].two = m_buf[i].three = m_buf[i].four = m_buf[i].five = m_buf[i].six = m_buf[i].seven = val;
			}
			
		}

		bitVector(const bitVector& oth) : m_size(oth.m_size), m_cap(oth.m_cap) {
			m_buf = new bits [m_cap];
			for (int i = 0; i < m_size / 8; ++i) {
				m_buf[i] = oth.m_buf[i];
			}
		}

		bitVector(bitVector&& oth) noexcept : m_size(oth.m_size), m_cap(oth.m_cap) {
			m_buf = oth.m_buf;
			oth.m_buf = nullptr;
			oth.m_size = 0;
			oth.m_cap = 0;
		}

	public:

		size_t size() const {
			return m_size;
		}

		size_t capacity() const {
			return m_cap * 8;
		}

		void set(size_t n) {
			size_t byte = n / 8;
			size_t bit = n % 8;
			switch (bit) {

				case 0 : m_buf[byte].zero = true; break;
				case 1 : m_buf[byte].one = true; break;
				case 2 : m_buf[byte].two = true; break;
				case 3 : m_buf[byte].three = true; break;
				case 4 : m_buf[byte].four = true; break;
				case 5 : m_buf[byte].five = true; break;
				case 6 : m_buf[byte].six = true; break;
				case 7 : m_buf[byte].seven = true; break;
			}
	    }

		void reset(size_t n) {
			size_t byte = n / 8;
			size_t bit = n % 8;
			switch (bit) {

				case 0 : m_buf[byte].zero = false; break;
				case 1 : m_buf[byte].one = false; break;
				case 2 : m_buf[byte].two = false; break;
				case 3 : m_buf[byte].three = false; break;
				case 4 : m_buf[byte].four = false; break;
				case 5 : m_buf[byte].five = false; break;
				case 6 : m_buf[byte].six = false; break;
				case 7 : m_buf[byte].seven = false; break;
			}
	    }

		const bool operator[] (size_t n) const {
			size_t byte = n / 8;
			size_t bit = n % 8;
			bool tmp;
			switch (bit) {

				case 0 : tmp =  m_buf[byte].zero; break;
				case 1 : tmp =  m_buf[byte].one; break;
				case 2 : tmp =  m_buf[byte].two; break;
				case 4 : tmp =  m_buf[byte].four; break;
				case 5 : tmp =  m_buf[byte].five; break;
				case 6 : tmp =  m_buf[byte].six; break;
				case 7 : tmp =  m_buf[byte].seven; break;

			}
			return tmp;
	    }	

		void push_back(bool val) {
			if (m_cap == 0) {
				++m_cap;
				m_buf = new bits [m_cap];
			}
			else if (m_size / 8 == m_cap) {
				_realloc(m_size / 4);
			}
			++m_size;
			size_t byte = m_size / 8;
			size_t bit = m_size % 8;
			switch (bit) {

				case 0 : m_buf[byte].zero = val; break;
				case 1 : m_buf[byte].one = val; break;
				case 2 : m_buf[byte].two = val; break;
				case 4 : m_buf[byte].four = val; break;
				case 5 : m_buf[byte].five = val; break;
				case 6 : m_buf[byte].six = val; break;
				case 7 : m_buf[byte].seven = val; break;

			}
	   }

	   void pop_back() {
		   if (m_size == 0) {
			   return;
		   }
		   --m_size;
	   }
		
	private:

		size_t m_size;
		size_t m_cap;
		bits* m_buf;

		void _realloc(size_t n) {
			m_cap = n;
			bits* tmp = new bits [n];
			for (int i = 0; i < m_size; ++i) {
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
		}
};
	

