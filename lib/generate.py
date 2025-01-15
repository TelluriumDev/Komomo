import re

def read_cpp_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()

def extract_class_name(cpp_code):
    class_pattern = re.compile(r'class (\w+) : public ScriptClass')
    match = class_pattern.search(cpp_code)
    return match.group(1) if match else None

def extract_methods(cpp_code):
    method_pattern = re.compile(r'Local<Value> (\w+)\(const Arguments& args\);')
    return method_pattern.findall(cpp_code)

def generate_dts_content(class_name, methods):
    dts_content = ""

    # 添加类声明
    dts_content += f"declare class {class_name} {{\n"
    for method in methods:
        dts_content += f"    {method}(): any;\n"
    dts_content += "}\n"

    return dts_content

def main():
    file_path = "E:\TelluriumDev\Komomo\src\API\Player\Player.h"  # 替换为你的 C++ 文件路径
    cpp_code = read_cpp_file(file_path)

    class_name = extract_class_name(cpp_code)
    methods = extract_methods(cpp_code)

    if class_name and methods:
        dts_content = generate_dts_content(class_name, methods)

        # 写入 .d.ts 文件
        output_file_path = 'LoggerClass.d.ts'
        with open(output_file_path, 'w') as f:
            f.write(dts_content)

        print(f"生成的 .d.ts 文件已保存到 {output_file_path}")
        print("生成的 .d.ts 文件内容如下：")
        print(dts_content)
    else:
        print("未找到类定义或方法定义。")

if __name__ == "__main__":
    main()