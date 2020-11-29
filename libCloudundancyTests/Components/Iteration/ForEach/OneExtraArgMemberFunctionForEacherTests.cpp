#include "pch.h"
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberFunctionForEacher.h"

template<typename ElementType, typename Arg2Type>
TEMPLATE_TESTS(OneExtraArgMemberFunctionForEacherTests, ElementType, Arg2Type)
AFACT(TwoArgMemberFunctionForEach_EmptyCollection_DoesNotCallFunc)
AFACT(TwoArgMemberFunctionForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
AFACT(TwoArgMemberFunctionForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
AFACT(CodeCoverage_ClassTypeTwoArgFunction)
EVIDENCE

class ClassType
{
public:
   virtual void TwoArgFunction(ElementType, Arg2Type) const {}
   virtual ~ClassType() = default;
};

class ClassTypeMock : public Metal::Mock<ClassType>
{
public:
   vector<ElementType> vec;
   METALMOCK_VOID2_CONST(TwoArgFunction, ElementType, Arg2Type)
};

using OneExtraArgMemberFunctionForEacherType = OneExtraArgMemberFunctionForEacher<
   ElementType, void (ClassType::*)(ElementType, Arg2Type) const, ClassType, Arg2Type>;

OneExtraArgMemberFunctionForEacherType _oneExtraArgMemberFunctionForEacher;

TEST(TwoArgMemberFunctionForEach_EmptyCollection_DoesNotCallFunc)
{
   const ClassTypeMock classInstance{};
   _oneExtraArgMemberFunctionForEacher.OneExtraArgMemberFunctionForEach(classInstance.vec, &ClassType::TwoArgFunction, &classInstance, 0);
}

TEST(TwoArgMemberFunctionForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
{
   ClassTypeMock classInstance;
   classInstance.vec = { 1 };
   classInstance.TwoArgFunctionMock.Expect();
   //
   _oneExtraArgMemberFunctionForEacher.OneExtraArgMemberFunctionForEach(classInstance.vec, &ClassType::TwoArgFunction, &classInstance, 10);
   //
   classInstance.TwoArgFunctionMock.CalledOnceWith(1, 10);
}

TEST(TwoArgMemberFunctionForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
{
   ClassTypeMock classInstance;
   classInstance.vec = { 1, 2 };
   classInstance.TwoArgFunctionMock.Expect();
   //
   _oneExtraArgMemberFunctionForEacher.OneExtraArgMemberFunctionForEach(classInstance.vec, &ClassType::TwoArgFunction, &classInstance, 20);
   //
   classInstance.TwoArgFunctionMock.CalledAsFollows(
   {
      { 1, 20 },
      { 2, 20 }
   });
}

TEST(CodeCoverage_ClassTypeTwoArgFunction)
{
   const ClassType classType;
   classType.TwoArgFunction(ElementType{}, Arg2Type{});
};

RUN_TEMPLATE_TESTS(OneExtraArgMemberFunctionForEacherTests, int, int)
THEN_RUN_TEMPLATE_TESTS(OneExtraArgMemberFunctionForEacherTests, double, char)
