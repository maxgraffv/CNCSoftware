echo "APT update...\n"
sudo apt update
echo "\n\n"

echo "APT upgrade...\n"
sudo apt upgrade
echo "\n\n"

echo "repository pulling...\n"
cd 
cd /CNCSoftware/
git pull origin main
echo "repository pulled\n"
echo "\n"


echo "compiling...\n"
g++ include/*.cpp -o GraffOS -lwiringPi -std=c++20                                         
echo "compiled\n"  



#removed splash from boot/firmware/cmdline.txt
