#pragma once
#include "Include.h"
template<typename T>
class CVector
{



private:
	int count;
	T* elements;



public:

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




	

	inline CVector<T>(const CVector<T>& other) 
	{
		count = other.count;
		elements = new T[count];
		for (int i = 0; i < count; i++)
		{
			elements[i] = other.elements[i];
		}
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
	









	inline ~CVector()
	{
		delete[] elements;
	}




	inline T get(int index)
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


	


	inline CVector<T>* add(CVector<T>* vec)
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


	inline CVector<T>* add(T v)
	{
		
		for (int i = 0; i < count; i++)
		{
			elements[i] += v;
		}
		return this;
	}


	inline CVector<T>* sub(CVector<T>* vec)
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


	inline CVector<T>* sub(T v)
	{
		
		for (int i = 0; i < count; i++)
		{
			elements[i] -= v;
		}
		return this;
	}




	inline static CVector<T>* sub(CVector<T>* vec1, CVector<T>* vec2)
	{
		if (vec1->count != vec2->count) return nullptr;

		CVector<T>* result = new CVector<T>({0});
		delete[] result->elements;
		result->elements = new T[vec1->count];
		result->count = vec1->count;

		for (int i = 0; i < vec1->count; i++)
		{
			result->elements[i] = vec1->elements[i] - vec2->elements[i];
		}

		return result;

	}




	inline static CVector<T>* sub(CVector<T>* vec1, T v)
	{

		CVector<T>* result = new CVector<T>({ 0 });
		delete[] result->elements;
		result->elements = new T[vec1->count];
		result->count = vec1->count;

		for (int i = 0; i < vec1->count; i++)
		{
			result->elements[i] = vec1->elements[i] - v;
		}

		return result;

	}







	inline CVector<T>* mult(CVector<T>* vec)
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



	inline CVector<T>* mult(T s)
	{
		for (int i = 0; i < count; i++)
		{
			elements[i] *= s;
		}
		return this;
	}


	inline static CVector<T>* mult(CVector<T>* vec1, CVector<T>* vec2)
	{
		if (vec1->count != vec2->count) return nullptr;

		CVector<T>* result = new CVector<T>({0});
		delete[] result->elements;
		result->elements = new T[vec1->count];
		result->count = vec1->count;
		for (int i = 0; i < vec1->count; i++)
		{
			result->elements[i] = vec1->elements[i] * vec2->elements[i];
		}
		return result;
	}



	inline static CVector<T>* mult(const CVector<T>* vec1, T s)
	{

		CVector<T>* result = new CVector<T>({ 0 });
		delete[] result->elements;
		result->elements = new T[vec1->count];
		result->count = vec1->count;
		for (int i = 0; i < vec1->count; i++)
		{
			result->elements[i] = vec1->elements[i] * s;
		}
		return result;
	}


};



