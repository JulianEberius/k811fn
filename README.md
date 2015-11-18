# k811fn
Configure the Logitech K811's function keys on Windows 

Since the K811 is supposed to be used only on OSX and iOS, the Logitech SetPoint tool won't recognize it on Windows. However, the K811 forgets its settings with respect to function keys vs. special keys (e.g. Mute Sound vs. F11) when turned off, so configuring on OSX and then using it on Windows is not an option either. 

Therefore, I used the OSX Packet Logger to reverse-engineer the byte string sent to the K811 to get it to switch its behavior, similarly to how it was done for the K810 at http://www.trial-n-error.de/posts/2012/12/31/logitech-k810-keyboard-configurator/ . Then, I wrote a simple platform independent C++ programm using HIDAPI (https://github.com/signal11/hidapi) to be able to configure the device on other platforms such as Windows. 
