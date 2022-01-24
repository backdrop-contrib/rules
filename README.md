# Rules

The Rules module allows site administrators to define conditionally executed
actions based on occurring events (known as reactive or ECA rules).

### Example use cases

 - Build flexible content publishing workflows changes
 - Send customized mails to notify your users about important
 - Create custom redirections, system messages, breadcrumbs, ...
 - Build an eCommerce store using Ubercart

And many more...

### Features

 - Obviously, you may use reaction rules to react upon any event with custom conditions and actions.
 - Allows functionality to be re-used via components.
 - Flexible scheduling system that allows scheduling any component / action.
 - Users can share their customizations by using the built-in import/export feature.
 - Modular input evaluation system.
 - The module has been developed with site performance in mind, so it makes use of caching routines to speed up rule evaluation.
 - Rules 2.x features improved APIs, a new admin UI, support for all entity types, parameter configuration via simple data selection (i.e. just pass node:author as argument) and much more.

## Installation

Install Entity Plus, Entity UI, and Entity Tokens and this module using the [official Backdrop CMS instructions](https://backdropcms.org/guide/modules).

If you will be upgrading a site from Drupal 7, you should [install stub modules](https://github.com/backdrop-contrib/rules/wiki/Upgrading-Rules-from-Drupal-7) in your D7 installation before starting the upgrade process.

Rules has four component modules, each with separate activation:
  + Rules
  + Rules Scheduler
  + Rules UI
  + Rules translation - for internationalization

Then visit the configuration page at **Administration >
Configuration > Category > Rules** (**admin/config/category/rules**)
and enter the required information.

## Documentation

Additional documentation is located in [the Wiki](https://github.com/backdrop-contrib/rules/wiki).

## Current Maintainers

- [Graham Oliver](https://github.com/Graham-72)
- [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org)
- [Robert J. Lang](https://github.com/bugfolder)
- [Alejandro Cremaschi](https://github.com/argiepiano)
- Seeking additional maintainers

## Credits

### Port to Backdrop:
- [Graham Oliver](https://github.com/Graham-72)
- Other contributors:
  - [Docwilmot](https://github.com/docwilmot)
  - [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org)
  - [Herb](https://github.com/herbdool/)

### Drupal:
  - Wolfgang Ziegler (fago) (lead maintainer)
  - Klaus Purer (klausi)
  - The Drupal 7 project has been sponsored by drunomics, epiqo,
    and Google Summer of Code.

## License

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.
