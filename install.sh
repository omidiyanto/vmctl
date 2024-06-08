#!bin/bash
wget https://raw.githubusercontent.com/omidiyanto/vmctl/main/vm-selector.c &>/dev/null
wget https://raw.githubusercontent.com/omidiyanto/vmctl/main/ctl-node1.c &>/dev/null
wget https://raw.githubusercontent.com/omidiyanto/vmctl/main/ctl-node2.c &>/dev/null
sudo dnf install gcc gtk3-devel -y  &>/dev/null
gcc vm-selector.c -o ctl-node-selector `pkg-config --cflags --libs gtk+-3.0` &>/dev/null
gcc ctl-node1.c -o ctl-node1 `pkg-config --cflags --libs gtk+-3.0` &>/dev/null
gcc ctl-node2.c -o ctl-node2 `pkg-config --cflags --libs gtk+-3.0` &>/dev/null
sudo mv ctl-node* /usr/bin/ &>/dev/null
sudo chmod 777 /usr/bin/ctl-node* &>/dev/null
rm -rf * &>/dev/null
echo "INSTALL FINISHED"
