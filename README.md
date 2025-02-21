# xilinx_librfdc_on_x86
xilinx_librfdc_on_x86  
工作上有透在x86平台透過上pcie 外接xilinx rfsoc開發版並直接控制內部rfdc的需求  
此專案分享直接能在x86上coding libxrfd相關模driver而不需將程式碼寫在開發版的ps上  
  
先簡述 driver librfdc libmetal三個的主要作用  
driver負責rfdc的初始化邏輯  
librfdc紀錄config_reg的位置和設定方式 並包成api  
iibmetal負責把librfdc內使用的syscall包掉 讓driver可以用一樣的src code運行在linix或metal  
libmetal在librfdc的使用上只負責兩件事1.抓dts intit ip初始設定 2.將reg讀寫的io用metalio讓他根據平台導向不同的syscall  
  
  
主要流程如下  
1. 首先確認ip相關配置要能將pcie的某個base bar映射到xilinx 開發版上控制librfdc的定址空間(原廠預設是pl ddr)  
2. 確認x86平台能build librfdc 和 libmetal  
3. 修改librfdc內的4個io function 使其原本操作plddr的部分改去操作映射後的pcie bar 以我的實作是開linux dev node: /dev/mmrfdc 並實作他的read write能直接對映到basebar的物理位置  
4. lib的init流程 需把rdfc的ip初始設定拉到x86上 可從dts可直接拉出來 附值給 xrfdc_config  
然後就可以直接在x86上編寫相關應用  
此方式只能設定rfdc功能,還不能中斷註冊,需再研究轉接中斷的方式  
