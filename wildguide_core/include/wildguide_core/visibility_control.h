#ifndef WILDGUIDE_CORE__VISIBILITY_CONTROL_H_
#define WILDGUIDE_CORE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define WILDGUIDE_CORE_EXPORT __attribute__ ((dllexport))
    #define WILDGUIDE_CORE_IMPORT __attribute__ ((dllimport))
  #else
    #define WILDGUIDE_CORE_EXPORT __declspec(dllexport)
    #define WILDGUIDE_CORE_IMPORT __declspec(dllimport)
  #endif
  #ifdef WILDGUIDE_CORE_BUILDING_LIBRARY
    #define WILDGUIDE_CORE_PUBLIC WILDGUIDE_CORE_EXPORT
  #else
    #define WILDGUIDE_CORE_PUBLIC WILDGUIDE_CORE_IMPORT
  #endif
  #define WILDGUIDE_CORE_PUBLIC_TYPE WILDGUIDE_CORE_PUBLIC
  #define WILDGUIDE_CORE_LOCAL
#else
  #define WILDGUIDE_CORE_EXPORT __attribute__ ((visibility("default")))
  #define WILDGUIDE_CORE_IMPORT
  #if __GNUC__ >= 4
    #define WILDGUIDE_CORE_PUBLIC __attribute__ ((visibility("default")))
    #define WILDGUIDE_CORE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define WILDGUIDE_CORE_PUBLIC
    #define WILDGUIDE_CORE_LOCAL
  #endif
  #define WILDGUIDE_CORE_PUBLIC_TYPE
#endif

#endif  // WILDGUIDE_CORE__VISIBILITY_CONTROL_H_
