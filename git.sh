#!/bin/bash

# 检查是否有提供提交信息
if [ -z "$1" ]; then
  echo "Usage: $0 '<commit-message>'"
  exit 1
fi

# 提交信息是第一个参数
commit_message="$1"

# 添加所有更改的文件到暂存区
git add .

# 提交更改
git commit -m "$commit_message"

# 推送到远程仓库（如果你想要的话，可以取消注释）
git push
