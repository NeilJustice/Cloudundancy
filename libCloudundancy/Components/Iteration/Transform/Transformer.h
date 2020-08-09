#pragma once

template<typename T, typename TransformedT>
class Transformer
{
public:
   virtual std::vector<TransformedT> Transform(
      const std::vector<T>& source, TransformedT(*transformer)(const T&)) const
   {
      const size_t sourceSize = source.size();
      std::vector<TransformedT> dest(sourceSize);
      for (size_t i = 0; i < sourceSize; ++i)
      {
         const T& element = source[i];
         dest[i] = transformer(element);
      }
      return dest;
   }

   virtual ~Transformer() = default;
};
