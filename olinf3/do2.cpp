//
// Created by yakuri354 on 28.01.2022.
//
#include <vector>
#include <iostream>

template<typename T, T F(T, T), T N>
class segment_tree {
    std::vector<T> tree;
    size_t size;

public:
    explicit inline segment_tree(std::vector<T> &data) : size(data.size()), tree() {
        this->tree.assign(1 << (std::__lg(this->size) + 1), N);

        for (int i = 0; i < this->size; ++i) {
            this->tree[this->tree.size() - 1 + i] = data[i];
        }
        for (int i = this->tree.size() - 2; i >= 0; --i) {
            this->tree[i] = F(this->tree[2 * i + 1], this->tree[2 * i + 2]);
        }
    }

    inline T query(size_t start, size_t end) {
        return this->query_impl(0, start, end, 0, this->tree.size());
    }

private:
    inline T query_impl(size_t node, size_t q_start, size_t q_end, size_t n_start, size_t n_end) {
        if (q_start >= n_end || q_end <= n_start) return N;
        if (q_start <= n_start && n_end <= q_end) return this->tree[node];

        auto n_mid = (n_start + n_end) / 2;

        return F(
                this->query_impl(node * 2 + 1, q_start, q_end, n_start, n_mid),
                this->query_impl(node * 2 + 2, q_start, q_end, n_mid, n_end)
        );
    }
};

using st_data_type = long long;

const st_data_type st_neutral = 0;

st_data_type op(st_data_type a, st_data_type b) {
    return a + b;
}

int main() {
    size_t N;
    std::cin >> N;

    std::vector<st_data_type> data(N);
    for (auto &el: data) {
        std::cin >> el;
    }

    segment_tree<st_data_type, op, st_neutral> tree(data);

    size_t K;
    std::cin >> K;
    for (size_t i = 0; i < K; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        std::cout << tree.query(a - 1, b);
    }
}