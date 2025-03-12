sudo ip netns add ns_sr
sudo ip netns add ns_peer0
sudo ip netns add ns_peer1
sudo ip link add veth0 netns ns_sr type veth peer name peer0 netns ns_peer0
sudo ip link add veth1 netns ns_sr type veth peer name peer1 netns ns_peer1