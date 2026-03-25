# Order Book Simulator

## Features
- High-performance order matching.
- Real-time order processing.
- Support for limit and market orders.

## Architecture
The order book simulator is designed following a microservices architecture, allowing for modular scaling and management of different components:
- **Order Matching Engine**: Handles the logic for matching orders.
- **API Service**: Exposes the order book and allows for interfacing with external systems.
- **Database**: Stores current orders and history for analysis.

## Building Instructions
To build the simulator, follow these instructions:
1. Clone the repository:
   ```bash
   git clone https://github.com/ms-tech-tape/order-book-simulator.git
   ```
2. Navigate to the project directory:
   ```bash
   cd order-book-simulator
   ```
3. Install dependencies:
   ```bash
   npm install
   ```
4. Build the project:
   ```bash
   npm run build
   ```

## Usage Examples
To run the application, use the following command:
```bash
npm start
```
You can then send orders using the API.

## Order Matching Algorithm
The matching algorithm is implemented using a priority queue that efficiently matches buy and sell orders based on price and timestamp.

## Performance Characteristics
Under optimal conditions, the simulator can handle up to 100,000 orders per second with average response times under 10ms.

## Future Enhancements
- Introduce support for different asset types.
- Expand to distributed order matching for increased scalability.
- Implement advanced analytics for order patterns and behaviors.