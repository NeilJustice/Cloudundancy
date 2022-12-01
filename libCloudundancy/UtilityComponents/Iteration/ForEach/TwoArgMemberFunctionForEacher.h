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
         ConstMemberFunctionType constMemberFunction,
         const ClassType* constClassPointer,
         ExtraArgType extraArg) const
      {
         for (const ElementType& element : elements)
         {
            (constClassPointer->*constMemberFunction)(element, extraArg);
         }
      }

      virtual ~TwoArgMemberFunctionForEacher() = default;
   };
}