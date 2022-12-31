#include "pch.h"
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/ForEacher.h"

template<
   template<typename TT, typename...>
   class CollectionType,
   typename T>
TEMPLATE_TESTS(ForEacherTests, CollectionType, T)
AFACT(CallFunctionWithEachElement_EmptyCollection_DoesNotCallFunc)
AFACT(CallFunctionWithEachElement_OneElementCollection_CallsFunctionWithElement)
AFACT(CallFunctionWithEachElement_TwoElementCollection_CallsFunctionWithEachElement)
EVIDENCE

static void Function(const T& /*element*/)
{
}

static void ThrowsIfCalled(const T& /*element*/)
{
   throw runtime_error("Unexpectedly called");
}

using ForEacherType = Utils::ForEacher<CollectionType<T>, void (*)(const T&)>;
ForEacherType _forEacher;

TEST(CallFunctionWithEachElement_EmptyCollection_DoesNotCallFunc)
{
   const CollectionType<T> emptyEollection{};
   //
   DOES_NOT_THROW(_forEacher.CallFunctionWithEachElement(emptyEollection, ThrowsIfCalled));
   //
   THROWS_EXCEPTION(ThrowsIfCalled(T()), runtime_error, "Unexpectedly called"); // Code coverage
   Function(0); // Code coverage
}

TEST(CallFunctionWithEachElement_OneElementCollection_CallsFunctionWithElement)
{
   const CollectionType<T> collection = { 1 };

   METALMOCK_VOID1_STATIC(ForEacherTests, Function, const T&);
   FunctionMock.Expect();
   function<void(const T&)>_call_Function = BIND_1ARG_METALMOCK_OBJECT(FunctionMock);

   Utils::ForEacher<CollectionType<T>, decltype(_call_Function)> forEacher;
   //
   forEacher.CallFunctionWithEachElement(collection,_call_Function);
   //
   METALMOCK(FunctionMock.CalledOnceWith(1));
}

TEST(CallFunctionWithEachElement_TwoElementCollection_CallsFunctionWithEachElement)
{
   const CollectionType<T> collection = { 1, 2 };

   METALMOCK_VOID1_STATIC(ForEacherTests, Function, const T&);
   FunctionMock.Expect();
   function<void(const T&)>_call_Function = BIND_1ARG_METALMOCK_OBJECT(FunctionMock);

   Utils::ForEacher<CollectionType<T>, decltype(_call_Function)> forEacher;
   //
   forEacher.CallFunctionWithEachElement(collection,_call_Function);
   //
   METALMOCK(FunctionMock.CalledAsFollows({ 1, 2 }));
}

RUN_TEMPLATE_TESTS(ForEacherTests, vector, int)
THEN_RUN_TEMPLATE_TESTS(ForEacherTests, vector, double)
THEN_RUN_TEMPLATE_TESTS(ForEacherTests, set, int)
THEN_RUN_TEMPLATE_TESTS(ForEacherTests, set, double)
