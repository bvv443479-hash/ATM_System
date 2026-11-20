#include <iostream>
#include <string>
using namespace std;

class Atm
{
private:
    // المتغيرات الأساسية
    long long balance = 0;
    long long deposit = 0;
    long long withdraw = 0;
    string name;
    string password;
    string typ;

    // عقدة القائمة المترابطة لبيانات المستخدمين
    struct Node2
    {
        string name2;
        string password2;
        long long balance2;
        Node2 *next2;
    };
    Node2 *head = NULL;
    Node2 *currentUser = NULL; // مؤشر لحفظ المستخدم الذي سجل دخوله حالياً

    // عقدة المكدس (Stack) لحفظ سجل العمليات والتراجع
    struct Node
    {
        long long data;
        Node *next;
    };
    Node *top = NULL;

public:
    void again()
    {
        bool keepRunning = true;
        while (keepRunning)
        {
            show();
            keepRunning = get();
        }
    }

    void clearInput()
    {
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // شاشة الترحيب
    void dis()
    {
        cout << "Hello to hazem ATM" << endl;
        cout << "****************" << endl;
    }

    // دالة إضافة مستخدم جديد إلى القائمة المترابطة
    void insert(string n, string p, long long b)
    {
        Node2 *newNode2 = new Node2;
        newNode2->name2 = n;
        newNode2->password2 = p;
        newNode2->balance2 = b;
        newNode2->next2 = NULL;

        if (head == NULL)
        {
            head = newNode2;
        }
        else
        {
            Node2 *current = head;
            while (current->next2 != NULL)
            {
                current = current->next2;
            }
            current->next2 = newNode2;
        }
    }

    // دالة تعبئة بيانات المستخدمين داخل القائمة المترابطة
    void data()
    {
        insert("hazem", "a1", 100000);
        insert("ahmed", "b1", 20000);
        insert("jasem", "c1", 5000);
        insert("ali", "d1", 648);
        insert("asmaael", "e1", 9462);
        insert("asama", "f1", 64894);
        insert("mohamed", "g1", 10000684680);
        insert("oob", "h1", 10068484684000);
    }

    // دالة البحث عن الاسم واستدعاء دالة التحقق من كلمة المرور
    void n()
    {
        bool found = false;

        do
        {
            cout << "enter your name : ";
            cin >> name;

            Node2 *current2 = head;
            while (current2 != NULL)
            {
                if (current2->name2 == name)
                {
                    currentUser = current2;
                    found = true;
                    break;
                }
                current2 = current2->next2;
            }

            if (!found)
            {
                cout << "your name is not found " << endl;
            }

        } while (!found);

        pass();
    }

    // دالة التحقق من كلمة المرور مع 3 محاولات كحد أقصى
    void pass()
    {
        cout << "Enter your password : ";
        cin >> password;

        if (password == currentUser->password2)
        {
            cout << "Log in Successfully" << endl;
            balance = currentUser->balance2;
        }
        else
        {
            int x = 2; // محاولتان متبقيتان
            do
            {
                cout << "Password is false !!" << endl;
                cout << "You have " << x << " tries " << endl;
                cout << "Enter password again : ";
                cin >> password;

                if (password == currentUser->password2)
                {
                    cout << "Log in Successfully" << endl;
                    balance = currentUser->balance2;
                    return;
                }
                x--;

            } while (x > 0);

            cout << "Your card is blocked" << endl;
            ::exit(0);
        }
    }

    // عرض القائمة الرئيسية
    void show()
    {
        cout << "*********" << endl;
        cout << "1- Balance\n"
             << "2- Withdraw\n"
             << "3- Deposit\n"
             << "4- register\n"
             << "5- delete last\n"
             << "6- Exit\n";
        cout << "*********" << endl;
    }

    // دالة الإيداع
    void dep()
    {
        cout << "Enter the money that you want to pay : ";

        if (!(cin >> deposit))
        {
            while (!(cin >> deposit))
            {
                cout << "false insert. try again\n";
                clearInput();
                cout << "Enter the money that you want to pay again : ";
            }
        }
        if (deposit <= 49)
        {
            do
            {
                cout << "you should pay money largger than 49$ " << endl;
                cout << "Enter the money that you want to pay again : ";
                cin >> deposit;
            } while (deposit <= 49);
        }
        cout << "Deposit done successfully\n";
        push(deposit);
        equation();
    }

    // دالة عرض الرصيد
    void bal()
    {
        if (balance == 0)
        {
            cout << "You dont have any thing in your account |_|" << endl;
            equation();
        }
        else
        {
            cout << "You have in your account " << balance << " $" << endl;
            equation();
        }
    }

    // دالة السحب
    void with()
    {
        if (balance == 0)
        {
            cout << "You dont have any thing in your account |_|" << endl;
            return;
        }

        cout << "How much money do you want : ";
        if (!(cin >> withdraw))
        {
            while (!(cin >> withdraw))
            {
                cout << "false insert. try again\n";
                clearInput();
                cout << "How much money do you want : ";
            }
        }

        if (withdraw > balance || withdraw <= 0)
        {
            do
            {
                cout << "Sorry you dont have that" << endl;
                cout << "You must choose a number between 1 to " << balance << " $" << endl;
                cout << "How much money do you want : ";
                cin >> withdraw;
            } while (withdraw > balance || withdraw <= 0);
        }

        cout << "successfully withdraw " << endl;
        push(-withdraw);
        equation();
    }

    // دالة تحديث الرصيد في المتغير وفي القائمة المترابطة
    void equation()
    {
        balance = balance - withdraw;
        balance = balance + deposit;

        if (currentUser != NULL)
        {
            currentUser->balance2 = balance;
        }

        withdraw = 0;
        deposit = 0;
    }

    // دالة تنفيذ اختيار المستخدم
    bool get()
    {
        cout << "Enter what do you want : ";
        cin >> typ;
        if (typ == "1")
        {
            bal();
        }
        else if (typ == "2")
        {
            with();
        }
        else if (typ == "3")
        {
            dep();
        }
        else if (typ == "4")
        {
            showRegister();
        }
        else if (typ == "5")
        {
            delete_last();
        }
        else if (typ == "6")
        {
            ex();
        }
        else
        {
            cout << "false enter !. enter again " << endl;
        }

        return true;
    }

    // إضافة عملية إلى سجل العمليات (Stack)
    void push(long long value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        if (top == NULL)
        {
            top = newNode;
            newNode->next = NULL;
        }
        else
        {
            newNode->next = top;
            top = newNode;
        }
    }

    // عرض سجل العمليات
    void showRegister()
    {
        if (top == NULL)
        {
            cout << "history is underflow \n";
            return;
        }
        else
        {
            Node *current = top;
            cout << "---history---\n";
            while (current != NULL)
            {
                if (current->data > 0)
                {
                    cout << "[+] deposit " << current->data << "$" << endl;
                }
                else
                {
                    cout << "[-] withdraw " << -current->data << "$" << endl;
                }
                current = current->next;
            }
        }
    }

    // حذف آخر عملية من المكدس
    long long pop()
    {
        if (top == NULL)
        {
            cout << "there is no data to delete\n";
            return 0;
        }
        else
        {
            Node *temp = top;
            long long value = temp->data;
            top = top->next;
            delete temp;
            return value;
        }
    }

    // التراجع عن آخر عملية سحب أو إيداع
    void delete_last()
    {
        if (top == NULL)
        {
            cout << "you dont do any thing to delete\n";
            return;
        }
        long long last = pop();
        balance = balance - last;

        if (currentUser != NULL)
        {
            currentUser->balance2 = balance;
        }

        cout << "Undo successful!. Reverted transaction of " << (last > 0 ? last : -last) << " $" << endl;
    }

    // دالة الخروج
    void ex()
    {
        cout << endl;
        cout << "************************" << endl;
        cout << "Thank you for your time " << endl;
        cout << "************************" << endl;
        ::exit(0);
    }

    // الدالة الرئيسية لتشغيل البرنامج بالترتيب الصحيح
    void all()
    {
        dis();
        data();
        n();
        again();
    }
};

int main()
{
    Atm ob1;
    ob1.all();

    return 0;
}