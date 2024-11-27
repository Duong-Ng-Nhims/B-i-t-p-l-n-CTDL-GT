#include <iostream>
#include <stack>
#include <cctype> // Thu vien de kiem tra ky tu (isdigit)
#include <string>
#include <cmath> //  Dung cho cac phep tinh toan hc
#include <sstream> // Ð? tách và chuy?n d?i chu?i thành s?

// Hàm xác d?nh d? uu tiên c?a toán t?
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // Phép luy th?a có d? uu tiên cao hon
    return 0;
}

// Hàm ki?m tra ký t? có ph?i là toán t?
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Hàm chuy?n bi?u th?c trung t? sang h?u t?
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;
    std::string postfix;
    
    for (std::size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        
        // N?u là toán h?ng (s?), thêm vào k?t qu?
        if (std::isdigit(c)) {
            // Thêm toàn b? s? (có th? nhi?u ch? s?)
            while (i < infix.length() && std::isdigit(infix[i])) {
                postfix += infix[i];
                ++i;
            }
            postfix += ' '; // Thêm kho?ng tr?ng d? phân bi?t gi?a các s?
            --i; // Gi?m ch? s? d? vòng l?p không b? qua ký t? ti?p theo
        }
        // N?u là d?u m? ngo?c, d?y vào stack
        else if (c == '(') {
            stack.push(c);
        }
        // N?u là d?u dóng ngo?c, l?y các ph?n t? ra kh?i stack cho d?n khi g?p d?u m? ngo?c
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            if (!stack.empty()) stack.pop(); // B? d?u m? ngo?c
        }
        // N?u là toán t?
        else if (isOperator(c)) {
            while (!stack.empty() && precedence(stack.top()) >= precedence(c)) {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }
    
    // Ð?y các ph?n t? còn l?i trong stack vào k?t qu?
    while (!stack.empty()) {
        postfix += stack.top();
        postfix += ' ';
        stack.pop();
    }
    
    return postfix;
}

// Hàm chuy?n d?i chu?i thành s? nguyên (thay cho std::stoi)
int stringToInt(const std::string& str) {
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}

// Hàm tính giá tr? c?a bi?u th?c h?u t?
int evaluatePostfix(const std::string& postfix) {
    std::stack<int> stack;
    std::istringstream iss(postfix);
    std::string token;
    
    while (iss >> token) {
        // N?u token là m?t s?
        if (std::isdigit(token[0]) || (token.length() > 1 && std::isdigit(token[1]))) {
            stack.push(stringToInt(token)); // Chuy?n chu?i thành s? và d?y vào stack
        }
        // N?u token là m?t toán t?
        else if (isOperator(token[0])) {
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            
            switch (token[0]) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
                case '^': stack.push(std::pow(a, b)); break;
            }
        }
    }
    
    return stack.top();
}

int main() {
    std::string infix;
    std::cout << "Nhap bieu thuc trung to: ";
    std::getline(std::cin, infix); // S? d?ng getline d? d?c c? dòng
    
    std::string postfix = infixToPostfix(infix);
    std::cout << "Bieu thuc hau to: " << postfix << std::endl;
    
    int result = evaluatePostfix(postfix);
    std::cout << "Gia tri cua bieu thuc: " << result << std::endl;
    
    return 0;
}

