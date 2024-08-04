echo "WiringPi installing...\n"
cd 
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build
gpio -v
cd 
echo "\n\n"


echo "fbi installing...\n"
sudo apt install fbi
echo "\n\n"


echo "splashscreen service...\n"
sudo mv CNCSoftware/splashScreen/splashScreen.service /etc/systemd/system/
sudo mv CNCSoftware/splashScreen/show_splash.sh /usr/local/bin/
sudo systemctl enable splashScreen.service
echo "\n\n"


