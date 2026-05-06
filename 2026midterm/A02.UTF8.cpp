#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

// ================== 学生需要实现的代码开始 ==================
// 完成 Neuron 类的完整定义（包括成员函数实现）
class Neuron
{
private:
    // TODO: 定义变量：输出值
    double output;
    // TODO: 定义变量：输入指针数组
    double *inputs[32];
    // TODO: 定义变量：输入权重数组
    double weights[32];
    // TODO: 定义变量：偏置
    double bias;
    // TODO: 定义变量：有效输入个数
    int inputSize;

public:
    // TODO：完成构造函数：按要求对成员变量进行初始化，或在成员变量定义时直接初始化	Neuron() { }
    Neuron()
    {
        output = 0.0;
        bias = 0.0;
        inputSize = 0;
        for (int i = 0; i < 32; i++) {
            inputs[i] = nullptr;
            weights[i] = 0.0;
        }
    }
    // TODO: 完成函数：返回第index个输入的地址	double* getInput(int index) { }
    double *getInput(int index) const
    {
        return inputs[index];
    }
    void setInput(int index, double *p)
    {
        if (index >= 0 && index < 32)
            inputs[index] = p;
    }
    // TODO: 完成函数：设置第index个输入的地址	void setInput(int index, double* p) { }
    double *getiopolicy_nput(int index)
    {
        return (index >= 0 && index < 32) ? inputs[index] : nullptr;
    }
    // 设置第index个输入对应的权重
    void setWeight(int index, double w)
    {
        if (index >= 0 && index < inputSize)
            weights[index] = w;
    }

    // 获得第index个输入对应的权重
    double getWeight(int index) const { return (index >= 0 && index < inputSize) ? weights[index] : 0.0; }

    // 设置偏移量
    void setBias(double b) { bias = b; }

    // 获得偏移量
    double getBias() const { return bias; }

    // 获得输出
    double getOutput() const { return output; }

    // TODO: 将下一个节点的第nextInputIndex个输入地址，设置为当前节点的输出存储单元output的地址
    void linkNext(Neuron &next, int nextInputIndex)
    {
        next.inputs[nextInputIndex] = &this->output;

        // 更新数据个数
        if (next.inputSize <= nextInputIndex)
            next.inputSize = nextInputIndex + 1;
    }

    // TODO: 对本节点进行计算，最后存储在output中
    void compute()
    {
        double sum = bias;
        for (int i = 0; i < inputSize - 1; i++) {
            if (inputs[i] == nullptr)
                continue;
            sum += weights[i] * (*inputs[i]);
        }
        output = 1 / (1 + exp(-sum));
    }

    // 回答问题：
    //  在 Neuron 类的设计中，将 inputs 设计为指向其他神经元 output 的指针数组，
    //  而不是直接存储输入值。这种设计在面向对象中称为“对象协作”或“依赖倒置”，
    //  请分析这种设计如何降低对象之间的耦合，以及它可能带来的风险。从软件工程
    //  角度看，应该如何管理这种关联关系才能提高程序的健壮性？
    /*
    答： 这种设计降低了神经元之间的耦合，因为每个神经元只依赖于输入指针，而不直接依赖于其他神经元的具体实现。
    这使得神经元可以独立修改和测试，而不影响其他神经元。
    风险在于，如果输入指针未正确设置或被意外修改，可能导致计算错误或程序崩溃。
    为了提高程序的健壮性，可以使用智能指针来管理输入指针，确保它们在使用前被正确初始化，并且在神经元销毁时自动释放资源
    。此外，可以添加错误检查机制，在计算前验证输入指针的有效性，以防止空指针访问。
    */
};

// ================== 学生需要实现的代码结束 ==================

// ========== 以下为题目提供的工具函数，无需学生实现 ==========

// 打印 5x5 图案
void printPattern(const char *name, int pat[5][5])
{
    cout << name << ":\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << (pat[i][j] ? "##" : "  ");
        }
        cout << endl;
    }
    cout << endl;
}

// 生成标准符号图案
void makePattern(char op, int pat[5][5])
{
    memset(pat, 0, sizeof(int) * 25);
    if (op == '+') {
        for (int i = 0; i < 5; i++)
            pat[2][i] = 1;
        for (int i = 0; i < 5; i++)
            pat[i][2] = 1;
    } else if (op == '-') {
        for (int i = 0; i < 5; i++)
            pat[2][i] = 1;
    } else if (op == '*') {
        for (int i = 0; i < 5; i++) {
            pat[i][i] = 1;
            pat[i][4 - i] = 1;
        }
    } else if (op == '/') {
        for (int i = 0; i < 5; i++)
            pat[2][i] = 1;
        pat[0][2] = pat[4][2] = 1;
    }
}

// 添加噪声（随机翻转像素）
void addNoise(int pat[5][5], double noiseLevel)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if ((rand() % 1000) < noiseLevel * 1000)
                pat[i][j] = 1 - pat[i][j];
}

// 符号字符转显示字符串
const char *opToStr(char op)
{
    if (op == '/')
        return "÷";
    if (op == '*')
        return "×";
    if (op == '-')
        return "－";
    if (op == '+')
        return "＋";
    return "?";
}

// ---------- 样本生成函数 ----------
// samples: 存储多个 5x5 图案的三维数组（最大 200 个样本）
// count:  需要生成的样本数量（≤200）
// noiseLevel: 噪声概率（0.0 ~ 1.0）
void generateSamples(int samples[200][5][5], int count, double noiseLevel)
{
    char ops[4] = {'+', '-', '*', '/'};
    for (int i = 0; i < count; i++) {
        char op = ops[i % 4]; // 轮流使用四种符号
        makePattern(op, samples[i]);
        if (noiseLevel > 0.0)
            addNoise(samples[i], noiseLevel);
    }
}

// ---------- 遗传算法参数 ----------
const int POP_SIZE = 50;
const int GENE_LEN = 4 * 25 + 4; // 4个输出神经元的权重+偏置
const int GENERATIONS = 1000;
const double MUTATION_RATE = 0.1;
const double CROSSOVER_RATE = 0.7;

// 基因解码到输出神经元
void decodeGenes(double genes[GENE_LEN], Neuron outNeurons[4])
{
    int idx = 0;
    for (int n = 0; n < 4; n++)
        for (int i = 0; i < 25; i++)
            outNeurons[n].setWeight(i, genes[idx++]);
    for (int n = 0; n < 4; n++)
        outNeurons[n].setBias(genes[idx++]);
}

// 输出神经元参数编码回基因
void encodeGenes(double genes[GENE_LEN], Neuron outNeurons[4])
{
    int idx = 0;
    for (int n = 0; n < 4; n++)
        for (int i = 0; i < 25; i++)
            genes[idx++] = outNeurons[n].getWeight(i);
    for (int n = 0; n < 4; n++)
        genes[idx++] = outNeurons[n].getBias();
}

// 评估个体适应度（负的 MSE，越大越好）
double evaluate(Neuron inputs[25], Neuron outputs[4], int samples[200][5][5], int sampleCount)
{
    double mse = 0.0;
    int total = 0;
    char ops[4] = {'+', '-', '*', '/'};
    for (int s = 0; s < sampleCount; s++) {
        int pat[5][5];
        memcpy(pat, samples[s], sizeof(pat));

        // 创建临时输入神经元并设置输出
        for (int i = 0; i < 25; i++) {
            inputs[i].setBias((pat[i / 5][i % 5] == 1) ? 1.0 : 0.0);
            inputs[i].compute();
        }

        // 前向计算
        for (int n = 0; n < 4; n++)
            outputs[n].compute();

        // 目标输出：符号类别由样本的原始符号决定（无法直接获得，此处用简单方法）
        // 由于样本生成时轮流使用 + - * /，所以 s%4 即为正确类别
        int classID = s % 4;
        double target[4] = {0, 0, 0, 0};
        target[classID] = 1.0;
        for (int n = 0; n < 4; n++) {
            double diff = outputs[n].getOutput() - target[n];
            mse += diff * diff;
            total++;
        }
    }
    return -mse / total; // 负数 MSE
}

// ---------- 训练函数 ----------
// 输入：输入神经元数组（仅用于建立全局链接，训练时不直接使用）
//      输出神经元数组（会被训练修改权重/偏置）
//      训练样本集
// 训练结束后自动将输出神经元重新链接到全局输入神经元
void trainNetwork(Neuron *inputNeurons, Neuron outNeurons[4],
                  int trainSamples[200][5][5], int trainCount)
{
    double population[POP_SIZE][GENE_LEN];
    double fitness[POP_SIZE];

    // 随机初始化种群
    for (int p = 0; p < POP_SIZE; p++)
        for (int g = 0; g < GENE_LEN; g++)
            population[p][g] = (rand() % 2000 - 1000) / 1000.0;

    for (int gen = 0; gen < GENERATIONS; gen++) {
        double bestFit = -1e9;
        int bestIdx = 0;
        for (int p = 0; p < POP_SIZE; p++) {
            decodeGenes(population[p], outNeurons);
            fitness[p] = evaluate(inputNeurons, outNeurons, trainSamples, trainCount);
            if (fitness[p] > bestFit) {
                bestFit = fitness[p];
                bestIdx = p;
            }
        }

        if (gen % 20 == 0)
            cout << "Generation " << gen << ", best MSE = " << -bestFit << endl;

        // 轮盘赌选择
        double minFit = fitness[0];
        for (int p = 1; p < POP_SIZE; p++)
            if (fitness[p] < minFit)
                minFit = fitness[p];
        double sumFit = 0;
        double shiftedFit[POP_SIZE];
        for (int p = 0; p < POP_SIZE; p++) {
            shiftedFit[p] = fitness[p] - minFit + 0.01;
            sumFit += shiftedFit[p];
        }

        double newPop[POP_SIZE][GENE_LEN];
        for (int p = 0; p < POP_SIZE; p++) {
            double r1 = (rand() % 10000) / 10000.0 * sumFit;
            double r2 = (rand() % 10000) / 10000.0 * sumFit;
            int parent1 = 0, parent2 = 0;
            double accum = 0;
            for (int i = 0; i < POP_SIZE; i++) {
                accum += shiftedFit[i];
                if (r1 <= accum) {
                    parent1 = i;
                    break;
                }
            }
            accum = 0;
            for (int i = 0; i < POP_SIZE; i++) {
                accum += shiftedFit[i];
                if (r2 <= accum) {
                    parent2 = i;
                    break;
                }
            }

            if ((rand() % 1000) / 1000.0 < CROSSOVER_RATE) {
                int cross = rand() % GENE_LEN;
                for (int g = 0; g < GENE_LEN; g++)
                    newPop[p][g] = (g < cross) ? population[parent1][g] : population[parent2][g];
            } else {
                for (int g = 0; g < GENE_LEN; g++)
                    newPop[p][g] = population[parent1][g];
            }

            for (int g = 0; g < GENE_LEN; g++) {
                if ((rand() % 1000) / 1000.0 < MUTATION_RATE) {
                    newPop[p][g] += (rand() % 2000 - 1000) / 5000.0;
                    if (newPop[p][g] > 1)
                        newPop[p][g] = 1;
                    if (newPop[p][g] < -1)
                        newPop[p][g] = -1;
                }
            }
        }

        for (int g = 0; g < GENE_LEN; g++)
            newPop[0][g] = population[bestIdx][g];

        for (int p = 0; p < POP_SIZE; p++)
            for (int g = 0; g < GENE_LEN; g++)
                population[p][g] = newPop[p][g];
    }

    // 训练结束，使用最佳个体
    decodeGenes(population[0], outNeurons);

    cout << "Training finished. Best MSE = " << -evaluate(inputNeurons, outNeurons, trainSamples, trainCount) << endl;
}

// ---------- 测试函数 ----------
void testNetwork(Neuron *inputNeurons, Neuron outNeurons[4],
                 int testSamples[200][5][5], int testCount)
{
    cout << "\n====== 测试结果（加噪样本识别） ======\n";
    char cs[4] = {'+', '-', '*', '/'};
    for (int s = 0; s < testCount; s++) {
        // 1. 创建临时输入神经元（像训练时一样）
        for (int i = 0; i < 25; i++) {
            inputNeurons[i].setBias((testSamples[s][i / 5][i % 5] == 1) ? 1.0 : 0.0);
            inputNeurons[i].compute();
        }

        // 3. 前向计算
        for (int n = 0; n < 4; n++)
            outNeurons[n].compute();

        // 找出最大输出
        int maxIdx = 0;
        double maxVal = outNeurons[0].getOutput();
        for (int n = 1; n < 4; n++) {
            double val = outNeurons[n].getOutput();
            if (val > maxVal) {
                maxVal = val;
                maxIdx = n;
            }
        }

        // 打印结果（与原来相同）
        cout << "样本 " << s + 1 << "（可能含噪声，真实类别: " << opToStr(cs[s % 4]) << "）:\n";
        printPattern("", testSamples[s]);
        cout << "输出: ";
        for (int n = 0; n < 4; n++) {
            cout << opToStr(cs[n]) << ":" << fixed << setprecision(2) << outNeurons[n].getOutput();
            if (n == maxIdx)
                cout << "√";
            cout << "  ";
        }
        cout << endl
             << endl;
    }
}

int main()
{
    srand((unsigned)time(0));

    // 创建网络结构
    Neuron inputNeurons[25];
    Neuron outputNeurons[4];

    // 全局链接
    for (int n = 0; n < 4; n++)
        for (int i = 0; i < 25; i++)
            inputNeurons[i].linkNext(outputNeurons[n], i);

    // 生成训练样本（40个，10个/类，含10%噪声）
    const int TRAIN_COUNT = 80;
    int trainSamples[200][5][5];
    auto p = trainSamples - 4;
    for (int i = 0; i < TRAIN_COUNT; i += 4)
        generateSamples(p += 4, 4, i * 0.0008);

    cout << "====== 训练样本展示（前4个为例） ======\n";
    for (int i = 0; i < 4; i++) {
        char label[10];
        sprintf(label, "类别 %s", opToStr("+-*/"[i % 4]));
        printPattern(label, trainSamples[i]);
    }

    // 训练网络
    trainNetwork(inputNeurons, outputNeurons, trainSamples, TRAIN_COUNT);

    // 生成测试样本
    const int TEST_COUNT = 4;
    int testSamples[200][5][5];
    generateSamples(testSamples, TEST_COUNT, 0.015);

    // 测试网络
    testNetwork(inputNeurons, outputNeurons, testSamples, TEST_COUNT);

    return 0;
}