# What this can do
- Parse and Unparse URL
- CRUD, create, read, update, and delete parameters of URL

# How to build
First make sure you have qt library installed:
```bash
sudo ldconfig -p | grep -i -E libqt+[0-9]+core
```
If you see something like this `libQt5Core.so.5` then you have needed libs.

If you dont have qt lib, you can install it using one of these commands
```bash
# Debian/Ubuntu
sudo apt install qtbase5-dev

# Arch
sudo pacman -S qt5-base
```
Once you have qt library installed, run these commands in project folder
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

# Screenshots
![example1]
![example2]
![example2]

[example1]: https://github.com/mikewii/urlparser/raw/main/resources/example1.png

[example2]: https://github.com/mikewii/urlparser/raw/main/resources/example2.png
[example3]: https://github.com/mikewii/urlparser/raw/main/resources/example3.png
