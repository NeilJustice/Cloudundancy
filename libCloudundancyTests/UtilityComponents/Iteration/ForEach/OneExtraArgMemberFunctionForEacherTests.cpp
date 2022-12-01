#include "pch.h"
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/OneExtraArgMemberFunctionForEacher.h"

template<typename ElementType, typename ExtraArgType>
TEMPLATE_TESTS(OneExtraArgMemberFunctionForEacherTests, ElementType, ExtraArgType)
AFACT(CallConstMemberFunctionWithEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
AFACT(CallConstMemberFunctionWithEachElement_TwoElementsVector_CallsThisPointerBoundFuncTwice)
AFACT(CodeCoverage_ClassType_TwoArgConstMemberFunctionFunction)
EVIDENCE

class ClassType
{
public:
   virtual void TwoArgConstMemberFunctionFunction(const ElementType&, ExtraArgType) const
   {
   }
   virtual ~ClassType() = default;
};

class ClassTypeMock : public Metal::Mock<ClassType>
{
public:
   vector<ElementType> elements;
   METALMOCK_VOID2_CONST(TwoArgConstMemberFunctionFunction, const ElementType&, ExtraArgType)
};

Utils::OneExtraArgMemberFunctionForEacher<ClassType, ElementType, ExtraArgType> _oneExtraArgMemberFunctionForEacher;

TEST(CallConstMemberFunctionWithEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
{
   const ClassTypeMock classInstance{};
   _oneExtraArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      classInstance.elements, &ClassType::TwoArgConstMemberFunctionFunction, &classInstance, ZenUnit::Random<ExtraArgType>());
}

TEST(CallConstMemberFunctionWithEachElement_TwoElementsVector_CallsThisPointerBoundFuncTwice)
{
   ClassTypeMock classInstance{};
   const ElementType element1 = ZenUnit::Random<ElementType>();
   const ElementType element2 = ZenUnit::Random<ElementType>();
   classInstance.elements = { element1, element2 };
   classInstance.TwoArgConstMemberFunctionFunctionMock.Expect();
   const ExtraArgType extraArg = ZenUnit::Random<ExtraArgType>();
   //
   _oneExtraArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      classInstance.elements, &ClassType::TwoArgConstMemberFunctionFunction, &classInstance, extraArg);
   //
   classInstance.TwoArgConstMemberFunctionFunctionMock.CalledAsFollows(
   {
      { element1, extraArg },
      { element2, extraArg }
   });
}

TEST(CodeCoverage_ClassType_TwoArgConstMemberFunctionFunction)
{
   const ClassType classType{};
   classType.TwoArgConstMemberFunctionFunction(ElementType{}, ExtraArgType{});
};

RUN_TEMPLATE_TESTS(OneExtraArgMemberFunctionForEacherTests, int, int)
THEN_RUN_TEMPLATE_TESTS(OneExtraArgMemberFunctionForEacherTests, double, char)
