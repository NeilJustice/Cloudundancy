#pragma once

template<typename ClassType, typename ElementType, typename TransformedElementType, typename Arg2Type>
class OneExtraArgMemberFunctionTransformer
{
public:
   virtual vector<TransformedElementType> Transform(
      const vector<ElementType>& elements,
      const ClassType* classInstance,
      TransformedElementType(ClassType::*transformer)(const ElementType&, Arg2Type) const,
      Arg2Type arg2) const
   {
      vector<TransformedElementType> transformedElements;
      transformedElements.reserve(elements.size());
      for (const ElementType& element : elements)
      {
         const TransformedElementType transformedElement = (classInstance->*transformer)(element, arg2);
         transformedElements.push_back(transformedElement);
      }
      return transformedElements;
   }

   virtual ~OneExtraArgMemberFunctionTransformer() = default;
};
