Ульянин Дмитрий 597а



sample using:
./28_10_2017_kr <fieldSize> <mode>


fieldSize                   : int
mode = VISUAL || SPEED_TEST : string



mkdir build
cd build
cmake ..
make
./28_10_2017_kr 40 VISUAL

или

./28_10_2017_kr 40 SPEED_TEST




note:
Если закомментировать строки с pragma, то программа работает дольше в режиме SPEED_TEST
