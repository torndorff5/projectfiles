#include <iostream>
using namespace std;
long long a[10];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int s, e, k;
        cin >> s >> e >> k;
        a[s] += k;
        a[e + 1] -= k;
    }
    long long now = 0;
    long long best = 0;
    for (int i = 1; i <= n; i++) {
        now += a[i];
        if (now > best)
            best = now;
    }
    cout << best << endl;
}
