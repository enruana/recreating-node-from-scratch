
# this script is used to copy the needed files from chapter-2 to chapter-3, (v8 files)

# Create the directories
mkdir -p ./v8

# Define the paths
V8_NEW_INCLUDE_DIR=./v8
V8_INCLUDE_DIR=../chapter-2/v8/v8
V8_OUT_DIR=$V8_INCLUDE_DIR/out.gn/x64.release.sample

# Copy files
cp $V8_OUT_DIR/obj/libv8_monolith.a $V8_NEW_INCLUDE_DIR
cp $V8_OUT_DIR/icudtl.dat $V8_NEW_INCLUDE_DIR
cp -r $V8_INCLUDE_DIR/include $V8_NEW_INCLUDE_DIR