#include "pch.h"
#include "libCloudundancy/Components/Iteration/ForEach/MemberFunctionForEacher.h"

template<typename ElementType>
TEMPLATE_TESTS(MemberFunctionForEacherTests, ElementType)
AFACT(CallConstMemberFunctionWithEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
AFACT(CallConstMemberFunctionWithEachElement_TwoElementsVector_CallsMemberFunctionForEachEachElement)
AFACT(CodeCoverage_ClassType_ConstMemberFunctionFunction)
EVIDENCE

class ClassType
{
public:
   virtual void ConstMemberFunctionFunction(const ElementType&) const {}
   virtual ~ClassType() = default;
};

class ClassTypeMock : public Metal::Mock<ClassType>
{
public:
   vector<ElementType> elements;
   METALMOCK_VOID1_CONST(ConstMemberFunctionFunction, const ElementType&)
};

Utils::MemberFunctionForEacher<ClassType, ElementType> _memberFunctionForEacher;

TEST(CallConstMemberFunctionWithEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
{
   const ClassTypeMock classInstance{};
   _memberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      classInstance.elements, &ClassType::ConstMemberFunctionFunction, &classInstance);
}

TEST(CallConstMemberFunctionWithEachElement_TwoElementsVector_CallsMemberFunctionForEachEachElement)
{
   ClassTypeMock classInstance{};
   const ElementType element1 = ZenUnit::Random<ElementType>();
   const ElementType element2 = ZenUnit::Random<ElementType>();
   classInstance.elements = { element1, element2 };
   classInstance.ConstMemberFunctionFunctionMock.Expect();
   //
   _memberFunctionForEacher.CallConstMemberFunctionWithEachElement(
      classInstance.elements, &ClassType::ConstMemberFunctionFunction, &classInstance);
   //
   METALMOCK(classInstance.ConstMemberFunctionFunctionMock.CalledNTimes(2));
   METALMOCKTHEN(classInstance.ConstMemberFunctionFunctionMock.CalledWith(element1)).Then(
   METALMOCKTHEN(classInstance.ConstMemberFunctionFunctionMock.CalledWith(element2)));
}

TEST(CodeCoverage_ClassType_ConstMemberFunctionFunction)
{
   const ClassType classType{};
   classType.ConstMemberFunctionFunction(ElementType{});
}

RUN_TEMPLATE_TESTS(MemberFunctionForEacherTests, int)
THEN_RUN_TEMPLATE_TESTS(MemberFunctionForEacherTests, string)
