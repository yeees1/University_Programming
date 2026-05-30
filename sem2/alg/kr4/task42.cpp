#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

struct Order {
    string id;
    int distance;
};

struct Courier {
    int id;
    int routeLimit;
    int usedDistance;
    vector<Order> orders;

    Courier(int id, int limit) : id(id), routeLimit(limit), usedDistance(0) {}

    int remaining() const {
        return routeLimit - usedDistance;
    }

    bool canTake(const Order& order) const {
        return order.distance <= remaining();
    }

    void addOrder(const Order& order) {
        usedDistance += order.distance;
        orders.push_back(order);
    }
};

struct DistributionResult {
    vector<Courier> couriers;
    bool allOrdersDelivered;
    bool enoughCouriers;
    vector<Order> impossibleOrders;
};

bool compareOrdersByDistance(const Order& a, const Order& b) {
    return a.distance > b.distance;
}

DistributionResult distributeOrdersGreedy(vector<Order> orders, int maxCouriers, int routeLimit) {
    sort(orders.begin(), orders.end(), compareOrdersByDistance);

    DistributionResult result;
    result.allOrdersDelivered = true;
    result.enoughCouriers = true;

    for (const Order& order : orders) {
        if (order.distance > routeLimit) {
            result.impossibleOrders.push_back(order);
            result.allOrdersDelivered = false;
            continue;
        }

        bool assigned = false;

        // Берём длинные заказы первыми и кладём заказ в первого курьера, где осталось место.
        for (Courier& courier : result.couriers) {
            if (courier.canTake(order)) {
                courier.addOrder(order);
                assigned = true;
                break;
            }
        }

        if (!assigned) {
            if ((int)result.couriers.size() == maxCouriers) {
                result.allOrdersDelivered = false;
                result.enoughCouriers = false;
                continue;
            }

            result.couriers.push_back(Courier((int)result.couriers.size() + 1, routeLimit));
            result.couriers.back().addOrder(order);
        }
    }

    return result;
}

int lowerBoundCouriers(const vector<Order>& orders, int routeLimit) {
    int totalDistance = 0;
    for (const Order& order : orders) {
        totalDistance += order.distance;
    }
    return (totalDistance + routeLimit - 1) / routeLimit;
}

void printOrders(const vector<Order>& orders) {
    for (const Order& order : orders) {
        cout << " " << order.id << ": " << order.distance << " км\n";
    }
}

void printDistribution(const vector<Order>& orders, int maxCouriers, int routeLimit) {
    cout << "Заказы:\n";
    printOrders(orders);
    cout << "Доступно курьеров K = " << maxCouriers << "\n";
    cout << "Лимит маршрута одного курьера T = " << routeLimit << " км\n";
    cout << "Нижняя граница по сумме расстояний: "
         << lowerBoundCouriers(orders, routeLimit) << " курьер(а/ов)\n\n";

    DistributionResult result = distributeOrdersGreedy(orders, maxCouriers, routeLimit);

    cout << "Жадное распределение по курьерам:\n";
    for (const Courier& courier : result.couriers) {
        cout << " Курьер " << courier.id
             << " [маршрут: " << courier.usedDistance << "/" << courier.routeLimit << " км]: ";
        for (int i = 0; i < (int)courier.orders.size(); ++i) {
            if (i) cout << ", ";
            cout << courier.orders[i].id << "(" << courier.orders[i].distance << ")";
        }
        cout << "\n";
    }

    if (!result.impossibleOrders.empty()) {
        cout << "\nЗаказы, которые нельзя доставить одним курьером из-за T:\n";
        for (const Order& order : result.impossibleOrders) {
            cout << " " << order.id << " (" << order.distance << " км > "
                 << routeLimit << " км)\n";
        }
    }

    cout << "\nИтог: задействовано " << result.couriers.size() << " курьер(а/ов).\n";
    if (result.allOrdersDelivered) {
        cout << "Все заказы распределены, лимит T нигде не нарушен.\n";
    } else if (!result.enoughCouriers) {
        cout << "Не все заказы распределены: доступных K курьеров не хватило.\n";
    } else {
        cout << "Не все заказы распределены: есть заказ длиннее лимита T.\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Order> orders = {
        {"Заказ-1", 15},
        {"Заказ-2", 8},
        {"Заказ-3", 20},
        {"Заказ-4", 5},
        {"Заказ-5", 12},
        {"Заказ-6", 18},
        {"Заказ-7", 3},
        {"Заказ-8", 9},
        {"Заказ-9", 14},
        {"Заказ-10", 7},
    };

    cout << "Тест 1: K=5, T=25\n";
    printDistribution(orders, 5, 25);

    cout << "\nТест 2: K=4, T=25 (курьеров мало)\n";
    printDistribution(orders, 4, 25);

    cout << "\nТест 3: K=3, T=30\n";
    printDistribution({{"A", 10}, {"B", 10}, {"C", 10}, {"D", 20}, {"E", 5}}, 3, 30);

    cout << "\nТест 4: заказ длиннее T\n";
    printDistribution({{"A", 12}, {"B", 40}, {"C", 8}}, 3, 25);

    return 0;
}
