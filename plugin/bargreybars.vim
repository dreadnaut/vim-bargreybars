" BarGreyBars.vim - Removes grey borders from maximised windows
" Platform:   Windows x86/x64
" Maintainer: Dreadnaut <dreadnaut@gmail.com>
" Version:    0.0.1


" Avoid executing the script more than once, if vim is running
" in a terminal or on the wrong platform
if exists("g:loaded_bargreybars") || !has("gui_running") || !has("win32")
  finish
endif
let g:loaded_bargreybars = 1

" Set this variable to 0 in your .vimrc to prevent this plugin
" to set up automatic triggers; you can still use the 'Colorscheme'
" command to apply a scheme and match the window background
if !exists("g:bargreybars_auto")
  let g:bargreybars_auto = 1
endif

if g:bargreybars_auto
  augroup bargreybars
    autocmd!

    " Match color when the GUI is up and the color scheme has
    " been applied; this means VIMEnter rather than GUIEnter
    autocmd VIMEnter * :call s:match()

    " Match color when a new color scheme is applied
    autocmd ColorScheme * :call s:match()

  augroup END
endif

" Defines the 'Colorscheme' command to apply a scheme and
" immediately match the window background color
command! -complete=color -nargs=1 Colorscheme
    \ :call bargreybars#Colorscheme(<f-args>)

" Syntax groups scanned to find a scheme background color
let g:bargreybars_syntax_groups = [ 'Normal', 'NonText' ]

" Try to retrieve the background color from the color scheme
function! s:getWindowBackground() abort

  " Checks the syntax groups in order, uses the first
  " background color it finds
  for group in g:bargreybars_syntax_groups
    let l:color = synIDattr(hlID(group), 'bg#')
    if l:color != ""
      return l:color
    endif
  endfor

  return ""

endfunction

" The path of the external dll, built from the path of this script
let s:dllFile = expand('<sfile>:p:h:h') . '/dll/bargreybars.dll'

" Call the external dll and set the window background
" to the specified hex color (e.g., "#3f3f3f")
function! s:setWindowBackground(hexColor) abort
  if strlen(a:hexColor) == 7 && strpart(a:hexColor, 0, 1) == "#"
    let l:color = str2nr(strpart(a:hexColor, 1, 6), 16)
  else
    let l:color = -1
  endif

  return libcallnr(s:dllFile, "SetWindowBackground", l:color)
endfunction

" Set the window background to the current scheme background color
function! s:match() abort
  let l:color = s:getWindowBackground()
  return s:setWindowBackground(l:color)
endfunction

" Applies a color scheme and matches the window background
function! bargreybars#Colorscheme(colorscheme) abort
  execute "colo " . a:colorscheme
  redraw
  call s:match()
endfunction

