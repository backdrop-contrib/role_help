<?php
/**
 * @file
 * Contains admin callbacks for the Role help module.
 */

/**
 * Return the admin listing of all roles with detailed help text.
 *
 * Used on admin/people/role-help page.
 */
function role_help_admin_page() {
  $header = t('All roles with detailed help text are listed below.');
  $roles_info = db_query("
    SELECT role, help
    FROM {role_help}
    WHERE help <> ''
    AND help IS NOT NULL
    ORDER BY role")
    ->fetchAllKeyed();
  return _role_help_role_list_output($header, $roles_info);
}
