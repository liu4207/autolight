# 自动调光控制设计 🚗

基于直流电源调控的自动调光控制设计，使用了 Buck 变换器、PID 闭环控制、自动调光与光伏 MPPT（最大功率点跟踪）等技术，适用于智能照明系统的控制和调节。

---

## 🧩 项目特点

- ✅ 使用 **Buck 变换器** 控制电压和电流，实现高效的功率转换。
- ✅ 基于 **PID 控制** 实现闭环控制，稳定系统响应。
- ✅ 支持 **自动调光功能**，根据环境光强度自动调节照明亮度。
- ✅ **光伏 MPPT** 技术用于最大化光伏电池的能量输出。
- ✅ **直流电源调控**，适用于低功耗环境下的智能照明控制。

---

## 📂 工程结构

| 文件夹       | 说明                              |
|--------------|-----------------------------------|
| `Drivers/`   | HAL库文件                         |
| `Inc/`       | 头文件定义                        |
| `MDK-ARM/`   | Keil 工程文件和外设驱动文件        |
| `Src/`       | 主业务逻辑代码，如 PID 控制、调光等 |
| `light2.ioc` | STM32CubeMX 配置文件               |
| `.mxproject` | Keil 项目文件                     |

---

## 🛠️ 开发环境

- **开发板**：STM32F103C8T6
- **IDE**：Keil MDK-ARM 5.38a
- **编译工具链**：ARMCC
- **项目生成工具**：STM32CubeMX（对应配置文件为 `light2.ioc`）

---

## 🚗 项目亮点总结

- ✅ 采用 **Buck 变换器** 实现高效电源管理，支持稳定电压输出。
- ✅ **PID 闭环控制** 逻辑保证调光系统响应快速且稳定。
- ✅ 实现 **自动调光**，基于环境光强自动调节光源亮度，提升能源利用效率。
- ✅ 结合 **光伏 MPPT** 技术，最大化光伏电池的能量输出，保证系统在各种环境下的稳定运行。

---

## 🚀 快速开始

 **打开 Keil 项目** `MDK-ARM/` 中的 `.uvprojx` 文件，使用 Keil 编译并下载程序。
 **调试与运行**：上传后即可通过串口或调试工具测试调光功能和控制系统。

---

## 🖥️ 控制系统说明


### PID 控制

- 使用 PID 控制算法调节电源输出，确保系统稳定并高效运行。

---

## 📸 效果展示

![16833f1ac112d06f17a1027b34e0bf1](https://github.com/user-attachments/assets/cdc9efca-4ac2-48fc-a023-478ed69351ff)


---


## 👨‍💻 作者

刘珅凯 @ 重庆大学明月班  
联系：2323453274@qq.com

---

## 📄 License

MIT License

Copyright (c) 2025 Liu Shenkai

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
