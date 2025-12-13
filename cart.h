#ifndef CART_H
#define CART_H

#include <vector>
#include <iostream>
#include "product.h"

using namespace std;

struct CartItem {
    Product product; // barangnya apa
    int qty;         // berapa banyak
    double subtotal; // harga x qty
};

class Cart {
private:
    vector<CartItem> items; // list belanjaan

public:
    Cart() {}

    //FUNGSI TAMBAH ITEM
    void addItem(Product p, int quantity) {
        if (quantity <= 0) return;

        // Cek barangnya sudah ada di keranjang atau belum
        bool found = false;
        for (int i = 0; i < items.size(); i++) {
            //Cek kesamaan ID Produk
            if (items[i].product.getId() == p.getId()) {
                // Barang ketemu, update jumlahnya aja
                items[i].qty += quantity;
                items[i].subtotal = items[i].qty * items[i].product.getPrice(); 
                found = true;
                break;
            }
        }

        // Kalau barang belum ada, masukkan sebagai item baru
        if (!found) {
            CartItem newItem;
            newItem.product = p;
            newItem.qty = quantity;
            newItem.subtotal = p.getPrice() * quantity;
            items.push_back(newItem);
        }
    }

    //FUNGSI HAPUS ITEM (Harus dideklarasikan sebelum dipanggil updateQty)
    void removeItem(int index) {
        if (index >= 0 && index < items.size()) {
            items.erase(items.begin() + index);
        }
    }

    //FUNGSI UPDATE JUMLAH (Manage Cart: Tombol +/-)
    void updateQty(int index, int newQty) {
        if (index >= 0 && index < items.size()) {
            if (newQty > 0) {
                items[index].qty = newQty;
                items[index].subtotal = items[index].qty * items[index].product.getPrice();
            } else {
                // Kalau diupdate jadi 0, otomatis hapus
                removeItem(index); // Panggil fungsi di atas
            }
        }
    }

    //FUNGSI HITUNG TOTAL
    double getCartTotal() {
        double total = 0;
        for (CartItem item : items) {
            total += item.subtotal;
        }
        return total;
    }

    //FUNGSI GET DATA (Buat Tabel Qt)
    vector<CartItem> getItems() {
        return items;
    }

    //FUNGSI CLEAR SAAT CO BERHASIL DAN CEK KOSONG
    void clear() { items.clear(); }
    bool isEmpty() { return items.empty(); }
};

#endif