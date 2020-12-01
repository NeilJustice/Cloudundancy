#pragma once

template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher
{
public:
   using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, ExtraArgType) const;

   virtual void CallConstMemberFunctionForEachElement(
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

   virtual ~OneExtraArgMemberFunctionForEacher() = default;
};
