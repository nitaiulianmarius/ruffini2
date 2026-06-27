POWERSHELL ?= powershell
CMAKE ?= $(shell $(POWERSHELL) -NoProfile -Command "$$cmd=Get-Command cmake -ErrorAction SilentlyContinue; if ($$cmd) { $$cmd.Source } else { $$vswhere=Join-Path ([Environment]::GetFolderPath('ProgramFilesX86')) 'Microsoft Visual Studio/Installer/vswhere.exe'; $$found=if(Test-Path $$vswhere){ & $$vswhere -latest -products '*' -find 'Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe' | Select-Object -First 1 }; if($$found){$$found}else{'cmake'} }")
MINGW_BIN ?= $(shell $(POWERSHELL) -NoProfile -Command "$$cmd=Get-Command g++ -ErrorAction SilentlyContinue; if ($$cmd) { Split-Path $$cmd.Source } else { $$paths=@('C:/Program Files/CodeBlocks/MinGW/bin','C:/Program Files (x86)/CodeBlocks/MinGW/bin','C:/msys64/mingw64/bin','C:/msys64/ucrt64/bin','C:/MinGW/bin'); $$found=$$paths | Where-Object { Test-Path (Join-Path $$_ 'g++.exe') } | Select-Object -First 1; if ($$found) { $$found } }")
MINGW_CXX ?= $(shell $(POWERSHELL) -NoProfile -Command "$$bin='$(MINGW_BIN)'; if ($$bin) { Join-Path $$bin 'g++.exe' } else { 'g++' }")
MINGW_MAKE ?= $(shell $(POWERSHELL) -NoProfile -Command "$$bin='$(MINGW_BIN)'; if ($$bin) { Join-Path $$bin 'mingw32-make.exe' } else { 'mingw32-make' }")
PHYSICAL_CORES := $(shell $(POWERSHELL) -NoProfile -Command "$$cores=(Get-CimInstance Win32_Processor | Measure-Object -Property NumberOfCores -Sum).Sum; if ($$cores) { $$cores } else { 1 }")
VCPKG_ROOT ?= $(shell $(POWERSHELL) -NoProfile -Command "if ($$env:VCPKG_ROOT) { $$env:VCPKG_ROOT } else { $$vswhere=Join-Path ([Environment]::GetFolderPath('ProgramFilesX86')) 'Microsoft Visual Studio/Installer/vswhere.exe'; $$found=if(Test-Path $$vswhere){ & $$vswhere -latest -products '*' -find 'VC/vcpkg/vcpkg.exe' | Select-Object -First 1 }; if($$found){Split-Path $$found} }")
VCPKG_INSTALLED_DIR ?= $(shell $(POWERSHELL) -NoProfile -Command "Join-Path $$env:LOCALAPPDATA 'vcpkg-installed/ruffini-2'")
VCPKG_OPTIONS := $(if $(strip $(VCPKG_ROOT)),-DCMAKE_TOOLCHAIN_FILE='$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake' -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic -DVCPKG_INSTALLED_DIR='$(VCPKG_INSTALLED_DIR)',)
WITH_MINGW_PATH = $$env:PATH='$(MINGW_BIN);' + $$env:PATH;

.PHONY: all debug release clean install

all: release debug

debug:
	$(POWERSHELL) -NoProfile -Command "$(WITH_MINGW_PATH) & '$(CMAKE)' -S . -B build/debug -G 'MinGW Makefiles' -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER='$(MINGW_CXX)' -DCMAKE_MAKE_PROGRAM='$(MINGW_MAKE)' $(VCPKG_OPTIONS)"
	$(POWERSHELL) -NoProfile -Command "$(WITH_MINGW_PATH) & '$(CMAKE)' --build build/debug -j$(PHYSICAL_CORES)"

release:
	$(POWERSHELL) -NoProfile -Command "$(WITH_MINGW_PATH) & '$(CMAKE)' -S . -B build/release -G 'MinGW Makefiles' -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER='$(MINGW_CXX)' -DCMAKE_MAKE_PROGRAM='$(MINGW_MAKE)' $(VCPKG_OPTIONS)"
	$(POWERSHELL) -NoProfile -Command "$(WITH_MINGW_PATH) & '$(CMAKE)' --build build/release -j$(PHYSICAL_CORES)"

clean:
	"$(CMAKE)" -E remove_directory build
	"$(CMAKE)" -E remove_directory dist

install: release
	"$(CMAKE)" --install build/release --config Release --prefix "$(CURDIR)/dist"
