#include "pch.h"
#include "libCloudundancy/Components/Iteration/Transform/OneExtraArgMemberFunctionTransformer.h"

template<typename ElementType, typename TransformedElementType, typename SecondArgType>
TEMPLATE_TESTS(OneExtraArgMemberFunctionTransformerTests, ElementType, TransformedElementType, SecondArgType)
AFACT(Transform_ElementsEmpty_DoesNotCallTransformFunction_ReturnsEmptyVector)
AFACT(Transform_TwoElements_CallsTransformFunctionOnEachElement_ReturnsTransformedElements)
EVIDENCE

#ifdef __linux__
OneExtraArgMemberFunctionTransformerTests()
{
}
#endif

class Class
{
public:
   mutable vector<pair<ElementType, SecondArgType>> calls;

   TransformedElementType ConstMemberFunctionThatThrowsIfCalled(const ElementType& element, SecondArgType secondArg) const
   {
      throw runtime_error("Expected call to ConstMemberFunctionThatThrows()");
   }

   TransformedElementType ConstMemberFunction(const ElementType& element, SecondArgType secondArg) const
   {
      calls.emplace_back(element, secondArg);
      const TransformedElementType transformedElement = static_cast<TransformedElementType>(element + ElementType{ 1 });
      return transformedElement;
   }
};

OneExtraArgMemberFunctionTransformer<
   Class, ElementType, TransformedElementType, SecondArgType> _oneExtraArgMemberFunctionTransformer;
const Class _classInstance;

TEST(Transform_ElementsEmpty_DoesNotCallTransformFunction_ReturnsEmptyVector)
{
   vector<ElementType> emptyElements;
   //
   const vector<TransformedElementType> transformedElements = _oneExtraArgMemberFunctionTransformer.Transform(
      emptyElements, &_classInstance, &Class::ConstMemberFunctionThatThrowsIfCalled, SecondArgType{});
   //
   IS_EMPTY(transformedElements);

   THROWS_EXCEPTION(_classInstance.ConstMemberFunctionThatThrowsIfCalled(ElementType{}, SecondArgType{}), runtime_error,
      "Expected call to ConstMemberFunctionThatThrows()"); // 100% code coverage
}

TEST(Transform_TwoElements_CallsTransformFunctionOnEachElement_ReturnsTransformedElements)
{
   vector<ElementType> elements = { ElementType{1}, ElementType{2} };
   const SecondArgType secondArg = ZenUnit::Random<SecondArgType>();
   //
   const vector<TransformedElementType> transformedElements = _oneExtraArgMemberFunctionTransformer.Transform(
      elements, &_classInstance, &Class::ConstMemberFunction, secondArg);
   //
   vector<pair<ElementType, SecondArgType>> expectedCalls =
   {
      { ElementType{1}, secondArg },
      { ElementType{2}, secondArg }
   };
   VECTORS_ARE_EQUAL(expectedCalls, _classInstance.calls);

   vector<TransformedElementType> expectedTransformedElements =
   {
      static_cast<TransformedElementType>(elements[0] + 1),
      static_cast<TransformedElementType>(elements[1] + 1)
   };
   VECTORS_ARE_EQUAL(expectedTransformedElements, transformedElements);
}

RUN_TEMPLATE_TESTS(OneExtraArgMemberFunctionTransformerTests, int, int, int)
THEN_RUN_TEMPLATE_TESTS(OneExtraArgMemberFunctionTransformerTests, unsigned long long, int, string)
