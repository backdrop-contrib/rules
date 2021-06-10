# Rules

This module is a port to Backdrop of the Drupal 
contributed module Rules version 7.x-2.9

The Rules module allows site administrators to define conditionally executed
actions based on occurring events (known as reactive or ECA rules).

The Drupal version of Rules makes extensive use of classes and functions
provided by the Drupal contributed module Entity API. Backdrop
includes an entity module in core but this does not provide all the required
functions. These are now available in the Entity Plus contributed module
which is requirement.

At the moment it may not be possible to upgrade Rules directly from a 
Drupal 7 to a Backdrop installation, however it should be possible 
to export rules from Drupal and import them into Backdrop.


## Status

This port to Backdrop is in active use and reported issues are being addressed.


## Installation

Install this module using the official Backdrop CMS instructions at
https://backdropcms.org/guide/modules.

Also install the required Entity Plus module.

Rules has four component modules, each with separate activation:
  + Rules
  + Rules Scheduler
  + Rules UI
  + Rules translation - for internationalization


Then visit the configuration page at Administration >
Configuration > Category > Rules (admin/config/category/rules)
and enter the required information.

## Documentation

Additional documentation is located in [the Wiki](https://github.com/backdrop-contrib/rules/wiki).

## Debug Information

An administrative setting enables debug information to be shown when 
rules are evaluated and is visible for users having the permission 
'Access the Rules debug log'. It is displayed in a pre-defined custom
block 'Rules Log' which the site administrator must configure in the
layout by adding it to their preferred region (e.g. the footer). When doing
this the administrator should also set the Visibility condition for this
block to be 'User: Permission  --  Access the Rules debug log'.

There is also an administrative option to include this Log debug 
information in the site's system log along with other 
notifications, warnings and error reports.

## Tests

There are six inbuilt tests:

  + Reaction Rules  -  Tests triggering reactive rules.

  + Rules Core Integration  -  Tests provided integration for backdrop core.

  + Rules Data test  -  Tests rules data saving and type matching.

  + Rules Engine tests - Test using the rules API to create and evaluate rules.

  + Rules event dispatchers  -  Tests event dispatcher functionality.

  + Rules invocation enabled  -  Tests that Rules events are enabled during
    menu item loads.


## License

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

## Current Maintainers

- Graham Oliver github.com/Graham-72

Seeking additional maintainers.

## Acknowledgement

This port to Backdrop would not, of course, be possible without
all the work done by the developers and maintainers of the Drupal module.


## Credits

### For Drupal:

  - Wolfgang Ziegler (fago) (lead maintainer)
  - Klaus Purer (klausi)

### Port to Backdrop:

  - Graham Oliver github.com/Graham-72
  - Other contributors : @docwilmot; @laryn; @ herbdool


The Drupal 7 project has been sponsored by drunomics, epiqo
and Google Summer of Code.

