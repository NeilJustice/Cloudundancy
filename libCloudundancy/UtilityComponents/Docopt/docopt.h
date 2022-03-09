#pragma once

#if defined _WIN32
#pragma warning(push)
#pragma warning(disable: 4365) // 'return': conversion from 'size_t' to 'ptrdiff_t', signed/unsigned mismatch
#pragma warning(disable: 4643) // Forward declaring 'allocator' in namespace std is not permitted by the C++ Standard.
#pragma warning(disable: 4800) // Implicit conversion from 'int' to bool. Possible information loss
#pragma warning(disable: 26812) // The enum type 'boost::detail::local_counted_base::count_type' is unscoped. Prefer 'enum class' over 'enum'
#endif
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <unordered_set>
#if defined _WIN32
#pragma warning(pop)
#endif
#include "libCloudundancy/StaticUtilities/ReleaseAssert.h"

template<typename T>
inline void hash_combine(size_t& seed, const T& v)
{
   // From boost::hash_combine
   hash<T> hasher;
   seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace docopt
{
   struct Value
   {
   public:
      enum class Kind
      {
         Empty,
         Bool,
         Long,
         SizeT,
         String,
         StringList
      };
   private:
      struct Variant
      {
         bool boolValue = false;
         long longValue = 0l;
         size_t sizeTValue = 0ull;
         string strValue;
         vector<string> strList;
      };

      Kind kind = Kind::Empty;
      Variant variant{};
   public:
      Value() = default;
      Value(string);
      explicit Value(vector<string>);

      explicit Value(bool);
      explicit Value(long);
      explicit Value(size_t);
      explicit Value(int value)
         : Value(static_cast<long>(value))
      {
      }

      Value(const Value&);
      Value(Value&&) noexcept;
      Value& operator=(const Value&);
      Value& operator=(Value&&) noexcept;

      explicit operator bool() const
      {
         return kind != Kind::Empty;
      }

      bool IsBool() const
      {
         return kind == Kind::Bool;
      }

      bool IsString() const
      {
         return kind == Kind::String;
      }

      bool IsLong() const
      {
         return kind == Kind::Long;
      }

      bool IsSizeT() const
      {
         return kind == Kind::SizeT;
      }

      bool IsStringList() const
      {
         return kind == Kind::StringList;
      }

      bool AsBool() const
      {
         return variant.boolValue;
      }

      long AsLong() const
      {
         if (kind == Kind::String)
         {
            const string& str = variant.strValue;
            size_t pos;
            const long ret = stol(str, &pos);
            if (pos != str.length())
            {
               throw invalid_argument(str + " contains non-numeric characters");
            }
            return ret;
         }
         return variant.longValue;
      }

      size_t AsSizeT() const
      {
         if (kind != Kind::String)
         {
            throw invalid_argument("AsSizeT() called with kind != Kind::String: " + to_string(static_cast<int>(kind)));
         }
         const string& str = variant.strValue;
         size_t pos;
         const size_t sizeTValue = stoull(str, &pos);
         if (pos != str.length())
         {
            throw invalid_argument(str + " contains non-numeric characters");
         }
         return sizeTValue;
      }

      const string& AsString() const
      {
         return variant.strValue;
      }

      const vector<string>& AsStringList() const
      {
         return variant.strList;
      }

      size_t Hash() const noexcept
      {
         switch (kind)
         {
         case Kind::String:
         {
            return hash<string>()(variant.strValue);
         }
         case Kind::StringList:
         {
            size_t seed = hash<size_t>()(variant.strList.size());
            for (const string& str : variant.strList)
            {
               hash_combine(seed, str);
            }
            return seed;
         }
         case Kind::Bool:
         {
            return hash<bool>()(variant.boolValue);
         }
         case Kind::Long:
         {
            return hash<long>()(variant.longValue);
         }
         case Kind::SizeT:
         {
            return hash<size_t>()(variant.sizeTValue);
         }
         case Kind::Empty:
         default:
         {
            return hash<void*>()(nullptr);
         }
         }
      }

      friend bool operator==(const Value&, const Value&);
      friend bool operator!=(const Value&, const Value&);
   private:
      static const char* KindAsString(Kind kind)
      {
         switch (kind)
         {
         case Kind::Empty: return "empty";
         case Kind::Bool: return "bool";
         case Kind::Long: return "long";
         case Kind::SizeT: return "size_t";
         case Kind::String: return "string";
         case Kind::StringList: return "string-list";
         default: return "unknown";
         }
      }
   };
}

namespace std
{
   template<>
   struct hash<docopt::Value>
   {
      size_t operator()(const docopt::Value& docoptValue) const noexcept
      {
         const size_t hashCode = docoptValue.Hash();
         return hashCode;
      }
   };
}

namespace docopt
{
   inline Value::Value(bool boolValue)
      : kind(Kind::Bool)
   {
      variant.boolValue = boolValue;
   }

   inline Value::Value(long longValue)
      : kind(Kind::Long)
   {
      variant.longValue = longValue;
   }

   inline Value::Value(size_t sizeTValue)
      : kind(Kind::SizeT)
   {
      variant.sizeTValue = sizeTValue;
   }

   inline Value::Value(string v)
      : kind(Kind::String)
   {
      new (&variant.strValue) string(move(v));
   }

   inline Value::Value(vector<string> v)
      : kind(Kind::StringList)
   {
      new (&variant.strList) vector<string>(move(v));
   }

   inline Value::Value(const Value& other)
      : kind(other.kind)
   {
      switch (kind)
      {
      case Kind::String:
         new (&variant.strValue) string(other.variant.strValue);
         break;
      case Kind::StringList:
         new (&variant.strList) vector<string>(other.variant.strList);
         break;
      case Kind::Bool:
         variant.boolValue = other.variant.boolValue;
         break;
      case Kind::Long:
         variant.longValue = other.variant.longValue;
         break;
      case Kind::SizeT:
         variant.sizeTValue = other.variant.sizeTValue;
         break;
      case Kind::Empty:
      default:
         break;
      }
   }

   inline Value::Value(Value&& other) noexcept
      : kind(other.kind)
   {
      switch (kind)
      {
      case Kind::String:
         new (&variant.strValue) string(move(other.variant.strValue));
         break;
      case Kind::StringList:
         new (&variant.strList) vector<string>(move(other.variant.strList));
         break;
      case Kind::Bool:
         variant.boolValue = other.variant.boolValue;
         break;
      case Kind::Long:
         variant.longValue = other.variant.longValue;
         break;
      case Kind::SizeT:
         variant.sizeTValue = other.variant.sizeTValue;
         break;
      case Kind::Empty:
      default:
         break;
      }
   }

   inline Value& Value::operator=(const Value& other)
   {
      return *this = Value{ other };
   }

   inline Value& Value::operator=(Value&& other) noexcept
   {
      this->~Value();
      new (this) Value(move(other));
      return *this;
   }

   inline bool operator==(const Value& v1, const Value& v2)
   {
      if (v1.kind != v2.kind)
      {
         return false;
      }
      switch (v1.kind)
      {
      case Value::Kind::String:
      {
         return v1.variant.strValue == v2.variant.strValue;
      }
      case Value::Kind::StringList:
      {
         return v1.variant.strList == v2.variant.strList;
      }
      case Value::Kind::Bool:
      {
         return v1.variant.boolValue == v2.variant.boolValue;
      }
      case Value::Kind::Long:
      {
         return v1.variant.longValue == v2.variant.longValue;
      }
      case Value::Kind::SizeT:
      {
         return v1.variant.sizeTValue == v2.variant.sizeTValue;
      }
      case Value::Kind::Empty:
      default:
         return true;
      }
   }

   inline bool operator!=(const Value& v1, const Value& v2)
   {
      const bool areNotEqual = !(v1 == v2);
      return areNotEqual;
   }

   struct DocoptLanguageError : runtime_error
   {
      using runtime_error::runtime_error;
   };

   struct DocoptArgumentError : runtime_error
   {
      using runtime_error::runtime_error;
   };

   struct DocoptExitHelp : runtime_error
   {
      DocoptExitHelp() : runtime_error("Docopt --help argument encountered") {}
   };

   struct DocoptExitVersion : runtime_error
   {
      DocoptExitVersion() : runtime_error("Docopt --version argument encountered") {}
   };

   // Parse user options from the given option string.
   //
   // @param doc   The usage string
   // @param argv  The user-supplied arguments
   // @param help  Whether to end early if '-h' or '--help' is in the argv
   // @param version Whether to end early if '--version' is in the argv
   // @param options_first  Whether options must precede all args (true), or if args and options
   //                can be arbitrarily mixed.
   //
   // @throws DocoptLanguageError if the doc usage string had errors itself
   // @throws DocoptExitHelp if 'help' is true and the user has passed the '--help' argument
   // @throws DocoptExitVersion if 'version' is true and the user has passed the '--version' argument
   // @throws DocoptArgumentError if the user's argv did not match the usage patterns
   inline map<string, Value> docopt_parse(
      const string& doc,
      const vector<string>& argv,
      bool help = true,
      bool version = true,
      bool options_first = false);

   // Parse user options from the given string, and exit appropriately
   //
   // Calls 'docopt_parse' and will terminate the program if any of the exceptions above occur:
   //  * DocoptLanguageError - print error and terminate (with exit code -1)
   //  * DocoptExitHelp - print usage string and terminate (with exit code 0)
   //  * DocoptExitVersion - print version and terminate (with exit code 0)
   //  * DocoptArgumentError - print error and usage string and terminate (with exit code -1)
   inline map<string, Value> docopt(
      const string& doc,
      const vector<string>& argv,
      bool help,
      const string& version,
      bool options_first) noexcept;

   inline bool starts_with(const string& str, const string& prefix)
   {
      if (str.length() < prefix.length())
      {
         return false;
      }
      return equal(prefix.begin(), prefix.end(), str.begin());
   }

   inline string trim(string&& str, const string& whitespace = " \t\n")
   {
      const size_t strEnd = str.find_last_not_of(whitespace);
      if (strEnd == string::npos)
      {
         return {}; // no content
      }
      str.erase(strEnd + 1);
      const size_t strBegin = str.find_first_not_of(whitespace);
      str.erase(0, strBegin);
      return move(str);
   }

   inline vector<string> split(const string& str, size_t pos = 0)
   {
      const char* const anySpace = " \t\r\n\v\f";
      vector<string> ret;
      while (pos != string::npos)
      {
         const size_t start = str.find_first_not_of(anySpace, pos);
         if (start == string::npos)
         {
            break;
         }
         const size_t end = str.find_first_of(anySpace, start);
         const size_t size = end == string::npos ? end : end - start;
         ret.emplace_back(str.substr(start, size));
         pos = end;
      }
      return ret;
   }

   inline tuple<string, string, string> partition(string str, const string& point)
   {
      tuple<string, string, string> ret;
      const size_t i = str.find(point);
      if (i == string::npos)
      {
         // no match: string goes in 0th spot only
      }
      else
      {
         get<2>(ret) = str.substr(i + point.size());
         get<1>(ret) = point;
         str.resize(i);
      }
      get<0>(ret) = move(str);
      return ret;
   }

   template<typename I>
   string join(I iter, I end, const string& delimiter)
   {
      if (iter == end)
      {
         return {};
      }
      string ret = *iter;
      for (++iter; iter != end; ++iter)
      {
         ret.append(delimiter);
         ret.append(*iter);
      }
      return ret;
   }

   inline vector<string> regex_split(const string& text, const regex& regexPattern)
   {
      vector<string> patternSplitText;
      for (auto it = sregex_token_iterator(text.begin(), text.end(), regexPattern, -1); it != sregex_token_iterator(); ++it)
      {
         patternSplitText.emplace_back(*it);
      }
      return patternSplitText;
   }

   class Pattern;
   class LeafPattern;

   struct PatternHasher
   {
      template<typename P>
      size_t operator()(const shared_ptr<P>& pattern) const
      {
         const size_t Hash = pattern->Hash();
         return Hash;
      }

      template<typename P>
      size_t operator()(P const* pattern) const
      {
         const size_t Hash = pattern->Hash();
         return Hash;
      }

      template<typename P>
      size_t operator()(const P& pattern) const
      {
         const size_t Hash = pattern.Hash();
         return Hash;
      }
   };

   struct PatternPointerEquality
   {
      template<typename P1, typename P2>
      bool operator()(const shared_ptr<P1>& p1, const shared_ptr<P2>& p2) const
      {
         const bool areEqual = p1->Hash() == p2->Hash();
         return areEqual;
      }

      template<typename P1, typename P2>
      bool operator()(P1 const* p1, P2 const* p2) const
      {
         const bool areEqual = p1->Hash() == p2->Hash();
         return areEqual;
      }
   };

   using UniquePatternSet = unordered_set<shared_ptr<Pattern>, PatternHasher, PatternPointerEquality>;

   class Pattern
   {
   public:
      vector<LeafPattern*> LeafPatterns();
      virtual vector<Pattern*> Flat(bool(*filter)(Pattern const*)) = 0;
      virtual void CollectLeaves(vector<LeafPattern*>&) = 0;
      virtual bool Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const = 0;
      virtual const string& Name() const = 0;
      virtual size_t Hash() const = 0;
      virtual bool HasValue() const { return false; }
      virtual ~Pattern() = default;
   };

   class LeafPattern : public Pattern
   {
   private:
      string _name;
      Value _value;
   protected:
      virtual pair<size_t, shared_ptr<LeafPattern>> SingleMatch(const vector<shared_ptr<Pattern>>&) const = 0;
   public:
      LeafPattern(string name, Value value = {})
         : _name(move(name))
         , _value(move(value))
      {
      }

      virtual vector<Pattern*> Flat(bool(*filter)(Pattern const*)) override
      {
         if (filter(this))
         {
            return { this };
         }
         return {};
      }

      virtual void CollectLeaves(vector<LeafPattern*>& outLeafPatterns) override final
      {
         outLeafPatterns.push_back(this);
      }

      virtual bool Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const override;

      virtual bool HasValue() const override
      {
         return static_cast<bool>(_value);
      }

      const Value& getValue() const
      {
         return _value;
      }

      void setValue(Value&& value)
      {
         _value = move(value);
      }

      virtual const string& Name() const override
      {
         return _name;
      }

      virtual size_t Hash() const override
      {
         size_t seed = typeid(*this).hash_code();
         hash_combine(seed, _name);
         hash_combine(seed, _value);
         return seed;
      }
   };

   class BranchPattern : public Pattern
   {
   private:
      void FixRepeatingArguments();
   protected:
      vector<shared_ptr<Pattern>> fChildren;
   public:
      BranchPattern(vector<shared_ptr<Pattern>> children = {})
         : fChildren(move(children))
      {
      }

      Pattern& fix()
      {
         UniquePatternSet patterns;
         fix_identities(patterns);
         FixRepeatingArguments();
         return *this;
      }

      virtual const string& Name() const override
      {
         throw runtime_error("Logic error: name() shouldnt be called on a BranchPattern");
      }

      virtual const Value& getValue() const
      {
         throw runtime_error("Logic error: name() shouldnt be called on a BranchPattern");
      }

      virtual vector<Pattern*> Flat(bool(*filter)(Pattern const*)) override
      {
         if (filter(this))
         {
            return { this };
         }
         vector<Pattern*> ret;
         for (auto& child : fChildren)
         {
            auto sublist = child->Flat(filter);
            ret.insert(ret.end(), sublist.begin(), sublist.end());
         }
         return ret;
      }

      virtual void CollectLeaves(vector<LeafPattern*>& lst) override final
      {
         for (auto& child : fChildren)
         {
            child->CollectLeaves(lst);
         }
      }

      void setChildren(vector<shared_ptr<Pattern>> children)
      {
         fChildren = move(children);
      }

      const vector<shared_ptr<Pattern>>& children() const
      {
         return fChildren;
      }

      virtual void fix_identities(UniquePatternSet& patterns)
      {
         for (auto& child : fChildren)
         {
            // this will fix up all its children, if needed
            if (BranchPattern* branchPattern = dynamic_cast<BranchPattern*>(child.get()))
            {
               branchPattern->fix_identities(patterns);
            }
            // then we try to add it to the list
            const auto inserted = patterns.insert(child);
            if (!inserted.second)
            {
               // already there? then reuse the existing shared_ptr for that thing
               child = *inserted.first;
            }
         }
      }

      virtual size_t Hash() const override
      {
         size_t seed = typeid(*this).hash_code();
         hash_combine(seed, fChildren.size());
         for (const auto& child : fChildren)
         {
            hash_combine(seed, child->Hash());
         }
         return seed;
      }
   };

   class ArgumentLeafPattern : public LeafPattern
   {
   public:
      using LeafPattern::LeafPattern;
   protected:
      virtual pair<size_t, shared_ptr<LeafPattern>> SingleMatch(
         const vector<shared_ptr<Pattern>>& left) const override;
   };

   class CommandArgumentLeafPattern : public ArgumentLeafPattern
   {
   public:
      explicit CommandArgumentLeafPattern(string name, Value v = Value{ false })
         : ArgumentLeafPattern(move(name), move(v))
      {
      }
   protected:
      virtual pair<size_t, shared_ptr<LeafPattern>> SingleMatch(
         const vector<shared_ptr<Pattern>>& left) const override;
   };

   class OptionLeafPattern final : public LeafPattern
   {
   protected:
      virtual pair<size_t, shared_ptr<LeafPattern>> SingleMatch(
         const vector<shared_ptr<Pattern>>& left) const override;
   private:
      string _shortOption;
      string _longOption;
      int _argCount;
   public:
      static OptionLeafPattern parse(const string& option_description);

      OptionLeafPattern(
         string shortOption,
         string longOption,
         int argcount = 0,
         Value v = Value{ false })
         : LeafPattern(longOption.empty() ? shortOption : longOption, move(v))
         , _shortOption(move(shortOption))
         , _longOption(move(longOption))
         , _argCount(argcount)
      {
         // From Python:
         //   self.value = None if value is False and argcount else value
         if (argcount && v.IsBool() && !v.AsBool())
         {
            setValue(Value{});
         }
      }

      OptionLeafPattern(const OptionLeafPattern&) = default;
      OptionLeafPattern(OptionLeafPattern&&) = default;
      OptionLeafPattern& operator=(const OptionLeafPattern&) = default;
      OptionLeafPattern& operator=(OptionLeafPattern&&) = default;

      using LeafPattern::setValue;

      const string& longOption() const
      {
         return _longOption;
      }

      const string& shortOption() const
      {
         return _shortOption;
      }

      int argCount() const
      {
         return _argCount;
      }

      virtual size_t Hash() const override
      {
         size_t seed = LeafPattern::Hash();
         hash_combine(seed, _shortOption);
         hash_combine(seed, _longOption);
         hash_combine(seed, _argCount);
         return seed;
      }
   };

   class RequiredBranchPattern : public BranchPattern
   {
   public:
      using BranchPattern::BranchPattern;
      bool Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const override;
   };

   class OptionalBranchPattern : public BranchPattern
   {
   public:
      using BranchPattern::BranchPattern;

      bool Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const override
      {
         for (const auto& pattern : fChildren)
         {
            pattern->Match(left, collected);
         }
         return true;
      }
   };

   class OptionsShortcutOptionalBranchPattern : public OptionalBranchPattern
   {
      using OptionalBranchPattern::OptionalBranchPattern;
   };

   class OneOrMoreBranchPattern : public BranchPattern
   {
   public:
      using BranchPattern::BranchPattern;
      bool Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const override;
   };

   class EitherBranchPattern : public BranchPattern
   {
   public:
      using BranchPattern::BranchPattern;
      bool Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const override;
   };

   inline vector<LeafPattern*> Pattern::LeafPatterns()
   {
      vector<LeafPattern*> leafPatterns;
      CollectLeaves(leafPatterns);
      return leafPatterns;
   }

   static inline vector<vector<shared_ptr<Pattern>>> transform(vector<shared_ptr<Pattern>> pattern)
   {
      vector<vector<shared_ptr<Pattern>>> result;
      vector<vector<shared_ptr<Pattern>>> groups;
      groups.emplace_back(move(pattern));
      while (!groups.empty())
      {
         // pop off the first element
         auto children = move(groups[0]);
         groups.erase(groups.begin());
         // find the first branch node in the list
         auto child_iter = find_if(children.begin(), children.end(), [](const shared_ptr<Pattern>& p)
         {
            return dynamic_cast<BranchPattern const*>(p.get());
         });
         // no branch nodes left : expansion is complete for this grouping
         if (child_iter == children.end())
         {
            result.emplace_back(move(children));
            continue;
         }
         // pop the child from the list
         auto child = move(*child_iter);
         children.erase(child_iter);
         // expand the branch in the appropriate way
         if (EitherBranchPattern* either = dynamic_cast<EitherBranchPattern*>(child.get()))
         {
            // "[e] + children" for each child 'e' in Either
            for (const auto& eitherChild : either->children())
            {
               vector<shared_ptr<Pattern>> group = { eitherChild };
               group.insert(group.end(), children.begin(), children.end());
               groups.emplace_back(move(group));
            }
         }
         else if (OneOrMoreBranchPattern* oneOrMore = dynamic_cast<OneOrMoreBranchPattern*>(child.get()))
         {
            // child.children * 2 + children
            const auto& subchildren = oneOrMore->children();
            vector<shared_ptr<Pattern>> group = subchildren;
            group.insert(group.end(), subchildren.begin(), subchildren.end());
            group.insert(group.end(), children.begin(), children.end());
            groups.emplace_back(move(group));
         }
         else
         {
            // Required, Optional, OptionsShortcut
            BranchPattern* branch = dynamic_cast<BranchPattern*>(child.get());
            // child.children + children
            vector<shared_ptr<Pattern>> group = branch->children();
            group.insert(group.end(), children.begin(), children.end());
            groups.emplace_back(move(group));
         }
      }
      return result;
   }

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4868) // compiler may not enforce left - to - right evaluation order in braced initializer list
#endif
   inline void BranchPattern::FixRepeatingArguments()
   {
      vector<vector<shared_ptr<Pattern>>> either = transform(children());
      for (const auto& group : either)
      {
         // use multiset to help identify duplicate entries
         unordered_multiset<shared_ptr<Pattern>, PatternHasher> group_set{ group.begin(), group.end() };
         for (const auto& e : group_set)
         {
            if (group_set.count(e) == 1)
            {
               continue;
            }
            LeafPattern* leaf = dynamic_cast<LeafPattern*>(e.get());
            if (!leaf)
            {
               continue;
            }
            bool ensureList = false;
            bool ensureInt = false;
            if (dynamic_cast<CommandArgumentLeafPattern*>(leaf))
            {
               ensureInt = true;
            }
            else if (dynamic_cast<ArgumentLeafPattern*>(leaf))
            {
               ensureList = true;
            }
            else if (OptionLeafPattern* o = dynamic_cast<OptionLeafPattern*>(leaf))
            {
               if (o->argCount())
               {
                  ensureList = true;
               }
               else
               {
                  ensureInt = true;
               }
            }
            if (ensureList)
            {
               vector<string> newValue;
               if (leaf->getValue().IsString())
               {
                  newValue = split(leaf->getValue().AsString());
               }
               if (!leaf->getValue().IsStringList())
               {
                  leaf->setValue(Value{ newValue });
               }
            }
            else if (ensureInt)
            {
               leaf->setValue(Value{ 0 });
            }
         }
      }
   }
#ifdef _WIN32
#pragma warning(pop)
#endif

   inline bool LeafPattern::Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const
   {
      auto match = SingleMatch(left);
      if (!match.second)
      {
         return false;
      }
      left.erase(left.begin() + static_cast<ptrdiff_t>(match.first));
      auto same_name = find_if(collected.begin(), collected.end(), [&](const shared_ptr<LeafPattern>& p)
      {
         return p->Name() == Name();
      });
      if (getValue().IsLong())
      {
         long val = 1;
         if (same_name == collected.end())
         {
            collected.push_back(match.second);
            match.second->setValue(Value{ val });
         }
         else if ((**same_name).getValue().IsLong())
         {
            val += (**same_name).getValue().AsLong();
            (**same_name).setValue(Value{ val });
         }
         else
         {
            (**same_name).setValue(Value{ val });
         }
      }
      else if (getValue().IsSizeT())
      {
         size_t val = 1;
         if (same_name == collected.end())
         {
            collected.push_back(match.second);
            match.second->setValue(Value{ val });
         }
         else if ((**same_name).getValue().IsSizeT())
         {
            val += (**same_name).getValue().AsSizeT();
            (**same_name).setValue(Value{ val });
         }
         else
         {
            (**same_name).setValue(Value{ val });
         }
      }
      else if (getValue().IsStringList())
      {
         vector<string> val;
         if (match.second->getValue().IsString())
         {
            val.push_back(match.second->getValue().AsString());
         }
         else if (match.second->getValue().IsStringList())
         {
            val = match.second->getValue().AsStringList();
         }
         else
         {
            cout << "docopt: Impossible is possible\n";
            ::exit(1);
         }
         if (same_name == collected.end())
         {
            collected.push_back(match.second);
            match.second->setValue(Value{ val });
         }
         else if ((**same_name).getValue().IsStringList())
         {
            const vector<string>& list = (**same_name).getValue().AsStringList();
            val.insert(val.begin(), list.begin(), list.end());
            (**same_name).setValue(Value{ val });
         }
         else
         {
            (**same_name).setValue(Value{ val });
         }
      }
      else
      {
         collected.push_back(match.second);
      }
      return true;
   }

   inline pair<size_t, shared_ptr<LeafPattern>> ArgumentLeafPattern::SingleMatch(
      const vector<shared_ptr<Pattern>>& left) const
   {
      pair<size_t, shared_ptr<LeafPattern>> ret{};
      for (size_t i = 0, size = left.size(); i < size; ++i)
      {
         auto arg = dynamic_cast<ArgumentLeafPattern const*>(left[i].get());
         if (arg)
         {
            ret.first = i;
            ret.second = make_shared<ArgumentLeafPattern>(Name(), arg->getValue());
            break;
         }
      }
      return ret;
   }

   inline pair<size_t, shared_ptr<LeafPattern>> CommandArgumentLeafPattern::SingleMatch(
      const vector<shared_ptr<Pattern>>& left) const
   {
      pair<size_t, shared_ptr<LeafPattern>> ret{};
      for (size_t i = 0, size = left.size(); i < size; ++i)
      {
         auto arg = dynamic_cast<ArgumentLeafPattern const*>(left[i].get());
         if (arg)
         {
            if (Value{Name()} == arg->getValue())
            {
               ret.first = i;
               ret.second = make_shared<CommandArgumentLeafPattern>(Name(), Value{ true });
            }
            break;
         }
      }
      return ret;
   }

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4868) // Warning   C4868   compiler may not enforce left - to - right evaluation order in braced initializer list
#endif
   inline OptionLeafPattern OptionLeafPattern::parse(const string& option_description)
   {
      string shortOption, longOption;
      int argcount = 0;
      Value val{ false };
      auto double_space = option_description.find("  ");
      auto options_end = option_description.end();
      if (double_space != string::npos)
      {
         options_end = option_description.begin() + static_cast<ptrdiff_t>(double_space);
      }
      static const regex pattern{ "(-{1,2})?(.*?)([,= ]|$)" };
      for (sregex_iterator i{ option_description.begin(), options_end, pattern, regex_constants::match_not_null },
         e{};
         i != e;
         ++i)
      {
         const smatch& match = *i;
         if (match[1].matched)
         { // [1] is optional.
            if (match[1].length() == 1)
            {
               shortOption = "-" + match[2].str();
            }
            else
            {
               longOption = "--" + match[2].str();
            }
         }
         else if (match[2].length() > 0)
         {
            // [2] always matches.
            string m = match[2];
            argcount = 1;
         }
         else
         {
            // delimeter
         }
         if (match[3].length() == 0)
         {
            // [3] always matches.
            // Hit end of string. For some reason 'match_not_null' will let us match empty
            // at the end, and then we'll spin in an infinite loop. So, if we hit an empty
            // match, we know we must be at the end.
            break;
         }
      }
      if (argcount)
      {
         smatch match;
         static const regex regexPattern{ "\\[default: (.*)\\]", regex::icase };
         if (regex_search(options_end, option_description.end(), match, regexPattern))
         {
            val = Value{match[1].str()};
         }
      }
      return { move(shortOption), move(longOption), argcount, move(val) };
   }
#ifdef _WIN32
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4868) // compiler may not enforce left - to - right evaluation order in braced initializer list
#endif
   inline pair<size_t, shared_ptr<LeafPattern>> OptionLeafPattern::SingleMatch(
      const vector<shared_ptr<Pattern>>& left) const
   {
      auto thematch = find_if(left.begin(), left.end(), [this](const shared_ptr<Pattern>& a)
      {
         auto leaf = dynamic_pointer_cast<LeafPattern>(a);
         return leaf && this->Name() == leaf->Name();
      });
      if (thematch == left.end())
      {
         return {};
      }
      const size_t theDistance = static_cast<size_t>(distance(left.begin(), thematch));
      const pair<size_t, shared_ptr<LeafPattern>> ret = make_pair(
         theDistance, dynamic_pointer_cast<LeafPattern>(*thematch));
      return ret;
   }
#ifdef _WIN32
#pragma warning(pop)
#endif

   inline bool RequiredBranchPattern::Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const
   {
      auto l = left;
      auto c = collected;
      for (const auto& pattern : fChildren)
      {
         bool ret = pattern->Match(l, c);
         if (!ret)
         {
            // leave (left, collected) untouched
            return false;
         }
      }
      left = move(l);
      collected = move(c);
      return true;
   }

   inline bool OneOrMoreBranchPattern::Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const
   {
      release_assert(fChildren.size() == 1);
      auto l = left;
      auto c = collected;
      bool matched = true;
      size_t times = 0;
      decltype(l) l_;
      bool firstLoop = true;
      while (matched)
      {
         // could it be that something didn't match but changed l or c?
         matched = fChildren[0]->Match(l, c);
         if (matched)
         {
            ++times;
         }
         if (firstLoop)
         {
            firstLoop = false;
         }
         else if (l == l_)
         {
            break;
         }
         l_ = l;
      }
      if (times == 0)
      {
         return false;
      }
      left = move(l);
      collected = move(c);
      return true;
   }

   inline bool EitherBranchPattern::Match(vector<shared_ptr<Pattern>>& left, vector<shared_ptr<LeafPattern>>& collected) const
   {
      using Outcome = pair<vector<shared_ptr<Pattern>>, vector<shared_ptr<LeafPattern>>>;
      vector<Outcome> outcomes;
      for (const auto& pattern : fChildren)
      {
         // need a copy so we apply the same one for every iteration
         auto l = left;
         auto c = collected;
         bool matched = pattern->Match(l, c);
         if (matched)
         {
            outcomes.emplace_back(move(l), move(c));
         }
      }
      auto min = min_element(outcomes.begin(), outcomes.end(), [](const Outcome& o1, const Outcome& o2)
      {
         return o1.first.size() < o2.first.size();
      });
      if (min == outcomes.end())
      {
         // (left, collected) unchanged
         return false;
      }
      tie(left, collected) = move(*min);
      return true;
   }

   class Tokens
   {
   private:
      vector<string> fTokens;
      size_t fIndex = 0;
      bool fIsParsingArgv;
   public:
      explicit Tokens(vector<string> tokens, bool isParsingArgv = true)
         : fTokens(move(tokens))
         , fIsParsingArgv(isParsingArgv)
      {
      }

      explicit operator bool() const
      {
         return fIndex < fTokens.size();
      }

      static Tokens FromPattern(const string& source)
      {
         static const regex re_separators
         {
            "(?:\\s*)" // any spaces (non-matching subgroup)
            "("
            "[\\[\\]\\(\\)\\|]" // one character of brackets or parens or pipe character
            "|"
            "\\.\\.\\."  // elipsis
            ")"
         };
         static const regex re_strings
         {
            "(?:\\s*)" // any spaces (non-matching subgroup)
            "("
            "\\S*<.*?>"  // strings, but make sure to keep "< >" strings together
            "|"
            "[^<>\\s]+"     // string without <>
            ")"
         };
         // We do two stages of regex matching. The '[]()' and '...' are strong delimeters
         // and need to be split out anywhere they occur (even at the end of a token). We
         // first split on those, and then parse the stuff between them to find the string
         // tokens. This is a little harder than the python version, since they have regex.split
         // and we dont have anything like that.
         vector<string> tokens;
         for_each(sregex_iterator{ source.begin(), source.end(), re_separators },
            sregex_iterator{},
            [&](const smatch& match)
         {
            // handle anything before the separator (this is the "stuff" between the delimeters)
            if (match.prefix().matched)
            {
               for_each(sregex_iterator{ match.prefix().first, match.prefix().second, re_strings },
                  sregex_iterator{},
                  [&](const smatch& m)
               {
                  tokens.push_back(m[1].str());
               });
            }
            // handle the delimter token itself
            if (match[1].matched)
            {
               tokens.push_back(match[1].str());
            }
         });
         return Tokens(tokens, false);
      }

      const string& current() const
      {
         if (*this)
         {
            return fTokens[fIndex];
         }
         static string const empty;
         return empty;
      }

      string the_rest() const
      {
         if (!*this)
         {
            return {};
         }
         return join(fTokens.begin() + static_cast<ptrdiff_t>(fIndex), fTokens.end(), " ");
      }

      string pop()
      {
         return move(fTokens.at(fIndex++));
      }

      bool isParsingArgv() const
      {
         return fIsParsingArgv;
      }

      struct OptionError : runtime_error
      {
         using runtime_error::runtime_error;
      };
   };

   // Get all instances of 'T' from the pattern
   template<typename T>
   vector<T*> FlatFilter(Pattern& pattern)
   {
      vector<Pattern*> flattened = pattern.Flat([](Pattern const* p) -> bool
      {
         return dynamic_cast<T const*>(p) != nullptr;
      });

      // now, we're guaranteed to have T*'s, so just use static_cast
      vector<T*> ret;
      transform(flattened.begin(), flattened.end(), back_inserter(ret), [](Pattern* p)
      {
         return static_cast<T*>(p);
      });
      return ret;
   }

   static vector<string> ParseSection(const string& name, const string& source)
   {
      // ECMAScript regex only has "?=" for a non-matching lookahead. In order to make sure we always have
      // a newline to anchor our matching, we have to avoid matching the final newline of each grouping.
      // Therefore, our regex is adjusted from the docopt Python one to use ?= to match the newlines before
      // the following lines, rather than after.
      const regex re_section_pattern
      {
         "(?:^|\\n)"  // anchored at a linebreak (or start of string)
         "("
         "[^\\n]*" + name + "[^\\n]*(?=\\n?)" // a line that contains the name
         "(?:\\n[ \\t].*?(?=\\n|$))*"         // followed by any number of lines that are indented
         ")",
         regex::icase
      };

      vector<string> trimmedMatches;
      for_each(sregex_iterator(source.begin(), source.end(), re_section_pattern), sregex_iterator(),
         [&](const smatch& match)
         {
            trimmedMatches.push_back(trim(match[1].str()));
         });
      return trimmedMatches;
   }

   static bool is_argument_spec(const string& token)
   {
      if (token.empty())
      {
         return false;
      }
      if (token[0] == '<' && token[token.size() - 1] == '>')
      {
         return true;
      }
      if (all_of(token.begin(), token.end(), &::isupper))
      {
         return true;
      }
      return false;
   }

   template<typename I>
   vector<string> longOptions(I iter, I end)
   {
      vector<string> ret;
      transform(iter, end, back_inserter(ret), [](typename I::reference opt) { return opt->longOption(); });
      return ret;
   }

   static vector<shared_ptr<Pattern>> parse_long(Tokens& tokens, vector<OptionLeafPattern>& outOptions)
   {
      // long ::= '--' chars [ ( ' ' | '=' ) chars ] ;
      string longOpt;
      string equal;
      Value val;
      const tuple<string, string, string> longOpt_equal_val = partition(tokens.pop(), "=");
      longOpt = get<0>(longOpt_equal_val);
      equal = get<1>(longOpt_equal_val);
      val = Value{get<2>(longOpt_equal_val)};
      release_assert(starts_with(longOpt, "--"));
      if (equal.empty())
      {
         val = Value{};
      }
      // detect with options match this long option
      vector<OptionLeafPattern const*> similar;
      for (const auto& option : outOptions)
      {
         if (option.longOption() == longOpt)
         {
            similar.push_back(&option);
         }
      }
      // maybe allow similar options that match by prefix
      if (tokens.isParsingArgv() && similar.empty())
      {
         for (const auto& option : outOptions)
         {
            if (option.longOption().empty())
            {
               continue;
            }
            if (starts_with(option.longOption(), longOpt))
            {
               similar.push_back(&option);
            }
         }
      }
      vector<shared_ptr<Pattern>> ret;
      if (similar.size() > 1)
      {
         // might be simply specified ambiguously 2+ times?
         vector<string> prefixes = longOptions(similar.begin(), similar.end());
         string error = "'" + longOpt + "' is not a unique prefix: ";
         error.append(join(prefixes.begin(), prefixes.end(), ", "));
         throw Tokens::OptionError(move(error));
      }
      else if (similar.empty())
      {
         int argcount = equal.empty() ? 0 : 1;
         outOptions.emplace_back("", longOpt, argcount);
         auto o = make_shared<OptionLeafPattern>(outOptions.back());
         if (tokens.isParsingArgv())
         {
            o->setValue(argcount ? Value{ val } : Value{ true });
         }
         ret.push_back(o);
      }
      else
      {
         auto o = make_shared<OptionLeafPattern>(*similar[0]);
         if (o->argCount() == 0)
         {
            if (val)
            {
               string error = o->longOption() + " must not have an argument";
               throw Tokens::OptionError(move(error));
            }
         }
         else
         {
            if (!val)
            {
               const auto& token = tokens.current();
               if (token.empty() || token == "--")
               {
                  string error = o->longOption() + " requires an argument";
                  throw Tokens::OptionError(move(error));
               }
               val = Value{tokens.pop()};
            }
         }
         if (tokens.isParsingArgv())
         {
            o->setValue(val ? move(val) : Value{ true });
         }
         ret.push_back(o);
      }
      return ret;
   }

   static vector<shared_ptr<Pattern>> parse_short(Tokens& tokens, vector<OptionLeafPattern>& outOptions)
   {
      // shorts ::= '-' ( chars )* [ [ ' ' ] chars ] ;
      auto token = tokens.pop();
      release_assert(starts_with(token, "-"));
      release_assert(!starts_with(token, "--"));
      auto i = token.begin();
      ++i; // skip the leading '-'
      vector<shared_ptr<Pattern>> ret;
      while (i != token.end())
      {
         string shortOpt = { '-', *i };
         ++i;
         vector<OptionLeafPattern const*> similar;
         for (const auto& option : outOptions)
         {
            if (option.shortOption() == shortOpt)
            {
               similar.push_back(&option);
            }
         }
         if (similar.size() > 1)
         {
            string error = shortOpt + " is specified ambiguously " + to_string(similar.size()) + " times";
            throw Tokens::OptionError(move(error));
         }
         else if (similar.empty())
         {
            outOptions.emplace_back(shortOpt, "", 0);
            auto o = make_shared<OptionLeafPattern>(outOptions.back());
            if (tokens.isParsingArgv())
            {
               o->setValue(Value{ true });
            }
            ret.push_back(o);
         }
         else
         {
            auto o = make_shared<OptionLeafPattern>(*similar[0]);
            Value val;
            if (o->argCount())
            {
               if (i == token.end())
               {
                  // consume the next token
                  const auto& ttoken = tokens.current();
                  if (ttoken.empty() || ttoken == "--")
                  {
                     string error = shortOpt + " requires an argument";
                     throw Tokens::OptionError(move(error));
                  }
                  val = Value{tokens.pop()};
               }
               else
               {
                  // consume all the rest
                  val = Value{string{ i, token.end() }};
                  i = token.end();
               }
            }
            if (tokens.isParsingArgv())
            {
               o->setValue(val ? move(val) : Value{ true });
            }
            ret.push_back(o);
         }
      }
      return ret;
   }

   static vector<shared_ptr<Pattern>> parse_expr(Tokens& tokens, vector<OptionLeafPattern>& outOptions);

   static vector<shared_ptr<Pattern>> parse_atom(Tokens& tokens, vector<OptionLeafPattern>& outOptions)
   {
      // atom ::= '(' expr ')' | '[' expr ']' | 'options'
      //             | long | shorts | argument | command ;
      const string& token = tokens.current();
      vector<shared_ptr<Pattern>> ret;
      if (token == "[")
      {
         tokens.pop();
         auto expr = parse_expr(tokens, outOptions);
         auto trailing = tokens.pop();
         if (trailing != "]")
         {
            throw DocoptLanguageError("Mismatched '['");
         }
         ret.emplace_back(make_shared<OptionalBranchPattern>(move(expr)));
      }
      else if (token == "(")
      {
         tokens.pop();
         auto expr = parse_expr(tokens, outOptions);
         auto trailing = tokens.pop();
         if (trailing != ")")
         {
            throw DocoptLanguageError("Mismatched '('");
         }
         ret.emplace_back(make_shared<RequiredBranchPattern>(move(expr)));
      }
      else if (token == "options")
      {
         tokens.pop();
         ret.emplace_back(make_shared<OptionsShortcutOptionalBranchPattern>());
      }
      else if (starts_with(token, "--") && token != "--")
      {
         ret = parse_long(tokens, outOptions);
      }
      else if (starts_with(token, "-") && token != "-" && token != "--")
      {
         ret = parse_short(tokens, outOptions);
      }
      else if (is_argument_spec(token))
      {
         ret.emplace_back(make_shared<ArgumentLeafPattern>(tokens.pop()));
      }
      else
      {
         ret.emplace_back(make_shared<CommandArgumentLeafPattern>(tokens.pop()));
      }
      return ret;
   }

   static vector<shared_ptr<Pattern>> parse_seq(Tokens& tokens, vector<OptionLeafPattern>& outOptions)
   {
      // seq ::= ( atom [ '...' ] )* ;"""
      vector<shared_ptr<Pattern>> ret;
      while (tokens)
      {
         const auto& token = tokens.current();
         if (token == "]" || token == ")" || token == "|")
         {
            break;
         }
         auto atom = parse_atom(tokens, outOptions);
         if (tokens.current() == "...")
         {
            ret.emplace_back(make_shared<OneOrMoreBranchPattern>(move(atom)));
            tokens.pop();
         }
         else
         {
            move(atom.begin(), atom.end(), back_inserter(ret));
         }
      }
      return ret;
   }

   static shared_ptr<Pattern> maybe_collapse_to_required(vector<shared_ptr<Pattern>>&& seq)
   {
      if (seq.size() == 1)
      {
         return move(seq[0]);
      }
      return make_shared<RequiredBranchPattern>(move(seq));
   }

   static shared_ptr<Pattern> maybe_collapse_to_either(vector<shared_ptr<Pattern>>&& seq)
   {
      if (seq.size() == 1)
      {
         return move(seq[0]);
      }
      return make_shared<EitherBranchPattern>(move(seq));
   }

   vector<shared_ptr<Pattern>> parse_expr(Tokens& tokens, vector<OptionLeafPattern>& outOptions)
   {
      // expr ::= seq ( '|' seq )* ;
      auto seq = parse_seq(tokens, outOptions);
      if (tokens.current() != "|")
      {
         return seq;
      }
      vector<shared_ptr<Pattern>> ret;
      ret.emplace_back(maybe_collapse_to_required(move(seq)));
      while (tokens.current() == "|")
      {
         tokens.pop();
         seq = parse_seq(tokens, outOptions);
         ret.emplace_back(maybe_collapse_to_required(move(seq)));
      }
      return { maybe_collapse_to_either(move(ret)) };
   }

   static RequiredBranchPattern parse_pattern(const string& source, vector<OptionLeafPattern>& outOptions)
   {
      auto tokens = Tokens::FromPattern(source);
      auto result = parse_expr(tokens, outOptions);
      if (tokens)
      {
         throw DocoptLanguageError("Unexpected ending: '" + tokens.the_rest() + "'");
      }
      release_assert(result.size() == 1 && "top level is always one big");
      return RequiredBranchPattern{ move(result) };
   }

   static string formal_usage(const string& section)
   {
      string ret = "(";
      auto i = section.find(':') + 1;  // skip past "usage:"
      auto parts = split(section, i);
      for (size_t ii = 1; ii < parts.size(); ++ii)
      {
         if (parts[ii] == parts[0])
         {
            ret += " ) | (";
         }
         else
         {
            ret.push_back(' ');
            ret += parts[ii];
         }
      }
      ret += " )";
      return ret;
   }

   static vector<shared_ptr<Pattern>> parse_argv(Tokens tokens, vector<OptionLeafPattern>& outOptions, bool options_first)
   {
      // Parse command-line argument vector.
      //
      // If options_first:
      //    argv ::= [ long | shorts ]* [ argument ]* [ '--' [ argument ]* ] ;
      // else:
      //    argv ::= [ long | shorts | argument ]* [ '--' [ argument ]* ] ;
      vector<shared_ptr<Pattern>> ret;
      while (tokens)
      {
         const auto& token = tokens.current();
         if (token == "--")
         {
            // option list is done; convert all the rest to arguments
            while (tokens)
            {
               ret.emplace_back(make_shared<ArgumentLeafPattern>("", tokens.pop()));
            }
         }
         else if (starts_with(token, "--"))
         {
            auto&& parsed = parse_long(tokens, outOptions);
            move(parsed.begin(), parsed.end(), back_inserter(ret));
         }
         else if (token[0] == '-' && token != "-")
         {
            auto&& parsed = parse_short(tokens, outOptions);
            move(parsed.begin(), parsed.end(), back_inserter(ret));
         }
         else if (options_first)
         {
            // option list is done; convert all the rest to arguments
            while (tokens)
            {
               ret.emplace_back(make_shared<ArgumentLeafPattern>("", tokens.pop()));
            }
         }
         else
         {
            ret.emplace_back(make_shared<ArgumentLeafPattern>("", tokens.pop()));
         }
      }
      return ret;
   }

   inline vector<OptionLeafPattern> parse_defaults(const string& doc)
   {
      // This pattern is a delimiter by which we split the options.
      // The delimiter is a new line followed by a whitespace(s) followed by one or two hyphens.
      static regex const re_delimiter
      {
         "(?:^|\\n)[ \\t]*"  // a new line with leading whitespace
         "(?=-{1,2})"        // [split happens here] (positive lookahead) ... and followed by one or two hyphes
      };
      vector<OptionLeafPattern> defaults;
      for (string& str : ParseSection("options:", doc))
      {
         str.erase(str.begin(), str.begin() + static_cast<ptrdiff_t>(str.find(':')) + 1); // get rid of "options:"
         for (const auto& opt : regex_split(str, re_delimiter))
         {
            if (starts_with(opt, "-"))
            {
               defaults.emplace_back(OptionLeafPattern::parse(opt));
            }
         }
      }
      return defaults;
   }

   static bool isOptionSet(const vector<shared_ptr<Pattern>>& options, const string& opt1, string const& opt2 = "")
   {
      return any_of(options.begin(), options.end(), [&](const shared_ptr<Pattern const>& opt) -> bool
      {
         const auto& name = opt->Name();
         if (name == opt1 || (!opt2.empty() && name == opt2))
         {
            const bool optionHasValue = opt->HasValue();
            return optionHasValue;
         }
         return false;
      });
   }

   static void extras(bool help, bool version, const vector<shared_ptr<Pattern>>& options)
   {
      if (help && isOptionSet(options, "-h", "--help"))
      {
         throw DocoptExitHelp();
      }
      if (version && isOptionSet(options, "--version"))
      {
         throw DocoptExitVersion();
      }
   }

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4868) // compiler may not enforce left - to - right evaluation order in braced initializer list
#endif
   static pair<RequiredBranchPattern, vector<OptionLeafPattern>> create_pattern_tree(const string& doc)
   {
      const vector<string> usage_sections = ParseSection("Usage:", doc);
      //const vector<string> usage_sections = ParseSection("usage:", doc);
      if (usage_sections.empty())
      {
         throw DocoptLanguageError("'usage:' (case-insensitive) not found.");
      }
      if (usage_sections.size() > 1)
      {
         throw DocoptLanguageError("More than one 'usage:' (case-insensitive).");
      }
      vector<OptionLeafPattern> options = parse_defaults(doc);
      RequiredBranchPattern pattern = parse_pattern(formal_usage(usage_sections[0]), options);
      const vector<OptionLeafPattern const*> pattern_options = FlatFilter<OptionLeafPattern const>(pattern);
      using UniqueOptions = unordered_set<OptionLeafPattern const*, PatternHasher, PatternPointerEquality>;
      const UniqueOptions uniq_pattern_options{ pattern_options.begin(), pattern_options.end() };
      // Fix up any "[options]" shortcuts with the actual option tree
      for (auto& options_shortcut : FlatFilter<OptionsShortcutOptionalBranchPattern>(pattern))
      {
         const vector<OptionLeafPattern> doc_options = parse_defaults(doc);
         // set(doc_options) - set(pattern_options)
         UniqueOptions uniqueDocOptions;
         for (const auto& opt : doc_options)
         {
            if (uniq_pattern_options.count(&opt))
            {
               continue;
            }
            uniqueDocOptions.insert(&opt);
         }
         // turn into shared_ptr's and set as children
         vector<shared_ptr<Pattern>> children;
         transform(uniqueDocOptions.begin(), uniqueDocOptions.end(),
            back_inserter(children), [](OptionLeafPattern const* opt)
         {
            return make_shared<OptionLeafPattern>(*opt);
         });
         options_shortcut->setChildren(move(children));
      }
      return { move(pattern), move(options) };
   }
#ifdef _WIN32
#pragma warning(pop)
#endif

   map<string, Value> docopt_parse(
      const string& doc,
      const vector<string>& argv,
      bool help,
      bool version,
      bool options_first)
   {
      RequiredBranchPattern pattern;
      vector<OptionLeafPattern> options;
      try
      {
         tie(pattern, options) = create_pattern_tree(doc);
      }
      catch (const Tokens::OptionError& error)
      {
         throw DocoptLanguageError(error.what());
      }
      vector<shared_ptr<Pattern>> argvPatterns;
      try
      {
         argvPatterns = parse_argv(Tokens(argv), options, options_first);
      }
      catch (const Tokens::OptionError& error)
      {
         throw DocoptArgumentError(error.what());
      }
      extras(help, version, argvPatterns);
      vector<shared_ptr<LeafPattern>> collected;
      bool didMatch = pattern.fix().Match(argvPatterns, collected);
      if (didMatch && argvPatterns.empty())
      {
         map<string, Value> ret;
         // (a.name, a.value) for a in (pattern.flat() + collected)
         for (LeafPattern* leafPattern : pattern.LeafPatterns())
         {
            ret[leafPattern->Name()] = leafPattern->getValue();
         }
         for (const auto& leafPattern : collected)
         {
            ret[leafPattern->Name()] = leafPattern->getValue();
         }
         return ret;
      }
      if (didMatch)
      {
         const string leftover = join(argv.begin(), argv.end(), " ");
         throw DocoptArgumentError("Unexpected argument: " + leftover);
      }
      throw DocoptArgumentError("Error: Invalid command line arguments. See program usage below for valid command line arguments:\n");
   }

   map<string, Value> docopt(
      const string& doc,
      const vector<string>& argv,
      bool help,
      const string& version,
      bool options_first) noexcept
   {
      try
      {
         const map<string, Value> docoptArguments =
            docopt_parse(doc, argv, help, !version.empty(), options_first);
         return docoptArguments;
      }
      catch (const DocoptExitHelp&)
      {
         cout << doc << '\n';
         exit(0);
      }
      catch (const DocoptExitVersion&)
      {
         cout << version << '\n';
         exit(0);
      }
      catch (const DocoptLanguageError& error)
      {
         cerr << "Docopt usage string could not be parsed\n";
         cerr << error.what() << '\n';
         exit(-1);
      }
      catch (const DocoptArgumentError& error)
      {
         cerr << error.what();
         cout << '\n';
         cout << doc << '\n';
         exit(-1);
      }
   }

   inline ostream& operator<<(ostream& os, const docopt::Value& docoptValue)
   {
      if (docoptValue.IsBool())
      {
         const bool docoptValueAsBool = docoptValue.AsBool();
         os << (docoptValueAsBool ? "true" : "false");
      }
      else if (docoptValue.IsLong())
      {
         const long docoptValueAsLong = docoptValue.AsLong();
         os << docoptValueAsLong;
      }
      else if (docoptValue.IsSizeT())
      {
         const size_t docoptValueAsSizeT = docoptValue.AsSizeT();
         os << docoptValueAsSizeT;
      }
      else if (docoptValue.IsString())
      {
         const string& docoptValueAsString = docoptValue.AsString();
         os << '"' << docoptValueAsString << '"';
      }
      else if (docoptValue.IsStringList())
      {
         const vector<string>& docoptValueAsStringList = docoptValue.AsStringList();
         os << "[";
         bool first = true;
         for (const string& el : docoptValueAsStringList)
         {
            if (first)
            {
               first = false;
            }
            else
            {
               os << ", ";
            }
            os << '"' << el << '"';
         }
         os << "]";
      }
      else
      {
         os << "null";
      }
      return os;
   }
}
