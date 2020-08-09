#pragma once

template<typename T, typename ClassType, typename MemberFunctionType, typename ExtraArgType>
class OneExtraArgMemberForEacher
{
public:
   OneExtraArgMemberForEacher() noexcept = default;

   virtual void OneExtraArgMemberForEach(
      const std::vector<T>& elements,
      const ClassType* constClassPointer,
      MemberFunctionType constMemberFunction,
      ExtraArgType extraArg) const
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
