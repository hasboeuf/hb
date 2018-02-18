Hb
==

Main repository of Hb project

## Presentation

Hb is a set of open-source libraries and tools helping developers to make application quicker. Highly based on Qt framework, this is a requirement to get Hb working. Hb is developed to fit my personal and current needs and as my personal projects (desktop and mobile) are based on it, it is constantly improved and fixed.

### HbTools

#### Overview

HbTools is a set of generic classes used by other projects. It is the only library of HB module which depends on no one. It is the base library.

### HbLog

#### Overview

HbLog is a powerful distributed log library which is simple of use and efficient. Moreover HbLog can fit together to be used in an multi-application and multi-machine environment.

#### Features

- Various log levels: Trace, Debug, Info, Warning, Error, Critical, Fatal.
- Free-lock programming.
- Convenient way to write a log entry (printf syntax).
- Convenient way to configure outputs and inputs ( via command arguments or programmatically )
- Redirection of qDebug() qWarning() qCritical() in HbLog.
- Available outputs:
    - Console : all is printfed.
    - Gui : any widget of your choice.
    - File : with rotation when max size limit is reached.
    - Local socket : to a local application (see HbLogViewer).
    - Tcp socket : to a distant application (see HbLogViewer).
- Available inputs: (used by a log supervisor or a log router, see HbLogViewer).
    - Local socket.
    - Tcp socket.
- Reinjection of inputs into outputs (useful to route log message to a third application).

### HbLogViewer

#### Overview

HbLogViewer is a useful tool to watch log entries.

#### Features

- Configuration of inputs via command arguments.
- Visualization of log file.
- Colorization of log entries.
- Pause mode.
- Multiple filters.
- Open the right file at the right line in your favorite editor when a log entry is double-clicked.
- Several tabs can be opened.
- All user options are saved using QSettings.

### HbPlugin

#### Overview

HbPlugin is a set of high-level classes, useful to create plugins based on Qt5 plugin mechanism.

#### Features

- Plugins have a version.
- Plug / unplug according to plugin dependencies (and versions)
- Plugins have strong and weak dependencies.
- Plugins can work in an idle mode if weak dependencies are absents.
- Plugin can request for an app service.
- Plugin can provide a feature.
- Plugins can depend on other plugins features.
- Unplug / plug in live.

### HbLink

#### Overview

HbLink a set of classes implementing OAuth 2 protocol. For now only Facebook is supported, the rest will be developped on need. This is designed for a client / server architecture.

#### Features

- Client side: Opening the default browser on the Facebook login dialog, ask user to allow your app and specific permissions.
- Client side: Get the auth code.
- Server side: Get the client access token via the client auth code.
- Server side: Request Facebook for client informations.

### HbNetwork

#### Overview

HbNetwork is a high-level network library which is simple of use and efficient.

#### Features

- Abstraction of network protocol, handles several way to communicate (TCP, SSL, WEB, UDP, Bluetooth, Local).
- No worries about serialization/deserialization.
- Strict protocol of communication.
- Registration of contracts (high-level network packet).
- Threaded communications (server side).
- Authentication service (via Facebook or custom strategy).
- Presence service.
- User service.
- Kick mechanism.
- Disconnection detection.
- Live creation of new server/client.
- Binding user connection to several sockets.
- ...

## How to compile

### Requierements

- Qt 5.10
- cmake >= 3.5

### Steps

```
cd hb
cmake --build . --target all
cmake --build . --target install
```
Distribuables will stands in `delivery`

## Documentation

Handled by doxygen.
