export TOP=~/busybox/
rm ~/busybox/build/initramfs/busybox-x86/bin/softmmu.ko
cp ./softmmu.ko ~/busybox/build/initramfs/busybox-x86/bin/
rm ~/busybox/build/initramfs-busybox-x86.cpio.gz
cd ~/busybox/build/initramfs/busybox-x86/
find . -print0 \
   | cpio --null -ov --format=newc \
   | gzip -9 > $TOP/build/initramfs-busybox-x86.cpio.gz
