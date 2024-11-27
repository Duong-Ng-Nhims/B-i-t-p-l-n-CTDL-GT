#include <bits/stdc++.h>
using namespace std;

template <class Object>
class ArrayStack {
private:
    int capacity; // Dung luong toi da cua ngan xep
    Object* S;    // Mang luu tru các phan tu
    int t;        // Chi so phan tu tren cung cua ngan xep
public:
    ArrayStack(int c);
    bool isEmpty();
    int size();
    Object top();
    void push(Object o);
    bool pop(Object &o);
    ~ArrayStack(); // H?y b? nh?
};

// Ham khoi tao ngan xep voi dung luong cho truoc
template <class Object>
ArrayStack<Object>::ArrayStack(int c) {
    capacity = c;
    S = new Object[capacity];
    t = -1; // Ngan xep ban dau rong
}

// H?y b? nh? c?p phát
template <class Object>
ArrayStack<Object>::~ArrayStack() {
    delete[] S;
}

// Kiem tra ngan xep co rong hay khong
template <class Object>
bool ArrayStack<Object>::isEmpty() {
    return (t < 0);
}

// Lay kich thuoc hien tai cua ngan xep
template <class Object>
int ArrayStack<Object>::size() {
    return t + 1;
}

// Tra ve phan tu tren cung cua ngan xep
template <class Object>
Object ArrayStack<Object>::top() {
    if (isEmpty()) {
        throw runtime_error("Ngan xep rong");
    }
    return S[t];
}

// Them phan tu vao ngan xep
template <class Object>
void ArrayStack<Object>::push(Object o) {
    if (t == capacity - 1) {
        throw runtime_error("Ngan xep day");
    }
    S[++t] = o;
}

// Loai bo phan tu tren cung khoi ngan xep va gan gia tri do cho bien truyen vao
template <class Object>
bool ArrayStack<Object>::pop(Object &o) {
    if (isEmpty()) {
        return false; // Ngan xep rong, khong the xoa
    }
    o = S[t--];
    return true;
}

int main() {
    int maxCapacity;
    cout << "Nhap dung luong toi da cua ngan xep: ";
    cin >> maxCapacity;

    ArrayStack<int> stack(maxCapacity);

    while (true) {
        cout << "\nMENU:\n";
        cout << "1. Them phan tu vao ngan xep\n";
        cout << "2. Lay phan tu tren cung cua ngan xep\n";
        cout << "3. Xoa phan tu tren cung cua ngan xep\n";
        cout << "4. Kiem tra ngan xep co rong\n";
        cout << "5. Hien thi kich thuoc cua ngan xep\n";
        cout << "6. Thoat\n";
        cout << "Chon: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int n, value;
                cout << "Nhap so luong phan tu muon them: ";
                cin >> n;

                if (n > (maxCapacity - stack.size())) {
                    cout << "Khong the them " << n << " phan tu vi ngan xep khong du cho.\n";
                } else {
                    for (int i = 1; i <= n; ++i) {
                        cout << "Nhap gia tri phan tu thu " << i << ": ";
                        cin >> value;
                        try {
                            stack.push(value);
                        } catch (const runtime_error& e) {
                            cout << "Loi: " << e.what() << endl;
                        }
                    }
                    cout << "Da them " << n << " phan tu vao ngan xep.\n";
                }
                break;
            }
            case 2: {
                try {
                    cout << "Phan tu tren cung: " << stack.top() << endl;
                } catch (const runtime_error& e) {
                    cout << "Loi: " << e.what() << endl;
                }
                break;
            }
            case 3: {
                int poppedValue;
                if (stack.pop(poppedValue)) {
                    cout << "Da xoa phan tu: " << poppedValue << endl;
                } else {
                    cout << "Ngan xep rong, khong co gi de xoa.\n";
                }
                break;
            }
            case 4: {
                cout << (stack.isEmpty() ? "Ngan xep rong.\n" : "Ngan xep khong rong.\n");
                break;
            }
            case 5: {
                cout << "Kich thuoc hien tai cua ngan xep: " << stack.size() << endl;
                break;
            }
            case 6: {
                cout << "Thoat chuong trinh.\n";
                return 0;
            }
            default: {
                cout << "Lua chon khong hop le.\n";
                break;
            }
        }
    }
}

