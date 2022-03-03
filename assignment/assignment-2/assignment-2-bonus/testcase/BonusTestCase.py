#!/usr/bin/env python


from __future__ import print_function

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.topo import Topo
from mininet.log import setLogLevel

import time


class StarfishShapeNetworks(Topo):
    '''
      h1  h2 h3
        \ | /
    h4 -- s1 -- h5
        / | \
      h6  h7 h8
    '''
    def __init__(self, **opts):
        Topo.__init__(self, **opts)
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        h3 = self.addHost('h3')
        h4 = self.addHost('h4')
        h5 = self.addHost('h5')
        h6 = self.addHost('h6')
        h7 = self.addHost('h7')
        h8 = self.addHost('h8')
        s1 = self.addSwitch('s1')

        self.addLink(h1, s1)
        self.addLink(h2, s1)
        self.addLink(h3, s1)
        self.addLink(h4, s1)
        self.addLink(h5, s1)
        self.addLink(h6, s1)
        self.addLink(h7, s1)
        self.addLink(h8, s1)



def testcase1():
    import os
    os.system("sudo mn -c")
    

    setLogLevel( 'info' )

    # topo = SimpleNetwork()
    topo = StarfishShapeNetworks()
    net = Mininet(topo=topo, autoSetMacs=True,
           autoStaticArp=True)
    ALPHA = 0.5

    net.start()

    proxy_node = 5
    proxy_PORT = 8888
    proxy_timeout = 100

    h1 = net.get('h1')
    h2 = net.get('h2')
    h3 = net.get('h3')
    h4 = net.get('h4')
    h5 = net.get('h5')
    h6 = net.get('h6') 
    h7 = net.get('h7')
    h8 = net.get('h8')

    h1.cmd("sudo python start_server.py 1")
    h2.cmd("sudo python start_server.py 2")
    h3.cmd("sudo python start_server.py 3")

    h4.cmd('./nameserver --rr 9000 testcase_servers.txt ns_log1.log &')
    
    
    h6.cmd("python firefox_open_url.py 1 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    h7.cmd("sleep 15 && python firefox_open_url.py 2 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    h8.cmd("sleep 30 && python firefox_open_url.py 3 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    
    h5.cmdPrint("make clean && make &&  timeout {} ./miProxy --dns {} 10.0.0.4 9000 {} log_bonus1.log"\
      .format(proxy_timeout, proxy_PORT, ALPHA))

def testcase2():
    import os
    os.system("sudo mn -c")
    

    setLogLevel( 'info' )

    topo = StarfishShapeNetworks()
    net = Mininet(topo=topo, autoSetMacs=True,
           autoStaticArp=True)
    ALPHA = 0.5

    net.start()

    proxy_node = 5
    proxy_PORT = 8888
    proxy_timeout = 100

    h1 = net.get('h1')
    h2 = net.get('h2')
    h3 = net.get('h3')
    h4 = net.get('h4')
    h5 = net.get('h5')
    h6 = net.get('h6') 
    h7 = net.get('h7')
    h8 = net.get('h8')

    h1.cmd("sudo python start_server.py 1")
    h2.cmd("sudo python start_server.py 2")
    h3.cmd("sudo python start_server.py 3")

    h4.cmd('./nameserver --rr 9000 testcase_servers.txt ns_log2.log &')
    
    
    h6.cmd("python firefox_open_url.py 1 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    
    h7.cmd("sleep 20 && python firefox_open_url.py 2 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    
    h8.cmd("sleep 30 && timeout 30 python firefox_open_url.py 3 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    h8.cmd("sleep 60 && timeout 40 python firefox_open_url.py 3 10.0.0.{}:{} & "\
      .format(proxy_node, proxy_PORT))
    
    h5.cmdPrint("make clean && make &&  timeout {} ./miProxy --dns {} 10.0.0.4 9000 {} log_bonus2.log"\
      .format(proxy_timeout, proxy_PORT, ALPHA))



    # CLI( net )

    h1.cmd("sudo killall httpd")

    net.stop()  

if __name__ == '__main__':
    testcase_list = [
            testcase1, 
            testcase2
            ]
    assert len(sys.argv) == 2, "Argument number error"
    case_idx = int(sys.argv[1]) - 1
    assert 0 <= case_idx <= 1, "Test case number not in 1-2"
    testcase_list[case_idx]()
