#ifndef PRODUCT_H
#define PRODUCT_H
// Include guards prevent multiple inclusion during compilation

#include <string>
#include <vector>
using namespace std;

// Struct to hold product information
struct product_info {
    int id;
    string name;
    int price;
    int stock;
};

// Product class
class Product {
private:
    int product_id;
    string product_name;
    int price;
    int stock;

public:
    // Constructors
    Product() = default;
    Product(int id, const string &name, int cost, int stk)
        : product_id(id), product_name(name), price(cost), stock(stk) {}

    // =================== Getters ===================
    product_info getProduct() const;

    int getId() const { return product_id; }
    string getName() const { return product_name; }
    int getPrice() const { return price; }
    int getStock() const { return stock; }

    // =================== Setters ===================
    void setProduct(int id, const string &name, int cost, int stk);
    void setId(int id) { product_id = id; }
    void setName(const string &name) { product_name = name; }
    void setPrice(int cost) { price = cost; }
    void setStock(int stk) { stock = stk; }

    // =================== Other Functions ===================
    bool delProduct(int id);  // delete product by id
};

#endif
