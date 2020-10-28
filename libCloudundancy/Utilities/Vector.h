#pragma once

class Vector
{
public:
	static std::vector<std::string> ArgcArgvToStringVector(int argc, char** argv);

	template<typename T>
	static std::string Join(const std::vector<T>& vec, char separator)
	{
      const size_t vectorSize = vec.size();
		if (vectorSize == 0)
		{
			return std::string();
		}
		std::ostringstream oss;
		for (size_t i = 0; i < vectorSize; ++i)
		{
			const T& element = vec[i];
			oss << element;
			if (i < vectorSize - 1)
			{
				oss << separator;
			}
		}
      const std::string joinedVectorString = oss.str();
		return joinedVectorString;
	}

   template<typename T>
	static std::string ReverseJoin(const std::vector<T>& vec, char separator)
	{
      const size_t vectorSize = vec.size();
		if (vectorSize == 0)
		{
			return std::string();
		}
		std::ostringstream oss;
		for (int i = static_cast<int>(vectorSize - 1); i >= 0; --i)
		{
			const T& element = vec[i];
			oss << element;
			if (i > 0)
			{
				oss << separator;
			}
		}
      const std::string joinedVectorString = oss.str();
		return joinedVectorString;
	}

   template<typename T>
   static std::string ReverseToStringJoin(const std::vector<T>& vec, char separator)
   {
      const size_t vectorSize = vec.size();
      if (vectorSize == 0)
      {
         return std::string();
      }
      std::ostringstream oss;
      for (int i = static_cast<int>(vectorSize - 1); i >= 0; --i)
      {
         const T& element = vec[i];
         const string elementAsString = element.ToString();
         if (i > 0)
         {
            oss << separator;
         }
      }
      const std::string joinedVectorString = oss.str();
      return joinedVectorString;
   }

	template<typename T>
	static bool Contains(const std::vector<T> v, const T& element)
	{
      const size_t size = v.size();
		for (size_t i = 0; i < size; ++i)
		{
			const T& vectorElement = v[i];
			if (vectorElement == element)
			{
				return true;
			}
		}
		return false;
	}
};
