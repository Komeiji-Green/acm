CPU与GPU：并行计算是关键

设计上的区别：

CPU：处理不同类型数据，处理分支跳转的逻辑 --> 内部结构复杂

GPU：处理统一类型的大规模浮点数据 --> 纯净的计算环境

特点：

CPU：需要成百上千条指令才能处理一个神经元 --> 笨拙

GPU：海量数据并行运算 --> 与深度学习的需求不谋而合

举个例子--向量相加：

CPU：for循环。GPU：开大量线程并行进行。

看看效果：12颗英伟达的GPU可以提供相当于2000颗CPU的深度学习性能（吴恩达亲测）



GPU与FPGA：可编程性是关键

人工智能正在迈向更多的领域，已不再局限于图像和声音。需要根据不同领域的训练需求来设计更加专门化、区别化的芯片。

GPU：架构固定，原生支持指令固定

FPGA：可编程，灵活针对算法修改电路

在性能上，

FPGA受限的设计资源使它的峰值性能远不及GPU，但是在架构上进行针对性优化后的FPGA的平均性能优于GPU。



FPGA与ASIC：通用就无法最优

虽然FPGA的可编程性使其可以完成针对于各领域的优化，但FPGA本身仍具有在电路级别上的通用性，想要追求极致的优化，最终还是要开发专门的芯片，即ASIC

CPU/GPU：架构级别的通用

FPGA：电路级别的通用

ASIC：把优化做到晶体管级别！

Google自研TPU（ASIC）：

仅仅针对线性代数做优化，用全新的方式对其编程。

第一代AlphaGo：1202个CPU和176个GPU

第二代AlphaGo：4块TPU

ASIC可以完全替代FPGA吗？

不可以，ASIC的开发周期长，难度大，风险高，面对一个新的领域，常常需要先用FPGA来试水，而只有那些有十足把握的团队才敢自行设计定制化的ASIC芯片。







|     CPU/GPU      |       FPGA       | ASIC/TPU | 深度学习 |
| :--------------: | :--------------: | :------: | :------: |
| 架构级别的通用性 | 电路级别的通用性 |          |  需要做  |
|   很强的兼容性   |                  |          |          |




$$
P(X_1+X_2=n) = \sum_{i=0}^{n}P(X_1=i)*P(X_2=n-i)
$$

$$
=\sum_{i=0}^{n}\frac{\lambda_1^{i}e^{-\lambda_1}}{i!}*\frac{\lambda_2^{n-i}e^{-\lambda_2}}{(n-i)!}
$$

$$
=\frac{e^{-(\lambda_1+\lambda_2)}}{n!}\sum_{i=0}^{n}C_n^i{\lambda_1^{i}}{\lambda_2^{n-i}}
$$

$$
=\frac{e^{-(\lambda_1+\lambda_2)}}{n!}(\lambda_1+\lambda_2)^n
$$

$$
P(X_1=i:X_1+X_2=n)=\frac{P(X_1=i,X_2=n-i)}{P(X_1+X_2=n)}
$$

$$
=({\frac{\lambda_1^{i}e^{-\lambda_1}}{i!}*\frac{\lambda_2^{n-i}e^{-\lambda_2}}{(n-i)!}})/({\frac{e^{-(\lambda_1+\lambda_2)}}{n!}(\lambda_1+\lambda_2)^n})
$$

$$
=C_n^i\frac{\lambda_1^i*\lambda_2^{n-i}}{(\lambda_1+\lambda_2)^n}
$$

$$
=C_n^i\frac{\lambda_1^i}{(\lambda_1+\lambda_2)^{i}}*\frac{\lambda_2^{n-i}}{(\lambda_1+\lambda_2)^{n-i}}
$$

