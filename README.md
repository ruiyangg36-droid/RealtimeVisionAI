# RealtimeVisionAI 

基于 C++ 的实时视觉 AI 推理与部署平台。

##  项目目标

打通从 PyTorch 到 ONNX，再到 C++ ONNX Runtime 的完整部署链路，构建一个支持模型替换、实时推理、界面可视化的跨平台视觉 AI 平台。

##  技术栈

- PyTorch：模型训练与导出
- ONNX：模型交换格式
- C++ / ONNX Runtime：高性能推理引擎
- OpenCV：图像读取、预处理、可视化
- Qt GUI：桌面端界面
- CMake：跨平台构建
- Git：版本管理
- Linux / Windows：目标平台

##  进度
ResNet18 preprocessing: aspect-ratio resize → center crop → RGB → float32 → [0,1] scaling → ImageNet normalization → CHW
