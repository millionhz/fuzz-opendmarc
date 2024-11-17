# Fuzz OpenDmarc

## Compilation

Make sure libopendmarc is installed:

```bash
sudo apt install libopendmarc-dev
```

Compile:

```bash
gcc ./main.c -lopendmarc -o main
```

## Usage

```bash
Usage: ./main <DMARC record> <domain> [organizational domain]
```