#include <iostream>
#include <string>
using namespace std;
class Product
{
private:
    int productID;
    string name;
    double price;
    int stock;

public:
    Product(int productID, string name, double price, int stock)
    {
        if (productID > 0)
        {
            this->productID = productID;
        }
        else
        {
            this->productID = -1;
            cout << "Invalid Product ID!" << endl;
        }
        if (!name.empty())
        {
            this->name = name;
        }
        else
        {
            this->name = "Unnamed";
            cout << "Invalid Product Name!" << endl;
        }
        if (price > 0)
        {
            this->price = price;
        }
        if (stock > 0)
        {
            this->stock = stock;
        }
    }

    void display()
    {
        cout << "Product ID: " << productID
             << "\nProduct name: " << name
             << "\nPrice: " << price
             << "\nStock: " << stock
             << endl;
    }

    int getProductID() const
    {
        return productID;
    }
    string getName() const
    {
        return name;
    }
    double getPrice() const
    {
        return price;
    }
    int getStock() const
    {
        return stock;
    }

    void increaseStock(int quantity)
    {
        if (quantity > 0)
        {
            stock += quantity;
        }
        cout << "After update stock now your stock is: " << this->stock << endl;
    }

    bool decreaseStock(int quantity)
    {
        if (quantity > 0 && quantity <= stock)
        {
            stock -= quantity;
            cout << "Stock decreased. New stock: " << stock << endl;
            return true;
        }
        else
        {
            cout << "Not enough stock available!" << endl;
            return false;
        }
    }
};

class CartItem
{
private:
    Product *product;
    int quantity;

public:
    CartItem(Product *product, int quantity)
    {
        if (product != nullptr && quantity > 0)
        {
            this->product = product;
            this->quantity = quantity;
        }
        else
        {
            this->product = nullptr;
            this->quantity = 0;
            cout << "Invalid Card Creation." << endl;
        }
    }

    Product *getProduct() const
    {
        return product;
    }
    int getQuantity() const
    {
        return quantity;
    }

    void updateQuantity(int newQuantity)
    {
        if (newQuantity > 0)
        {
            quantity = newQuantity;
        }
        else
        {
            cout << "Quantity must be postive!" << endl;
        }
    }

    double lineTotal() const
    {
        if (product != nullptr)
        {
            return product->getPrice() * quantity;
        }
        return 0.0;
    }

    void display() const
    {
        if (product != nullptr)
        {
            cout << "Product name: " << product->getName()
                 << "\nPrice: " << product->getPrice()
                 << "\nQuantity: " << quantity
                 << "\nLine Total: " << lineTotal()
                 << endl;
        }
        else
        {
            cout << "Invalid CartItem." << endl;
        }
    }
};

class ShoppingCart
{
private:
    CartItem **item;
    int count;
    int capacity;

    void grow()
    {
        int newCapacity = capacity * 2;
        CartItem **newItem = new CartItem *[newCapacity];
        for (int i = 0; i < count; i++)
        {
            newItem[i] = item[i];
        }
        delete[] item;
        item = newItem;
        capacity = newCapacity;
    }

public:
    ShoppingCart(int initialCapacity = 5)
    {
        item = new CartItem *[initialCapacity];
        count = 0;
        capacity = initialCapacity;
    }
    ~ShoppingCart()
    {
        for (int i = 0; i < count; i++)
        {
            delete item[i];
        }
        delete item;
    }

    void addProduct(Product *product, int quantity)
    {
        if (product == nullptr || quantity <= 0)
        {
            cout << "Invalid product or quantity." << endl;
            return;
        }

        for (int i = 0; i < count; i++)
        {
            if (item[i]->getProduct()->getProductID() == product->getProductID())
            {
                item[i]->updateQuantity(item[i]->getQuantity() + quantity);
                return;
            }
        }
        if (count == capacity)
        {
            grow();
        }

        item[count++] = new CartItem(product, quantity);
    }

    void removeProduct(int productID)
    {
        for (int i = 0; i < count; i++)
        {
            if (item[i]->getProduct()->getProductID() == productID)
            {
                delete item[i];

                for (int j = i; j < count - 1; j++)
                {
                    item[j] = item[j + 1];
                }
                count--;
                cout << "Product removed from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    void displayCart() const
    {
        if (count == 0)
        {
            cout << "Cart is empty." << endl;
            return;
        }
        double subtotal = 0;
        for (int i = 0; i < count; i++)
        {
            item[i]->display();
            subtotal += item[i]->lineTotal();
        }
        cout << "Cart Subtotal: " << subtotal << endl;
    }

    void ClearCart()
    {
        for (int i = 0; i < count; i++)
        {
            delete item[i];
        }
        count = 0;
        cout << "Cart cleared after checkout." << endl;
    }
};

class Customer
{
private:
    int customerID;
    string name;
    ShoppingCart cart;

public:
    Customer(int customerID, string name)
        : cart()
    {
        if (customerID > 0)
        {
            this->customerID = customerID;
        }
        else
        {
            this->customerID = -1;
            cout << "Invalid Customer ID!" << endl;
        }

        if (!name.empty())
        {
            this->name = name;
        }
        else
        {
            this->name = "Unname";
            cout << "Invalid customer name!" << endl;
        }
    }

    int getID() const
    {
        return customerID;
    }
    string getName() const
    {
        return name;
    }

    void display() const
    {
        cout << "Customer ID: " << customerID
             << "\nName: " << name << endl;
    }

    void addtoCart(Product *product, int quantity)
    {
        cart.addProduct(product, quantity);
    }

    void removefromcart(int productID)
    {
        cart.removeProduct(productID);
    }

    void veiwCart() const
    {
        cart.displayCart();
    }

    void clearCart()
    {
        cart.ClearCart();
    }

    double getCartSubtotal() const
    {
        double subtotal = 0;
        cart.displayCart();
        return subtotal;
    }
};

class Payment
{
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~Payment() {}
};

class CashPayment : public Payment
{
public:
    bool processPayment(double amount) override
    {
        if (amount > 0)
        {
            cout << "Cash payment accepted. Amount: " << amount << endl;
            return true;
        }
        else
        {
            cout << "Cash Payment Declined." << endl;
            return false;
        }
    }
};

class CardPayment : public Payment
{
public:
    bool processPayment(double amount) override
    {
        if (amount > 0)
        {
            cout << "Card payment accepted. Amount: " << amount << endl;
            return true;
        }
        else
        {
            cout << "Card Payment Declined." << endl;
            return false;
        }
    }
};

class ShoppingSystem
{
private:
    Product **products;
    Customer **customers;
    int productcount, productcapacity;
    int customercount, customercapacity;

    void growProduct()
    {
        int newcapacity = productcapacity * 2;
        Product **newarr = new Product *[newcapacity];
        for (int i = 0; i < productcount; i++)
        {
            newarr[i] = products[i];
        }
        delete products;
        products = newarr;
        productcapacity = newcapacity;
    }

    void growCustomer()
    {
        int newcapacity = customercapacity * 2;
        Customer **newarr = new Customer *[newcapacity];
        for (int i = 0; i < customercount; i++)
        {
            newarr[i] = customers[i];
        }
        delete customers;
        customers = newarr;
        customercapacity = newcapacity;
    }

public:
    ShoppingSystem(int prodCap = 5, int custCap = 5)
    {
        products = new Product *[prodCap];
        customers = new Customer *[custCap];
        productcount = customercount = 0;
        productcapacity = prodCap;
        customercapacity = custCap;
    }

    ~ShoppingSystem()
    {
        for (int i = 0; i < productcount; i++)
        {
            delete products[i];
        }
        for (int i = 0; i < customercapacity; i++)
        {
            delete customers[i];
        }
        delete products;
        delete customers;
    }

    // add product
    void addProduct(int id, string name, double price, int stock)
    {
        for (int i = 0; i < productcount; i++)
        {
            if (products[i]->getProductID() == id)
            {
                cout << "Duplicate id rejected!" << endl;
                return;
            }
        }
        if (productcapacity == productcount)
        {
            growProduct();
        }
        products[productcount++] = new Product(id, name, price, stock);
    }

    // search product
    Product *searchProduct(int id)
    {
        if (id <= 0)
        {
            cout << "ID must be positive." << endl;
            return nullptr;
        }
        for (int i = 0; i < productcount; i++)
        {
            if (products[i]->getProductID() == id)
            {
                products[i]->display();
                return products[i];
            }
        }
        cout << "You entered invalid id." << endl;
        return nullptr;
    }

    // display product
    void displayProduct() const
    {
        for (int i = 0; i < productcount; i++)
        {
            products[i]->display();
        }
    }

    // add customer
    void addcustomer(int id, string name)
    {
        if (id <= 0)
        {
            cout << "Customer id must be positive." << endl;
            return;
        }
        for (int i = 0; i < customercount; i++)
        {
            if (customers[i]->getID() == id)
            {
                cout << "Deplicate id rejected!" << endl;
                return;
            }
        }
        if (customercapacity = customercount)
        {
            growCustomer();
        }
        customers[customercount++] = new Customer(id, name);
    }

    // search customer
    Customer *searchCustomer(int id)
    {
        if (id <= 0)
        {
            cout << "ID must be postive.";
            return nullptr;
        }
        for (int i = 0; i < customercount; i++)
        {
            if (customers[i]->getID() == id)
            {
                customers[i]->display();
                return customers[i];
            }
        }
        cout << "You entered invalid id." << endl;
        return nullptr;
    }

    // display customer
    void displayCustomer() const
    {
        for (int i = 0; i < customercount; i++)
        {
            customers[i]->display();
        }
    }

    void checkout(int customerID, Payment *paymentMethod)
    {
        Customer *cust = searchCustomer(customerID);
        if (!cust)
        {
            cout << "Customer not found" << endl;
            return;
        }
        cout << "Checkout for: " << cust->getName() << endl;

        cust->veiwCart();

        double subtotal = 0;

        if (paymentMethod->processPayment(subtotal))
        {
            cout << "Payment successful! stock update." << endl;
        }
        else
        {
            cout << "Payment Failed!" << endl;
        }
    }
};
void veiwmenu()
{
    ShoppingSystem system;
    int choice = 0;
    while (choice != 10)
    {
        cout << "SHOPPING MANAGEMENT SYSTEM" << endl;
        cout << "1. Add product\t\t2. Display all products\t\t.3 Search product by ID\t\t4. Register customer\t\t\n";
        cout << "5. Display customers \t\t6. Select customer\t\t7. View products and add item to cart\t\t\n";
        cout << "8. Change quantity or remove cart item\t\t9. Display cart\t\t\n";
        cout << "10. Checkout using cash or simulated card\t\t11. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int productID, stock;
            double price;
            string name;
            cout << "Enter Product id, name, price,and stock: ";
            cin >> productID >> name >> price >> stock;
            system.addProduct(productID, name, price, stock);
            cout << endl;
        }
        else if (choice == 2)
        {
            system.displayProduct();
        }
        else if (choice == 3)
        {
            int productID;
            cout << "Enter product id: ";
            cin >> productID;
            system.searchProduct(productID);
            cout << endl;
        }
        else if (choice == 4)
        {
            int customerID;
            string name;
            cout << "Enter Customer id, and name: ";
            cin >> customerID >> name;
            system.addcustomer(customerID, name);
            cout << endl;
        }
        else if (choice == 5)
        {
            system.displayCustomer();
        }
        else if (choice == 6)
        {
            int custID;
            cout << "Enter customer: ";
            cin >> custID;
            Customer *c = system.searchCustomer(custID);
            if (c)
            {
                cout << "Customer selected: " << c->getName() << endl;
            }
            else
            {
                cout << "Customer not found!" << endl;
            }
        }
        else if (choice == 7)
        {
            int custID, prodID, quantity;
            cout << "Enter Customer ID, Product ID, and Quantity: ";
            cin >> custID >> prodID >> quantity;
            Customer *c = system.searchCustomer(custID);
            Product *p = system.searchProduct(prodID);
            if (c && p)
            {
                c->addtoCart(p, quantity);
            }
            else
            {
                cout << "Invalid customer or product!!!" << endl;
            }
        }
        else if (choice == 8)
        {
            int custID, prodID;
            cout << "Enter Customer id, and Product id: ";
            cin >> custID >> prodID;
            Customer *c = system.searchCustomer(custID);
            if (c)
            {
                c->removefromcart(prodID);
            }
            else
            {
                cout << "Customer not found!!!" << endl;
            }
        }
        else if (choice == 9)
        {
            int custID;
            cout << "Enter custometer ID: ";
            cin >> custID;
            Customer *c = system.searchCustomer(custID);
            if (c)
            {
                c->veiwCart();
            }
            else
            {
                cout << "Customer not found!!!" << endl;
            }
        }
        else if (choice == 10)
        {
            int custID, method;
            cout << "Enter customer id: ";
            cin >> custID;
            cout << endl;
            cout << "Enter payment method(1. Card, 2. Cash): ";
            cin >> method;
            Payment *pay = nullptr;
            if (method == 1)
            {
                pay = new CardPayment();
            }
            if (method == 2)
            {
                pay = new CashPayment();
            }
            if (pay)
            {
                system.checkout(custID, pay);
            }
            delete pay;
        }
        else if (choice == 11)
        {
            return;
        }
        else
        {
            cout << "Invalid choice!!!" << endl;
        }
    }
}
int main()
{
    veiwmenu();
    return 0;
}