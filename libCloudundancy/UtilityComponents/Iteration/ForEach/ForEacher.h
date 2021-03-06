#pragma once

template<typename CollectionType, typename FunctionType>
class ForEacher
{
public:
   ForEacher() {}

   virtual void ForEach(const CollectionType& collection, FunctionType func) const
   {
      const auto collectionConstEnd = collection.cend();
      for (auto iter = collection.cbegin(); iter != collectionConstEnd; ++iter)
      {
         const auto& element = *iter;
         func(element);
      }
   }

   virtual ~ForEacher() = default;
};
