#pragma once

#ifdef _WIN32
   #pragma warning(disable: 4061) // enumerator in switch of enum is not explicitly handled by a case label
   #pragma warning(disable: 4265) // class has virtual functions, but destructor is not virtual
   #pragma warning(disable: 4355) // 'this': used in base member initializer list
   #pragma warning(disable: 4365) // signed/unsigned mismatch
   #pragma warning(disable: 4371) // layout of class may have changed from a previous version of the compiler due to better packing of member 'ZenUnit::TestResult::responsibleCallResultField'
   #pragma warning(disable: 4503) // 'Function': decorated name length exceeded, name was truncated
   #pragma warning(disable: 4514) // 'Function' unreferenced inline function has been removed
   #pragma warning(disable: 4571) // catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
   #pragma warning(disable: 4619) // #pragma warning: there is no warning number '4800'
   #pragma warning(disable: 4623) // '__std_type_info_data': default constructor was implicitly defined as deleted
   #pragma warning(disable: 4625) // copy constructor was implicitly defined as deleted
   #pragma warning(disable: 4626) // assignment operator was implicitly defined as deleted
   #pragma warning(disable: 4668) // 'CONSTANT_NAME' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
   #pragma warning(disable: 4710) // function not inlined
   #pragma warning(disable: 4711) // function 'FunctionName' selected for automatic inline expansion
   #pragma warning(disable: 4774) // 'sprintf_s' : format string expected in argument 3 is not a string literal
   #pragma warning(disable: 4820) // 'TypeName': 'N' bytes padding added after data member 'dataMember'
   #pragma warning(disable: 4987) // nonstandard extension used : 'throw (...)'
   #pragma warning(disable: 5026) // move constructor was implicitly defined as deleted
   #pragma warning(disable: 5027) // move assignment operator was implicitly defined as deleted
   #pragma warning(disable: 4100) // '__testCase': unreferenced formal parameter
   #pragma warning(disable: 5039) // pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavimay occur if this function throws an exception.
   #pragma warning(disable: 5045) // Compiler will insert Spectre mitigation for memory load if / Qspectre switch specified
   #pragma warning(disable: 5204) // class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
   #pragma warning(disable: 5220) // 'Concurrency::details::_Task_impl_base::_M_TaskState': a non-static data member with a volatile qualified type no longer implies C:\VS2019\VC\Tools\MSVC\14.27.29110\include\ppltasks.h 2098
#endif
