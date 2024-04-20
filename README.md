# clox

My implementation of clox as described by Robert Nystrom in [crafting interpreters](https://craftinginterpreters.com/contents.html).

## Challenges
- [x] Devised an [efficient method](https://en.wikipedia.org/wiki/Run-length_encoding) for encoding line information.
- [x] Added support for 24 bit constants (OP_CONSTANT_LONG).
- [ ] Wrote an original implementation of `reallocate()` without using malloc, realloc, or free.
- [x] Hand-compiled `1 + 2 * 3 - 4 / -5` into bytecode.
- [x] Substituted OP_NEGATE for OP_SUBTRACT.
- [x] Made VM stack dynamically grown.
- [x] Made OP_NEGATE work in-place.
- [ ] Parsed C-style `?:` (ternary operator).
- [x] Made ObjString own its character array with [flexible array members](https://en.wikipedia.org/wiki/Flexible_array_member) technique.
- [x] Made ObjString differentiate between heap owned strings and source string literals.
- [ ] Added support for keys of primitive types: numbers, Booleans, and nil.
- [ ] Added support for constants (variables that cannot be re-assigned).
- [ ] Extended clox to allow more than 256 local variables to be in scope at a time.
- [x] Added support for `switch` statement.
- [ ] Added support for `continue` statement.
- [ ] Strored the `ip` in a CPU register.
- [ ] Added arity checking for native functions.
- [ ] Supported native functions to report runtime errors.
- [ ] Made a compact Obj header.
- [ ] Efficiently cleared `isMarked` field during garbage collection cycles.
- [ ] Object fields can be accessed by any string constructed string in Lox.
- [ ] Object fields can be deleted permanently.