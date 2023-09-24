#pragma once
#include "Include.h"




template<typename T>
class CMatrix
{

private:
	int rows, columns;
	T** elements;



public:

	inline CMatrix<T>()
	{
		rows = 0;
		columns = 0;
		elements = nullptr;
	}



	inline CMatrix<T>(int rows, int columns) : rows(rows), columns(columns)
	{
		elements = new T* [rows];
		for (int i = 0; i < rows; i++)
		{
			elements[i] = new T[columns];
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] = 0;
			}
		}

	}





	inline CMatrix<T>(const CMatrix<T>& other) : rows(other.rows), columns(other.columns)
	{
		elements = new T * [rows];
		for (int i = 0; i < rows; i++)
		{
			elements[i] = new T[columns];
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] = other.elements[i][j];
			}
		}
	}



	inline ~CMatrix<T>()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] elements[i];
		}
		delete[] elements;
	}



	inline CMatrix<T>& operator=(const CMatrix<T>& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < rows; i++) delete[] elements[i];
			delete[] elements;
			rows = other.rows;
			columns = other.columns;
			elements = new T * [rows];
			for (int i = 0; i < rows; i++) elements[i] = new T[columns];

			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
				{
					elements[i][j] = other.elements[i][j];
				}
		}
		return *this;
	}


	friend inline std::ostream& operator<<(std::ostream& os, const CMatrix<T>& obj)
	{
		os << obj.toString();
		return os;
	}


	inline CMatrix<T> add(CMatrix<T>& m)
	{
		if (m.rows != this->rows || m.columns != this->columns)
		{
			std::cout << "adding failed, matrices do not match\n" << rows << "X" << columns << " with " << m.rows << "X" << m.columns << "\n";
			return *this;
		}


		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				this->elements[i][j] += m.elements[i][j];
			}
		}
		return *this;
	}



	


	inline static CMatrix<T> add(CMatrix<T>& m1, CMatrix<T>& m2)
	{
		
		if (m1.rows != m2.rows || m1.columns != m2.columns)
		{
			std::cout << "adding failed, matrices do not match\n" << m1.rows << "X" << m1.columns << " with " << m2.rows << "X" << m2.columns << "\n";
			return CMatrix<T>(0,0);
		}

		CMatrix<T> result(m1.rows, m1.columns);

		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m1.columns; j++)
			{
				result.elements[i][j] = m1.elements[i][j] + m2.elements[i][j];
			}
		}

		return result;

	}






	inline CMatrix<T> add(T v)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				this->elements[i][j] += v;
			}
		}

		return *this;
	}



	inline static CMatrix<T> add(CMatrix<T>& m, T v)
	{
		CMatrix<T> result(m.rows, m.columns);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				result.elements[i][j] = m.elements[i][j] + v;
			}
		}

		return result;
	}








	inline CMatrix<T> sub(CMatrix<T>& m)
	{
		if (this->rows != m.rows || this->columns != m.columns)
		{
			std::cout << "subtracting failed! matrices do not match!\n" << rows << "X" << columns << " with " << m.rows << "X" << m.columns << "\n";
			return *this;
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				this->elements[i][j] -= m.elements[i][j];
			}
		}

		return *this;
	}






	inline static CMatrix<T> sub(CMatrix<T>& m1, CMatrix<T>& m2)
	{
		if (m1.rows != m2.rows || m1.columns != m2.columns)
		{
			std::cout << "subtracting failed, matrices do not match!\n" << m1.rows << "X" << m1.columns << " with " << m2.rows << "X" << m2.columns << "\n";
			return CMatrix<T>(0, 0);
		}

		CMatrix<T> result(m1.rows, m1.columns);

		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m1.columns; j++)
			{
				result.elements[i][j] = m1.elements[i][j] - m2.elements[i][j];
			}
		}

		return result;
	}








	inline CMatrix<T> sub(T v)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] -= v;
			}
		}

		return *this;
	}







	inline static CMatrix<T> sub(CMatrix<T>& m, T v)
	{
		CMatrix<T> result(m.rows, m.columns);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				result.elements[i][j] = m.elements[i][j] - v;
			}
		}
		return result;
	}





	inline CMatrix<T> mult(CMatrix<T>& m)
	{
		if (columns != m.rows)
		{
			std::cout << "muliplication failed, matrices do not match!\n" << rows << "X" << columns << " with " << m.rows << "X" << m.columns << "\n";
			return *this;
		}
		CMatrix<T> result(rows, m.columns);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				T current = 0;
				for (int k = 0; k < columns; k++)
				{
					result.elements[i][j] += elements[i][k] * m.elements[k][j];
				}
			}
		}
		overwrite(result);
		return *this;
	}







	inline static CMatrix<T> mult(CMatrix<T>& m1, CMatrix<T>& m2)
	{
		if (m1.columns != m2.rows)
		{
			std::cout << "muliplication failed, matrices do not match!\n" << m1.rows << "X" << m1.columns << " with " << m2.rows << "X" << m2.columns << "\n";
			return CMatrix<T>(0,0);
		}
		CMatrix<T> result(m1.rows, m2.columns);
		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m2.columns; j++)
			{
				T current = 0;
				for (int k = 0; k < m1.columns; k++)
				{
					result.elements[i][j] += m1.elements[i][k] * m2.elements[k][j];
				}
			}
		}
		return result;
	}







	inline CMatrix<T> mult(T v)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] *= v;
			}
		}
		return *this;
	}







	inline static CMatrix<T> mult(CMatrix<T>& m, T v)
	{
		CMatrix<T> result(m.rows, m.columns);
		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				result.elements[i][j] = m.elements[i][j] * v;
			}
		}
		return result;
	}






	inline CMatrix<T> multHadamard(CMatrix<T>& m)
	{
		if (rows != m.rows || columns != m.columns)
		{
			std::cout << "muliplication failed, matrices do not match!\n" << rows << "X" << columns << " with " << m.rows << "X" << m.columns << "\n";
			return *this;
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] *= m.elements[i][j];
			}
		}
		return *this;
	}






	inline static CMatrix<T> multHadamard(CMatrix<T>& m1, CMatrix<T>& m2)
	{
		if (m1.rows != m2.rows || m1.columns != m2.columns)
		{
			std::cout << "muliplication failed, matrices do not match!\n" << m1.rows << "X" << m1.columns << " with " << m2.rows << "X" << m2.columns << "\n";
			return CMatrix<T>(0,0);
		}

		CMatrix<T> result(m1.rows, m1.columns);

		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m1.columns; j++)
			{
				result.elements[i][j] = m1.elements[i][j] * m2.elements[i][j];
			}
		}
		return result;
	}

	




	inline CMatrix<T> divHadamard(CMatrix<T>& m)
	{
		if (rows != m.rows || columns != m.columns)
		{
			std::cout << "dividing failed, matrices do not match!\n" << rows << "X" << columns << " with " << m.rows << "X" << m.columns << "\n";
			return *this;
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] /= m.elements[i][j];
			}
		}
		return *this;
	}





	inline static CMatrix<T> divHadamard(CMatrix<T>& m1, CMatrix<T>& m2)
	{
		if (m1.rows != m2.rows || m1.columns != m2.columns)
		{
			std::cout << "dividing failed, matrices do not match!\n" << m1.rows << "X" << m1.columns << " with " << m2.rows << "X" << m2.columns << "\n";
			return CMatrix<T>(0, 0);
		}

		CMatrix<T> result(m1.rows, m1.columns);

		for (int i = 0; i < m1.rows; i++)
		{
			for (int j = 0; j < m1.columns; j++)
			{
				result.elements[i][j] = m1.elements[i][j] / m2.elements[i][j];
			}
		}
		return result;
	}






	inline CMatrix<T> div(T v)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				elements[i][j] /= v;
			}
		}
		return *this;
	}






	inline static CMatrix<T> fromArray(T* arr, int r, int c)
	{
		CMatrix<T> m(r, c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m.elements[i][j] = arr[c * i + j];
			}
		}
		return m;
	}





	inline static CMatrix<T> fromArray(T** arr, int r, int c)
	{
		CMatrix<T> m(r, c);
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				m.elements[i][j] = arr[i][j];
			}
		}
	}







	inline CMatrix<T> addRow(T* arr, int c)
	{
		if (c != this->columns)
		{
			std::cout << "adding row failed, dimensions do not match." << c << " columns to " << columns << "columns\n";
			return *this;
		}
		rows++;
		T** elem = new T*[rows];
		for (int i = 0; i < rows-1; i++)
		{
			elem[i] = elements[i];
		}
		elem[rows - 1] = new T[c];
		for (int i = 0; i < c; i++)
		{
			elem[rows - 1][i] = arr[i];
		}
		delete[] elements;
		elements = elem;

		return *this;
		
	}






	inline static CMatrix<T> addRow(CMatrix<T>& m, T* arr, int c)
	{
		if (c != m.columns)
		{
			std::cout << "adding row failed, dimensions do not match." << c << " columns to " << m.columns << "columns\n";
			return CMatrix(0,0);
		}
		CMatrix<T> result(m.rows + 1, m.columns);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				result.elements[i][j] = m.elements[i][j];
			}
		}

		for (int i = 0; i < m.columns; i++)
		{
			result.elements[result.rows - 1][i] = arr[i];
		}
			
		return result;
	}







	inline CMatrix<T> removeRow(int num)    //num is not an index
	{
		if (rows < num || num < 1)
		{
			std::cout << "removing row failed, the row number " << num << " does not exist. the number is NOT an index!\n";
			return *this;
		}
		rows--;
		int index = num - 1;
		T** elem = new T* [rows];

		int offset = 0;
		for (int i = 0; i < rows; i++)
		{
			if (index != i)
				elem[i] = elements[i + offset];
			else 
			{
				offset = 1;
				elem[i] = elements[i + offset];
			}
		}

		delete[] elements[index];
		delete[] elements;
		elements = elem;
		std::cout << "hier\n";
		return *this;
	}






	inline static CMatrix<T> removeRow(CMatrix<T>& m, int num)		 //num is not an index
	{
		if (m.rows < num || num < 1)
		{
			std::cout << "removing row failed, the row number " << num << " does not exist. the number is NOT an index!\n";
			return CMatrix(0,0);
		}
		int index = num - 1;
		int offset = 0;
		CMatrix<T> result(m.rows-1, m.columns);
		for (int i = 0; i < result.rows; i++)
		{
			if (i != index)
			{
				for (int j = 0; j < result.columns; j++)
				{
					result.elements[i][j] = m.elements[i+offset][j];
				}
			}
			else
			{
				offset = 1;
				for (int j = 0; j < result.columns; j++)
				{
					result.elements[i][j] = m.elements[i+offset][j];
				}
			}
			
		}
			
		return result;
	}




	inline void removeRowGetRow(int num, T* arr)    //num is not an index
	{
		if (rows < num || num < 1)
		{
			std::cout << "removing row failed, the row number " << num << " does not exist. the number is NOT an index!\n";
		}
		rows--;
		int index = num - 1;
		T** elem = new T * [rows];
		int offset = 0;
		for (int i = 0; i < rows; i++)
		{
			if (index != i)
				elem[i] = elements[i + offset];
			else
			{
				offset = 1;
				elem[i] = elements[i + offset];
			}
		}
		for (int i = 0; i < columns; i++)
		{
			arr[i] = elements[index][i];
		}
		

		//delete[] elements[index];
		delete[] elements;
		elements = elem;
		
	}




	inline CMatrix<T> addColumn(T* arr, int r)
	{
		if (rows != r)
		{
			std::cout << "adding column failed, rows do not match. " << r << " to " << rows << " rows\n";
			return *this;
		}
		columns++;

		T** elem = new T*[rows];
		for (int i = 0; i < rows; i++)
		{
			elem[i] = new T[columns];
			for (int j = 0; j < columns - 1; j++)
				elem[i][j] = elements[i][j];
			elem[i][columns - 1] = arr[i];
		}

		for (int i = 0; i < rows; i++)
		{
			delete[] elements[i];
		}
		delete[] elements;
		elements = elem;

		return *this;
	}






	inline static CMatrix<T> addColumn(CMatrix<T>& m, T* arr, int r)
	{
		if (m.rows != r)
		{
			std::cout << "adding column failed, rows do not match. " << r << " to " << m.rows << " rows\n";
			return CMatrix(0,0);
		}
		CMatrix<T> result(m.rows, m.columns+1);

		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				result.elements[i][j] = m.elements[i][j];
			}
		}
		for (int i = 0; i < result.rows; i++)
		{
			result.elements[i][result.columns-1] = arr[i];
		}
		return result;
	}





	inline CMatrix<T> removeColumn(int num)          //num is not an index
	{
		if (columns < num || num < 1)
		{
			std::cout << "removing column failed, the column number " << num << " does not exist. the number is NOT an index!\n";
			return *this;
		}
		columns -= 1;
		int index = num - 1;
		T** elem = new T*[rows];
		int offset = 0;
		for (int i = 0; i < this->rows; i++)
		{
			elem[i] = new T[columns];
			offset = 0;
			for (int j = 0; j < this->columns; j++)
			{
				if (index == j) offset = 1;
				elem[i][j] = this->elements[i][j+offset];
			}
		}
		for (int i = 0; i < rows; i++)
		{
			delete[] elements[i];
		}
		delete[] elements;
		elements = elem;
		return *this;
	}



	



	inline static CMatrix<T> removeColumn(CMatrix<T>& m, int num)
	{
		if (m.columns < num || num < 1)
		{
			std::cout << "removing column failed, the column number " << num << " does not exist. the number is NOT an index!\n";
			return CMatrix<T>(0,0);
		}
		int index = num - 1;
		int offset = 0;
		CMatrix<T> result(m.rows, m.columns-1);
		for (int i = 0; i < result.rows; i++)
		{
			offset = 0;
			for (int j = 0; j < result.columns; j++)
			{
				if (index == j)
				{
					offset = 1;
				}
				result.elements[i][j] = m.elements[i][j + offset];
				
			}
		}
		return result;
	}





	inline void removeColumnGetColumn(int num, T* arr)          //num is not an index
	{
		if (columns < num || num < 1)
		{
			std::cout << "removing column failed, the column number " << num << " does not exist. the number is NOT an index!\n";
		}
		columns -= 1;
		int index = num - 1;
		T** elem = new T * [rows];
		int offset = 0;
		for (int i = 0; i < this->rows; i++)
		{
			elem[i] = new T[columns];
			offset = 0;
			for (int j = 0; j < this->columns; j++)
			{
				if (index == j) offset = 1;
				elem[i][j] = this->elements[i][j + offset];
			}
			arr[i] = elements[i][index];
		}
		for (int i = 0; i < rows; i++)
		{
			delete[] elements[i];
		}
		delete[] elements;
		elements = elem;

	}





	inline void set(T v, int row, int column)           // row and column are not indices
	{
		elements[row-1][column-1] = v;
	}


	inline T get(int row, int column)				// row and column are not indices
	{
		return elements[row-1][column-1];
	}





	inline CMatrix<T> randomize(T min, T max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis((double)min, (double)max);

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				this->elements[i][j] = (T)dis(gen);
				
			}
		}
		return *this;
	}




	inline void print() const
	{
		std::cout << toString() << std::endl;
	}




	inline std::string toString() const
	{
		using namespace std;
		std::string result = "";
		for (int i = 0; i < rows; i++)
		{
			result += "\n";
			for (int j = 0; j < columns; j++)
			{
				result += to_string(elements[i][j]) + "|" + "\t";
			}
		}
		result += "\n";
		return result;
	}






	private:
		inline void overwrite(CMatrix<T> fresh) const
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] elements[i];
			}
			delete[] elements;
			rows = fresh.rows;
			columns = fresh.columns;
			elements = fresh.elements;
		}



};