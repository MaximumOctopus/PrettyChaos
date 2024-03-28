=================================================================================================
PrettyChaos 0.12
(c) Paul Alan Freshney 2023-2024

paul@freshney.org

Source code and portable install
  https://github.com/MaximumOctopus/PrettyChaos

March 28th 2024

=================================================================================================

PrettyChaos is an open source fractal generation tool.

Currently supports Julia Set, Julia Set (cubic), Mandelbrot, and Martin fractals.

=================================================================================================

Written with C++ Builder 11 (Update 3) Community Edition (free).
   https://www.embarcadero.com/products/cbuilder/starter

=================================================================================================

 Credits:

   All coding       : Paul A Freshney
   Development Cats : Rutherford, Freeman, and Maxwell
   Icon             : https://icon-icons.com

   Dedicated to Dad, Julie, Adam, and Dyanne.

All of my software is free and open source; please consider donating to a local cat charity or shelter. Thanks.

=================================================================================================

Release History

0.12 / March 28th 2024

Added a new menu item to copy current paramters to the clipboard.
Added a new button on the toolbar to centre the display at a specific point in the fractal (no zoom, just a recentre).
Fixed a few minor issues (including loading a project)

Modified the quick parameter change key combinations:

SHIFT + UP ARROW: increase parameter a by 0.1 (for Julia sets, 1 for Martins)
SHIFT + DOWN_ARRROW: decrease parameter a by 0.1 (for Julia sets, 1 for Martins)

CTRL + UP_ARROW: increase parameter b by 0.1 (for Julia sets, 1 for Martins)
CTRL + DOWN_ARROW: decrease paramrter b by 0.1 (for Julia sets, 1 for Martins)

ALT + UP_ARROW: increase parameter c by 0.1 (for Julia sets, 1 for Martins)
ALT + DOWN_ARROW: decrease paramrter c by 0.1 (for Julia sets, 1 for Martins)

With the specified modifier (SHIFT, CTRL, or ALT) hold the LEFT ARROW instead to increase the paramter by 0.01 (for
Julia sets, 0.1 for Martins); the RIGHT ARROW to decreease the paramter by 0.01 (for Julia sets, 0.1 for Martins).

0.11 / March 27th 2024

Added a test before rendering a Julia Set to ensure the real and imaginary values form a valid set (and you don't wait
20+ seconds for a blank image because each point tends to infinity!!).

Added the ability to quickly change the top two parameters (real and imaginary for the Julia sets) and render the result:

SHIFT + UP ARROW: increase parameter a (real) by 0.1
SHIFT + DOWN_ARRROW: decrease parameter a by 0.1

CTRL + UP_ARROW: increase parameter b (imaginary) by 0.1
CTRL + DOWN_ARROW: decrease paramrter b by 0.1

Hold down the ALT key in addition to either SHIFT or CTRL to increase/decrease by 0.01

0.10 / March 26th 2024

A few minor fixes and some code refactoring.

0.9 / March 25th 2024

Added minor performance improvement when generating image
Added multi-threading for Mandelbrot and Julia sets.
      Locked to four threads at the moment, performance improvement upto 4x

Fixed a bug which effected fractal aspect ratios and rendering.

0.8 / November 9th 2023

Added Julia Set (Quintic)
Added Julia Set (n-tic) for all Julia Sets of the form Z^n + C (eg Quintic is Z^5 + C)
Added Load palette option to main tool panel
Added Palette name to save files (will attempt to reopen palette upon load)
Added Interleve options to palette (allows for some very nice patterns)
Added Performance improvements to all Julia Sets

A few minor bug fixes and tweaks.

Moved the palette handling code to a new class for flexibility and unlocks functionality for the future.

Multi-threading coming in a future update.


0.7 / October 10th 2023

Added Rendering performance improvements
Added Julia Set (Quartic)
Added Three Martin fractal types
Added Simple animation system (by zoom, and/or parameter(s)) 

0.6 / October 4th 2023

Added nice icon!
Added Dragon curve
Added the ability to change the "infinity" colour from the right hand menu
Added an option to File menu to save fractal parameters to a text file

0.51 / October 2nd 2023

Fixed issues with project loader
Added "infinity" palette colour to right hand menu

0.5 / October 1st 2023

Added more render modes. 
Added cursor x/y location to right hand panel
Added stepping option to colour palette generator
Added menu with shortcut keys

Use the new Tools option "RMB on image sets parameters" to set the orbit point for the Mandelbrot
"orbit track" render method.

Lots of minor tweaks and improvements.

0.4 / September 28th 2023

Fixed a few small issues.
A single palette is now shared by all fractal sub-classes
Added auto save (saves every rendered image), and the option to save fractal parameters (as a separate file) for each image.

0.3 / September 25th 2023

Added Julia Sets.
Added Cubic Julia Sets.
Fixed RGB/HSV gradient displays repainting

Modifications to easily allow more fractal generators to be added in a modular way.

0.1 / September 23rd 2023

Initial release.