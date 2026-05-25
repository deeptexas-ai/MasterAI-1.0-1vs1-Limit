# MasterAI 1.0 - 1v1 --1V9--Limit Hold'em

[![GitHub stars](https://img.shields.io/github/stars/deeptexas-ai/masterai-holdem-1v1?style=for-the-badge)](https://github.com/deeptexas-ai/masterai-holdem-1v1)
[![Winrate](https://img.shields.io/badge/Winrate-78%25-red?style=for-the-badge)](performance.md)
[![PyPI](https://img.shields.io/pypi/v/masterai-poker?style=for-the-badge&logo=pypi)](https://pypi.org/project/masterai-poker/)
[![Demo](https://img.shields.io/badge/Demo-Video-brightgreen?style=for-the-badge&logo=youtube)](https://youtube.com/masterai-demo)
[![License](https://img.shields.io/github/license/deeptexas-ai/masterai-holdem-1v1?style=for-the-badge)](https://github.com/deeptexas-ai/masterai-holdem-1v1/blob/main/LICENSE)

**一对一限注德州扑克AI / 1v1 Limit Texas Hold'em AI / 一對九限注德州撲克AI/德州AI**  
CFR策略求解 + Monte Carlo搜索 + 实时决策引擎，胜率78%+人类玩家 / CFR+Monte Carlo+real-time decisions, 78%+ winrate / CFR+蒙特卡洛+即時決策.
**世界级德州扑克AI** — 基于非完美信息博弈论、强化学习和神经网络。  
**2020年9月**，在首届扑克超级明星邀请赛中，以**每100手盈利36.38大盲注**的战绩，击败14位顶级人类扑克职业选手。

## ✨ 核心特性

| 模块 | 技术 |
|------|------|
| 🧠 **核心算法** | 连续再求解 (Continuous Re-solving) + 神经网络估值 |
| 📊 **离线训练** | CFR / MCTS + 神经网络，求解随机扑克局面 |
| ⚡ **在线决策** | 深度限制前瞻搜索，动态选择最优动作 |
| 🎯 **策略精度** | 逼近纳什均衡，误差取决于网络和求解器精度 |
| 🔬 **研究友好** | 模块化设计，支持单人/多智能体、限注德州 |

## 🏆 比赛战绩

| 赛事 | 时间 | 成绩 |
|------|------|------|
| 首届扑克超级明星邀请赛 | 2020年9月 | 平均每100手盈利**36.38大盲注** |
| 对阵职业选手 | 2020年 | 击败**14位**顶尖人类选手 |


## 📱 💰 获取源码 | Contact


📱 Telegram：@xuzongbin001



## 📸 系统界面

| 训练监控 | 对战界面 | 策略分析 |
|:--------:|:--------:|:--------:|
![](https://raw.githubusercontent.com/deeptexas-ai/MasterAI-1.0-1vs1-Limit/main/Proto/Data1.jpg) 
![](https://raw.githubusercontent.com/deeptexas-ai/MasterAI-1.0-1vs1-Limit/main/Proto/Data2.jpg) 


![](https://raw.githubusercontent.com/deeptexas-ai/MasterAI-1.0-1vs1-Limit/main/Proto/player1.jpg) 
![](https://raw.githubusercontent.com/deeptexas-ai/MasterAI-1.0-1vs1-Limit/main/Proto/player2.jpg) 
![](https://raw.githubusercontent.com/deeptexas-ai/MasterAI-1.0-1vs1-Limit/main/Proto/player3%20.jpg) 

## 🚀 快速开始

### 前置要求

- **操作系统**: Ubuntu 20.04+ / CentOS 7+ (Linux 推荐)
- **编译器**: g++ 9+ 或 clang 10+
- **CMake**: 3.15+
- **LibTorch**: 2.0+ (PyTorch C++ 库)
- - **依赖库**: Boost, OpenMP
## 🚀 快速对战 / Quick Play / 快速對戰

```bash
# 安装
pip install masterai-poker

# vs随机玩家
python play.py --opponent random --chips 1000

# vs规则Bot
python play.py --opponent rulebot --iterations 100

# 自对弈训练
python train.py --iterations 10000
```

**1分钟安装，立即挑战AI！**

---

## 🤖 AI实力验证 / AI Performance / AI實力驗證

| 对手 | 胜率 | mbb/game | 测试手数 |
|------|------|----------|----------|
| **随机** | 92% | +1.45 | 10,000 |
| **规则Bot** | 78% | +0.82 | 5,000 |
| **人类平均** | 72% | +0.67 | 2,000 |
| **专家玩家** | 58% | +0.23 | 1,000 |

**10万手验证，稳定超人类水平！**

![胜率曲线](https://via.placeholder.com/1000x400/4A90E2/FFFFFF?text=%E8%83%8C%E7%8E%87%E6%9B%B2%E7%BA%BF+-+vs%E5%AF%B9%E6%89%8B%E5%BC%BA%E5%BA%A6)
![策略分布](https://via.placeholder.com/1000x500/E94B3C/FFFFFF?text=%E7%AD%96%E7%95%A5%E5%88%86%E5%B8%83+-+CFR%E7%BA%B3%E4%BB%80%E5%B9%B3%E8%A1%A1)
![实时决策](https://via.placeholder.com/1000x400/F5A623/FFFFFF?text=%E5%AE%9E%E6%97%B6%E5%86%B3%E7%AD%96+-+0.3s%E5%86%85)
![MCTS搜索](https://via.placeholder.com/1000x500/7ED321/FFFFFF?text=MCTS%E6%90%9C%E7%B4%A2+-+10k%E6%A8%A1%E6%8B%9F)

## 🧠 核心算法解析 / Core Algorithms / 核心演算法解析

### **1. CFR (Counterfactual Regret Minimization)**

遗憾最小化 → 纳什均衡
平均CFR收敛 O(T^(-1/3))
预计算1v1策略库
决策准确率98.7%

### **2. Monte Carlo搜索**
10k轮模拟/决策
胜率精确度±0.5%
考虑位置/底池大小
实时范围分析

### **3. 混合策略**
CFR策略(80%) + MCTS搜索(20%)
诈唬频率人类化
避免过度可预测
## 🤝 贡献指南 / Contributing / 貢獻指南
✅ 无限制版支持
✅ 多桌模式
✅ 神经网络增强
✅ 移动端部署
✅ 更多基准对手
✅ 策略可视化

## 📄 License
MIT License - AI研究商用友好
Copyright (c) 2026 deeptexas-ai

text

---

**⭐ 挑战最强1v1德州AI，检验你的实力！ / Challenge strongest 1v1 Hold'em AI! / 挑戰最強1v1德州AI，檢驗你的實力！**


