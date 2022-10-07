# SafeVMT
A header only, easy to use VMT hooking class.

Why it's truly safe:
- Doesn't change the Virtual Table page protection rights.
- Doesn't swap the Virtual Table pointer.

Example usage:

```javascript
int main()
{
   VMHook* virtualMethodHook = new VMHook(dummyClass);
   
   virtualMethodHook->Hook(YourDetourFunction, virtualIndex);
}
```
