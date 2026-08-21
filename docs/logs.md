```
This is mainly to keep track of why I made some of the most ludicrous
decisions made while working on this project.
```

## 260820
**1613**. the visible CPU flags (in `include/flags.h`) and its get and set
functions should be sufficient. I can't imagine having messed that up too much.

## 260819
**1624**. This particular part is a headache for me. In `include/cpu.h`, I have
declared `push` and `pop`; however, I wonder if I should just have push and
pop instructions or whatever exclusively in `lib/instruction_set.c`. As the
push and pop instructions exist in the ISA, it makes sense to interact
with the stack through the system's ISA... but I guess push and pop is done
so through the CPU... idk, I'll think about it. Other than that, `cpu.h`
implements the `fetch->decode->execute` loop, and register setting and
retrieval... wait... should that be placed in `include/register_file.h`
instead? ... hmmm....

**1543**. `include/bus.h` is a pretty important file. It almost acts like a
bridges that connects the project together. Essentially, `include/bus.c`
implements the interface for the DMG memory region. That said, I have not yet
implemented the cartridge and is a problem future me (sorry in advance). I
actually haven't a clue how the cartridge works and how it interacts with the
overall system.

Regardless, the actual implementation of the declared functions is basically
a bunch of ranges that define the boundaries of the memory regions.
`io` likely has a close association with the CPU registers... I think? It
doesn't sound right.

A key detail of the gameboy is that it has an 8-bit wide bus despite having
memory addresses that are 16 bits (as seen in `include/register_file.h`).
Apparently, this was a common CPU design during its era. The registers (`a`,
`b`, `c`, `d`, `e`, `f`, `h`, and `l`) can function as pairs: `af`, `bc`, `de`,
and `hl`. I think the idea is mainly for addressing. `hl` in particular is used
to hold 16-bit memory addresses, which a lone 8-bit register can't represent
(16 bits gives 256x the range of an 8-bit register).

**1529**. The purpose of `gbemu/main.c` is to act as the driver/entry point for
the gameboy emulator. The intention is that it wires up the subsystems of the
gameboy... the main issue being that I haven't a clue how it will act as an
entry point. Is there something else that I am supposed to add to it to make
it a true entry point? I haven't a clue. Additionally, I plan to have the
program produce APIs of sorts, but how do you even do that?

**1518 dev_instruction-set baa9583**. It's actually really hard to document my
work. I have come to realize that my issue is that I tend to work on the
project until I am tired for the day and then at that point, the thought of
documentation becomes absolutely exhausting. Lets just dedicate a few days
trying to figure out what it is that I developed thus far. This is for future
me's sake when I lose passion for the project again.
