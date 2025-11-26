#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Block {
    int width;
    int height;
};

struct BlockArray {
    Block* data;
    int size;
    int capacity;
};

void init_array(BlockArray* arr, int initial_capacity) {
    arr->data = new Block[initial_capacity];
    arr->capacity = initial_capacity;
    arr->size = 0;
}

void push_back(BlockArray* arr, Block block) {
    if (arr->size >= arr->capacity) {
        int new_capacity = arr->capacity * 2;
        Block* new_data = new Block[new_capacity];
        for (int i = 0; i < arr->size; i++) {
            new_data[i] = arr->data[i];
        }
        delete[] arr->data;
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size++] = block;
}

void destroy_array(BlockArray* arr) {
    delete[] arr->data;
}

bool compare_blocks(const Block& a, const Block& b) {
    if (a.width == b.width) {
        return a.height > b.height;
    }
    return a.width > b.width;
}

int find_max_pyramid_height(BlockArray* blocks) {
    sort(blocks->data, blocks->data + blocks->size, compare_blocks);
    
    vector<int> dp(blocks->size, 0);
    int max_height = 0;
    
    for (int i = 0; i < blocks->size; i++) {
        dp[i] = blocks->data[i].height;
        for (int j = 0; j < i; j++) {
            if (blocks->data[i].width < blocks->data[j].width) {
                dp[i] = max(dp[i], dp[j] + blocks->data[i].height);
            }
        }
        max_height = max(max_height, dp[i]);
    }
    
    return max_height;
}

int main() {
    int N;
    cin >> N;
    
    BlockArray blocks;
    init_array(&blocks, N);
    
    for (int i = 0; i < N; i++) {
        Block block;
        cin >> block.width >> block.height;
        push_back(&blocks, block);
    }
    
    long long max_height = find_max_pyramid_height(&blocks);
    cout << max_height << endl;
    
    destroy_array(&blocks);
    return 0;
}