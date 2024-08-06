echo -e "APT update...\n"
sudo apt update
echo "\n\n"

echo "APT upgrade...\n"
sudo apt upgrade
echo "\n\n"

echo "repository pulling...\n"
cd 
cd /home/max/CNCSoftware/
git pull origin main
cd
echo "repository pulled\n"
echo "\n"


echo "compiling...\n"
g++ /home/max/CNCSoftware/include/*.cpp -o /home/max/GraffOS -lwiringPi -std=c++20                                         
echo "compiled\n"  



