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
  struct Thing {};
  struct ParseResult {
    bool success{};
    Thing thing{};
    std::string msg;
    std::string const& s;
    int next;
    ParseResult(std::string const& s,Thing const& thing,int next) : s{s},success{true},thing{thing} {}
    ParseResult(std::string const& s,int next,std::string msg) : s{s},success{false},msg{msg} {}    
  };
  std::ostream& operator<<(std::ostream& os,ParseResult const& pr) {
    if (pr.s.size()>0) os << "\nSorry, parsing of " << std::quoted(pr.s) << " not yet implemented";
    return os;
  }
  ParseResult parse(std::string const& s) {
    ParseResult result{s,0,""};
    return result;
  }

}

int main(int argc, char *argv[]) {
  namespace parser = v0;
  std::string s{};
  do {
    std::cout << "\nEnter text to parse (input nothing,'q' or 'quit' to quit)>";
    std::getline(std::cin,s);
    auto result = parser::parse(s);
    std::cout << "\n" << result;
  } while (s.size()>0 and s!="q" and s!="quit");
  return 0;
 }