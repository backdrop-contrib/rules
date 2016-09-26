# Rules

This module is an incomplete port to Backdrop of the Drupal 
contributed module Rules version 7.x-2.9

The Rules module allows site administrators to define conditionally executed
actions based on occurring events (known as reactive or ECA rules).

The Drupal version of Rules makes extensive use of classes and functions
provided by the Drupal contributed module Entity API. Because Backdrop
includes an entity module in core, the required additional elements have
been integrated within this port of Rules for Backdrop, placing them in the
includes folder with file name prefix ext.

Because of this significant difference it will not be possible to upgrade
Rules directly from a Drupal 7 to a Backdrop installation, however it should
be possible to export rules from Drupal and import them into Backdrop.


## Status

This port to Backdrop is not yet complete.


## Installation

Install this module using the official Backdrop CMS instructions at
https://backdropcms.org/guide/modules

Rules has four component modules, each with separate activation:
  + Rules
  + Rules Scheduler
  + Rules UI
  + Rules translation - for internationalization


Then visit the configuration page at Administration >
Configuration > Category > Rules (admin/config/category/rules)
and enter the required information.

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

### For Drupal:

  - Wolfgang Ziegler (fago) (lead maintainer)
  - Klaus Purer (klausi)

### Port to Backdrop:

  - Graham Oliver github.com/Graham-72


## Acknowledgement

This port to Backdrop would not, of course, be possible without
all the work done by the developers and maintainers of the Drupal module.


## Credits

The Drupal 7 project has been sponsored by drunomics, epiqo
and Google Summer of Code.

