#ifndef ORDER_H
#define ORDER_H

#include <cstdint>
#include <string>

enum class OrderType {
    BUY,
    SELL
};

enum class OrderStatus {
    PENDING,
    PARTIALLY_FILLED,
    FILLED,
    CANCELLED
};

struct Order {
    uint64_t order_id;
    OrderType type;
    double price;
    uint64_t quantity;
    uint64_t filled_quantity;
    OrderStatus status;
    uint64_t timestamp;
    std::string trader_id;

    Order(uint64_t id, OrderType order_type, double order_price, uint64_t order_quantity, 
          uint64_t order_timestamp, const std::string& id_trader)
        : order_id(id), type(order_type), price(order_price), quantity(order_quantity),
          filled_quantity(0), status(OrderStatus::PENDING), 
          timestamp(order_timestamp), trader_id(id_trader) {}

    uint64_t getRemaining() const {
        return quantity - filled_quantity;
    }

    bool isFilled() const {
        return filled_quantity == quantity;
    }

    bool isPartiallyFilled() const {
        return filled_quantity > 0 && filled_quantity < quantity;
    }
};

#endif // ORDER_H