#include "pch.h"
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/MemberFunctionForEacher.h"

template<typename ElementType>
TEMPLATE_TESTS(MemberFunctionForEacherTests, ElementType)
AFACT(CallConstMemberFunctionForEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
AFACT(CallConstMemberFunctionForEachElement_TwoElementsVector_CallsMemberFunctionForEachEachElement)
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

MemberFunctionForEacher<ClassType, ElementType> _memberFunctionForEacher;

TEST(CallConstMemberFunctionForEachElement_EmptyElementsVector_DoesNotCallMemberFunction)
{
   const ClassTypeMock classInstance{};
   _memberFunctionForEacher.CallConstMemberFunctionForEachElement(
      classInstance.elements, &ClassType::ConstMemberFunctionFunction, &classInstance);
}

TEST(CallConstMemberFunctionForEachElement_TwoElementsVector_CallsMemberFunctionForEachEachElement)
{
   ClassTypeMock classInstance;
   const ElementType element1 = ZenUnit::Random<ElementType>();
   const ElementType element2 = ZenUnit::Random<ElementType>();
   classInstance.elements = { element1, element2 };
   classInstance.ConstMemberFunctionFunctionMock.Expect();
   //
   _memberFunctionForEacher.CallConstMemberFunctionForEachElement(
      classInstance.elements, &ClassType::ConstMemberFunctionFunction, &classInstance);
   //
   classInstance.ConstMemberFunctionFunctionMock.CalledAsFollows(
   {
      { element1 },
      { element2 }
   });
}

TEST(CodeCoverage_ClassType_ConstMemberFunctionFunction)
{
   const ClassType classType;
   classType.ConstMemberFunctionFunction(ElementType{});
};

RUN_TEMPLATE_TESTS(MemberFunctionForEacherTests, int)
THEN_RUN_TEMPLATE_TESTS(MemberFunctionForEacherTests, string)
