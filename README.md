##MMI-TLA33.226-2 For Moto e13

Kernel Modules:
---------------
Download prebuilts folder from Android distribution. Move it to $my_top_dir

For example:

my_top_dir=$PWD

mkdir -vp $my_root_dir/prebuilts/clang/host

cd $my_root_dir/prebuilts/clang/host

git clone https://android.googlesource.com/platform/prebuilts/clang/host/linux-x86

mkdir -vp $my_root_dir/prebuilts/gcc/linux-x86/aarch64

cd $my_root_dir/prebuilts/gcc/linux-x86/aarch64

git clone https://android.googlesource.com/platform/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9

Download kernel source code. Rename kernel-* folder to $my_root_dir/kernel5.4 

mkdir -p $my_top_dir/out/target/product/sabahlite/obj/kernel5.4

kernel_out_dir=$my_top_dir/out/target/product/sabahlite/obj/kernel5.4

clang_1=$my_top_dir/prebuilts/clang/host/linux-x86/clang-r416183b/bin/clang

make=$my_top_dir/prebuilts/build-tools/linux-x86/bin/make

aarch64_linux_android_=$my_top_dir/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-

export ARCH=arm64 LLVM=1 LLVM_LAS=1 INSTALL_MOD_STRIP=1 CLANG_TRIPLE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-androidkernel- SUBARCH=arm64 CROSS_COMPILE=aarch64-linux-androidkernel- LD_LIBRARY_PATH=$my_top_dir/prebuilts/clang/host/linux-x86/clang-r416183b/lib64:$$LD_LIBRARY_PATH PATH=$my_top_dir/prebuilts/clang/host/linux-x86/clang-r416183b/bin/:$aarch64_linux_android_:$PATH BSP_MODULES_OUT=$kernel_out_dir BSP_KERNEL_PATH=$my_top_dir/kernel5.4 BSP_BOARD_BASE_PATH=$my_top_dir/kernel5.4/modules BSP_KERNEL_OUT=$kernel_out_dir KERNEL_MAKE_ARGS="ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1" BSP_NPROC=96 CONFIG_MALI_PLATFORM_NAME=qogirl6 CONFIG_TARGET_BOARD=sabahlite BSP_ROOT_DIR=$my_top_dir BSP_KERNEL_VERSION=kernel5.4 BSP_BOARD_ARCH=


$make -C $BSP_KERNEL_PATH O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 sprd_qogirl6_defconfig -j96

$make -C $BSP_KERNEL_PATH O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 dtbs -j96

$make -C $BSP_KERNEL_PATH O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 -j96

$make -C $BSP_KERNEL_PATH O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 INSTALL_HDR_PATH=$kernel_out_dir/out/androidt/sabahlite/headers/kernel/usr headers_install -j96

$make -C $kernel_out_dir O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 ARCH=arm64 INSTALL_MOD_PATH=$kernel_out_dir/modules modules_install -j96


make -C $BSP_KERNEL_PATH LLVM=1 LLVM_IAS=1 DEPMOD=depmod O=$kernel_obj_out_dir CC=$clang_1 CROSS_COMPILE=$aarch64_linux_android_ clean

make -C $BSP_KERNEL_PATH LLVM=1 LLVM_IAS=1 DEPMOD=depmod O=$kernel_obj_out_dir CC=$clang_1 CROSS_COMPILE=$aarch64_linux_android_ mrproper

make -C $BSP_KERNEL_PATH LLVM=1 LLVM_IAS=1 DEPMOD=depmod O=$kernel_obj_out_dir  CC=$clang_1 CROSS_COMPILE=$aarch64_linux_android_ distclean

source kernel5.4/modules/modules.sh


WLAN Driver:
---------------
make -C $BSP_KERNEL_PATH/modules/kernel5.4/wcn/wlan/wlan_combo -f Makefile O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 modules -j96
make -C $BSP_KERNEL_PATH/modules/kernel5.4/wcn/wlan/wlan_combo -f Makefile O=$kernel_out_dir ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi- INSTALL_MOD_STRIP=1 INSTALL_MOD_PATH=$kernel_out_dir/modules modules_install -j96
