#pragma once
#if defined __linux__ || defined __APPLE__
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
#if defined __linux__ || defined __APPLE__
   static std::string Demangle(const char* mangledTypeName);
#elif _WIN32
   static std::string Demangle(const char* mangledTypeName);
#endif
};
