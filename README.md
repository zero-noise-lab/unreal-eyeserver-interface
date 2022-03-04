Unreal Plugin interfacing EyeLinkServer
=======================================

This is a project plugin for Unreal Engine projects that provides a Blueprint
Function Library to interface the ESI EyeServer. The EyeServer is part
of the [ARCADE suite](https://github.com/esi-neuroscience/arcade) and allows
monitoring the eye position tracked by the free iRecHS2 system or an SR Research Eyelink system.

For the Unreal Engine to be able to start the EyeServer, the iRecServer.exe or
EyeLinkServer.exe needs to be on the user's path. The provided Blueprint
functions can be mapped to any kinds of events such as `BeginPlay`, keyboard
presses, etc., see for example

![ExampleBlueprint](/Docs/exampleBlueprint.png)

It has been developed using Unreal Engine 4.24.2, iRecServer 1.0.4.0 and [EyeLinkServer 1.2.2.0](https://github.com/esi-neuroscience/EyeLinkServer/releases/tag/v1.2.2.0).

This plugin is free but copyrighted software, distributed under the terms of
the MIT License. See the file LICENSE for more details.
