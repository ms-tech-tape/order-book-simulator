#ifndef TRADE_H
#define TRADE_H

#include <cstdint>
#include <string>

struct Trade {
    uint64_t trade_id;
    uint64_t buy_order_id;
    uint64_t sell_order_id;
    double price;
    uint64_t quantity;
    uint64_t timestamp;
    std::string buyer_id;
    std::string seller_id;

    Trade(uint64_t id, uint64_t buy_id, uint64_t sell_id, double trade_price,
          uint64_t trade_quantity, uint64_t trade_timestamp, const std::string& buyer,
          const std::string& seller)
        : trade_id(id), buy_order_id(buy_id), sell_order_id(sell_id),
          price(trade_price), quantity(trade_quantity), timestamp(trade_timestamp),
          buyer_id(buyer), seller_id(seller) {}
};

#endif // TRADE_H