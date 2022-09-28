# Description

This utility will print the current state of `CAPS_LOCK` and `NUM_LOCK` respectively in json format (single item), however it was specifically written for monitoring the status over time.

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

Complete credit for the specivity of this project goes to [dharmx](https://github.com/dharmx)
