import torch
from pathlib import Path
import onnx
from torchvision.models import resnet18,ResNet18_Weights
#选择ResNet18的预训练权重版本（权重已经训练好了）
#.DEFAULT表示使用官方推荐默认版本
weights=ResNet18_Weights.DEFAULT
#构建resnet18模型并加载预训练权重
#resnet18()构建一个18层resnet网络结构
#weights=weights将上面选择的预训练权重参数加载到模型中
model=resnet18(weights=weights)
#模型切换到推理模式
model.eval()
print("ResNet18 loaded successfully.")
dummy_input=torch.randn(1,3,224,224,dtype=torch.float32)
print("Dummy input shape:", dummy_input.shape)
print("Dummy input dtype:", dummy_input.dtype)
#向上两级得到根目录并创建model文件夹（没有则自动创建，增强代码健壮性）
#__file__表示当前脚本文件的路径
#.resolve()把相对路径解析成绝对路径（最干净的路径表示）
#.parent返回上一级目录
project_root=Path(__file__).resolve().parent.parent
output_path=project_root/"models"/"resnet18.onnx"
#自动创建
output_path.parent.mkdir(parents=True, exist_ok=True)
#导出onnx模型
torch.onnx.export(
    model,
    dummy_input,
    output_path,
    input_names=["input"],
    output_names=["logits"],
    # 显式使用新版 torch.export-based ONNX 导出器
    dynamo=True
)
print("ONNX model exported successfully.")
print("Output path:", output_path)
#使用onnx checker验证
onnx_model = onnx.load(output_path)
#检查模型是否符合onnx格式规范
onnx.checker.check_model(onnx_model)
print("ONNX model check passed.")
