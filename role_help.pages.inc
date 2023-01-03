<?php
/**
 * @file
 * Contains user page callback for the Role help module.
 */

/**
 * Return the user page in the user's profile.
 *
 * Used on user/%/roles page if role_delegation module is not installed.
 */
function role_help_user_page($account) {
  $header = t('%name is enabled for the following roles on this site:',
    array('%name' => $account->name));
  $user_roles = array_values($account->roles);
  $placeholder_data = array();
  $placeholder_vals = array();
  foreach ($user_roles as $role => $user_role) {
    $placeholder_data[] = ':user_role_' . $role;
    $placeholder_vals[':user_role_' . $role] = $user_role;
  }
  $placeholders = implode(',', $placeholder_data);
  $roles_info = db_query("
    SELECT role, help
    FROM {role_help}
    WHERE role IN ($placeholders)
    AND help <> ''
    AND help IS NOT NULL
    ORDER BY role
    ", $placeholder_vals)
    ->fetchAllKeyed();
  return _role_help_role_list_output($header, $roles_info);
}
