echo "repository pulling...\n"
git pull origin main
echo "repository pulled\n"

echo "GPIO check...\n"
gpio -v

echo "compiling...\n"
g++ *.cpp -o main -lwiringPi -std=c++20
echo "compiled\n"

#./main
