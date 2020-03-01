# bargreybars.vim

Gvim windows have a grey background hidden behind the text area. When maximised their dimensions are not a multiple of the font size, so the background shows up as grey bars on the right and bottom side of the windows.

![The goggles do nothing!](http://dreadnaut.altervista.org/_altervista_ht/vim/without-bargreybars.png)

This plugin keeps the windows background in sync with your color scheme.

![Nice and uniform](http://dreadnaut.altervista.org/_altervista_ht/vim/with-bargreybars.png)

Grey bars gone, the world is safe again!

*Note: the plugin works only on Windows*. GTK-based Vim can be [tweaked](http://pastebin.com/N0G333nP) in a different way, and [the issue has been reported](https://github.com/vim/vim/issues/349) in the Vim tracker.

## Features

By default, bargreybars.vim runs automatically when you start gvim and when you switch colorscheme. This behaviour can be disabled in your `.vimrc` file with:

``` viml
let g:bargreybars_auto = 0
```

If the automatic color-matching is disabled, you can use the `Colorscheme` command to apply a scheme and match the window background color. It works the same way as the standard `colorscheme` command.

``` viml
:Colorscheme zenburn
```

## Installation

The plugin is compatible with [pathogen.vim](https://github.com/tpope/vim-pathogen) and a similar plugin managers.

Here's the clone command for you copy-paste convenience:

```
git clone https://github.com/dreadnaut/vim-bargreybars.git
```

There, no further configuration is needed, you are ready to go.

## Building the dll from source

The plugin relies on a C library that modifies the window attributes. It is heavily inspired by [gvimfullscreen](https://github.com/leonid-shevtsov/gvimfullscreen_win32), and compatible with it. Source code for the library is included in the `dll` directory.

The x86 and x64 DLLs in the repository were built with the [Visual C++ 2019 Build Tools](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools).

Choose your target environment by opening the correct Visual C++ command prompt, then run the matching batch file, or one of the commands below.

```
# x86
cl.exe /LD bargreybars.c Gdi32.lib User32.lib /Fe: bargreybars32.dll
# x64
cl.exe /LD bargreybars.c Gdi32.lib User32.lib /Fe: bargreybars64.dll
```