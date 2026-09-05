# 项目名称
实时视觉 AI 推理与部署平台
## 项目目标
PyTorch 模型训练/使用
→ 导出 ONNX
→ C++ 使用 ONNX Runtime 推理
→ OpenCV 完成图片、视频、摄像头输入与预处理
→ Qt GUI 实时显示推理结果
→ 推理线程与 UI 分离
→ FPS / 延迟统计
→ Linux 下 CMake 构建
→ Git 管理
→ README、Demo、Benchmark 完整。
## 技术栈
C++17 + Qt6 + OpenCV + PyTorch + ONNX Runtime + CMake + Git + Linux

## 当前状态
图像预处理支持 resize、BGR→RGB、float32 转换与 0~1 像素缩放,HWC.