Role Help
======================

The Role Help module allows a site administrator (with the 'administer access
control' permission) to set a summary and help text for each role.

The role help text may be shown to users on a tab in their user account. Only
the role descriptions that a user has access to are shown.

The summaries are shown in the role admin page and in forms that show role
checkboxes.

Installation
------------

- Install this module using [the official Backdrop CMS instruction](  https://backdropcms.org/guide/modules).

- Visit the Roles configuration page under Administration > Configuration >
  User Accounts > Roles (admin/config/people/roles). For each role, select
  Configure Role and enter the summary and help text for the role.

- Also on the Roles configuration page, choose the Help text format.


Differences from Drupal 7
-------------------------

- The Role Help settings admin page has gone away because all settings are in
or accessible from the Role settings page (admin/config/people/roles).

- The D7 version of Role Help provided a list of all roles visible to the user
at help/roles. Backdrop has dropped the Help menu and path. So instead, this
module optionally provides a list of all roles for administrators at
admin/people/roles and provides a list of the user's roles at user/%user/roles.

Documentation
-------------

Additional documentation is located in [the Wiki](https://github.com/backdrop-contrib/foo-project/wiki/Documentation).

Issues
------

Bugs and Feature requests should be reported in [the Issue Queue](https://github.com/backdrop-contrib/foo-project/issues).

Current Maintainers
-------------------

- [Robert J. Lang](https://github.com/bugfolder).

Credits
-------

- Ported to Backdrop CMS by [Robert J. Lang](https://github.com/bugfolder).
- Originally written for Drupal by
  [Joachim Noreiko](https://www.drupal.org/u/joachim).

License
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

