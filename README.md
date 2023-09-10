# clox

My implementation of clox as described by Robert Nystrom in [crafting interpreters](https://craftinginterpreters.com/contents.html).crafting interpreters.

## Challenges
- [x] Devised an efficient method for encoding line information.
- [ ] Added support for 24 bit constants (OP_CONSTANT_LONG).
- [ ] Wrote an original implementation of `reallocate()` without using malloc, realloc, or free.
- [x] Hand-compiled `1 + 2 * 3 - 4 / -5` into bytecode.
- [x] Substituted OP_NEGATE for OP_SUBTRACT.
- [x] Made VM stack dynamically grown.
- [x] Made OP_NEGATE work in-place.