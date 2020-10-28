#pragma once

template<typename T>
inline void hash_combine(std::size_t& seed, const T& v)
{
   // From boost::hash_combine
   std::hash<T> hasher;
   seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace docopt
{
   struct Value
   {
   private:
      enum class Kind
      {
         Empty,
         Bool,
         Long,
         String,
         StringList
      };

      struct Variant
      {
         bool boolValue = false;
         long longValue = 0;
         std::string strValue;
         std::vector<std::string> strList;
      };

      Kind kind = Kind::Empty;
      Variant variant{};
   public:
      Value() = default;
      Value(std::string);
      Value(std::vector<std::string>);

      explicit Value(bool);
      explicit Value(long);
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
            const std::string& str = variant.strValue;
            std::size_t pos;
            const long ret = stol(str, &pos); // Throws if it can't convert
            if (pos != str.length())
            {
               // The string ended in non-digits
               throw std::runtime_error(str + " contains non-numeric characters");
            }
            return ret;
         }
         return variant.longValue;
      }

      const std::string& AsString() const
      {
         return variant.strValue;
      }

      const std::vector<std::string>& AsStringList() const
      {
         return variant.strList;
      }

      size_t Hash() const noexcept
      {
         switch (kind)
         {
         case Kind::String:
         {
            return std::hash<std::string>()(variant.strValue);
         }
         case Kind::StringList:
         {
            size_t seed = std::hash<size_t>()(variant.strList.size());
            for (const std::string& str : variant.strList)
            {
               hash_combine(seed, str);
            }
            return seed;
         }
         case Kind::Bool:
         {
            return std::hash<bool>()(variant.boolValue);
         }
         case Kind::Long:
         {
            return std::hash<long>()(variant.longValue);
         }
         case Kind::Empty:
         default:
         {
            return std::hash<void*>()(nullptr);
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

inline std::ostream& operator<<(std::ostream& os, const docopt::Value& docoptValue)
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
   else if (docoptValue.IsString())
   {
      const std::string& docoptValueAsString = docoptValue.AsString();
      os << '"' << docoptValueAsString << '"';
   }
   else if (docoptValue.IsStringList())
   {
      const std::vector<std::string>& docoptValueAsStringList = docoptValue.AsStringList();
      os << "[";
      bool first = true;
      for (const std::string& el : docoptValueAsStringList)
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

namespace docopt
{
   inline Value::Value(bool v)
      : kind(Kind::Bool)
   {
      variant.boolValue = v;
   }

   inline Value::Value(long v)
      : kind(Kind::Long)
   {
      variant.longValue = v;
   }

   inline Value::Value(std::string v)
      : kind(Kind::String)
   {
      new (&variant.strValue) std::string(std::move(v));
   }

   inline Value::Value(std::vector<std::string> v)
      : kind(Kind::StringList)
   {
      new (&variant.strList) std::vector<std::string>(std::move(v));
   }

   inline Value::Value(const Value& other)
      : kind(other.kind)
   {
      switch (kind)
      {
      case Kind::String:
         new (&variant.strValue) std::string(other.variant.strValue);
         break;
      case Kind::StringList:
         new (&variant.strList) std::vector<std::string>(other.variant.strList);
         break;
      case Kind::Bool:
         variant.boolValue = other.variant.boolValue;
         break;
      case Kind::Long:
         variant.longValue = other.variant.longValue;
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
         new (&variant.strValue) std::string(std::move(other.variant.strValue));
         break;
      case Kind::StringList:
         new (&variant.strList) std::vector<std::string>(std::move(other.variant.strList));
         break;
      case Kind::Bool:
         variant.boolValue = other.variant.boolValue;
         break;
      case Kind::Long:
         variant.longValue = other.variant.longValue;
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
      new (this) Value(std::move(other));
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

   struct DocoptLanguageError : std::runtime_error
   {
      using runtime_error::runtime_error;
   };

   struct DocoptArgumentError : std::runtime_error
   {
      using runtime_error::runtime_error;
   };

   struct DocoptExitHelp : std::runtime_error
   {
      DocoptExitHelp() : std::runtime_error("Docopt --help argument encountered") {}
   };

   struct DocoptExitVersion : std::runtime_error
   {
      DocoptExitVersion() : std::runtime_error("Docopt --version argument encountered") {}
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
   inline std::map<std::string, Value> docopt_parse(
      const std::string& doc,
      const std::vector<std::string>& argv,
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
   inline std::map<std::string, Value> docopt(
      const std::string& doc,
      const std::vector<std::string>& argv,
      bool help,
      const std::string& version,
      bool options_first) noexcept;

   inline bool starts_with(const std::string& str, const std::string& prefix)
   {
      if (str.length() < prefix.length())
      {
         return false;
      }
      return std::equal(prefix.begin(), prefix.end(), str.begin());
   }

   inline std::string trim(std::string&& str, const std::string& whitespace = " \t\n")
   {
      const size_t strEnd = str.find_last_not_of(whitespace);
      if (strEnd == std::string::npos)
      {
         return {}; // no content
      }
      str.erase(strEnd + 1);
      const size_t strBegin = str.find_first_not_of(whitespace);
      str.erase(0, strBegin);
      return std::move(str);
   }

   inline std::vector<std::string> split(const std::string& str, size_t pos = 0)
   {
      const char* const anySpace = " \t\r\n\v\f";
      std::vector<std::string> ret;
      while (pos != std::string::npos)
      {
         const size_t start = str.find_first_not_of(anySpace, pos);
         if (start == std::string::npos)
         {
            break;
         }
         const size_t end = str.find_first_of(anySpace, start);
         const size_t size = end == std::string::npos ? end : end - start;
         ret.emplace_back(str.substr(start, size));
         pos = end;
      }
      return ret;
   }

   inline std::tuple<std::string, std::string, std::string> partition(std::string str, const std::string& point)
   {
      std::tuple<std::string, std::string, std::string> ret;
      const size_t i = str.find(point);
      if (i == std::string::npos)
      {
         // no match: string goes in 0th spot only
      }
      else
      {
         std::get<2>(ret) = str.substr(i + point.size());
         std::get<1>(ret) = point;
         str.resize(i);
      }
      std::get<0>(ret) = std::move(str);
      return ret;
   }

   template<typename I>
   std::string join(I iter, I end, const std::string& delimiter)
   {
      if (iter == end)
      {
         return {};
      }
      std::string ret = *iter;
      for (++iter; iter != end; ++iter)
      {
         ret.append(delimiter);
         ret.append(*iter);
      }
      return ret;
   }

   inline std::vector<std::string> regex_split(const std::string& text, const std::regex& regexPattern)
   {
      std::vector<std::string> patternSplitText;
      for (auto it = std::sregex_token_iterator(text.begin(), text.end(), regexPattern, -1); it != std::sregex_token_iterator(); ++it)
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
      size_t operator()(const std::shared_ptr<P>& pattern) const
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
      bool operator()(const std::shared_ptr<P1>& p1, const std::shared_ptr<P2>& p2) const
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

   using UniquePatternSet = std::unordered_set<std::shared_ptr<Pattern>, PatternHasher, PatternPointerEquality>;

   class Pattern
   {
   public:
      std::vector<LeafPattern*> LeafPatterns();
      virtual std::vector<Pattern*> Flat(bool(*filter)(Pattern const*)) = 0;
      virtual void CollectLeaves(std::vector<LeafPattern*>&) = 0;
      virtual bool Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const = 0;
      virtual const std::string& Name() const = 0;
      virtual size_t Hash() const = 0;
      virtual bool HasValue() const { return false; }
      virtual ~Pattern() = default;
   };

   class LeafPattern : public Pattern
   {
   private:
      std::string _name;
      Value _value;
   protected:
      virtual std::pair<size_t, std::shared_ptr<LeafPattern>> SingleMatch(const std::vector<std::shared_ptr<Pattern>>&) const = 0;
   public:
      LeafPattern(std::string name, Value value = {})
         : _name(std::move(name))
         , _value(std::move(value))
      {
      }

      virtual std::vector<Pattern*> Flat(bool(*filter)(Pattern const*)) override
      {
         if (filter(this))
         {
            return { this };
         }
         return {};
      }

      virtual void CollectLeaves(std::vector<LeafPattern*>& outLeafPatterns) override final
      {
         outLeafPatterns.push_back(this);
      }

      virtual bool Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const override;

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
         _value = std::move(value);
      }

      virtual const std::string& Name() const override
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
      std::vector<std::shared_ptr<Pattern>> fChildren;
   public:
      BranchPattern(std::vector<std::shared_ptr<Pattern>> children = {})
         : fChildren(std::move(children))
      {
      }

      Pattern& fix()
      {
         UniquePatternSet patterns;
         fix_identities(patterns);
         FixRepeatingArguments();
         return *this;
      }

      virtual const std::string& Name() const override
      {
         throw std::runtime_error("Logic error: name() shouldnt be called on a BranchPattern");
      }

      virtual const Value& getValue() const
      {
         throw std::runtime_error("Logic error: name() shouldnt be called on a BranchPattern");
      }

      virtual std::vector<Pattern*> Flat(bool(*filter)(Pattern const*)) override
      {
         if (filter(this))
         {
            return { this };
         }
         std::vector<Pattern*> ret;
         for (auto& child : fChildren)
         {
            auto sublist = child->Flat(filter);
            ret.insert(ret.end(), sublist.begin(), sublist.end());
         }
         return ret;
      }

      virtual void CollectLeaves(std::vector<LeafPattern*>& lst) override final
      {
         for (auto& child : fChildren)
         {
            child->CollectLeaves(lst);
         }
      }

      void setChildren(std::vector<std::shared_ptr<Pattern>> children)
      {
         fChildren = std::move(children);
      }

      const std::vector<std::shared_ptr<Pattern>>& children() const
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
      virtual std::pair<size_t, std::shared_ptr<LeafPattern>> SingleMatch(const std::vector<std::shared_ptr<Pattern>>& left) const override;
   };

   class CommandArgumentLeafPattern : public ArgumentLeafPattern
   {
   public:
      CommandArgumentLeafPattern(std::string name, Value v = Value{ false })
         : ArgumentLeafPattern(std::move(name), std::move(v))
      {
      }
   protected:
      virtual std::pair<size_t, std::shared_ptr<LeafPattern>> SingleMatch(const std::vector<std::shared_ptr<Pattern>>& left) const override;
   };

   class OptionLeafPattern final : public LeafPattern
   {
   protected:
      virtual std::pair<size_t, std::shared_ptr<LeafPattern>> SingleMatch(const std::vector<std::shared_ptr<Pattern>>& left) const override;
   private:
      std::string _shortOption;
      std::string _longOption;
      int _argCount;
   public:
      static OptionLeafPattern parse(const std::string& option_description);

      OptionLeafPattern(
         std::string shortOption,
         std::string longOption,
         int argcount = 0,
         Value v = Value{ false })
         : LeafPattern(longOption.empty() ? shortOption : longOption, std::move(v))
         , _shortOption(std::move(shortOption))
         , _longOption(std::move(longOption))
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

      const std::string& longOption() const
      {
         return _longOption;
      }

      const std::string& shortOption() const
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
      bool Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const override;
   };

   class OptionalBranchPattern : public BranchPattern
   {
   public:
      using BranchPattern::BranchPattern;

      bool Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const override
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
      bool Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const override;
   };

   class EitherBranchPattern : public BranchPattern
   {
   public:
      using BranchPattern::BranchPattern;
      bool Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const override;
   };

   inline std::vector<LeafPattern*> Pattern::LeafPatterns()
   {
      std::vector<LeafPattern*> leafPatterns;
      CollectLeaves(leafPatterns);
      return leafPatterns;
   }

   static inline std::vector<std::vector<std::shared_ptr<Pattern>>> transform(std::vector<std::shared_ptr<Pattern>> pattern)
   {
      std::vector<std::vector<std::shared_ptr<Pattern>>> result;
      std::vector<std::vector<std::shared_ptr<Pattern>>> groups;
      groups.emplace_back(std::move(pattern));
      while (!groups.empty())
      {
         // pop off the first element
         auto children = std::move(groups[0]);
         groups.erase(groups.begin());
         // find the first branch node in the list
         auto child_iter = std::find_if(children.begin(), children.end(), [](const std::shared_ptr<Pattern>& p)
            {
               return dynamic_cast<BranchPattern const*>(p.get());
            });
         // no branch nodes left : expansion is complete for this grouping
         if (child_iter == children.end())
         {
            result.emplace_back(std::move(children));
            continue;
         }
         // pop the child from the list
         auto child = std::move(*child_iter);
         children.erase(child_iter);
         // expand the branch in the appropriate way
         if (EitherBranchPattern* either = dynamic_cast<EitherBranchPattern*>(child.get()))
         {
            // "[e] + children" for each child 'e' in Either
            for (const auto& eitherChild : either->children())
            {
               std::vector<std::shared_ptr<Pattern>> group = { eitherChild };
               group.insert(group.end(), children.begin(), children.end());
               groups.emplace_back(std::move(group));
            }
         }
         else if (OneOrMoreBranchPattern* oneOrMore = dynamic_cast<OneOrMoreBranchPattern*>(child.get()))
         {
            // child.children * 2 + children
            const auto& subchildren = oneOrMore->children();
            std::vector<std::shared_ptr<Pattern>> group = subchildren;
            group.insert(group.end(), subchildren.begin(), subchildren.end());
            group.insert(group.end(), children.begin(), children.end());
            groups.emplace_back(std::move(group));
         }
         else
         {
            // Required, Optional, OptionsShortcut
            BranchPattern* branch = dynamic_cast<BranchPattern*>(child.get());
            // child.children + children
            std::vector<std::shared_ptr<Pattern>> group = branch->children();
            group.insert(group.end(), children.begin(), children.end());
            groups.emplace_back(std::move(group));
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
      std::vector<std::vector<std::shared_ptr<Pattern>>> either = transform(children());
      for (const auto& group : either)
      {
         // use multiset to help identify duplicate entries
         std::unordered_multiset<std::shared_ptr<Pattern>, PatternHasher> group_set{ group.begin(), group.end() };
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
               std::vector<std::string> newValue;
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

   inline bool LeafPattern::Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const
   {
      auto match = SingleMatch(left);
      if (!match.second)
      {
         return false;
      }
      left.erase(left.begin() + static_cast<std::ptrdiff_t>(match.first));
      auto same_name = std::find_if(collected.begin(), collected.end(), [&](const std::shared_ptr<LeafPattern>& p)
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
      else if (getValue().IsStringList())
      {
         std::vector<std::string> val;
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
            std::cout << "docopt: Impossible is possible\n";
            ::exit(1);
         }
         if (same_name == collected.end())
         {
            collected.push_back(match.second);
            match.second->setValue(Value{ val });
         }
         else if ((**same_name).getValue().IsStringList())
         {
            const std::vector<std::string>& list = (**same_name).getValue().AsStringList();
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

   inline std::pair<size_t, std::shared_ptr<LeafPattern>> ArgumentLeafPattern::SingleMatch(const std::vector<std::shared_ptr<Pattern>>& left) const
   {
      std::pair<size_t, std::shared_ptr<LeafPattern>> ret{};
      for (size_t i = 0, size = left.size(); i < size; ++i)
      {
         auto arg = dynamic_cast<ArgumentLeafPattern const*>(left[i].get());
         if (arg)
         {
            ret.first = i;
            ret.second = std::make_shared<ArgumentLeafPattern>(Name(), arg->getValue());
            break;
         }
      }
      return ret;
   }

   inline std::pair<size_t, std::shared_ptr<LeafPattern>> CommandArgumentLeafPattern::SingleMatch(const std::vector<std::shared_ptr<Pattern>>& left) const
   {
      std::pair<size_t, std::shared_ptr<LeafPattern>> ret{};
      for (size_t i = 0, size = left.size(); i < size; ++i)
      {
         auto arg = dynamic_cast<ArgumentLeafPattern const*>(left[i].get());
         if (arg)
         {
            if (Name() == arg->getValue())
            {
               ret.first = i;
               ret.second = std::make_shared<CommandArgumentLeafPattern>(Name(), Value{ true });
            }
            break;
         }
      }
      return ret;
   }

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4868) // Warning	C4868	compiler may not enforce left - to - right evaluation order in braced initializer list
#endif
   inline OptionLeafPattern OptionLeafPattern::parse(const std::string& option_description)
   {
      std::string shortOption, longOption;
      int argcount = 0;
      Value val{ false };
      auto double_space = option_description.find("  ");
      auto options_end = option_description.end();
      if (double_space != std::string::npos)
      {
         options_end = option_description.begin() + static_cast<std::ptrdiff_t>(double_space);
      }
      static const std::regex pattern{ "(-{1,2})?(.*?)([,= ]|$)" };
      for (std::sregex_iterator i{ option_description.begin(), options_end, pattern, std::regex_constants::match_not_null },
         e{};
         i != e;
         ++i)
      {
         const std::smatch& match = *i;
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
            std::string m = match[2];
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
         std::smatch match;
         static const std::regex regexPattern{ "\\[default: (.*)\\]", std::regex::icase };
         if (std::regex_search(options_end, option_description.end(), match, regexPattern))
         {
            val = match[1].str();
         }
      }
      return { std::move(shortOption), std::move(longOption), argcount, std::move(val) };
   }
#ifdef _WIN32
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 4868) // compiler may not enforce left - to - right evaluation order in braced initializer list
#endif
   inline std::pair<size_t, std::shared_ptr<LeafPattern>> OptionLeafPattern::SingleMatch(const std::vector<std::shared_ptr<Pattern>>& left) const
   {
      auto thematch = find_if(left.begin(), left.end(), [this](const std::shared_ptr<Pattern>& a)
         {
            auto leaf = std::dynamic_pointer_cast<LeafPattern>(a);
            return leaf && this->Name() == leaf->Name();
         });
      if (thematch == left.end())
      {
         return {};
      }
      return { std::distance(left.begin(), thematch), std::dynamic_pointer_cast<LeafPattern>(*thematch) };
   }
#ifdef _WIN32
#pragma warning(pop)
#endif

   inline bool RequiredBranchPattern::Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const
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
      left = std::move(l);
      collected = std::move(c);
      return true;
   }

   inline bool OneOrMoreBranchPattern::Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const
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
      left = std::move(l);
      collected = std::move(c);
      return true;
   }

   inline bool EitherBranchPattern::Match(std::vector<std::shared_ptr<Pattern>>& left, std::vector<std::shared_ptr<LeafPattern>>& collected) const
   {
      using Outcome = std::pair<std::vector<std::shared_ptr<Pattern>>, std::vector<std::shared_ptr<LeafPattern>>>;
      std::vector<Outcome> outcomes;
      for (const auto& pattern : fChildren)
      {
         // need a copy so we apply the same one for every iteration
         auto l = left;
         auto c = collected;
         bool matched = pattern->Match(l, c);
         if (matched)
         {
            outcomes.emplace_back(std::move(l), std::move(c));
         }
      }
      auto min = std::min_element(outcomes.begin(), outcomes.end(), [](const Outcome& o1, const Outcome& o2)
         {
            return o1.first.size() < o2.first.size();
         });
      if (min == outcomes.end())
      {
         // (left, collected) unchanged
         return false;
      }
      std::tie(left, collected) = std::move(*min);
      return true;
   }

   class Tokens
   {
   private:
      std::vector<std::string> fTokens;
      size_t fIndex = 0;
      bool fIsParsingArgv;
   public:
      Tokens(std::vector<std::string> tokens, bool isParsingArgv = true)
         : fTokens(std::move(tokens))
         , fIsParsingArgv(isParsingArgv)
      {
      }

      explicit operator bool() const
      {
         return fIndex < fTokens.size();
      }

      static Tokens FromPattern(const std::string& source)
      {
         static const std::regex re_separators
         {
            "(?:\\s*)" // any spaces (non-matching subgroup)
            "("
            "[\\[\\]\\(\\)\\|]" // one character of brackets or parens or pipe character
            "|"
            "\\.\\.\\."  // elipsis
            ")"
         };
         static const std::regex re_strings
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
         std::vector<std::string> tokens;
         std::for_each(std::sregex_iterator{ source.begin(), source.end(), re_separators },
            std::sregex_iterator{},
            [&](const std::smatch& match)
            {
               // handle anything before the separator (this is the "stuff" between the delimeters)
               if (match.prefix().matched)
               {
                  std::for_each(std::sregex_iterator{ match.prefix().first, match.prefix().second, re_strings },
                     std::sregex_iterator{},
                     [&](const std::smatch& m)
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

      const std::string& current() const
      {
         if (*this)
         {
            return fTokens[fIndex];
         }
         static std::string const empty;
         return empty;
      }

      std::string the_rest() const
      {
         if (!*this)
         {
            return {};
         }
         return join(fTokens.begin() + static_cast<std::ptrdiff_t>(fIndex), fTokens.end(), " ");
      }

      std::string pop()
      {
         return std::move(fTokens.at(fIndex++));
      }

      bool isParsingArgv() const
      {
         return fIsParsingArgv;
      }

      struct OptionError : std::runtime_error
      {
         using runtime_error::runtime_error;
      };
   };

   // Get all instances of 'T' from the pattern
   template<typename T>
   std::vector<T*> FlatFilter(Pattern& pattern)
   {
      std::vector<Pattern*> flattened = pattern.Flat([](Pattern const* p) -> bool
         {
            return dynamic_cast<T const*>(p) != nullptr;
         });

      // now, we're guaranteed to have T*'s, so just use static_cast
      std::vector<T*> ret;
      std::transform(flattened.begin(), flattened.end(), std::back_inserter(ret), [](Pattern* p)
         {
            return static_cast<T*>(p);
         });
      return ret;
   }

   static std::vector<std::string> ParseSection(const std::string& name, const std::string& source)
   {
      // ECMAScript regex only has "?=" for a non-matching lookahead. In order to make sure we always have
      // a newline to anchor our matching, we have to avoid matching the final newline of each grouping.
      // Therefore, our regex is adjusted from the docopt Python one to use ?= to match the newlines before
      // the following lines, rather than after.
      std::regex const re_section_pattern
      {
         "(?:^|\\n)"  // anchored at a linebreak (or start of string)
         "("
         "[^\\n]*" + name + "[^\\n]*(?=\\n?)" // a line that contains the name
         "(?:\\n[ \\t].*?(?=\\n|$))*"         // followed by any number of lines that are indented
         ")",
         std::regex::icase
      };
      std::vector<std::string> ret;
      std::for_each(std::sregex_iterator(source.begin(), source.end(), re_section_pattern),
         std::sregex_iterator(),
         [&](const std::smatch& match)
         {
            ret.push_back(trim(match[1].str()));
         });
      return ret;
   }

   static bool is_argument_spec(const std::string& token)
   {
      if (token.empty())
      {
         return false;
      }
      if (token[0] == '<' && token[token.size() - 1] == '>')
      {
         return true;
      }
      if (std::all_of(token.begin(), token.end(), &::isupper))
      {
         return true;
      }
      return false;
   }

   template<typename I>
   std::vector<std::string> longOptions(I iter, I end)
   {
      std::vector<std::string> ret;
      std::transform(iter, end, std::back_inserter(ret), [](typename I::reference opt) { return opt->longOption(); });
      return ret;
   }

   static std::vector<std::shared_ptr<Pattern>> parse_long(Tokens& tokens, std::vector<OptionLeafPattern>& outOptions)
   {
      // long ::= '--' chars [ ( ' ' | '=' ) chars ] ;
      std::string longOpt, equal;
      Value val;
      std::tie(longOpt, equal, val) = partition(tokens.pop(), "=");
      release_assert(starts_with(longOpt, "--"));
      if (equal.empty())
      {
         val = Value{};
      }
      // detect with options match this long option
      std::vector<OptionLeafPattern const*> similar;
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
      std::vector<std::shared_ptr<Pattern>> ret;
      if (similar.size() > 1)
      {
         // might be simply specified ambiguously 2+ times?
         std::vector<std::string> prefixes = longOptions(similar.begin(), similar.end());
         std::string error = "'" + longOpt + "' is not a unique prefix: ";
         error.append(join(prefixes.begin(), prefixes.end(), ", "));
         throw Tokens::OptionError(std::move(error));
      }
      else if (similar.empty())
      {
         int argcount = equal.empty() ? 0 : 1;
         outOptions.emplace_back("", longOpt, argcount);
         auto o = std::make_shared<OptionLeafPattern>(outOptions.back());
         if (tokens.isParsingArgv())
         {
            o->setValue(argcount ? Value{ val } : Value{ true });
         }
         ret.push_back(o);
      }
      else
      {
         auto o = std::make_shared<OptionLeafPattern>(*similar[0]);
         if (o->argCount() == 0)
         {
            if (val)
            {
               std::string error = o->longOption() + " must not have an argument";
               throw Tokens::OptionError(std::move(error));
            }
         }
         else
         {
            if (!val)
            {
               const auto& token = tokens.current();
               if (token.empty() || token == "--")
               {
                  std::string error = o->longOption() + " requires an argument";
                  throw Tokens::OptionError(std::move(error));
               }
               val = tokens.pop();
            }
         }
         if (tokens.isParsingArgv())
         {
            o->setValue(val ? std::move(val) : Value{ true });
         }
         ret.push_back(o);
      }
      return ret;
   }

   static std::vector<std::shared_ptr<Pattern>> parse_short(Tokens& tokens, std::vector<OptionLeafPattern>& outOptions)
   {
      // shorts ::= '-' ( chars )* [ [ ' ' ] chars ] ;
      auto token = tokens.pop();
      release_assert(starts_with(token, "-"));
      release_assert(!starts_with(token, "--"));
      auto i = token.begin();
      ++i; // skip the leading '-'
      std::vector<std::shared_ptr<Pattern>> ret;
      while (i != token.end())
      {
         std::string shortOpt = { '-', *i };
         ++i;
         std::vector<OptionLeafPattern const*> similar;
         for (const auto& option : outOptions)
         {
            if (option.shortOption() == shortOpt)
            {
               similar.push_back(&option);
            }
         }
         if (similar.size() > 1)
         {
            std::string error = shortOpt + " is specified ambiguously " + std::to_string(similar.size()) + " times";
            throw Tokens::OptionError(std::move(error));
         }
         else if (similar.empty())
         {
            outOptions.emplace_back(shortOpt, "", 0);
            auto o = std::make_shared<OptionLeafPattern>(outOptions.back());
            if (tokens.isParsingArgv())
            {
               o->setValue(Value{ true });
            }
            ret.push_back(o);
         }
         else
         {
            auto o = std::make_shared<OptionLeafPattern>(*similar[0]);
            Value val;
            if (o->argCount())
            {
               if (i == token.end())
               {
                  // consume the next token
                  const auto& ttoken = tokens.current();
                  if (ttoken.empty() || ttoken == "--")
                  {
                     std::string error = shortOpt + " requires an argument";
                     throw Tokens::OptionError(std::move(error));
                  }
                  val = tokens.pop();
               }
               else
               {
                  // consume all the rest
                  val = std::string{ i, token.end() };
                  i = token.end();
               }
            }
            if (tokens.isParsingArgv())
            {
               o->setValue(val ? std::move(val) : Value{ true });
            }
            ret.push_back(o);
         }
      }
      return ret;
   }

   static std::vector<std::shared_ptr<Pattern>> parse_expr(Tokens& tokens, std::vector<OptionLeafPattern>& outOptions);

   static std::vector<std::shared_ptr<Pattern>> parse_atom(Tokens& tokens, std::vector<OptionLeafPattern>& outOptions)
   {
      // atom ::= '(' expr ')' | '[' expr ']' | 'options'
      //             | long | shorts | argument | command ;
      const std::string& token = tokens.current();
      std::vector<std::shared_ptr<Pattern>> ret;
      if (token == "[")
      {
         const std::string popResult = tokens.pop();
         auto expr = parse_expr(tokens, outOptions);
         auto trailing = tokens.pop();
         if (trailing != "]")
         {
            throw DocoptLanguageError("Mismatched '['");
         }
         ret.emplace_back(std::make_shared<OptionalBranchPattern>(std::move(expr)));
      }
      else if (token == "(")
      {
         const std::string popResult = tokens.pop();
         auto expr = parse_expr(tokens, outOptions);
         auto trailing = tokens.pop();
         if (trailing != ")")
         {
            throw DocoptLanguageError("Mismatched '('");
         }
         ret.emplace_back(std::make_shared<RequiredBranchPattern>(std::move(expr)));
      }
      else if (token == "options")
      {
         const std::string popResult = tokens.pop();
         ret.emplace_back(std::make_shared<OptionsShortcutOptionalBranchPattern>());
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
         ret.emplace_back(std::make_shared<ArgumentLeafPattern>(tokens.pop()));
      }
      else
      {
         ret.emplace_back(std::make_shared<CommandArgumentLeafPattern>(tokens.pop()));
      }
      return ret;
   }

   static std::vector<std::shared_ptr<Pattern>> parse_seq(Tokens& tokens, std::vector<OptionLeafPattern>& outOptions)
   {
      // seq ::= ( atom [ '...' ] )* ;"""
      std::vector<std::shared_ptr<Pattern>> ret;
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
            ret.emplace_back(std::make_shared<OneOrMoreBranchPattern>(std::move(atom)));
            const std::string popResult = tokens.pop();
         }
         else
         {
            std::move(atom.begin(), atom.end(), std::back_inserter(ret));
         }
      }
      return ret;
   }

   static std::shared_ptr<Pattern> maybe_collapse_to_required(std::vector<std::shared_ptr<Pattern>>&& seq)
   {
      if (seq.size() == 1)
      {
         return std::move(seq[0]);
      }
      return std::make_shared<RequiredBranchPattern>(std::move(seq));
   }

   static std::shared_ptr<Pattern> maybe_collapse_to_either(std::vector<std::shared_ptr<Pattern>>&& seq)
   {
      if (seq.size() == 1)
      {
         return std::move(seq[0]);
      }
      return std::make_shared<EitherBranchPattern>(std::move(seq));
   }

   std::vector<std::shared_ptr<Pattern>> parse_expr(Tokens& tokens, std::vector<OptionLeafPattern>& outOptions)
   {
      // expr ::= seq ( '|' seq )* ;
      auto seq = parse_seq(tokens, outOptions);
      if (tokens.current() != "|")
      {
         return seq;
      }
      std::vector<std::shared_ptr<Pattern>> ret;
      ret.emplace_back(maybe_collapse_to_required(std::move(seq)));
      while (tokens.current() == "|")
      {
         const std::string popResult = tokens.pop();
         seq = parse_seq(tokens, outOptions);
         ret.emplace_back(maybe_collapse_to_required(std::move(seq)));
      }
      return { maybe_collapse_to_either(std::move(ret)) };
   }

   static RequiredBranchPattern parse_pattern(const std::string& source, std::vector<OptionLeafPattern>& outOptions)
   {
      auto tokens = Tokens::FromPattern(source);
      auto result = parse_expr(tokens, outOptions);
      if (tokens)
      {
         throw DocoptLanguageError("Unexpected ending: '" + tokens.the_rest() + "'");
      }
      release_assert(result.size() == 1 && "top level is always one big");
      return RequiredBranchPattern{ std::move(result) };
   }

   static std::string formal_usage(const std::string& section)
   {
      std::string ret = "(";
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

   static std::vector<std::shared_ptr<Pattern>> parse_argv(Tokens tokens, std::vector<OptionLeafPattern>& outOptions, bool options_first)
   {
      // Parse command-line argument vector.
      //
      // If options_first:
      //    argv ::= [ long | shorts ]* [ argument ]* [ '--' [ argument ]* ] ;
      // else:
      //    argv ::= [ long | shorts | argument ]* [ '--' [ argument ]* ] ;
      std::vector<std::shared_ptr<Pattern>> ret;
      while (tokens)
      {
         const auto& token = tokens.current();
         if (token == "--")
         {
            // option list is done; convert all the rest to arguments
            while (tokens)
            {
               ret.emplace_back(std::make_shared<ArgumentLeafPattern>("", tokens.pop()));
            }
         }
         else if (starts_with(token, "--"))
         {
            auto&& parsed = parse_long(tokens, outOptions);
            std::move(parsed.begin(), parsed.end(), std::back_inserter(ret));
         }
         else if (token[0] == '-' && token != "-")
         {
            auto&& parsed = parse_short(tokens, outOptions);
            std::move(parsed.begin(), parsed.end(), std::back_inserter(ret));
         }
         else if (options_first)
         {
            // option list is done; convert all the rest to arguments
            while (tokens)
            {
               ret.emplace_back(std::make_shared<ArgumentLeafPattern>("", tokens.pop()));
            }
         }
         else
         {
            ret.emplace_back(std::make_shared<ArgumentLeafPattern>("", tokens.pop()));
         }
      }
      return ret;
   }

   inline std::vector<OptionLeafPattern> parse_defaults(const std::string& doc)
   {
      // This pattern is a delimiter by which we split the options.
      // The delimiter is a new line followed by a whitespace(s) followed by one or two hyphens.
      static std::regex const re_delimiter
      {
         "(?:^|\\n)[ \\t]*"  // a new line with leading whitespace
         "(?=-{1,2})"        // [split happens here] (positive lookahead) ... and followed by one or two hyphes
      };
      std::vector<OptionLeafPattern> defaults;
      for (std::string& str : ParseSection("options:", doc))
      {
         str.erase(str.begin(), str.begin() + static_cast<std::ptrdiff_t>(str.find(':')) + 1); // get rid of "options:"
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

   static bool isOptionSet(const std::vector<std::shared_ptr<Pattern>>& options, const std::string& opt1, std::string const& opt2 = "")
   {
      return std::any_of(options.begin(), options.end(), [&](const std::shared_ptr<Pattern const>& opt) -> bool
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

   static void extras(bool help, bool version, const std::vector<std::shared_ptr<Pattern>>& options)
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
   static std::pair<RequiredBranchPattern, std::vector<OptionLeafPattern>> create_pattern_tree(const std::string& doc)
   {
      const std::vector<std::string> usage_sections = ParseSection("usage:", doc);
      if (usage_sections.empty())
      {
         throw DocoptLanguageError("'usage:' (case-insensitive) not found.");
      }
      if (usage_sections.size() > 1)
      {
         throw DocoptLanguageError("More than one 'usage:' (case-insensitive).");
      }
      std::vector<OptionLeafPattern> options = parse_defaults(doc);
      RequiredBranchPattern pattern = parse_pattern(formal_usage(usage_sections[0]), options);
      const std::vector<OptionLeafPattern const*> pattern_options = FlatFilter<OptionLeafPattern const>(pattern);
      using UniqueOptions = std::unordered_set<OptionLeafPattern const*, PatternHasher, PatternPointerEquality>;
      const UniqueOptions uniq_pattern_options{ pattern_options.begin(), pattern_options.end() };
      // Fix up any "[options]" shortcuts with the actual option tree
      for (auto& options_shortcut : FlatFilter<OptionsShortcutOptionalBranchPattern>(pattern))
      {
         const std::vector<OptionLeafPattern> doc_options = parse_defaults(doc);
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
         std::vector<std::shared_ptr<Pattern>> children;
         std::transform(uniqueDocOptions.begin(), uniqueDocOptions.end(),
            std::back_inserter(children), [](OptionLeafPattern const* opt)
            {
               return std::make_shared<OptionLeafPattern>(*opt);
            });
         options_shortcut->setChildren(std::move(children));
      }
      return { std::move(pattern), std::move(options) };
   }
#ifdef _WIN32
#pragma warning(pop)
#endif

   std::map<std::string, Value> docopt_parse(
      const std::string& doc,
      const std::vector<std::string>& argv,
      bool help,
      bool version,
      bool options_first)
   {
      RequiredBranchPattern pattern;
      std::vector<OptionLeafPattern> options;
      try
      {
         std::tie(pattern, options) = create_pattern_tree(doc);
      }
      catch (const Tokens::OptionError & error)
      {
         throw DocoptLanguageError(error.what());
      }
      std::vector<std::shared_ptr<Pattern>> argvPatterns;
      try
      {
         argvPatterns = parse_argv(Tokens(argv), options, options_first);
      }
      catch (const Tokens::OptionError & error)
      {
         throw DocoptArgumentError(error.what());
      }
      extras(help, version, argvPatterns);
      std::vector<std::shared_ptr<LeafPattern>> collected;
      bool didMatch = pattern.fix().Match(argvPatterns, collected);
      if (didMatch && argvPatterns.empty())
      {
         std::map<std::string, Value> ret;
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
         const std::string leftover = join(argv.begin(), argv.end(), " ");
         throw DocoptArgumentError("Unexpected argument: " + leftover);
      }
      throw DocoptArgumentError("Error: Invalid command line arguments. See program usage below for valid command line arguments:\n");
   }

   std::map<std::string, Value> docopt(
      const std::string& doc,
      const std::vector<std::string>& argv,
      bool help,
      const std::string& version,
      bool options_first) noexcept
   {
      try
      {
         const std::map<std::string, Value> docoptArguments =
            docopt_parse(doc, argv, help, !version.empty(), options_first);
         return docoptArguments;
      }
      catch (const DocoptExitHelp&)
      {
         std::cout << doc << '\n';
         std::exit(0);
      }
      catch (const DocoptExitVersion&)
      {
         std::cout << version << '\n';
         std::exit(0);
      }
      catch (const DocoptLanguageError & error)
      {
         std::cerr << "Docopt usage string could not be parsed\n";
         std::cerr << error.what() << '\n';
         std::exit(-1);
      }
      catch (const DocoptArgumentError & error)
      {
         std::cerr << error.what();
         std::cout << '\n';
         std::cout << doc << '\n';
         std::exit(-1);
      }
   }
}
