#pragma once

namespace Utils
{
   template<typename ClassType, typename ElementType>
   class MemberFunctionForEacher
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&) const;

      virtual void CallConstMemberFunctionForEachElement(
         const std::vector<ElementType>& elements,
         ConstMemberFunctionType constMemberFunction,
         const ClassType* constClassPointer) const
      {
         for (const ElementType& element : elements)
         {
            (constClassPointer->*constMemberFunction)(element);
         }
      }

      virtual ~MemberFunctionForEacher() = default;
   };
}