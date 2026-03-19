#ifndef NN_H
#define NN_H
class NN
{
private:
    // 数组 x 和数组 w 分别存放输入信号 xi 及其加权系数 wi,dt 存放非零参数 σ
    float *x, *w, dt;
    double y; // 神经元的输出
public:
    NN(float t[ ] , float d); // 用数组 t 初始化加权系统 wi，用 d 初始化 dt
    ~NN();
    void fun(float t[ ]); // 用数组 t 初始化 xi，并根据上述公式计算 y 的值
    void print( ); //输出输入信号和输出信号的值
};


#endif