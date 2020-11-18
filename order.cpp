#include "order.h"

Order::Order(std::string phone) : _phone{phone} { }
std::string Order::phone() const {return _phone;}
Order::Order(std::istream& ist) {
    std::getline(ist, _phone);
    int products;
    ist >> products; ist.ignore();
    while(products-- > 0) _products.push_back(new Product_order{ist});
}
void Order::save(std::ostream& ost) {
    ost << _phone << '\n';
    ost << _products.size() << '\n';
    for (Product_order* p : _products) p->save(ost);
}

double Order::cost() const {
    double sum;
    for (Product_order* po : _products) 
        sum += po->cost();
    return sum;
}
void Order::add_product_order(Product_order* po) {
    _products.push_back(po);
}
int Order::num_product_orders() {return _products.size();}
Product_order* Order::product_order(int index) {
    if (0 > index || index > (_products.size()-1)) 
        throw std::out_of_range{"Order: Product index " + std::to_string(index) 
            + " with only " + std::to_string(_products.size()-1) + " products"};
    return _products[index];
}
std::ostream& operator<<(std::ostream& ost, const Order& order) {
    ost << "  Phone: " << order.phone() << '\n';
    for (Product_order* po : order._products) ost << "  " << *(po) << '\n';
    ost << "\n  Order total is $" << order.cost() << '\n';
    return ost;
}
