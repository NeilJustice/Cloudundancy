#pragma once

namespace Utils
{
   template<typename ClassType, typename ElementType>
   class OneArgMemberFunctionForEacher
   {
   public:
      virtual ~OneArgMemberFunctionForEacher() = default;

      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&) const;

      virtual void CallConstMemberFunctionWithEachElement(
         const std::vector<ElementType>& elements,
         const ClassType* constClassPointer, ConstMemberFunctionType constMemberFunction) const
      {
         for (const ElementType& element : elements)
         {
            (constClassPointer->*constMemberFunction)(element);
         }
      }
   };
}
