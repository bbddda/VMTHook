# SafeVMT
A safe, header only easy to use VMT hooking class.

Why it's truly safe:
- Doesn't change the Virtual Table page protection rights.
- Doesn't swap the Virtual Table pointer.

Example usage:

```javascript

unsigned int GetVirtualFunction(void* virtualClass, unsigned int virtualIndex)
{
    return static_cast<unsigned int>((*static_cast<int**>(virtualClass))[virtualIndex]);
}
    
int main()
{
   VMHook* virtualMethodHook = new VMHook(dummyClass);
   
   void* addr = reinterpret_cast<void*>(GetVirtualFunction(yourClass, yourIndex));
   
   yourOriginal = (YourOriginalFn)addr;
   
   virtualMethodHook->Hook(YourDetourFunction, virtualIndex);
}
```
