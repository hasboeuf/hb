[![Build Status](https://travis-ci.org/hasboeuf/hb.svg?branch=master)](https://travis-ci.org/hasboeuf/hb)

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

### HbAuth

#### Overview

HbAuth a set of classes implementing OAuth 2 protocol. For now only Google and Facebook is supported,
the rest will be developped on need. This is designed for a client / server architecture.

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

### Requirements

- Qt 5.12
- cmake >= 3.5

### Steps

Let `<hb>` be where sources are.

Let `<qt>` be where Qt is (e.g.: `/opt/Qt/5.12.2/gcc_64`)

By default Hb is compiled in `Release`,
add `-DCMAKE_BUILD_TYPE=Debug` to the first `cmake` command if you want a debug build.

By default Hb is installed in `<hb>/delivery`,
add `-DCMAKE_INSTALL_PREFIX=<path>` to the first `cmake` command to customize it.

If you don't want to compile samples and unittests,
add `-DHB_MINIMAL_BUILD=ON` to the first `cmake` command.

```
mkdir hb-build
cd hb-build
cmake -DCMAKE_PREFIX_PATH=<qt> <hb>
cmake --build . --target all
cmake --build . --target install
```

Note: in case of error, add `-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON` to the first `cmake` command to generate verbose Makefiles.

## How to integrate

### Requirements

Let `<hb>` be where sources are.

Let `<hb-delivery>` be where Hb has been installed.

Let `<qt>` be where Qt is (e.g.: `/opt/Qt/5.12.2/gcc_64`)

### Steps

As an example, you can compile `HbSample` project in `hb/sample`

```
mkdir sample-build
cd sample-build
cmake \
    -DCMAKE_PREFIX_PATH="<qt>;<hb-delivery>" \
    -DCMAKE_INSTALL_PREFIX=<destdir> \
    <hb>/sample
cmake --build . --target all
cmake --build . --target install

export LD_LIBRARY_PATH=<qt>/lib (if needed)
<destdir>/bin/HbSample
```

## Documentation

Handled by doxygen.
