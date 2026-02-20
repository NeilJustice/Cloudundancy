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
         const ValueType& Value = m.at(key);
         return Value;
      }
      // When std::map::at() throws out_of_range, its what() text reads just "key not found",
      // not including in the message the key not found.
      catch (const std::out_of_range&)
      {
         ThrowKeyNotFound(key);
      }
   }

   template<typename MapType, typename KeyType, typename ValueType>
   static bool TryGetValue(const MapType& m, const KeyType& key, ValueType& outValue)
   {
      const typename MapType::const_iterator findIter = m.find(key);
      if (findIter != m.end())
      {
         outValue = findIter->second;
         return true;
      }
      return false;
   }

   Map() = delete;
private:
   template<typename KeyType>
   [[noreturn]] static void ThrowKeyNotFound(const KeyType& key)
   {
      std::ostringstream oss;
      oss << "Error: Key not found in map: [" << key << "]";
      const std::string what(oss.str());
      throw std::invalid_argument(what);
   }
};
