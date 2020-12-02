#pragma once
#ifdef __linux__
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"
#include <atomic>
#include <cxxabi.h>
#endif

class Type
{
   friend class TypeTests;
private:
   // Demangling is expensive so this demangled type name cache exists
   static std::unordered_map<const char*, std::string> s_mangledToDemangledTypeName;
public:
   static string GetExceptionClassNameAndMessage(const exception* ex);

   template<typename T>
   static const std::string* GetName(const T& variable)
   {
      return TypeInfoToTypeName(typeid(variable));
   }

   template<typename T>
   static const std::string* GetName()
   {
      return TypeInfoToTypeName(typeid(T));
   }
private:
   static const std::string* TypeInfoToTypeName(const std::type_info& typeInfo);
#ifdef __linux__
   static std::string Demangle(const char* mangledTypeName);
#elif _WIN32
   static std::string Demangle(const char* mangledTypeName);
#endif
};
