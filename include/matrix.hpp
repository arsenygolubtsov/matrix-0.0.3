#include <iostream>

template <typename T>
class matrix_t
{
private:
    T** elements_;
    std::size_t rows_;
    std::size_t collumns_;

public:
    matrix_t();
    matrix_t(matrix_t const& other);
    matrix_t& operator=(matrix_t const& other);
    ~matrix_t();

    std::size_t rows() const;
    std::size_t collumns() const;

    matrix_t operator+(matrix_t const& other) const;
    matrix_t operator-(matrix_t const& other) const;
    matrix_t operator*(matrix_t const& other) const;
    matrix_t& operator+=(matrix_t const& other);
    matrix_t& operator-=(matrix_t const& other);
    matrix_t& operator*=(matrix_t const& other);

    std::istream& read(std::istream& stream);
    std::ostream& write(std::ostream& stream) const;
};

template <typename T>
matrix_t<T>::matrix_t() : elements_{ nullptr }, rows_{ 0 }, collumns_{ 0 }
{
}

template <typename T>
matrix_t<T>::matrix_t( matrix_t const & other )
{
	rows_ = other.rows_;
	collumns_ = other.collumns_;
	elements_ = new T *[rows_];
	for (std::size_t i = 0; i < rows_; ++i) {
		elements_[i] = new T[collumns_];
		for (std::size_t j = 0; j < collumns_; ++j) {
			elements_[i][j] = other.elements_[i][j];
		}
	}
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator =( matrix_t const & other )
{
	if (this != &other) {
		for (std::size_t i = 0; i < rows_; ++i) {
			delete[] elements_[i];
		}
		delete[] elements_;
		rows_ = other.rows_;
		collumns_ = other.collumns_;
		elements_ = new T *[rows_];
		for (std::size_t i = 0; i < rows_; ++i) {
			elements_[i] = new T [collumns_];
		}
		for (std::size_t i = 0; i < rows_; ++i) {
			for (std::size_t j = 0; j < collumns_; ++j) {
				elements_[i][j] = other.elements_[i][j];
			}
		}
	}

	return *this;
}

template <typename T>
matrix_t<T>::~matrix_t()
{
	for (std::size_t i = 0; i < rows_; i++) {
		delete [] elements_[i];
	}
	delete []elements_;
}

template <typename T>
std::size_t matrix_t<T>::rows() const
{
    return rows_;
}

template <typename T>
std::size_t matrix_t<T>::collumns() const 
{
    return collumns_;
}

template <typename T>
matrix_t<T> matrix_t<T>::operator +( matrix_t const & other ) const
{
	matrix_t result;
	if (rows_ == other.rows_ && collumns_ == other.collumns_) {
		result.rows_ = rows_;
		result.collumns_ = collumns_;
		result.elements_ = new T *[rows_];
		for (std::size_t i = 0; i<collumns_; i++) {
			result.elements_[i] = new T [collumns_];
		}
		for (std::size_t i = 0; i<rows_; i++) {
			for (std::size_t j = 0; j<collumns_; j++) {
				result.elements_[i][j] = elements_[i][j] + other.elements_[i][j];
			}
		}
	}
	else {
		throw std::invalid_argument("exeption");
	}

	return result;
}

template <typename T>
matrix_t<T> matrix_t<T>::operator -( matrix_t const & other ) const
{
	matrix_t<T> result;
	if (rows_ == other.rows_ && collumns_ == other.collumns_) {
		result.rows_ = rows_;
		result.collumns_ = collumns_;
		result.elements_ = new T *[rows_];
		for (std::size_t i = 0; i<collumns_; i++) {
			result.elements_[i] = new T [collumns_];
		}
		for (std::size_t i = 0; i<rows_; i++) {
			for (std::size_t j = 0; j<collumns_; j++) {
				result.elements_[i][j] = elements_[i][j] - other.elements_[i][j];
			}
		}
	}
	else {
		throw std::invalid_argument("exeption");
	}

	return result;
}

template <typename T>
matrix_t<T> matrix_t<T>::operator *( matrix_t const & other ) const
{
	matrix_t<T> result;
	if (collumns_ == other.rows_) {
		result.rows_ = rows_;
		result.collumns_ = other.collumns_;		
		result.elements_ = new T *[rows_];
		for (std::size_t i = 0; i < rows_; ++i) {
			result.elements_[i] = new T [other.collumns_];
		}
		for (int i = 0; i < rows_; ++i) {
			for (std::size_t j = 0; j < other.collumns_; ++j) {
				std::size_t summ = 0;
				for (std::size_t k = 0; k < other.rows_; ++k) {
					summ += elements_[i][k] * other.elements_[k][j];
				}
				result.elements_[i][j] = summ;
			}
		}
	}
	else {
		throw std::invalid_argument("exeption");
	}

	return result;
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator -=( matrix_t const & other )
{
	if (rows_ == other.rows_ && collumns_ == other.collumns_) {
		for (std::size_t i = 0; i<rows_; i++) {
			for (std::size_t j = 0; j<collumns_; j++) {
				elements_[i][j] -= other.elements_[i][j];
			}
		}
	}
	else {
		throw std::invalid_argument("exeption");
	}
	return *this;
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator +=( matrix_t const & other )
{
	if (rows_ == other.rows_ && collumns_ == other.collumns_) {
		for (std::size_t i = 0; i < rows_; ++i) {
			for (std::size_t j = 0; j < collumns_; ++j) {
				elements_[i][j] += other.elements_[i][j];
			}	
		}
	}
	else {
		throw std::invalid_argument("exeption");
	}
	return *this;
}

template <typename T>
matrix_t<T> & matrix_t<T>::operator *=( matrix_t const & other )
{
	matrix_t result;
	if (collumns_ == other.rows_) {
		result.rows_ = rows_;
		result.collumns_ = other.collumns_;	
		result.elements_ = new T *[rows_];
		for (std::size_t i = 0; i < rows_; ++i) {
			result.elements_[i] = new T [other.collumns_];
		}
		for (int i = 0; i < rows_; ++i) {
			for (std::size_t j = 0; j < other.collumns_; ++j) {
				std::size_t summ = 0;
				for (std::size_t k = 0; k < other.rows_; ++k) {
					summ += elements_[i][k] * other.elements_[k][j];
				}
				result.elements_[i][j] = summ;
			}
		}
		*this = result;
	}
	else {
		throw std::invalid_argument("exeption");
	}
	return *this;
}

template <typename T>
std::istream & matrix_t<T>::read( std::istream & stream )
{
    std::size_t rows;
    std::size_t collumns;
    char symbol;
    
    bool success = true;
    if( stream >> rows && stream >> symbol && symbol == ',' && stream >> collumns ) {
        T ** elements = new T *[ rows ];
        for( std::size_t i = 0; success && i < rows; ++i ) {
            elements[ i ] = new T [ collumns ];
            for( std::size_t j = 0; j < collumns; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }
        
        if( success ) {
            for( std::size_t i = 0; i < rows_; ++i ) {
                delete [] elements_[ i ];
            }
            delete [] elements_;
            
            rows_ = rows;
            collumns_ = collumns;
            elements_ = elements;
        }
        else {
            for( std::size_t i = 0; i < rows; ++i ) {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else {
        success = false;
    }
    
    if( !success ) {
        stream.setstate( std::ios_base::failbit );
    }
    
	return stream;
}

template <typename T>
std::ostream & matrix_t<T>::write( std::ostream & stream ) const
{
    stream << rows_ << ", " << collumns_;
    for( std::size_t i = 0; i < rows_; ++i ) {
        stream << '\n';
        for( std::size_t j = 0; j < collumns_; ++j ) {
            stream << elements_[ i ][ j ];
            if( j != collumns_ - 1 ) {
                stream << ' ';
            }
        }
    }
    
	return stream;
}
