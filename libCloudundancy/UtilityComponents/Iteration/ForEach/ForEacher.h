#pragma once

namespace Utils
{
   template<typename CollectionType, typename FunctionType>
   class ForEacher
   {
   public:
      virtual void CallFunctionWithEachElement(const CollectionType& collection, FunctionType func) const
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
}
