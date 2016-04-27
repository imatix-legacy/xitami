# Xitami -- the iMatix Webserver

Xitami is a webserver from iMatix Corporation, based on the iMatix
[SFL (Standard Function Library)](https://github.com/imatix-legacy/sfl)
and [SMT (Simple Multi-Threading
kernel)](https://github.com/imatix-legacy/smt).

It was first released as part of SMT in 1996, and developed regularly
through early 2000. Xitami 2.4d7 was the last "production" release
from the 1990s development cycle, and shows on the iMatix website
through the [last archive.org snapshot of
imatix.com](https://web.archive.org/web/20020124053437/http://www.imatix.com/)
of http://www.imatix.com/ prior to the change to the [new design
in early
2002](https://web.archive.org/web/20020524230546/http://www.imatix.com/).

There was a later "beta" release, [Xitami
2.5b4](https://github.com/imatix/Xitami-25), which appears on the
http://legacy.imatix.com/ website, clearly updated *after* the
change of the main iMatix website.  This is not presented here
because (a) it is [already on the iMatix GitHub
Page](https://github.com/imatix/Xitami-25) and (b) it is not
consistent with the snapshot of the iMatix website shown.

The license for SMT is in [src/license.txt](src/license.txt).  Briefly
it allows usage under the GNU General Public License, the Perl Artistic
License, or with a advertising clause.  See [src/license.txt](src/license.txt)
for details.

This repository contains the Xitami source, binaries,and documentation
released in a stand alone version, retrieved from:

*  http://legacy.imatix.com/pub/xitami

*  http://legacy.imatix.com/html/xitami

on 2016-04-28.

See the [documentation](https://imatix-legacy.github.io/xitami/) for
more details on Xitami 2.4d7.  There is also the [website from
Xitami 2.5b4](https://imatix-legacy.github.io/xitami/25b4/) in a
subirectory for reference, and the source [Xitami
2.5b4](https://github.com/imatix/Xitami-25) can be seen on the
https://github.com/imatix account.

## `pub`

The `pub` directory contains the released artefacts (binaries, source
archives, etc) which are still retrievable; if older releases artefacts
are found they may be added later.  Due to their small size (well under
1MB each), and the fact that development ceased many years ago (so there
will not be growth in the archive), these are added directly into the
git repository.

This directory includes releases before and after the Xitami 2.4d7 presented.

## `src`

The `src` directory was created from the unpacked contents of
`pub/suni24d7.tgz`, for ease of reference.  To this the `doc`
directory was created from `xdoc24d7.zip`.

See the [src/xibuild](src/xibuild) for an overview of how to build
the source: it will automate building
[SFL](https://github.com/imatix-legacy/sfl) and
[SMT](https://github.com/imatix-legacy/smt/), including Xitami, as
well as some example programs.

The build scripts were built with
[otto](https://github.com/imatix-legacy/otto) from
[src/buildsmt.txt](src/buildsmt.txt).  It also needs
[libero](https://github.com/imatix-legacy/libero) if you want to
rebuild the state machines, and 
[htmlpp](https://github.com/imatix-legacy/htmlpp) if you want to 
rebuild the documentation.

## `website`

The `website` directory contains the *rendered* documentation.  The
documentation was taken from `src/webpages/xitami`, supplemented by
the images that it references from `src/webpages/images` -- with the 
URL of the `IMG SRC` updated to reference the images in the same
directory.

The documentation was built (with `htmlpp`) from a marked up text file,
`src/doc/xitami1.txt`.  In theory it should be possible to rebuild the
documentation to approximately the same state.

The `website/25b4` directory contains the website taken from 
http://legacy.imatix.com/xitami/ -- which had been updated with
Xitami 2.5b4 documentation.
