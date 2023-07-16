#include <iostream>
#include <string>
#include <vector>
using namespace std;

string obfuscateName(const string& name) {
    string obfuscatedName = name;
    for (char& c : obfuscatedName) {
        c = c + 1;
    }
    return obfuscatedName;
}

string obfuscateCode(const string& code) {
    vector<string> lines;

    size_t start = 0;
    size_t end = code.find('\n');
    while (end != std::string::npos) {
        lines.push_back(code.substr(start, end - start));
        start = end + 1;
        end = code.find('\n', start);
    }
    lines.push_back(code.substr(start, end));

    for (string& line : lines) {
        size_t pos = 0;
        while (pos < line.length()) {
            if (isalpha(line[pos])) {
                size_t startPos = pos;
                while (pos < line.length() && isalnum(line[pos])) {
                    ++pos;
                }
                string name = line.substr(startPos, pos - startPos);
                string obfuscatedName = obfuscateName(name);
                line.replace(startPos, pos - startPos, obfuscatedName);
                pos = startPos + obfuscatedName.length();
            } else {
                ++pos;
            }
        }
    }

   string obfuscatedCode;
    for (const string& line : lines) {
        obfuscatedCode += line + '\n';
    }

    return obfuscatedCode;
}

int main() {
    string originalCode = R"(
        #include <iostream>
        
        int main() {
            int x = 5;
            std::cout << "The value of x is: " << x << std::endl;
            return 0;
        }
    )";

    string obfuscatedCode = obfuscateCode(originalCode);
    cout << "Obfuscated code:\n" << obfuscatedCode << endl;

    return 0;
}
