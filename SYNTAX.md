# Syntax for the Turing Virtual Machine
## File Extensions
They don't really matter, but for the sake of consistency, we're going to use these:
- `.tc` for turing machines (**T**uring **C**ode);
- `.tt` for the input/output of turing machines (**T**uring **T**ape);

## Comments
Just like in C++/Java/JavaScript/etc. Anything considered as a comment is ignored by the compiler:

```c
// Short Comment

/*
    Long Comment
*/
```

## Symbols
Turing machines operate on symbols. In theory, the symbol space can be infinite, but to keep things simple, `tvm` accepts (almost) any non-whitespace unicode character.

**Notable exceptions are** the forward slash (`/`) and the hashtag (`#`).

### Special Symbols
- **Whitespace Symbol:** Represents nothingness. By default this is represented by the underscore (`_`). There is only one whitespace symbol;
- **Wildcard Symbol:** Used in transitions only. Matches any symbol in the symbol space. By default this is represented by the asterisk (`*`);

# Turing Code (`.tc` files)

## States
A turing machine consists of states. There are three special states to consider:

- `START` - the initial state of the machine. **Must** exist, otherwise it won't run.
- `ACCEPT` - this state terminates (i.e. halts) the machine and accepts the input. This is equivalent to a successful execution of the program. Program exits with code 0.
- `REJECT` - this state terminates the machine rejecting the input. In this context, the program will exit with code 1.

Neither the `ACCEPT` or `REJECT` states are mandatory (but they're recommended).

Other than that, any word (i.e. unicode sequence) can be a state, as long as there is no whitespace. For example, `thisIsAVeryLongStateNameAlsoKnownAsImTrying_So_HardToReachEntrepiseJavaLevelsOfVerbosityFactoryDto` is a valid name for a state. `lil state` is **not** a valid name for a state. State names are case sensitive.

## Transitions
Transitions link states together and define the behavior of the machine. The syntax for a transition is as follows:

```c
<STATE_FROM> <TAPE_READ>... <TAPE_WRITE>... <TAPE_MOVE>... <STATE_TO>
```
Transitions **cannot start** from `ACCEPT` or `REJECT` because they will never be executed.

**Example:**

```c
START _ 1 R t1 
```

In this case, the machine has one tape. This transition says that if you're in the `START` state and read whitespace, then you write `1` where that whitespace was; then you move the tape reader to the right. The `TAPE_MOVE` field can have one of these three values:

- `L` - move the tape reader to the left
- `S` - don't move the tape reader
- `R` - move the tape reader to the right

If the machine has more than one tape, you can do something like this (example for three tapes):

```c
t1 _1_ 11_ RRS t1
```

### Wildcards

Especially when you have a lot of symbols and tapes, you sometimes don't care what's in a given tape. But writing transitions for every single one of those symbols just to discard them is very error-prone and basically a waste of time. That's where wildcards come in.

```c
t1 11* 222 RRR t2
```

The transition will execute if there's a `1` in the first and second tapes, regardless of what's in the third one, then it will write `2` to the three tapes.

If you don't want to write on the third tape, place a wildcard there:

```c
t1 11* 22* RRR t2
```

### Other Considerations

- Only one pair `<STATE_FROM>`, `<TAPE_READ>` is allowed per Turing Machine. If multiple existed, the machine would become non-deterministic (which is out of the scope of this project... for now). Example:

```c
// Not allowed: Non-deterministic machine
tND 12* _2* RRR tND
tND 12* 22* RRR tND
```

- All transitions need to have the same number of tapes, the following examples are not allowed:

```c
// Not allowed: Different number of tapes in the same transition
t1 123 1234 RSLL t2

// Not allowed: Transitions with different number of tapes
t1 123 234 RSS t2
t2 1234 2341 SLRL t3
```

- Non-wildcard transitions take priority over wildcard transitions:

```c
t1 * 1 R t1
t1 1 1 L ACCEPT // This one will be checked first
```

- If the current `<STATE>`, `<TAPE>` tuple doesn't match any transition, the machine will be forcefully halted and the program will exit with code `<TBD>`.

- One turing machine per file.

### Running turing machines inside other turing machines

You can import turing code inside turing code (like a library/function in most actual programming languages).

To do so, you can add an `IMPORT` directive:

```c
# IMPORT <FILE> AS <TEMPLATE_NAME>
```

Imported turing machines **MUST** run on an equal or lesser number of tapes than the machine that is importing them.

> **Example:** A machine running on 4 tapes can import a machine with 2 tapes, but not a machine with 5 tapes.

However, it doesn't make it available to use right away. What you just imported is a _template_ of the machine. You may want the machine to use tapes 2 and 6, instead of 1 and 2. Or even have multiple instances of the same machine operating on different tapes. To instantiate a template:

```c
# TC.<STATE_NAME> = <TEMPLATE_NAME>(<TAPES...>)
```

**Example:**

```c
// Say this machine has four tapes,
// and we're running a 7-tape machine
# IMPORT "univ_checker.tc" AS UNIV_CHECK

// All of these are possible
# TC.UNIV1 = UNIV_CHECK(1, 2, 3, 4)
# TC.UNIV2 = UNIV_CHECK(5, 3, 1, 7)
# TC.UNIV3 = UNIV_CHECK(4, 3, 2, 1)
# TC.UNIV4 = UNIV_CHECK(1, 2, 3, 4)
# TC.UNIV5 = UNIV_CHECK(7, 5, 3, 1)
```

When instantiating a turing machine `<NAME>`, the states `<NAME>`, `<NAME>.ACCEPT`, `<NAME>.REJECT` and `<NAME>.HALT` are added to the state-space, and you can use them as you would normally would with other state.

> Of course, you should not transition to the `ACCEPT`/`REJECT`/`HALT` states of an imported machine.

**Example:**

```c
# IMPORT "code.tc" AS CODE

# TC.CODE = CODE(2)

START ** ** SS CODE

CODE.ACCEPT *1 *2 SS ACCEPT
CODE.REJECT ** ** SS REJECT
```

What you **MUST NOT** do:

```c
# IMPORT "code.tc" AS CODE

# TC.CODE = CODE(2)

...

CODE ** ** SS ... // Can't transition from the entry point of a turing machine - that's internal behavior!

... ** ** SS CODE.ACCEPT // Can't transition to the end of a turing machine
```

# Turing Tape (`.tt` files)

This file is optional when running a Turing machine (even though needed for most use-cases) and is used to initialize the memory before execution.

The file should (but doesn't need to) contain the same number of tapes as the machine it is going to initialize. If there are too little, the missing ones will be initialized as empty tapes. If there are too many, the exceeding ones will be discarded.

## Tape representation

Each tape is represented by two lines: The contents of the tape and the position of the tape header.

### Tape contents

A line containing symbols (see the [Symbols](#Symbols) section at the start of this file). Example:

```c
_ABCDEF12345
```

No whitespace is allowed.

### Tape header

Only spaces and the `^` character are allowed on this line. It specifies the position of the header in the tape at initialization-time.

## Example

```c
// Initializes a 3-tape machine
ABCDEF
  ^
_ // The equivalent of an unitialized tape
^
Q10A1A2A3A4
   ^
```
