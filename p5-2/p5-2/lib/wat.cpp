#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

class Node
{
public:
    char ch;
    int freq;
    Node *left, *right;

    Node(char ch, int freq, Node *left = nullptr, Node *right = nullptr)
        : ch(ch), freq(freq), left(left), right(right) {}

    bool isLeaf() const
    {
        return !left && !right;
    }
};

struct CompareNode
{
    bool operator()(const Node *left, const Node *right) const
    {
        return left->freq > right->freq;
    }
};

Node *buildHuffmanTree(std::map<char, int> &freqMap)
{
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> pq;
    for (const auto &p : freqMap)
    {
        pq.push(new Node(p.first, p.second));
    }

    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    return pq.top();
}

void buildCode(Node *root, std::string str, std::map<char, std::string> &huffmanCode, int &totalLength, int &totalFreq)
{
    if (root == nullptr)
        return;

    if (root->isLeaf())
    {
        huffmanCode[root->ch] = (str != "") ? str : "1";
        totalLength += str.length() * root->freq;
        totalFreq += root->freq;
    }
    else
    {
        buildCode(root->left, str + "0", huffmanCode, totalLength, totalFreq);
        buildCode(root->right, str + "1", huffmanCode, totalLength, totalFreq);
    }
}

std::string encode(const std::string &str, const std::map<char, std::string> &huffmanCode)
{
    std::string result;
    for (char c : str)
    {
        result += huffmanCode.at(c);
    }
    return result;
}

std::string decode(const std::string &str, Node *root)
{
    std::string result;
    Node *node = root;
    for (char bit : str)
    {
        node = (bit == '0') ? node->left : node->right;
        if (node == nullptr)
        {
            std::cerr << "Invalid Huffman Code" << std::endl;
            return "";
        }
        if (node->isLeaf())
        {
            result += node->ch;
            node = root;
        }
    }
    if (node != root)
    {
        std::cerr << "Invalid Huffman Code" << std::endl;
        return "";
    }
    return result;
}

int main()
{
    std::string command;
    std::string input;
    std::map<char, int> freqMap;

    // 读取 huffman.huff 文件
    std::ifstream file("huffman.huff");
    char ch;
    int freq;
    while (file >> ch >> freq)
    {
        freqMap[ch] = freq;
    }
    file.close();

    // 构建 Huffman 树
    Node *root = buildHuffmanTree(freqMap);

    // 构建编码表
    std::map<char, std::string> huffmanCode;
    int totalLength = 0, totalFreq = 0;
    buildCode(root, "", huffmanCode, totalLength, totalFreq);

    // 打印平均编码长度，使用四舍五入到两位小数
    std::cout << std::fixed << std::setprecision(2);
    double averageLength = static_cast<double>(totalLength) / totalFreq;
    double roundedAverage = round(averageLength * 100) / 100;
    if (abs(roundedAverage - averageLength) == 0.005)
    {
        std::cout << "Average Length is:" << roundedAverage - 0.01 << "*" << std::endl;
    }
    else
    {
        std::cout << "Average Length is:" << roundedAverage << std::endl;
    }
    // 读取命令和输入字符串
    std::cin >> command;
    std::cin >> input;

    // 执行命令
    if (command == "enc")
    {
        std::cout << encode(input, huffmanCode) << std::endl;
    }
    else if (command == "dec")
    {
        std::cout << decode(input, root) << std::endl;
    }
    else
    {
        std::cerr << "Invalid command" << std::endl;
    }

    return 0;
}
