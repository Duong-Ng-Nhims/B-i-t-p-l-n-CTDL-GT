#include <iostream>
#include <stack>
#include <cctype> // Thu vien de kiem tra ky tu (isdigit)
#include <string>
#include <cmath>  
#include <sstream> // De tach va chuyen doi chuoi thanh so

// Ham xac dinh thu tu uu tien cua toan tu
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // Phep luy thua co uu tien cao hon
    return 0;
}

// Ham kiem tra ky tu co phai la toan tu
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Ham chuyen bieu thuc trung to sang hau to
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;
    std::string postfix;
    
    for (std::size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        
        // Neu la toan hang (so), them vao ket qua
        if (std::isdigit(c)) {
            // Them toan bo so (co the nhieu chi so)
            while (i < infix.length() && std::isdigit(infix[i])) {
                postfix += infix[i];
                ++i;
            }
            postfix += ' '; // Them khoang trong de phan biet giua cac so
            --i; // Giam chi so de vong lap khong bo qua ky tu tiep theo
        }
        // Neu la dau mo ngoac, day vào stack
        else if (c == '(') {
            stack.push(c);
        }
        // Neu la dau dong ngoac, lay cac phan tu ra khoi stack cho den khi gap dau mo ngoac
        else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            if (!stack.empty()) stack.pop(); // Bo dau mo ngoac
        }
        // Neu la toan tu
        else if (isOperator(c)) {
            while (!stack.empty() && precedence(stack.top()) >= precedence(c)) {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }
    
    // Day cac phan tu con lai trong stack vao ket qua
    while (!stack.empty()) {
        postfix += stack.top();
        postfix += ' ';
        stack.pop();
    }
    
    return postfix;
}

// Ham chuyen doi chuoi thanh so nguyen (thay cho std::stoi)
int stringToInt(const std::string& str) {
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}

// Ham tinh gia tri cua bieu thuc hau to
int evaluatePostfix(const std::string& postfix) {
    std::stack<int> stack;
    std::istringstream iss(postfix);
    std::string token;
    
    while (iss >> token) {
        // Neu token là mot so
        if (std::isdigit(token[0]) || (token.length() > 1 && std::isdigit(token[1]))) {
            stack.push(stringToInt(token)); // Chuyen chuoi thanh so và day vào stack
        }
        // Neu token là mot toan tu
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
    std::getline(std::cin, infix); 
    
    std::string postfix = infixToPostfix(infix);
    std::cout << "Bieu thuc hau to: " << postfix << std::endl;
    
    int result = evaluatePostfix(postfix);
    std::cout << "Gia tri cua bieu thuc: " << result << std::endl;
    
    return 0;
}
