#include "pch.h"
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/TwoArgMemberFunctionForEacher.h"

template<typename ElementType, typename Arg2Type>
TEMPLATE_TESTS(TwoArgMemberFunctionForEacherTests, ElementType, Arg2Type)
AFACT(CallConstMemberFunctionWithEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
AFACT(CallConstMemberFunctionWithEachElement_TwoElementsVector_CallsThisPointerBoundFuncTwice)
AFACT(CodeCoverage_ClassType_TwoArgConstMemberFunctionFunction)
EVIDENCE

class ClassType
{
public:
   virtual void TwoArgConstMemberFunctionFunction(const ElementType&, Arg2Type) const
   {
   }
   virtual ~ClassType() = default;
};

class ClassTypeMock : public Metal::Mock<ClassType>
{
public:
   vector<ElementType> elements;
   METALMOCK_VOID2_CONST(TwoArgConstMemberFunctionFunction, const ElementType&, Arg2Type)
};

Utils::TwoArgMemberFunctionForEacher<ClassType, ElementType, Arg2Type> _twoArgMemberFunctionForEacher;

TEST(CallConstMemberFunctionWithEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
{
   const ClassTypeMock classInstanceMock{};
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      classInstanceMock.elements, &classInstanceMock,
      &ClassType::TwoArgConstMemberFunctionFunction, ZenUnit::Random<Arg2Type>());
}

TEST(CallConstMemberFunctionWithEachElement_TwoElementsVector_CallsThisPointerBoundFuncTwice)
{
   ClassTypeMock classInstanceMock{};
   const ElementType element1 = ZenUnit::Random<ElementType>();
   const ElementType element2 = ZenUnit::Random<ElementType>();
   classInstanceMock.elements = { element1, element2 };
   classInstanceMock.TwoArgConstMemberFunctionFunctionMock.Expect();
   const Arg2Type extraArg = ZenUnit::Random<Arg2Type>();
   //
   _twoArgMemberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      classInstanceMock.elements, &classInstanceMock,
      &ClassType::TwoArgConstMemberFunctionFunction, extraArg);
   //
   classInstanceMock.TwoArgConstMemberFunctionFunctionMock.CalledAsFollows(
   {
      { element1, extraArg },
      { element2, extraArg }
   });
}

TEST(CodeCoverage_ClassType_TwoArgConstMemberFunctionFunction)
{
   const ClassType classInstance{};
   classInstance.TwoArgConstMemberFunctionFunction(ElementType{}, Arg2Type{});
};

RUN_TEMPLATE_TESTS(TwoArgMemberFunctionForEacherTests, int, int)
THEN_RUN_TEMPLATE_TESTS(TwoArgMemberFunctionForEacherTests, double, char)
