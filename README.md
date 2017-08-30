# Doom Patcher

This is a patching tool that can apply multiple different hacks to the Doom 2 version 1.9 executable (709905 bytes).

This utility is made from a cumulation of hacks that were distributed on [Doomworld](https://www.doomworld.com/) over the years.

Most of the hacks are cumulative, which means that applying a hack doesn't change the bytes at an offset used by another hack.

### Glossary

`VANILLA`: The hack is not detected. The bytes at the offsets where the patch does the changes are the same as vanilla.

`PATCHED`: The executable is already patched with this hack.

`UNKNOWN`: The executable is corrupted or an incompatible hack has already been applied.

### List of hacks

* Increase the maximum mouse sensitivity form 9 to 127
* Increase the maximum heap size to 32MB
* Display "Picked up a medikit that you REALLY need!"
* Fix for fast doors reopening with wrong sound
* Fix for fast doors that make two closing sounds
* Fix for the ouch face
* Disable 'Q' when recording demos
* Use DPCHGUN/DSCHGUN for chaingunner's attack sound
* Extend the stack allocation size (64KB => 512KB)
* Enable random sound pitch
* Increase the static limits to those of Doom plus
* Enable long tics

The extended stack size hack is incompatible with Doom plus.

### Credits

Many thanks to the authors of the hacks who make them available on Doomworld. They are: Miguel Folatelli (aka myk), Andrey "entryway" Budko (aka e6y) and Colin Phipps (aka cph). If you can't find your name here and think I have forgotten you, then send me an email or contact me on Doomworld.

### Sumitting patches

On GNU/Linux, you can easily create a patch to be added to this script using this command:

`cmp -l DOOM2.EXE HACKED.EXE | gawk '{printf "[0x%08X, 0x%02X, 0x%02X],\n", $1-1, strtonum(0$2), strtonum(0$3)}'`

You can add the generated output to the Python script and make it work with minimal changes.

You may open a pull request and I will take a look at your new patch. Please, one pull request per hack.
