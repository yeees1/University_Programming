#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
struct Point {
    int x, y;
};

struct Node {
    int xKey;
    vector<Point> yPoints;
    Node* left;
    Node* right;
};

Node* buildRangeTree(vector<Point> points) {
    if (points.empty()) return nullptr;

    sort(points.begin(), points.end(),
         [](const Point &a, const Point &b){
             return a.x < b.x;
         });

    int mid = points.size() / 2;
    Node* node = new Node;
    node->xKey = points[mid].x;
    node->left = nullptr;
    node->right = nullptr;

    sort(points.begin(), points.end(),
         [](const Point &a, const Point &b){
             return a.y < b.y;
         });
    node->yPoints = points;

    vector<Point> leftPoints, rightPoints;
    for (int i = 0; i < (int)points.size(); i++) {
        if (i == mid) continue;
        if (points[i].x <= node->xKey) {
            leftPoints.push_back(points[i]);
        } else {
            rightPoints.push_back(points[i]);
        }
    }
    node->left = buildRangeTree(leftPoints);
    node->right = buildRangeTree(rightPoints);

    return node;
}

void queryRangeTree(Node* root,
    int x1, int x2,
    int y1, int y2,
    vector<Point> &result)
{
    if (!root) return;

    if (root->xKey < x1) {
        queryRangeTree(root->right, x1, x2, y1, y2, result);
    }
    else if (root->xKey > x2) {
        queryRangeTree(root->left, x1, x2, y1, y2, result);
    }
    else {
        const auto &vecY = root->yPoints;

        auto lower = lower_bound(vecY.begin(), vecY.end(), Point{0, y1},
        [](const Point &a, const Point &b){
            return a.y < b.y;
        });
        auto upper = upper_bound(vecY.begin(), vecY.end(), Point{0, y2},
            [](const Point &a, const Point &b){
                return a.y < b.y;
            });

        for (auto it = lower; it != upper; ++it) {
            if (it->x >= x1 && it->x <= x2) {
                result.push_back(*it);
            }
        }

        queryRangeTree(root->left, x1, x2, y1, y2, result);
        queryRangeTree(root->right, x1, x2, y1, y2, result);
    }
}

int main() {
    vector<Point> points = {
        {1,4}, {2,2}, {3,6}, {5,3}, {6,7}, {7,1}, {8,4}
    };

    Node* root = buildRangeTree(points);

    int x1 = 2, x2 = 6;
    int y1 = 2, y2 = 5;

    vector<Point> answer;
    queryRangeTree(root, x1, x2, y1, y2, answer);

    sort(answer.begin(), answer.end(),
         [](const Point &a, const Point &b){
             if (a.x == b.x) return a.y < b.y;
             return a.x < b.x;
         });

    answer.erase(unique(answer.begin(), answer.end(),
        [](const Point &a, const Point &b){
            return (a.x == b.x && a.y == b.y);
        }),
    answer.end());

    cout << "Найденные точки в диапазоне ["
         << x1 << ".." << x2 << "] x ["
         << y1 << ".." << y2 << "]:\n";

    for (auto &p : answer) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
 
    return 0;
}