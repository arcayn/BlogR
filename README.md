# Blogr
[![MIT Licence](https://badges.frapsoft.com/os/mit/mit.svg?v=103)](https://opensource.org/licenses/mit-license.php) 

A blogging software that is currently in (limited) beta testing. To setup, you must place these files in whichever directory you please, and run the command:

```sh
./blogsetup
```

This will run the setup program, creating everything required to begin blogging!

Some users are experiencing problems with not having permission to run the blogsetup program, this is precisely why we include the source
to fix this, you must recompile the source. Run these two commands to run the setup program:

```sh
g++ blogsetup.cpp
./a.out
```

This will run the setup program exactly as it should

It currently lacks the promised plugin API. Everything else up-n-running however.
