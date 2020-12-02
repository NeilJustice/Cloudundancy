#include "pch.h"
#include "libCloudundancy/StaticUtilities/Type.h"

unordered_map<const char*, string> Type::s_mangledToDemangledTypeName;

string Type::GetExceptionClassNameAndMessage(const exception* ex)
{
   const string* exceptionTypeName = Type::GetName(*ex);
   const string exceptionMessage = ex->what();
   const string exceptionClassNameAndMessage = String::Concat(*exceptionTypeName, ": ", exceptionMessage);
   return exceptionClassNameAndMessage;
}

const std::string* Type::TypeInfoToTypeName(const std::type_info& typeInfo)
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

std::string Type::Demangle(const char* mangledTypeName)
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

std::string Type::Demangle(const char* mangledTypeName)
{
   static const std::regex classStructPattern("(class |struct )");
   const std::string typeNameMinusClassAndStruct
      = std::regex_replace(mangledTypeName, classStructPattern, "");
   return typeNameMinusClassAndStruct;
}

#endif
