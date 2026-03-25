<<<<<<< HEAD
#include "OrderBook.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>

OrderBook::OrderBook() : next_order_id(1), next_trade_id(1) {}

uint64_t OrderBook::addBuyOrder(double price, uint64_t quantity, 
                               uint64_t timestamp, const std::string& trader_id) {
    uint64_t order_id = next_order_id++;
    auto order = std::make_shared<Order>(order_id, OrderType::BUY, price, quantity, timestamp, trader_id);
    
    buy_orders[price].push_back(order);
    std::cout << "[BUY ORDER] ID: " << order_id << " | Price: $" << price 
              << " | Quantity: " << quantity << " | Trader: " << trader_id << std::endl;
    
    matchOrders();
    return order_id;
}

uint64_t OrderBook::addSellOrder(double price, uint64_t quantity, 
                                uint64_t timestamp, const std::string& trader_id) {
    uint64_t order_id = next_order_id++;
    auto order = std::make_shared<Order>(order_id, OrderType::SELL, price, quantity, timestamp, trader_id);
    
    sell_orders[price].push_back(order);
    std::cout << "[SELL ORDER] ID: " << order_id << " | Price: $" << price 
              << " | Quantity: " << quantity << " | Trader: " << trader_id << std::endl;
    
    matchOrders();
    return order_id;
}

void OrderBook::matchOrders() {
    while (!buy_orders.empty() && !sell_orders.empty()) {
        auto best_buy_price = buy_orders.begin()->first;
        auto best_sell_price = sell_orders.begin()->first;

        if (best_buy_price < best_sell_price) {
            break;
        }

        auto& buy_queue = buy_orders.begin()->second;
        auto& sell_queue = sell_orders.begin()->second;

        if (buy_queue.empty() || sell_queue.empty()) {
            break;
        }

        auto buy_order = buy_queue.front();
        auto sell_order = sell_queue.front();

        uint64_t buy_remaining = buy_order->getRemaining();
        uint64_t sell_remaining = sell_order->getRemaining();
        uint64_t match_quantity = std::min(buy_remaining, sell_remaining);

        executeMatch(buy_order, sell_order, best_sell_price, match_quantity);

        if (buy_order->getRemaining() == 0) {
            buy_queue.pop_front();
            if (buy_queue.empty()) {
                buy_orders.erase(best_buy_price);
            }
        }

        if (sell_order->getRemaining() == 0) {
            sell_queue.pop_front();
            if (sell_queue.empty()) {
                sell_orders.erase(best_sell_price);
            }
        }
    }
}

uint64_t OrderBook::executeMatch(std::shared_ptr<Order> buy_order, 
                                std::shared_ptr<Order> sell_order, 
                                double price, uint64_t quantity) {
    uint64_t trade_id = next_trade_id++;
    
    buy_order->filled_quantity += quantity;
    sell_order->filled_quantity += quantity;

    if (buy_order->getRemaining() == 0) {
        buy_order->status = OrderStatus::FILLED;
    } else {
        buy_order->status = OrderStatus::PARTIALLY_FILLED;
    }

    if (sell_order->getRemaining() == 0) {
        sell_order->status = OrderStatus::FILLED;
    } else {
        sell_order->status = OrderStatus::PARTIALLY_FILLED;
    }

    Trade trade(trade_id, buy_order->order_id, sell_order->order_id, price, quantity,
                std::chrono::system_clock::now().time_since_epoch().count(),
                buy_order->trader_id, sell_order->trader_id);
    trade_history.push_back(trade);

    std::cout << "[TRADE EXECUTED] Trade ID: " << trade_id << " | Price: $" << price 
              << " | Quantity: " << quantity << " | Buyer: " << buy_order->trader_id 
              << " | Seller: " << sell_order->trader_id << std::endl;

    return trade_id;
}

bool OrderBook::cancelOrder(uint64_t order_id) {
    for (auto it = buy_orders.begin(); it != buy_orders.end(); ++it) {
        auto& queue = it->second;
        auto order_it = std::find_if(queue.begin(), queue.end(),
                              [order_id](const std::shared_ptr<Order>& o) { return o->order_id == order_id; });
        if (order_it != queue.end()) {
            (*order_it)->status = OrderStatus::CANCELLED;
            queue.erase(order_it);
            std::cout << "[ORDER CANCELLED] Buy Order ID: " << order_id << std::endl;
            return true;
        }
    }

    for (auto it = sell_orders.begin(); it != sell_orders.end(); ++it) {
        auto& queue = it->second;
        auto order_it = std::find_if(queue.begin(), queue.end(),
                              [order_id](const std::shared_ptr<Order>& o) { return o->order_id == order_id; });
        if (order_it != queue.end()) {
            (*order_it)->status = OrderStatus::CANCELLED;
            queue.erase(order_it);
            std::cout << "[ORDER CANCELLED] Sell Order ID: " << order_id << std::endl;
            return true;
        }
    }

    return false;
}

void OrderBook::displayOrderBook() const {
    std::cout << "\n=== ORDER BOOK ===" << std::endl;
    
    std::cout << "\n--- SELL ORDERS (Ask Side) ---" << std::endl;
    if (sell_orders.empty()) {
        std::cout << "No sell orders" << std::endl;
    } else {
        std::cout << std::setw(10) << "Price" << std::setw(12) << "Quantity" << std::setw(15) << "Orders" << std::endl;
        for (const auto& [price, queue] : sell_orders) {
            uint64_t total_qty = 0;
            for (const auto& order : queue) {
                total_qty += order->getRemaining();
            }
            std::cout << std::fixed << std::setprecision(2) << std::setw(10) << price 
                      << std::setw(12) << total_qty << std::setw(15) << queue.size() << std::endl;
        }
    }

    std::cout << "\n--- BUY ORDERS (Bid Side) ---" << std::endl;
    if (buy_orders.empty()) {
        std::cout << "No buy orders" << std::endl;
    } else {
        std::cout << std::setw(10) << "Price" << std::setw(12) << "Quantity" << std::setw(15) << "Orders" << std::endl;
        for (const auto& [price, queue] : buy_orders) {
            uint64_t total_qty = 0;
            for (const auto& order : queue) {
                total_qty += order->getRemaining();
            }
            std::cout << std::fixed << std::setprecision(2) << std::setw(10) << price 
                      << std::setw(12) << total_qty << std::setw(15) << queue.size() << std::endl;
        }
    }
    std::cout << "\n==================\n" << std::endl;
}

const std::vector<Trade>& OrderBook::getTradeHistory() const {
    return trade_history;
}

double OrderBook::getLastTradePrice() const {
    if (trade_history.empty()) return 0.0;
    return trade_history.back().price;
}

uint64_t OrderBook::getTotalTradesExecuted() const {
    return trade_history.size();
}
=======
#include <algorithm> // for std::find_if
#include <vector> // for std::vector
// other includes as needed

// Your code with corrected std::find_if usage here

// Example corrected usage of std::find_if: 
// auto it = std::find_if(vector.begin(), vector.end(), condition);
>>>>>>> 9b8f7de04e417ac33701c58d9c5579c2ce374ef4
