#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Order.h"
#include "Trade.h"
#include <map>
#include <deque>
#include <vector>
#include <memory>

class OrderBook {
private:
    std::map<double, std::deque<std::shared_ptr<Order>>, std::greater<double>> buy_orders;
    std::map<double, std::deque<std::shared_ptr<Order>>, std::less<double>> sell_orders;
    std::vector<Trade> trade_history;
    uint64_t next_order_id;
    uint64_t next_trade_id;

    void matchOrders();
    uint64_t executeMatch(std::shared_ptr<Order> buy_order, 
                         std::shared_ptr<Order> sell_order, double price, uint64_t quantity);

public:
    OrderBook();

    uint64_t addBuyOrder(double price, uint64_t quantity, 
                        uint64_t timestamp, const std::string& trader_id);
    uint64_t addSellOrder(double price, uint64_t quantity, 
                         uint64_t timestamp, const std::string& trader_id);
    bool cancelOrder(uint64_t order_id);

    void displayOrderBook() const;
    const std::vector<Trade>& getTradeHistory() const;
    
    double getLastTradePrice() const;
    uint64_t getTotalTradesExecuted() const;
};

#endif // ORDERBOOK_H