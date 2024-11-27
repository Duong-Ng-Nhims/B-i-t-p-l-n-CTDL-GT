#include <iostream>
#include <stack>
#include <cctype> // Thu vien de kiem tra ky tu (isdigit)
#include <string>
#include <cmath> //  Dung cho cac phep tinh toan hc
#include <sstream> // �? t�ch v� chuy?n d?i chu?i th�nh s?

// H�m x�c d?nh d? uu ti�n c?a to�n t?
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // Ph�p luy th?a c� d? uu ti�n cao hon
    return 0;
}

// H�m ki?m tra k� t? c� ph?i l� to�n t?
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// H�m chuy?n bi?u th?c trung t? sang h?u t?
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;
    std::string postfix;
    
    for (std::size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        
        // N?u l� to�n h?ng (s?), th�m v�o k?t qu?
        if (std::isdigit(c)) {
            // Th�m to�n b? s? (c� th? nhi?u ch? s?)
            while (i < infix.length() && std::isdigit(infix[i])) {
                postfix += infix[i];
                ++i;
            }
            postfix += ' '; // Th�m kho?ng tr?ng d? ph�n bi?t gi?a c�c s?
            --i; // Gi?m ch? s? d? v�ng l?p kh�ng b? qua k� t? ti?p theo
        }
        // N?u l� d?u m? ngo?c, d?y v�o stack
        else if (c == '(') {
            stack.push(c);
        }
        // N?u l� d?u d�ng ngo?c, l?y c�c ph?n t? ra kh?i stack cho d?n khi g?p d?u m? ngo?c
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            if (!stack.empty()) stack.pop(); // B? d?u m? ngo?c
        }
        // N?u l� to�n t?
        else if (isOperator(c)) {
            while (!stack.empty() && precedence(stack.top()) >= precedence(c)) {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }
    
    // �?y c�c ph?n t? c�n l?i trong stack v�o k?t qu?
    while (!stack.empty()) {
        postfix += stack.top();
        postfix += ' ';
        stack.pop();
    }
    
    return postfix;
}

// H�m chuy?n d?i chu?i th�nh s? nguy�n (thay cho std::stoi)
int stringToInt(const std::string& str) {
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}

// H�m t�nh gi� tr? c?a bi?u th?c h?u t?
int evaluatePostfix(const std::string& postfix) {
    std::stack<int> stack;
    std::istringstream iss(postfix);
    std::string token;
    
    while (iss >> token) {
        // N?u token l� m?t s?
        if (std::isdigit(token[0]) || (token.length() > 1 && std::isdigit(token[1]))) {
            stack.push(stringToInt(token)); // Chuy?n chu?i th�nh s? v� d?y v�o stack
        }
        // N?u token l� m?t to�n t?
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
    std::getline(std::cin, infix); // S? d?ng getline d? d?c c? d�ng
    
    std::string postfix = infixToPostfix(infix);
    std::cout << "Bieu thuc hau to: " << postfix << std::endl;
    
    int result = evaluatePostfix(postfix);
    std::cout << "Gia tri cua bieu thuc: " << result << std::endl;
    
    return 0;
}

