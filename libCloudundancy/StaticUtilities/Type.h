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
   static const std::string* TypeInfoToTypeName(const std::type_info& typeInfo)
   {
      const char* const mangledTypeName = typeInfo.name();
      const std::unordered_map<const char*, std::string>::const_iterator findIter
         = s_mangledToDemangledTypeName.find(mangledTypeName);
      if (findIter == s_mangledToDemangledTypeName.end())
      {
         const std::string demangledTypeName = Demangle(mangledTypeName);
         const std::pair<std::unordered_map<const char*, std::string>::const_iterator, bool>
            emplaceResult = s_mangledToDemangledTypeName.emplace(mangledTypeName, demangledTypeName);
         const std::string* const cachedDemangledTypeName = &emplaceResult.first->second;
         return cachedDemangledTypeName;
      }
      const std::string* cachedDemangledTypeName = &findIter->second;
      return cachedDemangledTypeName;
   }

#ifdef __linux__
   static std::string Demangle(const char* mangledTypeName)
   {
      int demangleStatus = -1;
      std::unique_ptr<char, void(*)(void*)> demangledTypeNamePointer(
         abi::__cxa_demangle(mangledTypeName, nullptr, nullptr, &demangleStatus),
         std::free);
      release_assert(demangleStatus == 0);
      const std::string demangledTypeName(demangledTypeNamePointer.get());
      return demangledTypeName;
   }
#elif _WIN32
   static std::string Demangle(const char* mangledTypeName)
   {
      static const std::regex classStructPattern("(class |struct )");
      const std::string typeNameMinusClassAndStruct
         = std::regex_replace(mangledTypeName, classStructPattern, "");
      return typeNameMinusClassAndStruct;
   }
#endif
};
