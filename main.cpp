<<<<<<< HEAD
#include "OrderBook.h"
#include <iostream>
#include <chrono>

int main() {
    OrderBook orderBook;
    uint64_t timestamp = std::chrono::system_clock::now().time_since_epoch().count();

    std::cout << "=== ORDER BOOK SIMULATOR ===" << std::endl;
    std::cout << "HFT Software Engineering Internship Project" << std::endl;
    std::cout << "============================\n" << std::endl;

    std::cout << "--- SCENARIO: Trading Session Started ---\n" << std::endl;

    orderBook.addSellOrder(100.50, 1000, timestamp, "Seller1");
    orderBook.addSellOrder(100.75, 500, timestamp + 1, "Seller2");
    orderBook.addBuyOrder(99.50, 200, timestamp + 2, "Buyer1");
    
    orderBook.displayOrderBook();

    std::cout << "Adding matching buy order...\n" << std::endl;
    orderBook.addBuyOrder(100.50, 500, timestamp + 3, "Buyer2");
    
    orderBook.displayOrderBook();

    std::cout << "Adding sell order that crosses...\n" << std::endl;
    orderBook.addSellOrder(99.75, 300, timestamp + 4, "Seller3");
    
    orderBook.displayOrderBook();

    std::cout << "Cancelling order ID 1...\n" << std::endl;
    orderBook.cancelOrder(1);
    
    orderBook.displayOrderBook();

    std::cout << "=== TRADE HISTORY ===" << std::endl;
    const auto& trades = orderBook.getTradeHistory();
    if (trades.empty()) {
        std::cout << "No trades executed" << std::endl;
    } else {
        std::cout << "Total Trades: " << orderBook.getTotalTradesExecuted() << std::endl;
        std::cout << "Last Trade Price: $" << orderBook.getLastTradePrice() << std::endl;
        std::cout << "\nDetailed Trades:" << std::endl;
        for (const auto& trade : trades) {
            std::cout << "Trade ID: " << trade.trade_id << " | Price: $" << trade.price 
                      << " | Qty: " << trade.quantity << " | Buyer: " << trade.buyer_id 
                      << " | Seller: " << trade.seller_id << std::endl;
        }
    }
    std::cout << "====================\n" << std::endl;
=======
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
>>>>>>> 9b8f7de04e417ac33701c58d9c5579c2ce374ef4

    return 0;
}