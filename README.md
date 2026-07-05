<div align="center">

# 📦 Gcano Ain't Not an Organizer!

### Lightweight package helper for Linux written in C

A fast **ncurses** interface for managing packages using your system's native package manager.

![License](https://img.shields.io/github/license/guisodre12/gcano)
![Language](https://img.shields.io/badge/language-C-blue?logo=c)
![Platform](https://img.shields.io/badge/platform-Linux-success)
![Status](https://img.shields.io/badge/status-Alpha-orange)

---

[Installation](#installation) •
[Features](#features) •
[Usage](#usage) •
[Build](#building) •
[Configuration](#configuration) •
[Contributing](#contributing)

</div>

---

## 🚀 Overview

**Gcano** is a lightweight terminal package helper written entirely in **C**.

Instead of using the bare bones terminal, Gcano provides an intuitive **ncurses-based interface** for browsing, searching, and installing packages while automatically using the package manager available on your system. Kinda like aptitude, but for everything.

Supported backends include:

- `pacman`
- `apt`
- `dnf`

---

## ✨ Features

-  Keyboard-driven terminal interface
-  Extremely lightweight and fast
-  Search packages easily
-  Install packages from one interface
-  Automatically detects your package manager
-  Optional Lua plugin support(SOON!)
-  Works across multiple Linux distributions
-  Written in pure C

---

## 📸 Preview


<img width="1366" height="742" alt="Screenshot From 2026-07-04 23-39-08" src="https://github.com/user-attachments/assets/9fc8707d-1dfb-4251-82cc-9a30bfaccfc2" />
<img width="1366" height="742" alt="Screenshot From 2026-07-04 23-39-30" src="https://github.com/user-attachments/assets/d3d777b6-87cb-4d03-a669-40240a4389a2" />



---

# 📥 Installation

### Requirements

| Dependency | Version |
|------------|----------|
| GCC | 7+ |
| GNU Make | 4+ |
| ncurses | 6+ |
| Lua *(optional)* | 5.3+ |


## Install dependencies:
Debian:
```
sudo apt update
sudo apt install gcc make libncurses5-dev libncursesw5-dev 
```

Arch Linux:
```
sudo pacman -S gcc make ncurses
```

Fedora:
```
sudo dnf install gcc make ncurses-devel
```
## Build from source

```bash
git clone https://github.com/guisodre12/gcano.git
cd gcano
make
sudo make install
```

---

# 💻 Usage
---

```
user@computer[~}$: gcano
```

---

# ⚙️ Configuration (In development)

Configuration files are soon to be stored inside:

```
~/.config/gcano/
```

Lua plugins will soon be possible to be added as to customize menus and extend functionality.

---

# 🤝 Contributing

Contributions are welcome!

You can help by:

- Reporting bugs
- Suggesting new features
- Improving documentation
- Submitting pull requests

---

# 📄 Gcano is free software!

This project is free and open source and licensed under the **GNU GPL v3**.

See the **LICENSE** file for details.

---

<div align="center">

## ⭐ If you like Gcano, consider giving it a star!

Named after the king of the Americas in 2023, made with ❤️ by **Gui Sodré**

</div>
