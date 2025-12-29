#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

/*
  分块维护按 value 排序的元素 (value, index)。
  每个块内有序（用 vector），块之间按 value 递增。
  插入：先通过块的最大值 binary search 定位块，再在块内 lower_bound 插入。
  查最接近元素：检查插入位置的前后元素，以及前一块的尾、后一块的首。
  当块变得过大时（> 2*B），将块二分为两个块以平衡。
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    if (n <= 0) return 0;

    int first;
    cin >> first;

    // block size 参数，经验值：sqrt(n) 或至少 100
    int B = max(100, (int)(sqrt(n)));
    vector<vector<pair<int,int>>> blocks; // 每块：有序的 (value, index)
    blocks.push_back(vector<pair<int,int>>(1, {first, 1}));

    for (int i = 2; i <= n; ++i) {
        int v;
        cin >> v;
        // 用 blocks.back().back().first 构造一个由块最大值组成的单调序列以二分定位块
        int lo = 0, hi = (int)blocks.size() - 1, blk = (int)blocks.size() - 1;
        // 找第一个块，其末元素 >= v
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (blocks[mid].back().first >= v) {
                blk = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        // blk 是第一个块末 >== v 的块，如果没有（v 大于所有块末），blk = blocks.size()-1 (最后一个块)
        // 在该块内用 lower_bound 找插入位置
        auto &block = blocks[blk];
        auto it = lower_bound(block.begin(), block.end(), make_pair(v, -1),
                              [](const pair<int,int>& a, const pair<int,int>& b){
                                  if (a.first != b.first) return a.first < b.first;
                                  return a.second < b.second;
                              });
        int pos = (int)distance(block.begin(), it);

        // 候选点：块内 pos 和 pos-1；前一块的最后元素；后一块的第一个元素
        long long best_diff = LLONG_MAX;
        int best_idx = 0;
        int best_val = INT_MAX;

        auto consider = [&](int valcand, int idxcand) {
            long long diff = llabs(1LL * valcand - v);
            if (diff < best_diff || (diff == best_diff && valcand < best_val)) {
                best_diff = diff;
                best_idx = idxcand;
                best_val = valcand;
            }
        };

        if (pos < (int)block.size()) consider(block[pos].first, block[pos].second);
        if (pos - 1 >= 0) consider(block[pos - 1].first, block[pos - 1].second);
        if (blk - 1 >= 0) {
            auto &pb = blocks[blk - 1];
            consider(pb.back().first, pb.back().second);
        }
        if (blk + 1 < (int)blocks.size()) {
            auto &nb = blocks[blk + 1];
            if (!nb.empty()) consider(nb.front().first, nb.front().second);
        }

        cout << best_diff << ' ' << best_idx << '\n';

        // 插入 (v, i) 到 block 的 pos 位置
        block.insert(block.begin() + pos, {v, i});

        // 若 block 太大则拆分
        if ((int)block.size() > 2 * B) {
            int mid = (int)block.size() / 2;
            vector<pair<int,int>> newBlock;
            newBlock.reserve(block.size() - mid);
            newBlock.insert(newBlock.end(), block.begin() + mid, block.end());
            block.erase(block.begin() + mid, block.end());
            // 插入到 blocks 中间位置 blk+1
            blocks.insert(blocks.begin() + (blk + 1), std::move(newBlock));
        }
    }

    return 0;
}
