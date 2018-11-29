#ifndef __ARRAYT_H__
#define __ARRAYT_H__

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include <vector>
#include <functional>
#include <algorithm>


NS_CC_BEGIN

template<class T>
class ArrayT
{
public:


	/** Constructor. */
	ArrayT<T>(): _data()
	{
		static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::ArrayT<T>!");
	}


	/** Constructor with initializer list. */
	ArrayT<T>(std::initializer_list<T> list)
	{
		for (auto& element : list)
		{
			pushBack(element);
		}
	}

	/** Destructor. */
	~ArrayT<T>()
	{
		CCLOGINFO("In the destructor of ArrayT.");
		clear();
	}

	/** Copy constructor. */
	ArrayT<T>(const ArrayT<T>& other)
	{
		static_assert(std::is_convertible<T, Ref*>::value, "Invalid Type for cocos2d::ArrayT<T>!");
		CCLOGINFO("In the copy constructor!");
		_data = other._data;
		addRefForAllObjects();
	}


	ArrayT<T>& operator=(const ArrayT<T>& other)
	{
		if (this != &other) {
			CCLOGINFO("In the copy assignment operator!");
			clear();
			_data = other._data;
			addRefForAllObjects();
		}
		return *this;
	}

	void reserve(ssize_t n)
	{
		_data.reserve(n);
	}

	ssize_t size() const
	{
		return  _data.size();
	}

	/** @brief Returns whether the ArrayT is empty (i.e. whether its size is 0).
	 *  @note This function does not modify the container in any way. To clear the content of a ArrayT, see ArrayT<T>::clear.
	 */
	bool empty() const
	{
		return _data.empty();
	}

	/** Returns the maximum number of elements that the ArrayT can hold. */
	ssize_t max_size() const
	{
		return _data.max_size();
	}

	/** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
	ssize_t getIndex(T object) const
	{
		auto iter = std::find(_data.begin(), _data.end(), object);
		if (iter != _data.end())
			return iter - _data.begin();

		return -1;
	}

	/** @brief Find the object in the ArrayT.
	 *  @param object The object to find.
	 *  @return Returns an iterator which refers to the element that its value is equals to object.
	 *          Returns ArrayT::end() if not found.
	 */
	

	/** Returns the element at position 'index' in the ArrayT. */
	T at(ssize_t index) const
	{
		CCASSERT(index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
		return _data[index];
	}

	/** Returns the first element in the ArrayT. */
	T front() const
	{
		return _data.front();
	}

	/** Returns the last element of the ArrayT. */
	T back() const
	{
		return _data.back();
	}

	/** Returns a random element of the ArrayT. */
	T getRandomObject() const
	{
		if (!_data.empty())
		{
			ssize_t randIdx = RandomHelper::random_int<int>(0, static_cast<int>(_data.size()) - 1);
			return *(_data.begin() + randIdx);
		}
		return nullptr;
	}

	bool contains(T object) const
	{
		return(std::find(_data.begin(), _data.end(), object) != _data.end());
	}

	/**
	 * Checks whether two ArrayTs are equal.
	 */
	bool equals(const ArrayT<T> &other) const
	{
		ssize_t s = this->size();
		if (s != other.size())
			return false;

		for (ssize_t i = 0; i < s; i++)
		{
			if (this->at(i) != other.at(i))
			{
				return false;
			}
		}
		return true;
	}

	// Adds objects

	/** Adds a new element at the end of the ArrayT. */
	void pushBack(T object)
	{
		CCASSERT(object != nullptr, "The object should not be nullptr");
		_data.push_back(object);
		object->retain();
	}

	/** Push all elements of an existing ArrayT to the end of current ArrayT. */
	void pushBack(const ArrayT<T>& other)
	{
		for (const auto &obj : other) {
			_data.push_back(obj);
			obj->retain();
		}
	}

	void insert(ssize_t index, T object)
	{
		CCASSERT(index >= 0 && index <= size(), "Invalid index!");
		CCASSERT(object != nullptr, "The object should not be nullptr");
		_data.insert((std::begin(_data) + index), object);
		object->retain();
	}

	void popBack()
	{
		CCASSERT(!_data.empty(), "no objects added");
		auto last = _data.back();
		_data.pop_back();
		last->release();
	}


	void eraseObject(T object, bool removeAll = false)
	{
		CCASSERT(object != nullptr, "The object should not be nullptr");

		if (removeAll)
		{
			for (auto iter = _data.begin(); iter != _data.end();)
			{
				if ((*iter) == object)
				{
					iter = _data.erase(iter);
					object->release();
				}
				else
				{
					++iter;
				}
			}
		}
		else
		{
			auto iter = std::find(_data.begin(), _data.end(), object);
			if (iter != _data.end())
			{
				_data.erase(iter);
				object->release();
			}
		}
	}

	

	void clear()
	{
		for (auto& it : _data) {
			it->release();
		}
		_data.clear();
	}

	void swap(T object1, T object2)
	{
		ssize_t idx1 = getIndex(object1);
		ssize_t idx2 = getIndex(object2);

		CCASSERT(idx1 >= 0 && idx2 >= 0, "invalid object index");

		std::swap(_data[idx1], _data[idx2]);
	}

	/** Swap two elements by indexes. */
	void swap(ssize_t index1, ssize_t index2)
	{
		CCASSERT(index1 >= 0 && index1 < size() && index2 >= 0 && index2 < size(), "Invalid indices");

		std::swap(_data[index1], _data[index2]);
	}

	/** Replace value at index with given object. */
	void replace(ssize_t index, T object)
	{
		CCASSERT(index >= 0 && index < size(), "Invalid index!");
		CCASSERT(object != nullptr, "The object should not be nullptr");

		_data[index]->release();
		_data[index] = object;
		object->retain();
	}

	/** Reverses the ArrayT. */
	void reverse()
	{
		std::reverse(std::begin(_data), std::end(_data));
	}

	/** Requests the container to reduce its capacity to fit its size. */
	void shrinkToFit()
	{
		_data.shrink_to_fit();
	}

protected:

	/** Retains all the objects in the ArrayT */
	void addRefForAllObjects()
	{
		for (const auto &obj : _data) {
			obj->retain();
		}
	}

	ArrayT<T> _data;
};

// end of base group
/** @} */

NS_CC_END

#endif // __CCArrayT_H__