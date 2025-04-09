# xilinx_librfdc_on_x86
In this project, there is a requirement to control the internal RFDC of a Xilinx RFSoC development board via PCIe from an x86 platform. This setup allows us to directly code and control the RFDC using libxrfdc drivers on the x86 host, without writing code on the Processing System (PS) of the RFSoC board.  

Overview of the roles of driver, librfdc, and libmetal:  
driver: Responsible for the RFDC initialization logic.  
  
librfdc: Records the locations of the config registers and their configuration methods, and encapsulates them as APIs.  

libmetal: Wraps the syscalls used in librfdc so that the same source code can run on both Linux and bare-metal platforms. Specifically, when used by librfdc, libmetal only handles two things:  

Parsing the device tree (DTS) and initializing IP settings.  

Handling register read/write operations by abstracting them through platform-specific syscalls via metal_io.  
  
Main flow:  
First, ensure that the IP configuration maps one of the PCIe BARs (Base Address Registers) from the x86 platform to the address space required by librfdc to control the RFDC on the Xilinx board. (By default, this is mapped to PL DDR.)  
  
Make sure librfdc and libmetal can be built successfully on the x86 platform.  
  
Modify four I/O functions in librfdc so that instead of accessing PL DDR, they operate on the PCIe BAR that has been mapped.  
In my implementation, I created a Linux device node: /dev/mmrfdc, and implemented its read/write operations to directly map to the physical address of the base BAR.  
  
During library initialization, the RFDC IP configuration must be pulled to the x86 side. This can be extracted from the device tree (DTS) and assigned to xrfdc_config struct .  
  
After that, RFDC-related applications can be developed directly on the x86 host.  
  
Note: This approach currently only supports RFDC configuration. Interrupt registration is not yet supported, and further research is required to implement interrupt routing across PCIe.  

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
xilinx_librfdc_on_x86  
工作上有透在x86平台透過上pcie 外接xilinx rfsoc開發版並直接控制內部rfdc的需求  
此專案分享直接能在x86上coding libxrfdc相關driver模組而不需將程式碼寫在開發版的ps上  
  
先簡述 driver librfdc libmetal三個的主要作用  
driver負責rfdc的初始化邏輯  
librfdc紀錄config_reg的位置和設定方式 並包成api  
iibmetal負責把librfdc內使用的syscall包掉 讓driver可以用一樣的src code運行在linix或metal  
libmetal在librfdc的使用上只負責兩件事1.抓dts intit ip初始設定 2.將reg讀寫的io用metalio讓他根據平台導向不同的syscall  
  
  
主要流程如下  
1. 首先確認ip相關配置要能將pcie的某個base bar映射到xilinx 開發版上控制librfdc的定址空間(原廠預設是pl ddr)  
2. 確認x86平台能build librfdc 和 libmetal  
3. 修改librfdc內的4個io function 使其原本操作plddr的部分改去操作映射後的pcie bar，以我的實作是開linux dev node: /dev/mmrfdc 並實作他的read write能直接對映到basebar的物理位置  
4. lib的init流程 需把rdfc的ip初始設定拉到x86上 可從dts可直接拉出來 附值給 strucrt xrfdc_config  
然後就可以直接在x86上編寫相關應用  
此方式只能設定rfdc功能,還不能中斷註冊,需再研究轉接中斷的方式  
