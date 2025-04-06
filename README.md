This is a very basic implementation of thread local store (TLS), for AmigaOS. There has been a lot of talk about how this couldn't be implemented or is the impossible to do on AmigaOS4.0 and why we can't have the modern web browsers. That is actually just a big excuse for why we don't have it.

TLS should be supported by GCC, but I believe it's broken under AmigaOS3.x and 4.x.
AmigaOS has had place for local / user data, for a long time, it’s just not specified for TLS, as it predates it. This is what this implementation depends on.

This implementation is limited to what can be statically linked. 
This does not work across amiga libraries. (An Amiga library is basically a separate program, the offset won’t be copied, it could result in undocumented behavior, if you tried to set up the offsets, the offsets depend on order they are initiated).

Also because they created as templates, I believe they are static. It can be a good idea to put it in a header file, to prevent it being initialized in bad order. You can run into some unforeseen issues, or else.

On the main process you cannot set up TLS before, the main function, but it is easy to make wrapper, for that. if program calls Exit(), you should setup the process death function, but if it does not, you can just free TLS buffer at end of the process.

The new TLS buffer can be passed to NewProccesTags(), there is way you can allocate it before it’s called, just remember to free it, if NewProcessTags failed.. as this implementation does not cover that part. (In that case it’s up to you if you copy or clear the new TLS.)
