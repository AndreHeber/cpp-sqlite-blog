conan install . --profile:host=debug --profile:build=debug --output-folder=build --build=missing
cd build && make
