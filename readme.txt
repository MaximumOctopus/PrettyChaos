=================================================================================================
  PrettyChaos 0.24
  (c) Paul Alan Freshney 2023-2025

  paul@freshney.org

  Source code and portable install
    https://github.com/MaximumOctopus/PrettyChaos

  November 16th 2025

=================================================================================================

PrettyChaos is an open source fractal generation tool.

Currently supports Julia Set, Julia Set (with any polynomial degree), Mandelbrot, Dragon, and Martin fractals.

=================================================================================================

Written with C++ Builder 12 (Update 1) Community Edition (free).
   https://www.embarcadero.com/products/cbuilder/starter

=================================================================================================

 Credits:

   All coding       : Paul A Freshney
   Development Cats : Rutherford, Freeman, and Maxwell

   Dedicated to Dad, Julie, Adam, and Dyanne.

All of my software is free and open source; please consider donating to a local cat charity or shelter. Thanks.

=================================================================================================

Release History

0.24 / November 16th 2025

Added: Canvas dimensions. A range of populare Canvas sizes in 150 and 300dpi
Added: "Reset" to Palette editor (reloads default grey gradient and resets everything)
Added: Quick Load Palette button to the Palette section on the right hand menu
Added: 2x Interleve now works correctly

A few minor fixes and tweaks.

0.23 / August 13th 2025

Added: Martin de Jong attractor.

A few minor performance improvements and fixes.

0.22 / June 29th 2025

Added: Support for gradients to replace the "infinity" colour
       Instead of solid colour to represent points that tend to infinity
       a gradient can be used instead.	   

0.21 / April 13th 2025

Added: Julia sin(z) + cos(z) + c

A couple of minor fixes and changes.

0.20 / April 4th 2025

Added: Resize options to Width/Height popup menu

A few minor tweaks.

0.19 / March 16th 2025

Added: Save/Load Fractal history (every generated fractal's information is saved for later recall)
Added: "Reverse" palette option on Palette Editor dialog
Added: "Random" palette options on Palette Editor dialog
       Rand 1 uses the first key's colour as a "seed" for the rest
       Rand 2 randomly generates each colour
	   These can produce some suprisingly awesome palettes!
Added: Copy rendered image to clipboard menu option

A few tweaks and minor fixes.

0.18 / March 11th 2025

Added: Cos, cubic, and quartic, z^n, and Cos(z^n) Mandelbrots
       Cos(z^n) and z^n are slow though. Keep iterations around 100 until you find the one you want to keep
Added: Cos Julia set
Added: Configurable super-sampling options of 4x/8x/16x/32x.
Added: Changing palette will automatically recolour the current fractal (no render needed!).
       Not available when "show preview" is active.
Fixed: Project file now saves super-sampling information; and sets correctly on load

A few performance improvements to Martin and Dragon fractals. Some minor performance improvements to all fractals.

0.17 / August 31st 2024

Fixed: Fractal parameters not always being saved with enough mathematical precision
Added: Loaded/saved project file name to title bar

0.16 / July 8th 2024

Added: Super-sampling! Hard-coded to 8x in this version.
       Creates much nicer, smoother fractals with fewer jaggies but at significant processing cost
       I've increased the default number of threads for super-sampling to 10 (non-ss is 5).
Added: Zoom out (useful when loading a new project)
Fixed: Preview now updates when zooming, resetting, and navigating zoom history
Fixed: Reseting the view now calculates a correct aspect ratios if the width and/or height has changed
Fixed: A few minor bugs.	   

0.15 / June 18th 2024

Added: description and fractal properties to rendered image
Fixed: Coeff n value not being saved correctly to project files

0.14 / June 9th 2024

Added: Quick parameter value options via the Edit menu.
Added: Render preview (activate via the Render menu).

The usual minor tweaks and fixes.

0.13 / April 1st 2024

Fixed a bug where the palette would be deleted if the load palette dialog was cancelled!

Added a "copy render image buffer" button to the toolbar, used in conjunction with...
Added a "merge with buffer" button to the toolbar. Merges the rendered output to the copy buffer
        pixels set to the "infinity" colour will be replaced with the new render

A few minor tweaks and fixes

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