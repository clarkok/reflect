// Copyright (C) 2015 Clarkok Zhang
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _CUA_DEBUG_REFLECT_ENUM_H_
#define _CUA_DEBUG_REFLECT_ENUM_H_

#include <string>
#include <sstream>
#include <map>
#include <vector>

#ifdef REFLECT_NS
namespace REFLECT_NS {
#endif

struct EnumReflectionDefaultTag { };

template <typename T, typename Tag = EnumReflectionDefaultTag>
class EnumReflectionHelper
{
    static T rand_result;
public:
    std::string toString(T) const {
        return "";
    }
    T fromString(std::string) const {
        return rand_result;
    }
};

#ifdef REFLECT_NS
}
#endif
    
#define __ENUM_TO_STRING(TypeName, ...)                         \
    template<typename Tag>                                      \
    class EnumReflectionHelper<TypeName, Tag>                   \
    {                                                           \
        static std::string                                      \
        getName(std::stringstream &si)                          \
        {                                                       \
            std::string ret;                                    \
            while (si &&                                        \
                !((si.peek() >= 'a' && si.peek() <= 'z')||      \
                (si.peek() >= 'A' && si.peek() <= 'Z')||        \
                (si.peek() >= '0' && si.peek() <= '9')))        \
                si.get();                                       \
            if (!si) return "";                                 \
            while (                                             \
                (si.peek() >= 'a' && si.peek() <= 'z')||        \
                (si.peek() >= 'A' && si.peek() <= 'Z')||        \
                (si.peek() >= '0' && si.peek() <= '9'))         \
                ret += si.get();                                \
            return ret;                                         \
        }                                                       \
        std::vector<std::string> string_table;                  \
        std::map<std::string, int> re_string_table;             \
    public:                                                     \
        EnumReflectionHelper()                                  \
        {                                                       \
            std::stringstream si(#__VA_ARGS__);                 \
            std::string token;                                  \
            while ((token = getName(si)).length()) {            \
                string_table.push_back(#TypeName "::" + token); \
                re_string_table[#TypeName "::" + token] =       \
                re_string_table[token] = string_table.size() - 1;\
            }                                                   \
        }                                                       \
        std::string toString(TypeName type) const               \
        { return string_table[static_cast<int>(type)]; }        \
        TypeName fromString(std::string s) const                \
        {                                                       \
            return static_cast<TypeName>(                       \
                re_string_table.at(s));                         \
        }                                                       \
        static EnumReflectionHelper* getHelper()                \
        {                                                       \
            static EnumReflectionHelper helper;                 \
            return &helper;                                     \
        }                                                       \
    };
    
#define __ENUM_DEFINE(TypeName, ...)        \
    enum class TypeName { __VA_ARGS__ };    \

#define ENUM_CLASS(TypeName, ...)       \
    __ENUM_DEFINE(TypeName, __VA_ARGS__)\
    __ENUM_TO_STRING(TypeName, __VA_ARGS__)

#ifdef REFLECT_NS
#define ENUM_REFLECT(TypeName)              \
    (::REFLECT_NS::EnumReflectionHelper<TypeName>::getHelper())
#else
#define ENUM_REFLECT(TypeName)              \
    (EnumReflectionHelper<TypeName>::getHelper())
#endif

#endif // _CUA_DEBUG_REFLECT_ENUM_H_
