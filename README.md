<!---
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
-->

# xtensor Arrow GLib

xtensor Arrow GLib is a xtensor and Apache Arrow integration
library. xtensor Arrow GLib provides C API.

xtensor Arrow GLib supports
[GObject Introspection](https://wiki.gnome.org/Projects/GObjectIntrospection).
It means that you can create language bindings at runtime or compile
time.

For example, you can use xtensor with Apache Arrow from Ruby by
xtensor Arrow GLib,
[red-arrow gem](https://rubygems.org/gems/red-arrow) and
[gobject-introspection gem](https://rubygems.org/gems/gobject-introspection)
with the following code:

```ruby
# Generate bindings at runtime
require "gi"
XtensorArrow = GI.load("xtensor-arrow")

# TODO
```

## Install

You can use packages or build by yourself to install xtensor Arrow
GLib. It's recommended that you use packages.

### Package

There are supported platforms:

  * Debian GNU/Linux Jessie
  * Debian GNU/Linux Stretch
  * Ubuntu 16.04 LTS or later
  * CentOS 7

You can feedback to https://github.com/red-data-tools/arrow-packages
about packages things.

#### Debian GNU/Linux Jessie

Ensure installing `apt-transport-https` package:

```text
% sudo apt update
% sudo apt install -y apt-transport-https
```

You need to add the following apt-lines to
`/etc/apt/sources.list.d/groonga.list`:

```text
deb https://packages.groonga.org/debian/ jessie main
deb-src https://packages.groonga.org/debian/ jessie main
```

Then you need to run the following command lines:

```text
% sudo apt update
% sudo apt install -y --allow-unauthenticated groonga-keyring
% sudo apt update
```

Now you can install xtensor Arrow GLib packages:

```text
% sudo apt install -y libxtensor-arrow-glib-dev
```

#### Debian GNU/Linux Stretch

Ensure installing `apt-transport-https` package:

```text
% sudo apt update
% sudo apt install -y apt-transport-https
```

You need to add the following apt-lines to
`/etc/apt/sources.list.d/groonga.list`:

```text
deb https://packages.groonga.org/debian/ stretch main
deb-src https://packages.groonga.org/debian/ stretch main
```

Then you need to run the following command lines:

```text
% sudo apt update
% sudo apt install -y --allow-unauthenticated groonga-keyring
% sudo apt update
```

Now you can install xtensor Arrow GLib packages:

```text
% sudo apt install -y libxtensor-arrow-glib-dev
```

#### Ubuntu 16.04 LTS or later

You need to add an APT repository:

```text
% sudo apt install -y software-properties-common
% sudo add-apt-repository -y ppa:groonga/ppa
% sudo apt update
```

Now you can install xtensor Arrow GLib packages:

```text
% sudo apt install -y libxtensor-arrow-glib-dev
```

#### CentOS 7

You need to add a Yum repository:

```text
% sudo yum install -y https://packages.groonga.org/centos/groonga-release-1.3.0-1.noarch.rpm
```

Now you can install xtensor arrow GLib packages:

```text
% sudo yum install -y --enablerepo=epel xtensor-arrow-glib-devel
```

### How to build by users

xtensor Arrow GLib users should use released source archive to build
xtensor Arrow GLib:

```text
% wget https://github.com/red-data-tools/xtensor-arrow-glib/releases/download/1.0.0/xtensor-arrow-glib-1.0.0.tar.gz
% tar xf xtensor-arrow-glib-1.0.0.tar.gz
% cd xtensor-arrow-glib-1.0.0
```

You need to install [xtensor](https://github.com/QuantStack/xtensor)
and [Apache Arrow](https://arrow.apache.org/) GLib before you install
xtensor Arrow GLib. See documents about how to install them.

You can build and install xtensor Arrow GLib after you install them:

```text
% ./configure
% make
% sudo make install
```

### How to build by developers

You need to install [xtensor](https://github.com/QuantStack/xtensor)
and [Apache Arrow](https://arrow.apache.org/) GLib before you install
xtensor Arrow GLib. See documents about how to install them.

You need [GTK-Doc](https://www.gtk.org/gtk-doc/) and
[GObject Introspection](https://wiki.gnome.org/Projects/GObjectIntrospection)
to build xtensor Arrow GLib. You can install them by the followings:

On Debian GNU/Linux or Ubuntu:

```text
% sudo apt install -y -V gtk-doc-tools autoconf-archive libgirepository1.0-dev
```

On CentOS 7 or later:

```text
% sudo yum install -y gtk-doc gobject-introspection-devel
```

On macOS with [Homebrew](https://brew.sh/):

```text
% brew install -y gtk-doc gobject-introspection
```

Now, you can build xtensor Arrow GLib:

```text
% ./autogen.sh
% ./configure --enable-gtk-doc
% make
% sudo make install
```

## Usage

You can use xtensor Arrow GLib with C or other languages. If you use
xtensor Arrow GLib with C, you use C API. If you use xtensor Arrow
GLib with other languages, you use GObject Introspection based
bindings.

### C

You can find API reference in the
`/usr/local/share/gtk-doc/html/xtensor-arrow-glib/` directory. If you
specify `--prefix` to `configure`, the directory will be different.

TODO: Examples

### Language bindings

TODO
