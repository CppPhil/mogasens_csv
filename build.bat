@echo off

set dir=%~dp0
set prev_dir="%CD%"
set goto_ruby="%dir%\external\goto-ruby\goto-ruby.bat"

cd %dir%

call %goto_ruby% "%dir%\ruby\build_windows.rb" %*

cd %prev_dir%
exit /B 0

