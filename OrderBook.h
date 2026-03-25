// OrderBook.h

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

class OrderBook {
public:
    // Constructor
    OrderBook();

    // Add buy order
    void addBuyOrder(int orderId, double price, int quantity);

    // Add sell order
    void addSellOrder(int orderId, double price, int quantity);

    // Other member functions...
};

#endif // ORDERBOOK_H
