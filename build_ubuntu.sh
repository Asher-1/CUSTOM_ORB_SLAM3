echo "Configuring and building Thirdparty/DBoW2 ..."

cd Thirdparty/DBoW2
mkdir build_ubuntu
cd build_ubuntu
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j 4

cd ../../g2o

echo "Configuring and building Thirdparty/g2o ..."

mkdir build_ubuntu
cd build_ubuntu
cmake .. -DCMAKE_BUILD_TYPE=Release
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
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j 4
