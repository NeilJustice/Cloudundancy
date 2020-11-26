#pragma once

template<typename T, typename MemberFunctionType, typename ClassType, typename ExtraArgType>
class OneExtraArgMemberForEacher
{
public:
   virtual void OneExtraArgMemberForEach(
      const std::vector<T>& elements,
      MemberFunctionType constMemberFunction,
      const ClassType* constClassPointer, ExtraArgType extraArg) const
   {
      const typename std::vector<T>::const_iterator elementsEnd = elements.cend();
      for (typename std::vector<T>::const_iterator iter = elements.cbegin(); iter != elementsEnd; ++iter)
      {
         const T& element = *iter;
         (constClassPointer->*constMemberFunction)(element, extraArg);
      }
   }

   virtual ~OneExtraArgMemberForEacher() = default;
};
