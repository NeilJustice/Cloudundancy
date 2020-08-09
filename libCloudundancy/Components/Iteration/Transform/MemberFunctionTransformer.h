#pragma once

template<typename ClassType, typename ElementType, typename TransformedElementType>
class MemberFunctionTransformer
{
public:
   virtual vector<TransformedElementType> Transform(
      const vector<ElementType>& elements,
      const ClassType* classInstance,
      TransformedElementType(ClassType::*transformer)(const ElementType&) const) const
   {
      vector<TransformedElementType> transformedElements;
      transformedElements.reserve(elements.size());
      for (const ElementType& element : elements)
      {
         const TransformedElementType transformedElement = (classInstance->*transformer)(element);
         transformedElements.push_back(transformedElement);
      }
      return transformedElements;
   }

   virtual ~MemberFunctionTransformer() = default;
};
