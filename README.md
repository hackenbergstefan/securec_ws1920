# Secure implementations on microcontrollers (WS 19/20)

In this repository the materials for the course "Sichere Implementierungen auf Mikrocontrollern" teached at Hochschule Augsburg in WS 2019/2020 can be found.


## How to install

### Requirements
* [ChipWhisperer v5 release](https://github.com/newaetech/chipwhisperer/releases). Either Virtual Machine or source code.
* ChipWhisperer Lite XMEGA (CW1173)

### 1. Install using ChipWhisperer Virtual Machine
1. Log into the VM and go to root of chipwhisperer source which is usually `/home/vagrant/work/projects/chipwhisperer`.
2. Clone this repository.

In summary
```sh
$ cd /home/vagrant/work/projects/chipwhisperer
$ git clone https://github.com/hackenbergstefan/securec_ws1920.git
```

### 2. Install using ChipWhisperer source
1. Clone this repository somewhere.
2. If this repository is parallel or inside ChipWhisperer's source there is nothing to. Otherwise you have to edit `util/Init.ipynb` and setup `CWPATH` and `FIRMWAREPATH` manually.
