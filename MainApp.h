#ifndef MAINAPP_H
#define MAINAPP_H

#include <vector>
#include <string>
#include "user.h"
#include "product.h"
#include "cart.h"        
#include "transaction.h" 

using namespace std;

class MainApp {
private:
    //DATABASE (RAM)
    vector<User> databaseUser;
    vector<Product> databaseProduct;
    vector<Transaction> databaseTrx; 

    //SESI AKTIF
    User* currentUser; // Siapa yang lagi login?
    Cart userCart;     // Keranjang belanjaannya

    //Load Data dari File
    void loadDataUser();
    void loadDataProduct();
    void loadDataTrx(); 

public:
    MainApp(); // Constructor

    //1. USER MANAGEMENT
    bool login(string username, string password);
    bool registerUser(string user, string pass, string name, string address, string phone);
    void logout();
    User* getCurrentUser();
    
    // Edit Profile (Nama, Alamat, HP)
    bool editProfile(string newName, string newAddress, string newPhone);

    //2. PRODUCT MANAGEMENT
    vector<Product> getAllProducts();
    // Admin nambah produk
    bool addProduct(string pname, double price, int stock, string description);

    //3. SHOPPING CART (MANAGE CART)
    bool addToCart(int productId, int qty);
    vector<CartItem> getCartItems();
    double getCartTotal();
    
    // Fitur Edit Keranjang
    void updateCartQty(int index, int newQty); // Ubah jumlah (+/-)
    void removeCartItem(int index);            // Hapus item (Sampah)
    void clearCart();                          // Kosongkan semua

    //4. CHECKOUT & PAYMENT
    // User pilih metode bayar: "QRIS" atau "COD"
    bool checkout(string paymentMethod); 

    //5. ORDER HISTORY & STATUS
    vector<Transaction> getMyHistory();       // Customer liat pesanan sendiri
    vector<Transaction> getAllTransactions(); // Admin liat semua pesanan
    
    // Update Status:
    // - Admin: "Dikirim"
    // - Customer: "Selesai" atau "Dibatalkan"
    bool updateTransactionStatus(int trxId, string newStatus);
};

#endif