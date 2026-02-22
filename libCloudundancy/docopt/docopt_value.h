//
//  value.h
//  docopt
//
//  Created by Jared Grubb on 2013-10-14.
//  Copyright (c) 2013 Jared Grubb. All rights reserved.
//

#pragma once
#include <stdexcept>
#include <string>
#include <vector>

namespace docopt
{
   enum class Kind
   {
      Empty,
      Bool,
      Long,
      SizeT,
      String,
      StringList
   };

   /// A generic type to hold the various types that can be produced by docopt.
   ///
   /// This type can be one of: {bool, long, string, vector<string>}, or empty.
   struct value
   {
      union Variant
      {
         Variant() {}
         ~Variant() {}

         bool boolValue;
         long longValue;
         size_t sizeTValue = 0ULL;
         std::string strValue;
         std::vector<std::string> strList;
      };

      Kind kind_ = Kind::Empty;
      Variant variant_{};

      value() {}
      value(std::string);
      value(std::vector<std::string>);

      explicit value(bool);

      explicit value(size_t sizeTValue)
         : kind_(Kind::SizeT)
      {
         variant_.sizeTValue = sizeTValue;
      }

      explicit value(long);
      explicit value(int v)
         : value(static_cast<long>(v))
      {
      }

      ~value();
      value(const value&);
      value(value&&) noexcept;
      value& operator=(const value&);
      value& operator=(value&&) noexcept;

      Kind kind() const
      {
         return kind_;
      }

      // Test if this object has any contents at all
      explicit operator bool() const
      {
         return kind_ != Kind::Empty;
      }

      // Test the type contained by this value object
      bool isBool() const
      {
         return kind_ == Kind::Bool;
      }

      bool isString() const
      {
         return kind_ == Kind::String;
      }

      bool isLong() const
      {
         return kind_ == Kind::Long;
      }

      bool isSizeT() const
      {
         return kind_ == Kind::SizeT;
      }

      bool isStringList() const
      {
         return kind_ == Kind::StringList;
      }

      // Throws std::invalid_argument if the type does not match
      bool asBool() const;
      long asLong() const;
      size_t asSizeT() const;
      const std::string& asString() const;
      const std::vector<std::string>& asStringList() const;

      size_t hash() const noexcept;
      friend bool operator==(const value&, const value&);
      friend bool operator!=(const value&, const value&);

   private:
      static const char* kindAsString(Kind kind)
      {
         switch (kind)
         {
         case Kind::Empty: return "empty";
         case Kind::Bool: return "bool";
         case Kind::Long: return "long";
         case Kind::String: return "string";
         case Kind::StringList: return "string-list";
         default: return "unknown";
         }
      }

      void throwIfNotKind(Kind expected) const
      {
         if (kind_ == expected)
         {
            return;
         }
         std::string error = "Illegal cast to ";
         error += kindAsString(expected);
         error += "; type is actually ";
         error += kindAsString(kind_);
         throw std::runtime_error(std::move(error));
      }
   };

   std::ostream& operator<<(std::ostream&, const value&);
}

namespace std
{
   template<>
   struct hash<docopt::value>
   {
      size_t operator()(const docopt::value& val) const noexcept
      {
         return val.hash();
      }
   };
}

namespace docopt
{
   inline value::value(bool v)
      : kind_(Kind::Bool)
   {
      variant_.boolValue = v;
   }

   inline value::value(long v)
      : kind_(Kind::Long)
   {
      variant_.longValue = v;
   }

   inline value::value(std::string v)
      : kind_(Kind::String)
   {
      new (&variant_.strValue) std::string(std::move(v));
   }

   inline value::value(std::vector<std::string> v)
      : kind_(Kind::StringList)
   {
      new (&variant_.strList) std::vector<std::string>(std::move(v));
   }

   inline value::value(const value& other)
      : kind_(other.kind_)
   {
      switch (kind_)
      {
      case Kind::String:
      {
         new (&variant_.strValue) std::string(other.variant_.strValue);
         break;
      }
      case Kind::StringList:
      {
         new (&variant_.strList) std::vector<std::string>(other.variant_.strList);
         break;
      }
      case Kind::Bool:
      {
         variant_.boolValue = other.variant_.boolValue;
         break;
      }
      case Kind::Long:
      {
         variant_.longValue = other.variant_.longValue;
         break;
      }
      case Kind::SizeT:
      {
         variant_.sizeTValue = other.variant_.sizeTValue;
         break;
      }
      case Kind::Empty:
      default:
      {
         break;
      }
      }
   }

   inline value::value(value&& other) noexcept
      : kind_(other.kind_)
   {
      switch (kind_)
      {
      case Kind::String:
      {
         new (&variant_.strValue) std::string(std::move(other.variant_.strValue));
         break;
      }
      case Kind::StringList:
      {
         new (&variant_.strList) std::vector<std::string>(std::move(other.variant_.strList));
         break;
      }
      case Kind::Bool:
      {
         variant_.boolValue = other.variant_.boolValue;
         break;
      }
      case Kind::Long:
      {
         variant_.longValue = other.variant_.longValue;
         break;
      }
      case Kind::SizeT:
      {
         variant_.sizeTValue = other.variant_.sizeTValue;
         break;
      }
      case Kind::Empty:
      default:
      {
         break;
      }
      }
   }

   inline value::~value()
   {
      switch (kind_)
      {
      case Kind::String:
      {
         variant_.strValue.~basic_string();
         break;
      }
      case Kind::StringList:
      {
         variant_.strList.~vector();
         break;
      }
      case Kind::Empty:
      case Kind::Bool:
      case Kind::Long:
      case Kind::SizeT:
      default:
      {
         // trivial dtor
         break;
      }
      }
   }

   inline value& value::operator=(const value& other)
   {
      // make a copy and move from it; way easier.
      return *this = value{ other };
   }

   inline value& value::operator=(value&& other) noexcept
   {
      // move of all the types involved is noexcept, so we dont have to worry about
      // these two statements throwing, which gives us a consistency guarantee.
      this->~value();
      new (this) value(std::move(other));
      return *this;
   }

   template <class T>
   void hash_combine(std::size_t& seed, const T& v);

   inline size_t value::hash() const noexcept
   {
      switch (kind_)
      {
      case Kind::String:
      {
         return std::hash<std::string>()(variant_.strValue);
      }
      case Kind::StringList:
      {
         size_t seed = std::hash<size_t>()(variant_.strList.size());
         for (const auto& str : variant_.strList)
         {
            hash_combine(seed, str);
         }
         return seed;
      }
      case Kind::Bool:
      {
         return std::hash<bool>()(variant_.boolValue);
      }
      case Kind::Long:
      {
         return std::hash<long>()(variant_.longValue);
      }
      case Kind::SizeT:
      {
         size_t hashCode = std::hash<size_t>()(variant_.sizeTValue);
         return hashCode;
      }
      case Kind::Empty:
      default:
      {
         return std::hash<void*>()(nullptr);
      }
      }
   }

   inline bool value::asBool() const
   {
      throwIfNotKind(Kind::Bool);
      return variant_.boolValue;
   }

   inline long value::asLong() const
   {
      if (kind_ == Kind::String)
      {
         const std::string& str = variant_.strValue;
         std::size_t pos;
         long ret = stol(str, &pos);  // Throws if it can't convert
         if (pos != str.length())
         {
            // The string ended in non-digits.
            throw std::runtime_error(str + " contains non-numeric characters.");
         }
         return ret;
      }
      throwIfNotKind(Kind::Long);
      return variant_.longValue;
   }

   inline size_t value::asSizeT() const
   {
      if (kind_ == Kind::String)
      {
         const std::string& str = variant_.strValue;
         std::size_t pos;
         size_t ret = stoull(str, &pos);  // Throws if it can't convert
         if (pos != str.length())
         {
            // The string ended in non-digits.
            throw std::runtime_error(str + " contains non-numeric characters.");
         }
         return ret;
      }
      throwIfNotKind(Kind::SizeT);
      return variant_.sizeTValue;
   }

   inline const std::string& value::asString() const
   {
      throwIfNotKind(Kind::String);
      return variant_.strValue;
   }

   inline const std::vector<std::string>& value::asStringList() const
   {
      throwIfNotKind(Kind::StringList);
      return variant_.strList;
   }

   inline bool operator==(const value& v1, const value& v2)
   {
      if (v1.kind_ != v2.kind_)
      {
         return false;
      }
      switch (v1.kind_)
      {
      case Kind::String:
      {
         return v1.variant_.strValue == v2.variant_.strValue;
      }
      case Kind::StringList:
      {
         return v1.variant_.strList == v2.variant_.strList;
      }
      case Kind::Bool:
      {
         return v1.variant_.boolValue == v2.variant_.boolValue;
      }
      case Kind::Long:
      {
         return v1.variant_.longValue == v2.variant_.longValue;
      }
      case Kind::SizeT:
      {
         return v1.variant_.sizeTValue == v2.variant_.sizeTValue;
      }
      case Kind::Empty:
      default:
      {
         return true;
      }
      }
   }

   inline bool operator!=(const value& v1, const value& v2)
   {
      return !(v1 == v2);
   }
}
