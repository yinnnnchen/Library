// hw3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//
#include <iostream>
#include <list>
#include <forward_list>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

struct Book {
    string title;
    string author;
    string id;
};

struct Borrower {
    string name;
    vector<string> borrowedBookIds;
};

class Library {
private:
    list<Book> books;
    forward_list<Borrower> borrowers;

    bool isValidBookId(const string& id) {
        regex pattern("^[A-Z][0-9]{4}$");
        return regex_match(id, pattern);
    }

public:
    void addBook() {
        Book newBook;
        cout << "書名: ";
        cin >> newBook.title;
        cout << "作者: ";
        cin >> newBook.author;

        do {
            cout << "輸入編號: ";
            cin >> newBook.id;
            if (!isValidBookId(newBook.id)) {
                cout << "輸入錯誤，請重新輸入" << endl;
            }
        } while (!isValidBookId(newBook.id));

        books.push_back(newBook);
        cout << "輸入成功\n";
    }

    void deleteBook() {
        string id;
        cout << "輸入編號: ";
        cin >> id;
        books.remove_if([&](const Book& book) { return book.id == id; });
        cout << "刪除成功\n";
    }

    void searchBook() {
        string id;
        cout << "輸入編號: ";
        cin >> id;
        for (const auto& book : books) {
            if (book.id == id) {
                cout << "書籍為: " << book.title << " 作者: " << book.author << endl;
                return;
            }
        }
        cout << "未找到書籍\n";
    }

    void listBooks() {
        books.sort([](const Book& a, const Book& b) { return a.id < b.id; });
        cout << "\n";
        for (const auto& book : books) {
            cout << book.id << ": " << book.title << " by " << book.author << endl;
        }
    }

    void addBorrower() {
        Borrower newBorrower;
        cout << "輸入名字: ";
        cin >> newBorrower.name;

        int n;
        cout << "輸入書名: ";
        cin >> n;
        cout << "輸入編號:\n";
        for (int i = 0; i < n; ++i) {
            string bookId;
            cin >> bookId;
            newBorrower.borrowedBookIds.push_back(bookId);
        }

        borrowers.push_front(newBorrower);
        cout << "添加成功\n";
    }

    void deleteBorrower() {
        string name;
        cout << "輸入名字:";
        cin >> name;
        borrowers.remove_if([&](const Borrower& borrower) { return borrower.name == name; });
        cout << "已刪除\n";
    }

    void searchBorrower() {
        string name;
        cout << "輸入名字: ";
        cin >> name;
        for (const auto& borrower : borrowers) {
            if (borrower.name == name) {
                cout << "借閱者: " << borrower.name << "\n借閱書籍:";
                for (const auto& bookId : borrower.borrowedBookIds) {
                    cout << " " << bookId;
                }
                cout << endl;
                return;
            }
        }
        cout << "查無此書籍\n";
    }

    void listBorrowers() {
        cout << "\n";
        for (const auto& borrower : borrowers) {
            cout << borrower.name << " 已借閱: ";
            for (const auto& bookId : borrower.borrowedBookIds) {
                cout << bookId << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\n圖書管理\n";
        cout << "1. 新稱書籍\n";
        cout << "2. 刪除書籍\n";
        cout << "3. 搜尋書籍\n";
        cout << "4. 列出所有書籍\n";
        cout << "5. 新增借閱者\n";
        cout << "6. 刪除借閱者\n";
        cout << "7. 搜尋借閱者\n";
        cout << "8. 列出所有借閱者\n";
        cout << "0. 離開\n";
        cout << "輸入選項: ";
        cin >> choice;

        switch (choice) {
        case 1: library.addBook(); break;
        case 2: library.deleteBook(); break;
        case 3: library.searchBook(); break;
        case 4: library.listBooks(); break;
        case 5: library.addBorrower(); break;
        case 6: library.deleteBorrower(); break;
        case 7: library.searchBorrower(); break;
        case 8: library.listBorrowers(); break;
        case 0: return 0;
        default: cout << "輸入錯誤，請重新輸入\n";
        }
    }
    return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
