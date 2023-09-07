#pragma once
#include "Include.h"
template<typename T>
class CVector
{



private:
	int count;
	T* elements;
	


public:

	inline CVector<T>()
	{
		count = 0;
		elements = nullptr;
	}


	inline CVector<T>(std::initializer_list<T> values)
	{
		count = values.size();
		int counter = 0;
		elements = new T[values.size()];
		for (T v : values)
		{
			elements[counter] = v;
			counter++;
		}
	}


	inline CVector<T>(T x)
	{
		count = 1;
		elements = new T[1];
		elements[0] = x;
	}

	inline CVector<T>(T x, T y)
	{
		count = 2;
		elements = new T[2];
		elements[0] = x;
		elements[1] = y;
	}

	inline CVector<T>(T x, T y, T z)
	{
		count = 3;
		elements = new T[3];
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
	}



	

	inline CVector<T>(const CVector<T>& other) 
	{
		count = other.count;
		elements = new T[count];
		for (int i = 0; i < count; i++)
		{
			elements[i] = other.elements[i];
		}
	}



	inline ~CVector()
	{
		delete[] elements;
	}




	inline CVector<T>& operator=(const CVector<T>& other)
	{
		if (this != &other)
		{
			delete[] elements;
			count = other.count;
			elements = new T[count];
			for (int i = 0; i < count; i++)
			{
				elements[i] = other.elements[i];
			}
		}
		return *this;
	}


	friend inline std::ostream& operator<<(std::ostream& os, const CVector<T>& obj)
	{
		os << obj.toString();
		return os;
	}
	








	inline T get(int index) const
	{
		return elements[index];
	}




	inline void set(T v, int index)
	{
		elements[index] = v;
	}




	inline double getMag()
	{
		double result = 0;

		for (int i = 0; i < count; i++)
		{
			result += elements[i] * elements[i];
		}

		return std::sqrt(result);
	}



	inline void setMag(double mag)
	{
		normalize();
		this->mult(mag);

	}


	
	inline CVector<T>* normalize()
	{
		double mag = getMag();
		if (mag != 0) return this->mult(1 / mag);
		else
		{
			return this;
		}
	}




	inline static double dot(const CVector<T>* a, const CVector<T>* b)
	{
		if (a->count != b->count)
		{
			std::cout << "Dot Product not possible, Vectors do not match! " << a->count << " to " << b->count << "\n";
			return -1;
		}
		double dot = 0;
		for (int i = 0; i < a->count; i++)
		{
			dot += a->elements[i] * b->elements[i];
		}
		return dot;
	}



	inline double dot(const CVector<T>* vec)
	{
		if (count != vec->count)
		{
			std::cout << "Dot Product not possible, Vectors do not match! " << count  << " to " << vec->count << "\n";
			return -1;
		}
		double dot = 0;
		for (int i = 0; i < count; i++)
		{
			dot += elements[i] * vec->elements[i];
		}
		return dot;
	}

	


	inline CVector<T>* add(const CVector<T>* vec)
	{
		if (vec->count != count)
		{
			std::cerr << "adding failed, vectors not match\n";
			return nullptr;
		}
		for (int i = 0; i < count; i++)
		{
			elements[i] += vec->elements[i];
		}
		return this;
	}


	inline CVector<T>* add(const T v)
	{
		
		for (int i = 0; i < count; i++)
		{
			elements[i] += v;
		}
		return this;
	}








	inline static CVector<T>* add(const CVector<T>* vec1, const CVector<T>* vec2, CVector<T>* target)
	{
		if (vec1->count != vec2->count) return nullptr;

		delete[] target->elements;
		target->elements = new T[vec1->count];
		target->count = vec1->count;

		for (int i = 0; i < vec1->count; i++)
		{
			target->elements[i] = vec1->elements[i] + vec2->elements[i];
		}

		return target;

	}




	inline static CVector<T>* add(const CVector<T>* vec1, const T v, CVector<T>* target)
	{
		delete[] target->elements;
		target->elements = new T[vec1->count];
		target->count = vec1->count;

		for (int i = 0; i < vec1->count; i++)
		{
			target->elements[i] = vec1->elements[i] + v;
		}

		return target;

	}








	inline CVector<T>* sub(const CVector<T>* vec)
	{
		if (vec->count != count)
		{
			std::cerr << "sub failed, vectors not match\n";
			return nullptr;
		}
		for (int i = 0; i < count; i++)
		{
			elements[i] -= vec->elements[i];
		}
		return this;

	}


	inline CVector<T>* sub(const T v)
	{
		
		for (int i = 0; i < count; i++)
		{
			elements[i] -= v;
		}
		return this;
	}




	inline static CVector<T>* sub(const CVector<T>* vec1, const CVector<T>* vec2, CVector<T>* target)
	{
		if (vec1->count != vec2->count) return nullptr;

		delete[] target->elements;
		target->elements = new T[vec1->count];
		target->count = vec1->count;

		for (int i = 0; i < vec1->count; i++)
		{
			target->elements[i] = vec1->elements[i] - vec2->elements[i];
		}

		return target;

	}




	inline static CVector<T>* sub(const CVector<T>* vec1, const T v, CVector<T>* target)
	{
		delete[] target->elements;
		target->elements = new T[vec1->count];
		target->count = vec1->count;

		for (int i = 0; i < vec1->count; i++)
		{
			target->elements[i] = vec1->elements[i] - v;
		}

		return target;

	}







	inline CVector<T>* mult(const CVector<T>* vec)
	{
		if (vec->count != count)
		{
			std::cerr << "mult failed, vectors not match\n";
			return nullptr;
		}
		for (int i = 0; i < count; i++)
		{
			elements[i] *= vec->elements[i];
		}
		return this;
	}



	inline CVector<T>* mult(const T s)
	{
		for (int i = 0; i < count; i++)
		{
			elements[i] *= s;
		}
		return this;
	}


	inline static CVector<T>* mult(const CVector<T>* vec1, const CVector<T>* vec2, CVector<T>* target)
	{
		if (vec1->count != vec2->count) return nullptr;

		delete[] target->elements;
		target->elements = new T[vec1->count];
		target->count = vec1->count;
		for (int i = 0; i < vec1->count; i++)
		{
			target->elements[i] = vec1->elements[i] * vec2->elements[i];
		}
		return target;
	}



	inline static CVector<T>* mult(const CVector<T>* vec1, const T s, CVector<T>* target)
	{
		delete[] target->elements;
		target->elements = new T[vec1->count];
		target->count = vec1->count;
		for (int i = 0; i < vec1->count; i++)
		{
			target->elements[i] = vec1->elements[i] * s;
		}
		return target;
	}



	inline CVector<T> randomize(const T min,  const T max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis((double)min, (double)max);

		for (int i = 0; i < count; i++)
		{
			this->elements[i] = (T)dis(gen);
		}
		return *this;
	}



	inline std::string toString() const
	{
		std::string result;
		result += "(";
		result += std::to_string(elements[0]);
		for (int i = 1; i < count; i++)
		{
			result += " , " + std::to_string(elements[i]);
		}
		result += ")";
		return result;
	}


};



