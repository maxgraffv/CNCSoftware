echo "ssh enabling..."
echo ""
sudo systemctl enable ssh
sudo systemctl start ssh
sudo systemctl status ssh
echo ""
echo ""

echo -e "git installing...\n"
sudo apt install git
echo ""
echo ""

echo -e "vim installing...\n"
sudo apt install vim
echo ""
echo ""


echo -e "WiringPi installing...\n"
cd 
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build
gpio -v
cd 
echo ""
echo ""


echo -e "fbi installing...\n"
sudo apt install fbi
echo ""
echo ""


echo -e "splashscreen service...\n"
sudo mv ~/CNCSoftware/splashScreen/splashScreen.service /etc/systemd/system/
sudo mv ~/CNCSoftware/splashScreen/show_splash.sh /usr/local/bin/
sudo mv ~/CNCSoftware/splashScreen/logo.png /usr/local/share/
sudo chmod +x /usr/local/bin/show_splash.sh
sudo chmod 644 /usr/local/share/logo.png
sudo systemctl enable splashScreen.service
sudo systemctl start splashScreen.service
#add "quiet" to /boot/firmaware/cmdline.txt
sudo systemctl deamon-reload
sudo systemctl restart splashScreen.service
echo ""
echo ""


echo -e "Rebooting...\n"
sudo reboot

