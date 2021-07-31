#pragma once

template<
   typename TransformedContainerType,
   typename SourceContainerType,
   typename TransformFunctionType,
   typename ExtraArgType>
class OneExtraArgTransformer
{
public:
   virtual TransformedContainerType Transform(
      const SourceContainerType& sourceContainer,
      TransformFunctionType transformFunction,
      ExtraArgType extraArg) const
   {
      TransformedContainerType transformedElements{};
      transformedElements.reserve(sourceContainer.size());
      const auto endSourceIter = sourceContainer.end();
      size_t index = 0;
      for (auto iter = sourceContainer.begin(); iter != endSourceIter; ++iter)
      {
         const auto& sourceElement = *iter;
         auto transformedElement = transformFunction(index++, sourceElement, extraArg);
         transformedElements.emplace_back(std::move(transformedElement));
      }
      return transformedElements;
   }

   virtual ~OneExtraArgTransformer() = default;
};
