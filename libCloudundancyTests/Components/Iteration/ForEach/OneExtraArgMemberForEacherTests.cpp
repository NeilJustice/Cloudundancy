#include "pch.h"
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberForEacher.h"

template<typename ElementType, typename Arg2Type>
TEMPLATE_TESTS(OneExtraArgMemberForEacherTests, ElementType, Arg2Type)
AFACT(TwoArgMemberForEach_EmptyCollection_DoesNotCallFunc)
AFACT(TwoArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
AFACT(TwoArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
AFACT(CodeCoverage_ClassTypeTwoArgFunction)
EVIDENCE

class ClassType
{
public:
   virtual void TwoArgFunction(ElementType, Arg2Type) const {}
   virtual ~ClassType() = default;
};

class ClassTypeMock : public Zen::Mock<ClassType>
{
public:
   vector<ElementType> vec;
   ZENMOCK_VOID2_CONST(TwoArgFunction, ElementType, Arg2Type)
};

using OneExtraArgMemberForEacherType = OneExtraArgMemberForEacher<
   ElementType, ClassType, void (ClassType::*)(ElementType, Arg2Type) const, Arg2Type>;

OneExtraArgMemberForEacherType _oneExtraArgMemberForEacher;

TEST(TwoArgMemberForEach_EmptyCollection_DoesNotCallFunc)
{
   const ClassTypeMock classInstance{};
   _oneExtraArgMemberForEacher.OneExtraArgMemberForEach(classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 0);
}

TEST(TwoArgMemberForEach_OneItemCollection_CallsThisPointerBoundFuncOnce)
{
   ClassTypeMock classInstance;
   classInstance.vec = { 1 };
   classInstance.TwoArgFunctionMock.Expect();
   //
   _oneExtraArgMemberForEacher.OneExtraArgMemberForEach(classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 10);
   //
   classInstance.TwoArgFunctionMock.CalledOnceWith(1, 10);
}

TEST(TwoArgMemberForEach_TwoItemCollection_CallsThisPointerBoundFuncTwice)
{
   ClassTypeMock classInstance;
   classInstance.vec = { 1, 2 };
   classInstance.TwoArgFunctionMock.Expect();
   //
   _oneExtraArgMemberForEacher.OneExtraArgMemberForEach(classInstance.vec, &classInstance, &ClassType::TwoArgFunction, 20);
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

RUN_TEMPLATE_TESTS(OneExtraArgMemberForEacherTests, int, int)
THEN_RUN_TEMPLATE_TESTS(OneExtraArgMemberForEacherTests, double, char)
