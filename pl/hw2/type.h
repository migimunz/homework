#ifndef TYPE_H
#define TYPE_H

#include <map>
#include <string>
#include <vector>

enum MemberType {
  POINTER,
  OTHER
};

class Member {
  std::string mName;
  MemberType  mType;
  int         mSize;
  int         mOffset;
public:
  Member(const std::string& name, MemberType type, int size, int offset) {
    mName   = name;
    mType   = type;
    mSize   = size;
    mOffset = offset;
  }

  const std::string& name() const {
    return mName;
  }

  int offset() const {
    return mOffset;
  }

  int size() const {
    return mSize;
  }

  MemberType type() const {
    return mType;
  }
};

class Type {
protected:
  static std::vector<const Type*> cALL;
public:
  static const Type& create(std::stringstream& stream) {
    cALL.append(new Type(stream));
  }

  static const Type& get(int id) {
    return cALL.at(id);
  }
protected:
  int mSize;
  std::string mName;
  std::map<std::string, Member> mMembers;
public:
  Type(std::stringstream& stream) {
    mSize = 0;
    stream >> mName;

    std::string member;
    while(stream >> member) {
      std::string name = member.substr(1);
      MemberType type = (member[0] == 'p')? POINTER : OTHER;
      mMembers[name] = Member(name, type, 4, mSize);
      mSize += 4;
    }
  }

  const Member& member(const std::string& name) const {
    return mMembers.at(name);
  }

  const std::map<std::string, Member>& members() const {
    return mMembers;
  }

  const std::string& name() const {
    return mName;
  }

  int size() const {
    return mSize;
  }
};

#endif
