#pragma once

template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher
{
public:
   using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, const ExtraArgType&) const;

   virtual void CallConstMemberFunctionForEachElement(
      const std::vector<ElementType>& elements,
      ConstMemberFunctionType constMemberFunction,
      const ClassType* constClassPointer,
      const ExtraArgType& extraArg) const
   {
      for (const ElementType& element : elements)
      {
         (constClassPointer->*constMemberFunction)(element, extraArg);
      }
   }

   virtual ~OneExtraArgMemberFunctionForEacher() = default;
};
