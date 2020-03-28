#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <stack>

class Brainfuck {
private:
    unsigned char mem[30000];
    unsigned char* ptr;
    std::stack<int> loops;
public:
    Brainfuck() :
        ptr(mem)
    {}

    void parse(const char* str) {
        for (int i = 0; i < strlen(str); i++) {
            switch (str[i]) {
                case '?':
                    std::cout << (int)(*ptr) << std::endl;
                    break;
                case '<':
                    ptr--;
                    break;
                case '>':
                    ptr++;
                    break;
                case '+':
                    (*ptr)++;
                    break;
                case '-':
                    (*ptr)--;
                    break;
                case ',':
                    *ptr = getchar();
                    break;
                case '.':
                    putchar(*ptr);
                    break;
                case '[':
                    if (*ptr == 0) {
                        int skip = 0;
                        i++; // Skip over current char
                        for (; skip != 0 || str[i] != ']'; i++) {
                            if (str[i] == '[') skip++;
                            else if (str[i] == ']') skip--;
                        }
                    } else {
                        loops.push(i);
                    }
                    break;
                case ']':
                    if (*ptr != 0) {
                        i = loops.top();
                    } else {
                        loops.pop();
                    }
                    break;
            }
        }
    }
};

std::string read_file(char* file_name) {
    std::ifstream file(file_name, std::ios::ate);
    size_t length = file.tellg();
    file.seekg(0);

    std::string str(length, '\0');
    file.read(&str[0], length);
    return str;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Brainfuck fuck;
        std::string str = read_file(argv[1]);
        fuck.parse(str.c_str());
    } else {
        std::cout << "Usage: " << argv[0] << " <bf file>" << std::endl;
    }
    return 0;
}
