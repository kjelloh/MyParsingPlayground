#include <iostream> // std::cin,
#include <iomanip> // std::getline,
#include <string> // std::shared_ptr,
#include <ostream> // std::ostream,

namespace v0 {

  // AST (structured representation of the input text)
  enum class ConstructId {
     Undefined
    ,Number
    ,Text
    ,AnyOf
    ,AllOf
    ,Unknown
  };
  struct Node {
    using Pointer = std::shared_ptr<Node>;
    ConstructId id;
    std::vector<Pointer> children{};
  };
  using Root = Node;
  using Tree = Root;

  // Parser (text -> AST)
  enum class ThingId {
    Undefined
    ,Digit
    ,Unknown
  };
  struct Thing {
    ThingId id;
    std::string value;
    Thing(ThingId id,std::string value) : id{id},value{value} {}
  };
  std::ostream& operator<<(std::ostream& os,Thing const& thing) {
    switch (thing.id) {
      case ThingId::Undefined: os << "Undefined"; break;
      case ThingId::Digit: os << "Digit"; break;
      case ThingId::Unknown: os << "Unknown"; break;
    }
    return os;
  }
  struct ParseResult {
    std::string const& s;
    int next;
    bool success;
    std::string msg;
    Thing thing;
    ParseResult(std::string const& s,int next,bool success,std::string msg,Thing thing) 
      : s{s},next{next},success{success},msg{msg},thing{thing} {}
  };
  std::ostream& operator<<(std::ostream& os,ParseResult const& pr) {
    if (pr.success) {
      os << pr.thing;
    }
    else {
      os << "Error," << pr.msg;
    }
    return os;
  }
  ParseResult parse_digit(std::string const& s,int current) {
    auto next = current;
    if (next < s.size()) {
      auto ch = s[next];
      if (std::isdigit(ch)) {
        ++next;
        return ParseResult(s,next,true,"Ok",Thing{ThingId::Digit,std::to_string(ch)});
      }
      else return ParseResult(s,current,false,"Expected digit",Thing{ThingId::Unknown,""});
    }
    else {
      return ParseResult(s,current,false,"Expected digit but found end of text",Thing{ThingId::Unknown,""});
    }
  }
  ParseResult parse(std::string const& s,int current) {
    return parse_digit(s,current);
  }

}

int main(int argc, char *argv[]) {
  namespace parser = v0;
  std::string s{};
  do {
    std::cout << "\nEnter text to parse (input nothing,'q' or 'quit' to quit)>";
    std::getline(std::cin,s);
    auto result = parser::parse(s,0);
    std::cout << "\n" << result;
  } while (s.size()>0 and s!="q" and s!="quit");
  return 0;
 }