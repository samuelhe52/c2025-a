all: release debug

release:
	cmake --build ./cmake-build-release -j --config Release

debug:
	cmake --build ./cmake-build-debug -j --config Debug
