<div align="center">

# 📦 Gcano Ain't Not an Organizer!

### Lightweight package helper for Linux written in C

A fast **ncurses** interface for managing packages using your system's native package manager.

![License](https://img.shields.io/github/license/guisodre12/gcano)
![Language](https://img.shields.io/badge/language-C-blue?logo=c)
![Platform](https://img.shields.io/badge/platform-Linux-success)
![Status](https://img.shields.io/badge/status-Beta-orange)

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

Instead of using the bare bones terminal, Gcano provides an intuitive **ncurses-based interface** for browsing, searching, and installing packages while automatically using the package manager available on your system.

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
-  Optional Lua plugin support
-  Works across multiple Linux distributions
-  Written in pure C

---

## 📸 Preview

```text
┌──────────────────────────────────────────┐
│               GCANO                      │
├──────────────────────────────────────────┤
│ > Install Package                        │
│   Remove Package                         │
│   Search Repository                      │
│   Update System                          │
│   Configuration                          │
│   Exit                                   │
└──────────────────────────────────────────┘
```

*(Replace with a real screenshot later.)*

---

# 📥 Installation

## Build from source

```bash
git clone https://github.com/guisodre12/gcano.git
cd gcano
make
sudo make install
```

---

## Download latest release

```bash
curl -L \
https://github.com/guisodre12/gcano/releases/latest/download/gcano.tar.gz \
| tar -xz

sudo install gcano /usr/local/bin/
```

---

# 🔨 Building

### Requirements

| Dependency | Version |
|------------|----------|
| GCC | 7+ |
| GNU Make | 4+ |
| ncurses | 6+ |
| Lua *(optional)* | 5.3+ |

Manual build:

```bash
gcc -std=c99 src/*.c -o gcano -lncurses -llua
```

---

# 💻 Usage
---
If you want the TUI:
---
Launch the inteface:

```bash
gcano tui
```

---
If you wanna go the CLI way:
---
Install a package:

```bash
gcano install nginx
```

Search packages:

```bash
gcano search firefox
```

Update repositories:

```bash
gcano update
```

---

# ⚙️ Configuration

Configuration files are stored inside:

```
~/.config/gcano/
```

Lua plugins can be added to customize menus and extend functionality.

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
