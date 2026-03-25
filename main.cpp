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

    return 0;
}