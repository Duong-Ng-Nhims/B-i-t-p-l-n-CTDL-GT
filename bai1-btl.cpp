#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
using namespace std;

// Template MyVector
template <class T>
class MyVector {
private:
    T* arr;				//dung mang dong arr de luu cac phan tu
    int capacity;		//kich thuoc cua mang
    int currentSize;	//so luong phan tu dang duoc su dung

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    MyVector() {
        capacity = 2;
        currentSize = 0;
        arr = new T[capacity];
    }

    ~MyVector() {
        delete[] arr;
    }

    void push_back(const T& element) {		//them phan tu
        if (currentSize == capacity) {		//neu mang day, tang kich thuoc mang bang cach resize, sao chep du lieu cu sang mang moi co kich thuoc gap doi
            resize();
        }
        arr[currentSize++] = element;		//them phan tu moi vao cuoi mang
    }

    void removeAt(int index) {								//xoa phan tu tai vi tri bat ki
        if (index < 0 || index >= currentSize) {			//
            throw out_of_range("Index out of range");
        }
        for (int i = index; i < currentSize - 1; i++) {		//dich cac phan tu sau vi tri xoa len 1 buoc
            arr[i] = arr[i + 1];
        }
        currentSize--;										//giam kich thuoc mang
    }

    int size() const {										//tra ve so phan tu hien tai
        return currentSize;
    }

    T& operator[](int index) {								//truy cap phan tu trong mang
        if (index >= currentSize || index < 0) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& operator[](int index) const {
        if (index >= currentSize || index < 0) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }

    void clear() {
        currentSize = 0;
    }
    
    void erase(int index){
    	removeAt(index);
	}
};

// Class SinhVien
class SinhVien {
public:
    string maSV;
    string ten;
    int tuoi;
    float diem;

    friend istream& operator>>(istream& in, SinhVien& sv) {		//ham nhap thong tin sinh vien
        cout << "Nhap ma sinh vien: ";
        cin >> sv.maSV;
        cout << "Nhap ten sinh vien: ";
        cin.ignore();
        getline(in, sv.ten);
        cout << "Nhap tuoi: ";
        cin >> sv.tuoi;
        cout << "Nhap diem: ";
        cin >> sv.diem;
        return in;
    }

    friend ostream& operator<<(ostream& out, const SinhVien& sv) {		// ham xuat danh sach thong tin sinh vien
        cout << "Ma SV: " << sv.maSV << ", Ten: " << sv.ten
            << ", Tuoi: " << sv.tuoi << ", Ðiem: " << sv.diem;
        return out;
    }

    bool operator<(const SinhVien& other) const {		//ham so sanh diem
        return diem < other.diem;
    }
    
    bool operator>(const SinhVien& other) const{
		return diem > other.diem;
	}
};

// Class DanhSachSinhVien
class DanhSachSinhVien {
private:
    MyVector<SinhVien> danhSach;

public:
    void nhapDanhSach() {
        int n;
        cout << "Nhap so luong sinh vien: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            SinhVien sv;
            cin >> sv;
            danhSach.push_back(sv);
        }
    }

    void xuatDanhSach() const {
        for (int i = 0; i < danhSach.size(); ++i) {
            cout << danhSach[i] << endl;
        }
    }

    void SapXepminmax() {
        for (int i = 0; i < danhSach.size() - 1; ++i) {
            for (int j = i + 1; j < danhSach.size(); ++j) {
                if (danhSach[j] < danhSach[i]) {
                    swap(danhSach[i], danhSach[j]);
                }
            }
        }
    }
    
    void SapXepmaxmin() {
        for (int i = 0; i < danhSach.size() - 1; ++i) {
            for (int j = i + 1; j < danhSach.size(); ++j) {
                if (danhSach[j] > danhSach[i]) {
                    swap(danhSach[i], danhSach[j]);
                }
            }
        }
    }
 
    SinhVien timMax() const {
        if (danhSach.size() == 0) {
            throw runtime_error("Danh sach rong");
        }
        SinhVien maxSV = danhSach[0];
        for (int i = 1; i < danhSach.size(); ++i) {
            if (maxSV < danhSach[i]) {
                maxSV = danhSach[i];
            }
        }
        return maxSV;
    }
    
    SinhVien timMin() const{
		if (danhSach.size() == 0){
			throw runtime_error("Danh sac rong");
		}
		SinhVien minSV = danhSach[0];
		for(int i=1; i<danhSach.size(); ++i){
			if(minSV > danhSach[i]){
				minSV = danhSach[i];
			}
		}
		return minSV;
	}

    void themSinhVien(const SinhVien& sv) {
        danhSach.push_back(sv);
        cout << "Da them sinh vien vao danh sach.\n";
    }
    
    void xoaSinhvien(const string& maSV){
		int index = -1;
        for (int i = 0; i < danhSach.size(); ++i) {
            if (danhSach[i].maSV == maSV) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            danhSach.erase(index);
            cout << "Da xoa sinh vien co ma: " << maSV << endl;
        } else {
            cout << "Khong tim thay sinh vien co ma: " << maSV << endl;
        }
    }

    void inSinhvientheoma(const string& maSV) const {
		for (int i=0; i<danhSach.size(); ++i){
			if (danhSach[i].maSV == maSV){
				cout << "Thong tin sinh vien:\n" << danhSach[i] <<endl;
				return;
			}
		}
		cout << "Khong tim thay sinh vien co ma: " << maSV << endl;
	}
};

// Class App
class App {
private:
    DanhSachSinhVien ds;

public:
    void run() {
        int choice;
        do {
            cout << "\nMenu:\n";
            cout << "1. Nhap danh sach sinh vien\n";
            cout << "2. Xuat danh sach sinh vien\n";
            cout << "3. Sap xep danh sach theo diem tu nho den lon\n";
            cout << "4. Sap xep danh sach theo diem tu lon den nho\n";
            cout << "5. Tim sinh vien co diem cao nhat\n";
            cout << "6. Tim sinh vien co diem thap nhap\n";
            cout << "7. Them sinh vien\n";
            cout << "8. Xoa sinh vien theo ma\n";
            cout << "9. In thong tin sinh vien theo ma\n";
            cout << "10. Thoat\n";
            cout << "Chon chuc nang: ";
            cin >> choice;

            switch (choice) {
            case 1:
                ds.nhapDanhSach();
                break;
            case 2:
                ds.xuatDanhSach();
                break;
            case 3:
                ds.SapXepminmax();
                cout << "Danh sach da duoc sap xep.\n";
                break;
            case 4:
                ds.SapXepmaxmin();
                cout << "Danh sach da duoc sap xep.\n";
                break;
            case 5:
                try {
                    cout << "Sinh vien co diem cao nhat la:\n" << ds.timMax() << endl;
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            case 6:
                try {
                    cout << "Sinh vien co diem thap nhat la:\n" << ds.timMin() << endl;
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            case 7:
            	{
            		SinhVien sv;
            		cout << "Nhap thong tin sinh vien can them:\n";
            		cin >> sv;
            		ds.themSinhVien(sv);
            		break;
				}
			case 8:
				{
					string maSV;
					cout << "Nhap ma sinh vien can xoa:";
					cin >> maSV;
					ds.xoaSinhvien(maSV);
					break;
				}
			case 9:
				{
					string maSV;
					cout << "Nhap ma sinh vien can tim: ";
					cin >> maSV;
					ds.inSinhvientheoma(maSV);
					break;
				}
            case 10:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong phu hop.\n";
            }
        } while (choice != 10);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}

