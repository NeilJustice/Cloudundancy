#pragma once

namespace Utils
{
   template<typename ClassType, typename ElementType, typename ExtraArgType>
   class TwoArgMemberFunctionForEacher
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, ExtraArgType) const;

      virtual void CallConstMemberFunctionWithEachElement(
         const std::vector<ElementType>& elements,
         const ClassType* constClassPointer,
         ConstMemberFunctionType constMemberFunction,
         ExtraArgType arg2) const
      {
         for (const ElementType& element : elements)
         {
            (constClassPointer->*constMemberFunction)(element, arg2);
         }
      }

      virtual ~TwoArgMemberFunctionForEacher() = default;
   };
}
