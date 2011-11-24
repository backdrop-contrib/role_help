<?php
/**
 * @file
 * Contains page callbacks for the Role help module.
 */

/**
 * Menu callback for the role help page.
 *
 * Access control admins are shown all roles.
 */
function role_help_page() {
  if (user_access('administer permissions')) {
    $header = t('You are an access control administrator. All roles with help text are listed below:');

    // The h.help <> '' WHERE clause filters out both NULL and empty text.
    $result = db_query("SELECT name, help FROM {role} r INNER JOIN {role_help} h ON r.rid = h.rid WHERE h.help <> ''");
  }
  else {
    $header = t('Your user account is enabled to do the following on this site:');

    global $user;
    $user_rids = array_keys($user->roles);
    $placeholders = implode(',', array_fill(0, count($user_rids), '%d'));
    $result = db_query("SELECT name, help FROM {role} r INNER JOIN {role_help} h ON r.rid = h.rid WHERE r.rid IN ($placeholders) AND h.help <> '' ORDER BY r.rid", $user_rids );
  }

  $role_help_items = array();
  while ($item = db_fetch_array($result)) {
    $role_help_items[] = theme('role_help_section', $item['name'], $item['help']);
  }
  if (!count($role_help_items)) {
    $header = t('No role help text has been set.');
  }

  $output = "<p>$header</p>";
  $output .= theme('item_list', $role_help_items);

  return $output;
}

/**
 * Display the role help admin settings page.
 *
 * Set the description for the anonymous and authorized users here.
 */
function role_help_admin_settings() {
  $result = db_query('SELECT rid, help FROM {role_help} WHERE rid IN (%d, %d)', 1, 2);
  while ($item = db_fetch_array($result)) {
    $descriptions[$item['rid']] = $item['help'];
  }
  #$form['#submit'] = array('role_help_admin_settings_submit' => array());

  $form['anonymous_help'] = array(
      '#type' => 'textarea',
      '#title' => t('Anonymous user'),
      '#default_value' => $descriptions[1],
      '#description' => t('A description of what an anonymous user can accomplish. You should only set this if anonymous users have rights beyond accessing content. If non-empty, this will be shown to anonymous users on the site help page.'),
    );
  $form['authenticated_help'] = array(
      '#type' => 'textarea',
      '#title' => t('Authenticated user'),
      '#default_value' => $descriptions[2],
      '#description' => t('A description of what an authenticated user can accomplish. If non-empty, this will be shown to authenticated users on the site help page. You should only'),
    );


  $form['role_help_format'] = filter_form(variable_get('role_help_format', FILTER_FORMAT_DEFAULT));
  $form['role_help_format']['#collapsible'] = 0;
  $form['role_help_format']['#collapsed'] = 0;
  $form['role_help_format']['#description'] = 'The input format to use for all role help text.';

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration') );

  return $form;
}

/**
 * Submit function for admin settings form.
 *
 * Save or update text, delete if blanked.
 */
function role_help_admin_settings_submit($form, &$form_state) {
  variable_set('role_help_format', $form_state['values']['format']);

  foreach (array(1 => 'anonymous_help', 2 => 'authenticated_help') as $rid => $role) {
    db_query('DELETE FROM {role_help} WHERE rid = %d', $rid);
    if ($form_state['values'][$role] != '') {
      db_query("INSERT INTO {role_help} (rid, help) VALUES (%d, '%s')", $rid, $form_state['values'][$role]);
    }
  }
  // Rebuild menus so anon users either gain or lose the site help menu item.
  menu_rebuild();

  drupal_set_message(t('The role help settings have been saved.'));
}
