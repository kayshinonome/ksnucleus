# Syscall

Generically a syscall is made by calling the syscall handler with a pointer to a array of void pointers, each pointing to the intended data

For example, a user space library would do something like this to fill a buffer with random numbers:

C++

```c++
uint8_t buffer[100];
size_t length = sizeof(lol);
void *args[] = {reinterpret_cast<void *>(buffer), reinterpret_cast<void *>(&length)};
mk_syscall(KsSyscallID::RANDOM, args);
```

## Syscall descriptions

| Id  | Syscall | Args             | Description                                                                     |
| --- | ------- | ---------------- | ------------------------------------------------------------------------------- |
| 0   | random  | void *, uint32_t | Using arg1 as a array, write random bytes to the length of the array (arg2)     |
| 2   | fission | char *           | Output a message (Arg1) before rebooting the system because of a critical error |
