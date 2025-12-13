#include "MainApp.h"
#include <fstream>
#include <sstream>

// CONSTRUCTOR & LOAD DATA
MainApp::MainApp() {
    currentUser = nullptr; // Awalnya belum ada yang login
    loadDataUser();
    loadDataProduct();
    loadDataTrx();
}

// 1. FITUR USER (Login, Register, Profile)
bool MainApp::login(string username, string password) {
    for (int i = 0; i < databaseUser.size(); i++) {
        // Pake pointer (&) biar data asli bisa diedit
        if (databaseUser[i].getUsername() == username && databaseUser[i].login(password)) {
            currentUser = &databaseUser[i]; 
            return true; 
        }
    }
    return false; 
}

bool MainApp::registerUser(string user, string pass, string name, string address, string phone) {
    // Cek username kembar
    for (User u : databaseUser) {
        if (u.getUsername() == user) return false;
    }

    int id = databaseUser.size() + 1;
    string role = "customer"; // Default customer
    
    // Masukkan ke RAM
    User newUser(id, user, pass, role, name, address, phone);
    databaseUser.push_back(newUser);

    // Simpan ke File
    ofstream file("database_user.txt", ios::app);
    if (file.is_open()) {
        file << id << "|" << user << "|" << pass << "|" << role << "|" 
             << name << "|" << address << "|" << phone << endl;
        file.close();
        return true;
    }
    return false;
}

bool MainApp::editProfile(string newName, string newAddress, string newPhone) {
    if (currentUser == nullptr) return false;

    // 1. Update di RAM (Pake method dari User.cpp)
    currentUser->editProfile(newName, newAddress, newPhone);

    // 2. Update di File (Overwrite/Tulis Ulang semua data user)
    ofstream file("database_user.txt");
    if (file.is_open()) {
        for (User u : databaseUser) {
            file << u.getId() << "|" << u.getUsername() << "|" << u.getPassword() << "|" 
                 << u.getRole() << "|" << u.getFullName() << "|" 
                 << u.getAddress() << "|" << u.getPhone() << endl;
        }
        file.close();
        return true;
    }
    return false;
}

void MainApp::logout() { 
    currentUser = nullptr; 
    userCart.clear(); // Hapus keranjang pas logout biar aman
}

User* MainApp::getCurrentUser() { return currentUser; }

// 2. FITUR PRODUCT
vector<Product> MainApp::getAllProducts() { return databaseProduct; }

bool MainApp::addProduct(string pname, double price, int stock, string description) {
    int id = databaseProduct.size() + 1;
    Product p(id, pname, price, stock, description);
    databaseProduct.push_back(p);

    ofstream file("database_produk.txt", ios::app);
    if (file.is_open()) {
        file << id << "|" << pname << "|" << price << "|" << stock << "|" << description << endl;
        file.close();
        return true;
    }
    return false;
}

// 3. FITUR CART (KERANJANG)
bool MainApp::addToCart(int productId, int qty) {
    if (qty <= 0) return false;
    for (Product p : databaseProduct) {
        if (p.getId() == productId) {
            // Masukkan ke keranjang
            userCart.addItem(p, qty);
            return true;
        }
    }
    return false; // Produk gak ketemu
}

//Wrapper fungsi Cart buat dipanggil Qt (Ini sifatnya public)
vector<CartItem> MainApp::getCartItems(){return userCart.getItems();}
double MainApp::getCartTotal(){return userCart.getCartTotal();}
void MainApp::updateCartQty(int index, int newQty){userCart.updateQty(index, newQty);}
void MainApp::removeCartItem(int index){userCart.removeItem(index);}
void MainApp::clearCart(){userCart.clear();}

// 4. FITUR CHECKOUT & TRANSAKSI
bool MainApp::checkout(string paymentMethod) {
    if (currentUser == nullptr || userCart.isEmpty()) return false;

    int trxId = databaseTrx.size() + 1;
    string username = currentUser->getUsername();
    double total = userCart.getCartTotal();
    
    // Bikin ringkasan belanjaan jadi string
    string detail = "";
    vector<CartItem> items = userCart.getItems();
    for (int i = 0; i < items.size(); i++) {
        detail += items[i].product.getName() + " (" + to_string(items[i].qty) + ")";
        if (i < items.size() - 1) detail += ", ";
    }

    string status = "Menunggu"; // Default status awal

    // Simpan ke RAM
    Transaction newTrx(trxId, username, total, detail, paymentMethod, status);
    databaseTrx.push_back(newTrx);

    // Simpan ke File Transaksi
    ofstream file("database_transaksi.txt", ios::app);
    if (file.is_open()) {
        file << trxId << "|" << username << "|" << total << "|" << detail << "|" 
             << paymentMethod << "|" << status << endl;
        file.close();
        
        userCart.clear(); // Kosongin keranjang setelah sukses
        return true;
    }
    return false;
}

// Ambil history belanjaan Customer
vector<Transaction> MainApp::getMyHistory() {
    vector<Transaction> myTrx;
    if (currentUser == nullptr) return myTrx;

    for (Transaction t : databaseTrx) {
        if (t.getUsername() == currentUser->getUsername()) {
            myTrx.push_back(t);
        }
    }
    return myTrx;
}

// Ambil SEMUA history Admin
vector<Transaction> MainApp::getAllTransactions() {
    return databaseTrx; 
}

// Update Status Pesanan (Dikirim/Selesai/Cancel)
bool MainApp::updateTransactionStatus(int trxId, string newStatus) {
    bool found = false;
    
    // 1. Update di RAM
    for (int i = 0; i < databaseTrx.size(); i++) {
        if (databaseTrx[i].getId() == trxId) {
            databaseTrx[i].setStatus(newStatus);
            found = true;
            break;
        }
    }

    // 2. Update di File (Overwrite)
    if (found) {
        ofstream file("database_transaksi.txt");
        if (file.is_open()) {
            for (Transaction t : databaseTrx) {
                file << t.getId() << "|" << t.getUsername() << "|" << t.getTotal() << "|" 
                     << t.getItemsDetail() << "|" << t.getPaymentMethod() << "|" 
                     << t.getStatus() << endl;
            }
            file.close();
            return true;
        }
    }
    return false;
}

// 5. LOAD DATA DARI FILE .TXT
void MainApp::loadDataUser() {
    databaseUser.clear();
    ifstream file("database_user.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string segment;
            vector<string> data;
            while (getline(ss, segment, '|')) data.push_back(segment);
            
            // Format: ID|User|Pass|Role|Name|Addr|Phone
            if (data.size() >= 7) {
                User u(stoi(data[0]), data[1], data[2], data[3], data[4], data[5], data[6]);
                databaseUser.push_back(u);
            }
        }
        file.close();
    }
}

void MainApp::loadDataProduct() {
    databaseProduct.clear();
    ifstream file("database_produk.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string segment;
            vector<string> data;
            while (getline(ss, segment, '|')) data.push_back(segment);
            
            // Format: ID|Name|Price|Stock|Desc
            if (data.size() >= 5) {
                Product p(stoi(data[0]), data[1], stod(data[2]), stoi(data[3]), data[4]);
                databaseProduct.push_back(p);
            }
        }
        file.close();
    }
}

void MainApp::loadDataTrx() {
    databaseTrx.clear();
    ifstream file("database_transaksi.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string segment;
            vector<string> data;
            while (getline(ss, segment, '|')) data.push_back(segment);
            
            // Format: ID|User|Total|Detail|Payment|Status
            if (data.size() >= 6) {
                Transaction t(stoi(data[0]), data[1], stod(data[2]), data[3], data[4], data[5]);
                databaseTrx.push_back(t);
            }
        }
        file.close();
    }
}