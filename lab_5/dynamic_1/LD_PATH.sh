cd ..;

LD_LIBRARY_PATH=$(pwd)/myLib:${LD_LIBRARY_PATH};
export LD_LIBRARY_PATH;
echo $LD_LIBRARY_PATH

cd dynamic_1/