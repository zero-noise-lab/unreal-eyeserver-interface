Unreal Plugin interfacing EyeLinkServer
=======================================

This is a project plugin for Unreal Engine projects that provides a Blueprint
Function Library to interface the ESI EyeLinkServer. The EyeLinkServer is part
of the [ARCADE suite](https://github.com/esi-neuroscience/arcade) and allows
monitoring the eye position tracked by an SR Research Eyelink system.

For the Unreal Engine to be able to start the EyeLinkServer, the
EyeLinkServer.exe needs to be on the user's path. The provided Blueprint
functions can be mapped to any kinds of events such as `BeginPlay`, keyboard
presses, etc., see for example

![ExampleBlueprint](/Docs/ExampleBlueprint.png)

This plugin is free but copyrighted software, distributed
under the terms of the MIT License. See the file LICENSE for more details.