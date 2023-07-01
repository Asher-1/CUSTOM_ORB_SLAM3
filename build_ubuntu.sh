echo "Configuring and building Thirdparty/DBoW2 ..."

if [ -n "$1" ]; then 
    if [ "$1" = "OFF" -o "$1" = "ON" ]; then
        BUILD_NATIVE=$1
    else
        echo "Wrong parameter for -BUILD_NATIVE! Only support OFF or ON"
        exit
    fi
else
    BUILD_NATIVE=ON
fi

echo "Build all libraries with native: $BUILD_NATIVE"

cd Thirdparty/DBoW2
mkdir build_ubuntu
cd build_ubuntu
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_NATIVE=$BUILD_NATIVE
make -j 4

cd ../../g2o

echo "Configuring and building Thirdparty/g2o ..."

mkdir build_ubuntu
cd build_ubuntu
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_NATIVE=$BUILD_NATIVE
make -j 4

cd ../../Sophus

echo "Configuring and building Thirdparty/Sophus ..."

mkdir build_ubuntu
cd build_ubuntu
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j 4

cd ../../../

echo "Uncompress vocabulary ..."

cd Vocabulary
tar -xf ORBvoc.txt.tar.gz
cd ..

echo "Configuring and building ORB_SLAM3 ..."

mkdir build_ubuntu
cd build_ubuntu
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_NATIVE=$BUILD_NATIVE
make -j 4
