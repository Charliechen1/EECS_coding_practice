class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        size_t num_len = nums.size();
        if (num_len <= 1) {
            return num_len;
        }
        int8_t is_raise = -1;
        int res = 1;
        for (vector<int>::const_iterator it=nums.begin();
            it!=nums.end()-1;
            ++it){
            if (*(it + 1) == *it) continue;
            if (*(it+1) > *it != is_raise) {
                is_raise = *(it+1) > *it;
                res++;
            }
        }
        return res;
    }
};