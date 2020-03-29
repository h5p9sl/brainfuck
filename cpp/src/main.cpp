#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <stack>

#define DEBUG_PRINT(x, ...) if (debug) printf(x)

class Brainfuck {
private:
    unsigned char mem[30000];
    unsigned char* ptr;
    std::stack<int> loops;
    bool debug;
public:
    Brainfuck(bool debug) :
        ptr(mem)
        , debug(debug)
    {}

    void parse(const char* str) {
        for (int i = 0; i < strlen(str); i++) {
            switch (str[i]) {
                case '?':
                    std::cout << (int)(*ptr) << std::endl;
                    break;
                case '<':
                    DEBUG_PRINT("<");
                    ptr--;
                    break;
                case '>':
                    DEBUG_PRINT(">");
                    ptr++;
                    break;
                case '+':
                    DEBUG_PRINT("+");
                    (*ptr)++;
                    break;
                case '-':
                    DEBUG_PRINT("-");
                    (*ptr)--;
                    break;
                case ',':
                    *ptr = getchar();
                    break;
                case '.':
                    putchar(*ptr);
                    break;
                case '[':
                    DEBUG_PRINT("[");
                    if (*ptr == 0) {
                        DEBUG_PRINT("Skipping over loop\n");
                        int skip = 0;
                        i++; // Skip over current char
                        for (; skip != 0 || str[i] != ']'; i++) {
                            DEBUG_PRINT("Skip: %i, %c, %i\n", i, str[i], skip);
                            if (str[i] == '[') skip++;
                            else if (str[i] == ']') skip--;
                        }
                    } else {
                        DEBUG_PRINT("Entering loop");
                        loops.push(i);
                    }
                    break;
                case ']':
                    DEBUG_PRINT("]");
                    if (*ptr != 0) {
                        DEBUG_PRINT("Going to start of loop\n");
                        i = loops.top();
                    } else {
                        DEBUG_PRINT("Exiting loop\n");
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
        Brainfuck fuck(false);
        std::string str = read_file(argv[1]);
        fuck.parse(str.c_str());
    } else {
        std::cout << "Usage: " << argv[0] << " <bf file>" << std::endl;
    }
    return 0;
}
