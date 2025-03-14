#include <iostream>
#include <iomanip>
#include<conio.h>
#include<fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class OrderManagement {
private:
    string loggedInUsername;
public:
    OrderManagement() {}
    OrderManagement(const string& username) : loggedInUsername(username) {}


    void saveOrderHistory(const string& name, const float& price, const int& points) {

        ofstream file("orderhistory.txt", ios::app);

        if (!file.is_open()) {
            cout << "Error: Unable to open file for writing." << endl;
            return;
        }


        file << name << ":" << " " << price << " " << points << " " << endl;

        file.close();

        cout << " Order history saved successfully." << endl;
    }

    void printhistory(const string& name) {
        ifstream file("orderhistory.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open file for reading." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            if (line.substr(0, name.size()) == name) {
                cout << line << endl;
            }
        }
        file.close();
    }
};
class User {
private:
    string firstName;
    string lastName;
    string phone;
    string address;
    string username;
    string password;
public:
    User() {};
    User(const string& firstName, const string& lastName, const string& phone, const string& address, const string& username, const string& password) :
        firstName(firstName), lastName(lastName), phone(phone), address(address), username(username), password(password) {}

    bool signup() {
        ofstream file("users.txt", ios::app);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for writing." << endl;
            return false;
        }

        file << username << " " << password << " " << firstName << " " << lastName << " " << phone << " " << address << endl;
        file.close();
        return true;
    }

    bool login(const string& enteredUsername, const string& enteredPassword) const {
        ifstream file("users.txt");
        if (!file.is_open()) {
            cerr << "Error: Unable to open file for reading." << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string fileUsername, filePassword;
            iss >> fileUsername >> filePassword;
            if (fileUsername == enteredUsername && filePassword == enteredPassword) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void setUsername(string un) {
        username = un;
    }

    string getUsername() {
        return username;
    }
};

class product {
private:
    string prod_name[25];
    string prod_code[25];
    float prod_price[25];
    int prod_points[25];

public:
    product() :prod_name{ "soft drink", "coffee", "cordial","milk","tea","chicory","concentrate","skin serum","suncreen lotion","skin gel","laundry powder","floor polish","paint thinner","stripper","remover","pesticide","motor oil","abaya","hoodie","bath robes","blazer","bridal dress","coat","denim wear","capri" },
        prod_code{ "a1", "a2", "a3","a4","a5", "a6", "a7","a8" ,"a9", "a10", "a11","a12","a13", "a14", "a15","a16","a17", "a18", "a19","a20","a21", "a22", "a23","a24","a25" },
        prod_price{ 85, 225.55, 550,500,75,135,225,650,1050,440,750,299,999,785,622,2050,2250,4000,1899,920,760,2999,3250,10500,50500 },
        prod_points{ 8,22,55,50,7,13,22,65,100,44,75,29,99,78,62,205,225,400,189,92,76,290,325,1050,5050 } {}
    /* prod_name[0] = "soft drink";
     prod_code[0] = "a1";
     prod_price[0] = 25;
     prod_name[1] = "coffee";
     prod_code[1] = "a2";
     prod_price[1] = 55;
     prod_name[2] = "juice";
     prod_code[2] = "a3";
     prod_price[2] = 13;*/

    string getProductCode(int index) {
        return prod_code[index];
    }

    string getProductName(int index) {
        return prod_name[index];
    }

    float getProductPrice(int index) {
        return prod_price[index];
    }

    int getProductPoints(int index) {
        return prod_points[index];
    }

    void display() {
        cout << "Available products:\n";
        cout << left << setw(20) << "Product Name" << setw(20) << "Product Code" << setw(20) << "Price" << setw(20) << "Product Points" << endl;
        for (int i = 0; i < 25; i++) {
            cout << left << setw(20) << prod_name[i] << setw(20) << prod_code[i] << setw(20) << prod_price[i] << setw(20) << prod_points[i] << endl;
        }
    }
};

class PaymentMethod {
public:
    virtual void pay(double amount) = 0;
};

class CreditCard : public PaymentMethod {
private:
    string name;
    string number;
    string expiryDate;
    string cvv;
public:
    CreditCard(string name, string number, string expiryDate, string cvv) {
        this->name = name;
        this->number = number;
        this->expiryDate = expiryDate;
        this->cvv = cvv;
    }
    void pay(double amount) {
        // Use a payment gateway API to process the payment
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

class PayPal : public PaymentMethod {
private:
    string email;
    string password;
public:
    PayPal(string email, string password) {
        this->email = email;
        this->password = password;
    }
    void pay(double amount) {
        // Use a payment gateway API to process the payment
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

class Cart :public OrderManagement {
private:
    product p;
    int index;
    string cart_prod_name[25];
    string cart_prod_code[25];
    float cart_prod_price[25];
    int cart_prod_points[25];
    int count = 0; //counter for number of different products bought.
    int quantity[25];
    int total_no_of_products = 0;
    float total_price;
    static float total_amount;
    static int total_points;
    /*   int redemption_points = 0;*/
    /*OrderManagement OM;*/
public:

    Cart() {}


    void addProduct(string code) {
        index = -1;
        for (int i = 0; i < 25; i++) {
            if (code == p.getProductCode(i)) {
                index = i;


                // int quantity;
                cout << "\nEnter the quantity of this item you wish to purchase: ";
                cin >> quantity[count];
                total_no_of_products += quantity[count];

                while (quantity[count] <= 0) {
                    cout << "\nEnter appropriate number of items: ";
                    cin >> quantity[count];
                }

                cart_prod_name[count] = p.getProductName(i);
                cart_prod_code[count] = p.getProductCode(i);
                cart_prod_price[count] = p.getProductPrice(i) * quantity[count];
                cart_prod_points[count] = p.getProductPoints(i) * quantity[count];
                //redemption_points += cart_prod_price[count];
                total_amount += p.getProductPrice(i) * quantity[count];
                total_points += p.getProductPoints(i) * quantity[count];
                //saveOrderHistory(p.getProductName(i), p.getProductPrice(i), p.getProductPoints(i), p.getProductCode(i));


                count++;

                cout << "\nPRODUCT ADDED TO THE CART!" << endl;
            }
        }
        if (index == -1) {
            cout << "\nInvalid Product Code.\n";
        }
    }

    void removeProduct(string code) {
        bool found = false;

        for (int i = 0; i < count; i++) {
            if (code == cart_prod_code[i]) {
                found = true;
                count--;

                for (int j = i; j < count; j++) {
                    cart_prod_name[j] = cart_prod_name[j + 1];

                    cart_prod_code[j] = cart_prod_code[j + 1];
                    cart_prod_price[j] = cart_prod_price[j + 1];
                    cart_prod_points[j] = cart_prod_points[j + 1];
                    quantity[j] = quantity[j + 1];
                 } //abort1q;
                    break;
            }

            cout << "\nPRODUCT REMOVED SUCCESSFULY" << endl;
        }
        if (!found) {
            cout << "\nProduct not found in the cart.\n";
        }
    }

    void displayCart() {
        if (count == 0) {
            cout << "\nYour cart is empty.\n";
            return;
        }
        cout << "\nYour cart:\n";
        cout << left << setw(20) << "Product Name" << setw(20) << "Product Code" << setw(20) << "Quantity" << setw(20) << "Price" << setw(20) << "Product Points" << endl;
        for (int i = 0; i < count; i++) {
            cout << left << setw(20) << cart_prod_name[i] << setw(20) << cart_prod_code[i] << setw(20) << quantity[i] << setw(20) << cart_prod_price[i] << setw(20) << cart_prod_points[i] << endl;
        }

        /*     cout << "\n\nTotal amount: " << total_amount;*/
    }

    void checkout(PaymentMethod* payment) {
        if (total_no_of_products == 0) {
            cout << "\nYour cart is empty. Cannot checkout.\n";
            return;
        }
        displayCart();
        char choice;
        cout << "\nConfirm purchase? (Y/N): ";
        cin >> choice;
        if (choice == 'N' || choice == 'n') {
            cout << "\nPurchase cancelled.\n";
            return;
        }
        payment->pay(total_amount);
        cout << "\nThank you for your purchase! Your order has been placed.\n";

        total_price = total_amount;
        total_amount = 0;
        total_no_of_products = 0;
        /*for (int i = 0; i < count; i++)
        {
            OM.points += cart_prod_points[i];
        }

        cout << "\nTOTAL POINTS: " << OM.points << endl;
        count = 0;*/
    }

    int getTotalProducts() {
        return total_no_of_products;
    }

    float getTotalPrice() {
        return total_price;
    }
    /* int getRedemptionPoints() {
         return redemption_points;
     }*/
    static int getTotalPoints() {
        return total_points;
    }

};

float Cart::total_amount = 0;
int Cart::total_points = 0;


int main() {
    string firstName;
    string lastName;
    string phone;
    string address;
    string username;
    string password;
    product p1;
    Cart c1;
    string code;
    OrderManagement OM;
    int choice = 0;
    char y;
    int choicels;
    User u;

    cout << "Enter:\n1 to Signup\n2 to login: ";
    cin >> choicels;

    while (choicels != 1 && choicels != 2)
    {
        cout << "Ivalid choice!\nEnter:\n1 to Signup\n2 to login: ";
        cin >> choicels;

    }

    if (choicels == 1)
    {
        cout << "\t\t\t\t\tFirst Name: "; cin >> firstName;
        cout << "\t\t\t\t\tLast Name: "; cin >> lastName;
        cout << "\t\t\t\t\tPhone: "; cin >> phone;
        cin.ignore();

        cout << "\t\t\t\t\tAddress: ";
        getline(cin, address);
        cout << "\n\t\t\t\t\tUser Name: "; cin >> username;
        u.setUsername(username);
        cout << "\t\t\t\t\tPassword: "; cin >> password;
        User u(firstName, lastName, phone, address, username, password);
        if (u.signup())
        {
            cout << "\n\n\t\t\t\t\tAccount Created Successfuly!" << endl;
        }



    }

    if (choicels == 2)
    {
        cout << "\t\t\t\t\t" << "User Name: "; cin >> username;
        u.setUsername(username);
        cout << "\t\t\t\t\t" << "Password: "; cin >> password;

        int checkl = u.login(username, password);

        while (!checkl)
        {
            cout << "\t\t\t\t\t" << "Login Failed, Try again: " << endl;
            cout << "\t\t\t\t\t" << "User Name: "; cin >> username;
            cout << "\t\t\t\t\t" << "Password: "; cin >> password;

            checkl = u.login(username, password);



        }

        OrderManagement OM(username);

        cout << "\n\t\t\t\t\tLogged in SUCCESSFULY!\n";
        cout << "\n\n\t\t\t\t\t\tPRESS Y TO CONTINUE !";
        cin >> y;


    }




    while (choice != 6) {
        system("cls");
        cout << "\t\t\t\t\t" << "\b\t1 to add product to the cart\n\t\t\t\t\t2 to remove product\n\t\t\t\t\t3 to display\n\t\t\t\t\t4 to checkout\n\t\t\t\t\t5 to print your Order History\n\t\t\t\t\t6 to end." << endl << "\t\t\t\t\t";
        cin >> choice;
        if (choice == 6)
            break;
        cout << "\n\n\t\t\t\t\tPRESS Y TO CONTINUE !";
        cin >> y;
        system("cls");
        if (choice == 1) {
            cout << "\nchoose from following:\n";
            p1.display();
            cout << "\nEnter product code: ";
            cin >> code;

            c1.addProduct(code);
        }


        else if (choice == 2) {
            cout << "\nThis is your cart:\n";
            c1.displayCart();
            cout << "\nEnter code from following to remove.\n";
            cin >> code;
            c1.removeProduct(code);
        }
        else if (choice == 3) {
            c1.displayCart();
        }
        else if (choice == 4) {
            int choice2;
            cout << "\t\t\t\t\t" << "\nEnter\n1 for credit card\n2 for PayPal: ";
            cin >> choice2;
            while (choice2 != 1 && choice2 != 2) {
                cout << "\t\t\t\t\t" << "\nINVALID CHOICE.\nEnter\n1 for credit card\n2 for PayPal: ";
                cin >> choice2;
            }
            if (choice2 == 1) {
                string name, number, expiryDate, cvv;
                cout << "Enter Credit Card Info:\nName: ";
                cin >> name;
                cout << "Card Number(16 digits without dashes): ";
                cin >> number;
                while (number.length() != 16) {
                    cout << "INVALID CREDIT CARD NUMBER.\nEnter Card Number(16 digits without dashes): ";
                    cin >> number;
                }
                cout << "Expiry Date(MM/YY): ";
                cin >> expiryDate;
                cout << "CVV(3-digits): ";
                cin >> cvv;

                while (cvv.length() != 3) {
                    cout << "INVALID CVV.\nEnter CVV(3-digits): ";
                    cin >> cvv;
                }

                CreditCard creditcard(name, number, expiryDate, cvv);
                c1.checkout(&creditcard);

                string username = u.getUsername();
                cout << "\n\n\n\n" << username << "'s";
                float price = c1.getTotalPrice();
                int points = c1.getTotalPoints();

                OM.saveOrderHistory(username, price, points);


            }
            else if (choice2 == 2) {
                string email, password;
                cout << "Enter PayPal info:\nEmail: ";
                cin >> email;
                cout << "Password: ";
                cin >> password;

                PayPal paypal(email, password);
                c1.checkout(&paypal);

                string username = u.getUsername();
                cout << "\n\n\n\n" << username;
                float price = c1.getTotalPrice();
                int points = c1.getTotalPoints();

                OM.saveOrderHistory(username, price, points);
            }
        }
        else if (choice == 5)
        {
            OM.printhistory(username);
        }
        cout << "\n\n\t\t\t\t\tPRESS Y TO CONTINUE !";
        cin >> y;
        //cout << "\n1 to add product to the cart\n2 to remove product\n3 to display\n4 to checkout\n5 to end." << endl;
        //cin >> choice;
    }

    return 0;
}