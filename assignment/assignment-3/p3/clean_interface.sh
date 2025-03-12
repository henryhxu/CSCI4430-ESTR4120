#!/bin/bash

# 删除接口
# sudo ip link delete veth0 2>/dev/null
# sudo ip link delete veth1 2>/dev/null

# # 清理残留IP配置
# sudo ip addr flush dev veth0 2>/dev/null
# sudo ip addr flush dev veth1 2>/dev/null

# delete namespaces
sudo ip netns del ns_sr 2>/dev/null
sudo ip netns del ns_peer0 2>/dev/null
sudo ip netns del ns_peer1 2>/dev/null

echo "Cleanup completed."