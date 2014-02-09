#Make sure that the build directory is a case-sensitive filesystem.

$(BUILD_DIR):toolchain.sparseimage
	hdiutil attach -mountpoint $@ $<

toolchain.sparseimage:
	hdiutil create -size 8G -fs JHFS+X -type SPARSE -volname toolchain $@

clean-target:
	umount $(BUILD_DIR)
	rm toolchain.sparseimage
