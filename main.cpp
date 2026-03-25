// Simulation of a simple order book system demonstrating buy orders, sell orders, order matching, and trade execution.
#include <iostream>
#include <queue>
#include <map>
#include <string>

struct Order {
    std::string type; // "buy" or "sell"
    double price;
    int quantity;
};

class OrderBook {
    std::priority_queue<Order> buyOrders;
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>> sellOrders;
    
public:
    void addOrder(const Order& order) {
        if (order.type == "buy") {
            buyOrders.push(order);
        } else if (order.type == "sell") {
            sellOrders.push(order);
        }
        matchOrders();
    }
    
    void matchOrders() {
        while (!buyOrders.empty() && !sellOrders.empty()) {
            Order buy = buyOrders.top();
            Order sell = sellOrders.top();
            
            if (buy.price >= sell.price) {
                int tradeQuantity = std::min(buy.quantity, sell.quantity);
                std::cout << "Trade executed: " << tradeQuantity << " units at price " << sell.price << "\n";
                
                // Update quantities
                buy.quantity -= tradeQuantity;
                sell.quantity -= tradeQuantity;
                
                // Remove orders if fully executed
                if (buy.quantity == 0) {
                    buyOrders.pop();
                }
                if (sell.quantity == 0) {
                    sellOrders.pop();
                }
            } else {
                break;
            }
        }
    }
};

int main() {
    OrderBook orderBook;
    
    // Simulate orders
    orderBook.addOrder({"buy", 100.5, 10}); // Buy order for 10 units at $100.5
    orderBook.addOrder({"sell", 100.0, 5}); // Sell order for 5 units at $100.0
    orderBook.addOrder({"sell", 101.0, 10}); // Sell order for 10 units at $101.0
    orderBook.addOrder({"buy", 100.0, 5}); // Buy order for 5 units at $100.0

    return 0;
}