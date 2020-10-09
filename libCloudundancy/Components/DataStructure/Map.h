#pragma once

class Map
{
public:
	template<
		template<typename...>
		typename MapType,
		typename KeyType, typename ValueType, typename... Types>
		static const ValueType& At(const MapType<KeyType, ValueType, Types...>& m, const KeyType& key)
	{
		try
		{
			const ValueType& value = m.at(key);
			return value;
		}
		// When std::map::at() throws out_of_range, its what() text reads just "key not found",
		// not including in the message the key not found.
		catch (const std::out_of_range&)
		{
			ThrowKeyNotFound(key);
		}
	}

	template<typename MapType, typename KeyType>
	static bool ContainsKey(const MapType& m, const KeyType& key)
	{
      const bool keyIsInMap = m.find(key) != m.end();
		return keyIsInMap;
	}

	template<
      template<typename...>
      typename MapType,
      typename KeyType, typename ValueType>
	static pair<bool, ValueType> TryGetValue(const MapType<KeyType, ValueType>& m, const KeyType& key)
	{
      const typename MapType<KeyType, ValueType>::const_iterator findIter = m.find(key);
		if (findIter != m.end())
		{
         const pair<bool, ValueType> trueAndValueInMap = { true, findIter->second };
         return trueAndValueInMap;
		}
      const pair<bool, ValueType> falseAndDefaultValue = { false, ValueType{} };
      return falseAndDefaultValue;
	}

	template<typename MapType, typename KeyType, typename ValueType>
	static ValueType* ThrowingInsert(MapType& m, const KeyType& key, const ValueType& value)
	{
      const size_t sizeBeforeInsert = m.size();
      const auto insertedIter = m.insert(std::make_pair(key, value));
		m[key] = value;
      const size_t sizeAfterInsert = m.size();
		if (sizeAfterInsert == sizeBeforeInsert)
		{
			std::ostringstream whatBuilder;
			whatBuilder << "key already present in map: " << key;
         const std::string what = whatBuilder.str();
			throw std::invalid_argument(what);
		}
		ValueType* const valueInMap = &(*insertedIter.first).second;
		return valueInMap;
	}
private:
	template<typename KeyType>
	static
#ifdef __linux__
	__attribute__((noreturn))
#elif _WIN32
	__declspec(noreturn)
#endif
	void ThrowKeyNotFound(const KeyType& key)
	{
		std::ostringstream oss;
		oss << "Key not found in map: [" << key << "]";
      const std::string what(oss.str());
		throw std::out_of_range(what);
	}
};
