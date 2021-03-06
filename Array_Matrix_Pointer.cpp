//DoubleIndex
/*88. 合并两个有序数组*/
/*
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

说明：
初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
*/
class Solution {
public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int p1 = m - 1, p2 = n - 1;
    int p = m + n - 1;
    while ( (p1 >= 0) && (p2 >= 0) ) {
      nums1[p --] = (nums1[p1] < nums2[p2]) ? nums2[p2--] : nums1[p1--];
    }
    for(int i = 0; i <= p2; i ++) {
      nums1[i] = nums2[i];
    }
  }
};


/***76. 最小覆盖子串*/
/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。
*/
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> map(128, 0);
        // 存放目标t需要的字符计数
        for(auto ch : t) ++map[ch];
        // 目标t的字符数量
        int counter = t.size();
        int begin = 0, end = 0;
        int head = 0;
        int len = INT_MAX;
        while(end < s.size()) {
            /* 右边加，当这个字符是滑动窗缺少的字符时，计数器减一 */
            if(map[s[end ++]] -- > 0) 
                -- counter;
            while(counter == 0) {
                if(end - begin < len) {
                    len = end - begin;
                    head = begin;
                }
                /* 左边减，当这个字符是滑动窗不缺也不富余的字符时，计数器加一 */
                if(map[s[begin ++]] ++ == 0) ++ counter;
            }
        }
        return len == INT_MAX ? "" : s.substr(head, len);
    }
};


/*26. 删除排序数组中的重复项*/
/*
给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
*/
/*典型的双指针用法，注意与 189 原地 旋转数组 的方法做对比*/
class Solution {
public:
  int removeDuplicates(vector<int>& nums) {
    if(nums.size() <= 0)
      return 0;
    int i = 0, j = 1, n = nums.size();
    while(++i < n) {
      if(nums[i] != nums[i - 1]) {
        nums[j++] = nums[i];
      }
    }
    return j;
  }
};


/*
283. 移动零
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
*/
class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    int n = nums.size(), j = 0;
    for(int i = 0; i < n; i ++) {
      if(nums[i] != 0) {
        swap(nums[i], nums[j]);
        j ++;
      }
    }
  }
};


/*75. 颜色分类*/
/*
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

进阶：
你可以不使用代码库中的排序函数来解决这道题吗？
你能想出一个仅使用常数空间的一趟扫描算法吗？
*/
// 三指针：最前面填充0，中间i顺延填充1，最后的位置留给2
class Solution {
public:
  void sortColors(vector<int>& nums) {
    int size = nums.size();
    if(size < 2) return;
    int i = 0, zero = 0, two = size;
    while(i < two) {
      if(nums[i] == 0) swap(nums[zero ++], nums[i ++]);
      else if(nums[i] == 1) i ++;
      else swap(nums[-- two], nums[i]);
    }
  }
};


/*====================================最大容积问题====================================*/
// 可对比 Stack_Queue_DFS_BFS 中的 /*84. 柱状图中最大的矩形*/
/**11. 盛最多水的容器*/
/*
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
*/
// 双指针
class Solution {
public:
  int maxArea2(vector<int>& height) {
    int l = 0, r = height.size() - 1;
    int ans = 0;
    while (l < r) {
      int area = min(height[l], height[r]) * (r - l);
      ans = max(ans, area);
      if (height[l] <= height[r]) {
          ++ l;
      } else {
          -- r;
      }
    }
    return ans;
  }
};


/**42. 接雨水*/
/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
*/
class Solution {
public:
  int trap2(vector<int>& height) {
    int n = height.size(), ans = 0;
    if(n <= 1)
      return 0;
    vector<int> leftMax(n, 0), rightMax(n, 0);
    leftMax[0] = height[0];
    for(int i = 1; i < n; i ++) {
      leftMax[i] = max(height[i], leftMax[i-1]);
    }
    rightMax[n-1] = height[n-1];
    for(int i = n-2; i >= 0; i --) {
      rightMax[i] = max(height[i], rightMax[i+1]);
    }
    for(int i = 1; i <= n-2; i ++) {
      ans += min(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
  }

  int trap1(vector<int>& height) {
    int n = height.size(), ans = 0;
    if(n <= 1)
      return 0;
    stack<int> stk; stk.push(0);
    for(int i = 1; i < n; i ++) {
      // 单调递减栈
      while(!stk.empty() && height[i] >= height[stk.top()]) {
        int base = stk.top(); stk.pop();
        if(stk.empty()) break;
        ans += (min(height[i], height[stk.top()]) - height[base]) * (i - stk.top() - 1);
      }
      stk.push(i);
    }
    return ans;
  }

  int trap(vector<int>& height) {
    int leftMax = 0, rightMax = 0, ans = 0;
    int left = 0, right = height.size()-1;
    while(left < right) {
      if(height[left] < height[right]) {
        (height[left] >= leftMax) ? leftMax = height[left] : ans += (leftMax - height[left]);
        left ++;
      } else {
        (height[right] >= rightMax) ? rightMax = height[right] : ans += (rightMax - height[right]);
        right --;
      }
    }
    return ans;
  }
};
/*===========================================================================================*/


/*=============================================二分查找==================================================*/
/**牛课网：有序矩阵查找*/
/*现在有一个行和列都排好序的矩阵，请设计一个高效算法，快速查找矩阵中是否含有值x。*/
class Finder {
public:
    bool findX(vector<vector<int> > mat, int n, int m, int x) {
        // write code here
        int i = 0, j = m - 1;
        while(i < n && j >= 0){
            if(x > mat[i][j]){
                ++ i;
            } else if(x < mat[i][j]){
                -- j;
            } else {
                return true;  // return {i, j};
            }
        }
        return false; // return {};
    }
};

/*33. 搜索旋转排序数组*/
// 二分查找，注意区间特性
class Solution {
public:
  int search(vector<int>& nums, int target) {
    int n = nums.size();
    int l = 0, r = n - 1;
    while(l <= r) {
      int m = (l + r) >> 1;
      if(nums[m] == target) return m;
      if(nums[m] >= nums[0]) {
        if(nums[0] <= target && target < nums[m])
          r = m - 1;
        else 
          l = m + 1;
      } else {
        if(nums[m] < target && target <= nums[n - 1])
          l = m + 1;
        else 
          r = m - 1;
      }
    }
    return -1;
  }
};


/**189. 旋转数组*/
/*
给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数
要求使用空间复杂度为 O(1) 的 原地 算法。
*/
// 方法一：使用环状替换
// 注意这里使用count进行计数
class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size(), count = 0;
    k %= n;
    for(int i = 0; count < n; i ++) {
      int c = i, prev = nums[i];
      do {
        int j = (c + k) % n;
        int curr = nums[j];
        nums[j] = prev;
        prev = curr;
        c = j;
        count ++;
      } while(c != i);
    }
  }
};
// 方法二：使用反转
/* 这个方法基于这个事实：当我们旋转数组 k 次， k%n 个尾部元素会被移动到头部，剩下的元素会被向后移动。
原始数组                  : 1 2 3 4 5 6 7
反转所有数字后             : 7 6 5 4 3 2 1
反转前 k 个数字后          : 5 6 7 4 3 2 1
反转后 n-k 个数字后        : 5 6 7 1 2 3 4 --> 结果
*/
class Solution {
public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    reverse(nums, 0, n - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, n - 1);
  }

  void reverse(vector<int>& nums, int start, int end) {
    while(start < end) {
      swap(nums[start ++], nums[end --]);
    }
  }
};


/*===================================================通过横纵索引对矩阵进行旋转=====================================================================*/
/*剑指 Offer 29. 顺时针打印矩阵*/
/*输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。*/
class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int nrow = matrix.size();
    if(nrow == 0) return vector<int>();
    int ncol = matrix[0].size();
    if(ncol == 0) return vector<int>();
    int t = 0, b = nrow - 1, l = 0, r = ncol - 1, x = 0;
    vector<int> ans(nrow * ncol);
    while(1) {
      // 从左往右
      for(int i = l; i <= r; i ++) ans[x ++] = matrix[t][i];
      // 最上层遍历完，下移
      if(++ t > b) break;

      // 从上往下
      for(int i = t; i <= b; i ++) ans[x ++] = matrix[i][r];
      // 最右侧遍历完，左移
      if(l > -- r) break;

      // 从右往左
      for(int i = r; i >= l; i --) ans[x ++] = matrix[b][i];
      // 最下层遍历完，上移
      if(t > -- b) break;

      // 从下往上
      for(int i = b; i >= t; i --) ans[x ++] = matrix[i][l];
      // 最左侧遍历完，右移
      if(++ l > r) break;
    }
    return ans;
  }
};


/*48. 旋转图像*/
/*给定一个 n × n 的二维矩阵表示一个图像。
将图像顺时针旋转 90 度。

说明：
你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。
*/
class Solution {
public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; ++i) {
      for (int j = 0; j < (n + 1) / 2; ++j) {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[n - j - 1][i];
        matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
        matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
        matrix[j][n - i - 1] = temp;
      }
    }
  }
};


/*===================================================构造排列组合并去重=====================================================================*/
// 15题、16题都是二分查找，最重要的是学习如何对排列组合进行去重复
/*15. 三数之和*/
/*
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
*/
class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector< vector<int> > res;
    if(nums.size() < 3)
      return res;
    // 排序是遍历构造组合时的技巧
    sort(nums.begin(), nums.end());
    // 减 2，注意
    for(int i = 0; i < nums.size() - 2; i ++) {
      // 剪枝，可以没有
      if(nums[i] > 0) return res; 
      // 开始的时候，若是连着的两个相同，取前面的（同样的起点不用两次） ！！！
      if(i > 0 && nums[i] == nums[i - 1]) continue;
      int t = -1 * nums[i];
      int l = i + 1, r = nums.size() - 1;
      while(l < r) {
        if(nums[l] + nums[r] > t)
          r --;
        else if(nums[l] + nums[r] < t)
          l ++;
        else {
          res.push_back({nums[i], nums[l], nums[r]});
          // 去重逻辑应该放在找到一个三元组之后
          while (r > l && nums[r] == nums[r - 1]) r --;
          while (r > l && nums[l] == nums[l + 1]) l ++;
          l ++; r --;
        }
      }
    }
    return res;
  }
};


/*16. 最接近的三数之和*/
/*
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
*/
class Solution {
public:
  int threeSumClosest(vector<int>& nums, int target) {
    long ans = INT_MAX;
    sort(nums.begin(), nums.end());

    // 根据差值的绝对值来更新答案
    auto update = [&](long cur) {
      if (abs(cur - target) < abs(ans - target)) {
        ans = cur;
      }
    };

    for(int i = 0; i < nums.size() - 2; i ++) {
      if(i > 0 && nums[i] == nums[i - 1])
        continue ;
      int l = i + 1, r = nums.size() - 1;
      while(l < r) {
        int sum3 = nums[i] + nums[l] + nums[r];
        if(sum3 == target)
          return target;
        update(sum3);
        if(sum3 < target) {
          while(l < r && nums[l] == nums[l + 1]) l ++;
          l ++;
        } else {
          while(r > l && nums[r] == nums[r - 1]) r --;
          r --;
        }
      }
    }
    return ans;
  }
};


/*
18. 四数之和
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，
使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：
答案中不可以包含重复的四元组。
*/
class Solution {
public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> res;
    if(nums.size() < 4)
      return res;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size() - 3; i ++) {
      if(i > 0 && nums[i] == nums[i - 1])
        continue;
      for(int j = i + 1; j < nums.size() - 2; j ++) {
        if(j > i + 1 && nums[j] == nums[j - 1])
          continue;
        int nt = target - nums[i] - nums[j];
        int l = j + 1, r  = nums.size() - 1;
        while( l < r) {
          if(l > j + 1 && nums[l] == nums[l - 1]) {
            l ++;
            continue;
          }
          if(nums[l] + nums[r] > nt)
            r --;
          else if(nums[l] + nums[r] < nt)
            l ++;
          else {
            res.push_back({nums[i], nums[j], nums[l], nums[r]});
            l ++; r --;
          }
        }
      }
    }
    return res;
  }
};


/*=================================================== 排列组合问题 ===========================================================*/

/*78. 子集*/
/*
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
*/
class Solution {
private:
  vector< vector<int> > ans;
  vector<int> perm;
public:
  vector<vector<int>> subsets(vector<int>& nums) {
    backtracking(nums, 0);
    return ans;
  }

  void backtracking(vector<int>& nums, int idx) {
    if(idx == nums.size()) {
      ans.push_back(perm);
      return;
    }
    perm.push_back(nums[idx]);
    backtracking(nums, idx + 1);
    perm.pop_back();
    backtracking(nums, idx + 1);
  }
};


/*46. 全排列*/
/*给定一个 没有重复 数字的序列，返回其所有可能的全排列。*/
class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    backTracking(res, nums, 0, (int)nums.size());
    return res;
  }

  void backTracking(vector<vector<int>>& res, vector<int>& nums, int idx, int len) {
    if(idx == len) {
      res.push_back(nums);
      return ;
    }
    for(int i = idx; i < len; i ++) {
      swap(nums[idx], nums[i]);
      backTracking(res, nums, idx + 1, len);
      swap(nums[idx], nums[i]);
    }
  }
};


/*47. 全排列 II， 见下面的 ‘组合总和 II’ 注意对比*/
/*给定一个可包含重复数字的序列 nums，按任意顺序 返回所有不重复的全排列。
时间复杂度：O(N * N!)，这里 NN 为数组的长度。
空间复杂度：O(N * N!)。
*/
class Solution {
private:
vector<vector<int>> res;
vector<int> perm;
// 必须记住这个技巧和下面的去重复操作
vector<int> visit;

public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    visit.resize(nums.size(), 0);
    sort(nums.begin(), nums.end());
    backTracking(nums, 0, nums.size());
    return res;
  }

  void backTracking(vector<int>& nums, int idx, int len) {
    if(idx == len) {
      res.push_back(perm); return;
    }
    // 为什么从0开始？？？
    for(int i = 0; i < len; i ++) {
      // !visit[i - 1] == true 也就是 visit[i - 1] = false
      // visit[i - 1] = true  说明 在同一分支用过
      // visit[i - 1] = flase 说明 在同一分层用过
      if(i > 0 && nums[i] == nums[i - 1] && !visit[i - 1]) continue;
      // 初始值是0，如果=0说明是第一次用到它
      if(!visit[i]) {
        visit[i] = 1;
        perm.push_back(nums[i]);
        backTracking(nums, idx + 1, len);
        perm.pop_back();
        visit[i] = 0;
      }
    }
  }
};


/*31. 下一个排列*/
/*
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。
如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。
必须 原地 修改，只允许使用额外常数空间。
*/
class Solution {
public:
  // 3 5 2 4 7 1 6 8
  void nextPermutation(vector<int>& nums) {
    int i = nums.size() - 2;
    // 从后往前找到第一个升序对
    while(i >= 0 && nums[i] >= nums[i + 1]) i --;
    if(i >= 0) {
      int j = nums.size() - 1;
      // 在 [i+1, end) 里找到比 nums[i] 大的 最小的数
      while(j >= 0 && nums[i] >= nums[j]) j --;
      swap(nums[i], nums[j]);
    }
    // [i+1, end) 做成正序 保证当前组合最小
    reverse(nums.begin() + i + 1, nums.end());
  }
};


/*
39. 组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
*/
class Solution {
private:
  vector< vector<int> > ans;
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    backTracking(candidates, {}, 0, target);
    return ans;
  }

  void backTracking(vector<int>& candidates, vector<int> perm, int idx, int target) {
    if(target == 0) {
      ans.push_back(perm); return;
    }
    for(int i = idx; i < candidates.size(); i ++) {
      if(target - candidates[i] < 0)
        break;
      perm.push_back(candidates[i]);
      backTracking(candidates, perm, i, target - candidates[i]);
      perm.pop_back();
    }
  }
};

/*========================================================================================================================*/

/*40. 组合总和 II
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 
*/
// 使用visited进行层间剪枝，耗时从8ms降低到4ms，也可以不用
class Solution {
private:
vector<vector<int>> ans;
vector<int> visited;
public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    visited.resize(candidates.size(), 0);
    sort(candidates.begin(), candidates.end());
    backTracking(candidates, {}, target, 0);
    return ans;
  }

  void backTracking(vector<int>& candidates, vector<int> perm, int target, int idx) {
    if(target == 0) {
      ans.push_back(perm); return;
    }
    for(int i = idx; i < candidates.size(); i ++) {
      if(target - candidates[i] < 0) break;
      if(i > idx && candidates[i] == candidates[i - 1] && !visited[i - 1]) continue;
      if(!visited[i]) {
        visited[i] = 1;
        perm.push_back(candidates[i]);
        backTracking(candidates, perm, target - candidates[i], i + 1);
        perm.pop_back();
        visited[i] = 0;
      }
    }
  } 
};


/*=========================================================================================================================================*/


/*41. 缺失的第一个正数 (287.寻找重复数 也用到了这一题的技巧，原地判重)*/
/*给你一个未排序的整数数组，请你找出其中没有出现的最小的正整数。*/
//对于一个长度为 N 的数组，其中没有出现的最小正整数只能在 [1, N+1] 中。这是因为如果 [1, N] 都出现了，那么答案是 N+1，否则答案是 [1, N] 中没有出现的最小正整数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int& num: nums) {
            if (num <= 0) {
                num = n + 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};


/*287.寻找重复数*/
/*给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。*/
class Solution {
public:
  int findDuplicate(vector<int>& nums) {
    for(int i = 0; i < nums.size(); i ++) {
      int x = abs(nums[i]);
      if(nums[x - 1] < 0)
        return x;
      else
        nums[x - 1] = -abs(nums[x - 1]);
    }
    return -1;
  }
};

// 方法二：置换
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};


/***209. 长度最小的子数组*/
/*
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
示例：
输入：s = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
*/
class Solution {
public:
  int minSubArrayLen(int s, vector<int>& nums) {
    int sum = 0, i = 0, ans = INT_MAX;
    for( int j = 0; j < nums.size(); j ++ ) {
      sum += nums[j];
      while( i <= j && sum >= s ) {
        ans = min(ans, (j - i + 1));
        sum -= nums[i];
        i ++;
      }
    }
    return (ans == INT_MAX) ? 0 : ans;
  }
};


/*最接近零的子数组和*/
/*
做法就是利用前缀和，先用一个数组sum[i]来保存从nums[0]到nums[i]的和，同时还要记录下标。

那么，我们想要得到nums[i]到nums[j]的和，只要用sum[j] - sum[i-1]就可以了。
剩下的工作就是对sum数组排序，找到排序后相邻的差的绝对值最小的那一对节点。
*/
class Solution {
public:
  vector<int> subarraySumClosest(vector<int>& nums) {
    int n = nums.size();
    vector< pair<int, int> > sum(n + 1);
    sum[0].first = 0; sum[0].second = -1;
    for(int i = 0; i < n; i ++) {
      sum[i + 1].first = sum[i].first + nums[i];
      sum[i + 1].second = i;
    }
    sort(sum.begin(), sum.end(), [](pair<int, int> a, pair<int, int> b) {return a.first < b.first});
    vector<int> ans(2);
    int diff = INT_MAX;
    for(int i = 1; i <= n; i ++) {
      int curr = abs(sum[i].first - sum[i - 1].first);
      if(curr < diff) {
        diff = curr;
        ans[0] = min(sum[i].second, sum[i - 1].second) + 1;
        ans[1] = max(sum[i].second, sum[i - 1].second);
      }
    }
    return ans;
  }
};

/*166. 分数到小数*/
/*
给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。
如果小数部分为循环小数，则将循环的部分括在括号内。
如果存在多个答案，只需返回 任意一个 。
对于所有给定的输入，保证 答案字符串的长度小于 104 。
*/
// 这道题目的关键用到一个数学定理：一个分数不是有限小数，就是无限循环小数
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }

        string res;
        bool isNegative = false;
        if (numerator > 0 && denominator < 0 || numerator < 0 && denominator > 0) {
            isNegative = true;
        }

        long num = labs(numerator);
        long denom = labs(denominator);
        long remainder = num;
        // 如果分子大于分母
        if (num >= denom) {
            remainder = num % denom;
            // 大于0的部分
            res += to_string(num / denom);
        }
        // 是不是整除
        if (remainder == 0) {
            return isNegative ? "-" + res : res;
        }

        // 如果分子小于分母，就是0开头
        if (remainder == labs(num)) {
            res += "0";
        }
        // 加小数点开始小数部分
        res += ".";
        unordered_map<int, int> rem2Pos;
        int index = res.size();

       // 分数一定是有限小数或者无限循环小数，这里通过 remainder=0 或者 remainder重复出现 作为循环退出的判断条件
        while (remainder && !rem2Pos.count(remainder)) {
            rem2Pos[remainder] = index++;
            // 技巧，分数除法向后借10
            remainder *= 10;
            int digit = remainder / denom;
            remainder = remainder % denom;
            res += to_string(digit);
        }

        if (rem2Pos.count(remainder)) {
          // 上面记录index是为了下面插入'('，循环小数的开始位置
            res.insert(rem2Pos[remainder], "(");
            res.push_back(')');
        }

        return isNegative ? "-" + res : res;
    }
};

// 作者：jyj407
// 链接：https://leetcode-cn.com/problems/fraction-to-recurring-decimal/solution/zhong-gui-zhong-ju-xi-jie-kao-cha-ti-by-jyj407/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。


/*842. 将数组拆分成斐波那契序列*/
/*
给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]。

形式上，斐波那契式序列是一个非负整数列表 F，且满足：

0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
F.length >= 3；
对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。

返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。
*/
class Solution {
private:
  vector<int> ans;
public:
  vector<int> splitIntoFibonacci(string S) {
    backTracking(S, 0, 0, 0);
    return ans;
  }

  bool backTracking(string S, int idx, long long sum, long long prev) {
    if(idx >= S.size()) {
      return ans.size() >= 3;
    }
    long long curr = 0;
    for(int i = idx; i < S.size(); i ++) {
      // 可以是0本身，即 S[idx]=0, 但要排除0开头
      if(i > idx && S[idx] == '0') break;
      curr = curr * 10 + (S[i] - '0');
      // 数值不能超
      if(curr > INT_MAX) break;
      // 首先得满足斐波那契式序列有了两个数
      // curr 需要等于前两个数的和
      if(ans.size() >= 2) {
        if(sum > curr) continue;
        else if(sum < curr) break;
      }
      ans.push_back(curr);
      if(backTracking(S, i + 1, prev + curr, curr)) 
        return true;
      ans.pop_back();
    }
    return false;
  }
};


/*剑指 Offer 14- I. 剪绳子*/
/*
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
*/
class Solution {
public:
  vector<int> maxProd;
  int cuttingRope2(int n) {
    maxProd.resize(n + 1, 0);
    if(n <= 2)
      return 1;
    if(n == 3)
      return 2;
    maxProd[1] = 1;
    maxProd[2] = 2;
    maxProd[3] = 3;
    return findMaxProd(n);
  }

  int findMaxProd(int n) {
    int ans = 0;
    for(int i = 1; i <= n / 2; i ++) {
      int l = i, r = n - i, lp, rp;
      if(maxProd[l] != 0)
        lp = maxProd[l];
      else
        lp = findMaxProd(l);
      if(maxProd[r] != 0)
        rp = maxProd[r];
      else
        rp = findMaxProd(r);
      ans = max(ans, l * r);
      ans = max(ans, lp * rp);
    }
    maxProd[n] = ans;
    return ans;
  }

  int cuttingRope(int n) {
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
      for (int j = 1; j <= i / 2; j++) {
        // 绳子分成两段，一段是j，另一段是i - j，此时i - j要判断是否需要继续切割
        dp[i] = max(dp[i], j * max(i - j, dp[i - j]));
      }
    }
    return dp[n];
  }
};

/*剑指 Offer 14- II. 剪绳子 II*/
/*
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。
请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
*/
class Solution {
public:
  int cuttingRope(int n) {
    if (n <= 3) 
      return n - 1;
    long rs = 1;
    while (n > 4) {
      rs *= 3;
      rs %= 1000000007;
      n -= 3;
    }
    return (rs * n) % 1000000007;
  }
};


/**219. 存在重复元素 II*/
/*给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至多为 k。*/
class Solution {
public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    int n = nums.size();
    if(n < 2) return false;
    unordered_map<int, int> map;
    for(int i = 0; i < n; i ++) {
      if(!map.count(nums[i])) 
        map[nums[i]] = i;
      else {
        if(i - map[nums[i]] <= k) return true;
        else map[nums[i]] = i;
      } 
    }
    return false;
  }
};


/*220. 存在重复元素 III*/
/*
level: 中等
在整数数组 nums 中，是否存在两个下标 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值小于等于 t ，且满足 i 和 j 的差的绝对值也小于等于 ķ 。
如果存在则返回 true，不存在返回 false。
---
题目：在整数数组 nums 中，是否存在两个下标 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值小于等于 t ，且满足 i 和 j 的差的绝对值也小于等于k
要满足两个条件
1、存在两个下标 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值小于等于 t
2、满足 i 和 j 的差的绝对值也小于等于k
第二个条件很好满足，维持一个滑动窗口即可，关键是第一个条件
由|nums[i]-num[j]|<=t可以推出
nums[i]-t<=nums[j]<=nums[i]+t
现在，set的内置函数lower_bound可以找到第一个大于等于nums[i]-t的数，则这个数再满足小于等于nums[i]+t即可
同时，这道题目不需要multiset。即便有重复，重复数字挨得足够近在插入之前就已经满足条件了；重复数字离得太远，不会同时进入滑动窗口
*/
class Solution {
public:
  bool containsNearbyAlmostDuplicate(std::vector<int>& nums, int k, int t) {
    std::set<long> s;
    for (int i = 0; i < nums.size(); ++ i) {
      auto pos = s.lower_bound(long(nums[i]) - t);
      ////< @attention
      if(pos != s.end() && *pos <= long(nums[i]) + t) {return true;}
      s.insert(nums[i]);
      if(s.size() > k) {s.erase(nums[i - k]);} ////< @note 维护活动窗口
    }
    return false;
  }
};
// 作者：zhu-que-3
// 链接：https://leetcode-cn.com/problems/contains-duplicate-iii/solution/jian-dan-yi-dong-de-cjie-fa-by-zhu-que-3-4p53/
// 来源：力扣（LeetCode）


