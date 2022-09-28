# Description

This utility will print the current state of `CAPS_LOCK` and `NUM_LOCK` respectively, however it was specifically written for monitoring the status over time.

# Installation

```bash
git clone --depth=1 https://github.com/beyond9thousand/xkb
cd xkb
cc -O3 --std=c11 -pedantic -Wall xkb.c -o xkb -lX11 -lXi
```

Move the executable to your desired location

# Synopsis

```
xkb [-s|-s1|-s0|-j|-j[1|0]]
```

# Options

- `-s` -- `indicators CAPS_LOCK_STATE NUM_LOCK_STATE`
- `-j` -- `{"caps":"CAPS_LOCK_STATE","num":"NUM_LOCK_STATE"}`

## Examples

- `-s1` -- Will print the initial value
- `-s0` -- Won't print the initial value / not providing any args will have the same effect
- `-j[1|0]` -- Same as `-s`

# Credits

Complete credit for the specivity of this project goes to [dharmx](https://github.com/dharmx)
