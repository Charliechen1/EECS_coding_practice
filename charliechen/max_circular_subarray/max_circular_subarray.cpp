using namespace std;

// using kadene algorithm directly for one-order subarray
// for two-order subarray, it's the total sum excluding
// the smallest subarray, thus using an inverse version
// of the kadene algorith
int maxSubarraySumCircular(vector<int>& A) {
    int sum = accumulate(A.begin(), A.end(), 0);

    int res1 = kadene(A, 0, A.size(), false);
    int res2 = sum + kadene(A, 1, A.size(), true);
    int res3 = sum + kadene(A, 0, A.size() - 1, true);
    return max(max(res1, res2), res3);
}

// kadene algorithm is to find the sum of max subarray of an array
// it's idea is based on dynamic programming
// define D_i as the sum of the maximum subarray ending at
// i-th element. Easy to find out that D_i+1 will be decieded
// by D_i and A_i+1. If D_i < 0, then D_i+1 is just A_i+1,
// otherwise, it's the sum of the two part
// With D array, the sum of the maximum of subarray will be the
// maximum of D.
int kadene(vector<int>& A, int start, int end, bool inverse) {
    if (start < 0 || end > A.size()) {
        return 0;
    }
    int cur = numeric_limits<int>::min();
    int res = numeric_limits<int>::min();
    for (int idx=start; idx<end; idx++) {
        int a = A[idx];
        if (inverse) {
            a = -a;
        }
        cur = a + max(cur, 0);
        res = max(cur, res);
    }
    return res;
}
