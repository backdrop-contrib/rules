<?php
/**
 * @file
 * Implements rule management and configuration screens.
 */

/**
 * Reaction rules overview.
 */
function rules_admin_reaction_overview($form, &$form_state, $base_path) {
  RulesPluginUI::formDefaults($form, $form_state);

  $conditions = array('plugin' => 'reaction rule', 'active' => TRUE);
  $collapsed = TRUE;
  if (empty($_GET['tag'])) {
    $tag = 0;
  }
  else {
    $tag = $_GET['tag'];
    $conditions['tags'] = array($tag);
    $collapsed = FALSE;
  }
  if (empty($_GET['event'])) {
    $event = 0;
  }
  else {
    $event = $_GET['event'];
    // Filter using a wildcard suffix so configured event names with suffixes
    // are found also.
    $conditions['event'] = $event . '%';
    $collapsed = FALSE;
  }
  $form['help'] = array(
    '#markup' => t('Reaction rules, listed below, react on selected events on the site. Each reaction rule may fire any number of <em>actions</em>, and may have any number of <em>conditions</em> that must be met for the actions to be executed. You can also set up <a href="@url1">components</a> – stand-alone sets of Rules configuration that can be used in Rules and other parts of your site. See <a href="@url2">the online documentation</a> for an introduction on how to use Rules.',
      array('@url1' => url('admin/config/workflow/rules/components'),
            '@url2' => rules_external_help('rules'))),
  );

  $form['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter'),
    '#collapsible' => TRUE,
  );
  $form['filter']['#id'] = 'rules-filter-form';
  $form['filter']['#attached']['css'][] = backdrop_get_path('module', 'rules') . '/ui/rules.ui.css';
  $form['filter']['event'] = array(
    '#type' => 'select',
    '#title' => t('Filter by event'),
    '#options' => array(0 => t('<All>')) + RulesPluginUI::getOptions('event'),
    '#default_value' => $event,
  );
  $form['filter']['tag'] = array(
    '#type' => 'select',
    '#title' => t('Filter by tag'),
    '#options' => array(0 => t('<All>')) + RulesPluginUI::getTags(),
    '#default_value' => $tag,
  );
  $form['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#name' => '', // prevent from showing up in $_GET.
  );

  $options = array('show plugin' => FALSE, 'base path' => $base_path);
  $form['active'] = rules_ui()->overviewTable($conditions, $options);
  $form['active']['#caption'] = t('Active rules');
  $form['active']['#empty'] = t('There are no active rules. <a href="!url">Add new rule</a>.', array('!url' => url('admin/config/workflow/rules/reaction/add')));

  $conditions['active'] = FALSE;
  $form['inactive'] = rules_ui()->overviewTable($conditions, $options);
  $form['inactive']['#caption'] = t('Inactive rules');
  $form['inactive']['#empty'] = t('There are no inactive rules.');

  $form['filter']['#collapsed'] = $collapsed;
  $form['#submit'][] = 'rules_form_submit_rebuild';
  $form['#method'] = 'get';
  return $form;
}

/**
 * Components overview.
 */
function rules_admin_components_overview($form, &$form_state, $base_path) {
  RulesPluginUI::formDefaults($form, $form_state);

  $collapsed = TRUE;
  if (empty($_GET['tag'])) {
    $tag = 0;
  }
  else {
    $tag = $_GET['tag'];
    $conditions['tags'] = array($tag);
    $collapsed = FALSE;
  }
  if (empty($_GET['plugin'])) {
    // Get the plugin name usable as component.
    $conditions['plugin'] = array_keys(rules_filter_array(rules_fetch_data('plugin_info'), 'component', TRUE));
    $plugin = 0;
  }
  else {
    $plugin = $_GET['plugin'];
    $conditions['plugin'] = $plugin;
    $collapsed = FALSE;
  }
  $form['help'] = array(
    '#markup' => t('Components are stand-alone sets of Rules configuration that can be used by Rules and other modules on your site. Components are for example useful if you want to use the same conditions, actions or rules in multiple places, or call them from your custom module. You may also export each component separately. See <a href="@url">the online documentation</a> for more information about how to use components.',
      array('@url' => rules_external_help('components'))),
  );
  $form['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter'),
    '#collapsible' => TRUE,
  );
  $form['filter']['#id'] = 'rules-filter-form';
  $form['filter']['#attached']['css'][] = backdrop_get_path('module', 'rules') . '/ui/rules.ui.css';
  $form['filter']['plugin'] = array(
    '#type' => 'select',
    '#title' => t('Filter by plugin'),
    '#options' => array(0 => t('<All>')) + rules_admin_component_options(),
    '#default_value' => $plugin,
  );
  $form['filter']['tag'] = array(
    '#type' => 'select',
    '#title' => t('Filter by tag'),
    '#options' => array(0 => '<All>') + RulesPluginUI::getTags(),
    '#default_value' => $tag,
  );
  $form['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#name' => '', // prevent from showing up in $_GET.
  );

  $form['table'] = RulesPluginUI::overviewTable($conditions, array('hide status op' => TRUE));
  $form['table']['#empty'] = t('There are no rule components.');

  $form['filter']['#collapsed'] = $collapsed;
  $form['#submit'][] = 'rules_form_submit_rebuild';
  $form['#method'] = 'get';
  return $form;
}

/**
 * Rules settings form.
 */
function rules_admin_settings($form, &$form_state) {

  // Present a list of available path cleaning callbacks.
  // @see rules_clean_path()
  $options = array(
    'rules_path_clean_path' => t('Path'),
    'rules_path_default_cleaning_method' => t('Rules (built in, deprecated)'),
  );
  $form['path']['rules_path_cleaning_callback'] = array(
    '#type' => 'select',
    '#title' => t('URL path cleaning method'),
    '#description' => t('Choose the path cleaning method to be applied when generating URL path aliases.'),
    '#default_value' => config_get('rules.settings','rules_path_cleaning_callback'),
    '#options' => $options,
  );

  $form['path']['built_in_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Rules (built-in) path cleaning settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="rules_path_cleaning_callback"]' => array('value' => 'rules_path_default_cleaning_method'),
      ),
    ),
  );
  $form['path']['built_in_settings']['rules_path_transliteration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transliteration'),
    '#description' => t('Check to transliterate aliases.'),
    '#default_value' => config_get('rules.settings','rules_path_transliteration'),
  );
  $form['path']['built_in_settings']['rules_path_replacement_char'] = array(
    '#type' => 'textfield',
    '#title' => t('Replacement character'),
    '#description' => t('Enter the replacement character for non-ASCII characters in the path.'),
    '#default_value' => config_get('rules.settings','rules_path_replacement_char'),
    '#size' => 1,
  );
  $form['path']['built_in_settings']['rules_path_regex'] = array(
    '#type' => 'textfield',
    '#title' => t('Clean path regex'),
    '#description' => t('Enter the regex for the characters to be kept, e.g., "/[^a-zA-Z0-9\-_]+/".'),
    '#default_value' => config_get('rules.settings','rules_path_regex'),
  );
  $form['path']['built_in_settings']['rules_path_lower_case'] = array(
    '#type' => 'checkbox',
    '#title' => t('Lower case'),
    '#description' => t('Check to convert all characters in the path to lower case.'),
    '#default_value' => config_get('rules.settings','rules_path_lower_case'),
  );

  $form['path']['path_settings'] = array(
    '#type' => 'fieldset',
    '#description' => t("Path module's URL path cleaning method can be configured at <a href='!url'>admin/config/urls/path/patterns/settings</a>.", array('!url' => url('admin/config/urls/path/patterns/settings'))),
    '#states' => array(
      'visible' => array(
        ':input[name="rules_path_cleaning_callback"]' => array('value' => 'rules_path_clean_path'),
      ),
    ),
  );

  $form['rules_log_errors'] = array(
    '#type' => 'radios',
    '#title' => t('Logging of Rules evaluation errors'),
    '#options' => array(
      RulesLog::WARN => t('Log all warnings and errors'),
      RulesLog::ERROR => t('Log errors only'),
    ),
    '#default_value' => config_get('rules.settings','rules_log_errors'),
    '#description' => t('Evaluations errors are logged to the system log.'),
  );

  $form['debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debugging'),
  );
  $form['debug']['rules_debug_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log debug information to the system log'),
    '#default_value' => config_get('rules.settings','rules_debug_log'),
  );
  $form['debug']['rules_debug'] = array(
    '#type' => 'radios',
    '#title' => t('Show debug information'),
    '#default_value' => config_get('rules.settings','rules_debug'),
    '#options' => array(
      0 => t('Never'),
      RulesLog::WARN => t('In case of errors'),
      RulesLog::INFO => t('Always'),
    ),
    '#description' => t('Debug information is only shown when rules are evaluated and is visible for users having the permission <a href="!url">%link</a>.', array('%link' => t('Access the Rules debug log'), '!url' => url('admin/config/people/permissions', array('fragment' => 'module-rules')))),
  );

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  // Return the form!
  return $form;
}


// Add a submit function to process config
function rules_admin_settings_submit($form, &$form_state) {
  $config = config('rules.settings');
  $config->set('rules_path_cleaning_callback', $form_state['values']['rules_path_cleaning_callback']);
  $config->set('rules_path_transliteration', $form_state['values']['rules_path_transliteration']);
  $config->set('rules_path_replacement_char', $form_state['values']['rules_path_replacement_char']);
  $config->set('rules_path_regex', $form_state['values']['rules_path_regex']);
  $config->set('rules_path_lower_case', $form_state['values']['rules_path_lower_case']);
  $config->set('rules_log_errors', $form_state['values']['rules_log_errors']);
  $config->set('rules_debug_log', $form_state['values']['rules_debug_log']);
  $config->set('rules_debug', $form_state['values']['rules_debug']);
  $config->save();

  backdrop_set_message(t('The configuration options have been saved.'));
}


/**
 * Advanced settings form.
 */
function rules_admin_settings_advanced($form, &$form_state) {

  $form['integrity'] = array(
    '#type' => 'fieldset',
    '#title' => t('Integrity'),
    '#description' => t('Rules checks the integrity of your configurations to discover and exclude broken configurations from evaluation.'),
  );
  $form['integrity']['start_integrity_check'] = array(
    '#type' => 'submit',
    '#value' => t('Recheck integrity'),
    '#submit' => array('rules_admin_settings_integrity_check_submit'),
  );
  $form['cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache'),
    '#description' => t('Rules caches information about available actions, conditions and data types. Additionally all components and reaction rules are cached for efficient evaluation.'),
  );
  $form['cache']['rebuild_rules_cache'] = array(
    '#type' => 'submit',
    '#value' => t("Rebuild Rules' cache"),
    '#weight' => 2,
    '#submit' => array('rules_admin_settings_cache_rebuild_submit'),
  );
  return $form;
}

/**
 * Form submit callback to check the integrity of all configurations.
 */
function rules_admin_settings_integrity_check_submit($form, &$form_state) {
  $start = microtime(TRUE);
  $count = 0;
  $rules_configs = rules_config_load_multiple(FALSE);
  foreach ($rules_configs as $rules_config) {
    rules_config_update_dirty_flag($rules_config, TRUE, TRUE);
    if ($rules_config->dirty) {
      $count++;
      $variables = array(
        '%label' => $rules_config->label(),
        '%name' => $rules_config->name,
        '@plugin' => $rules_config->plugin(),
        '!uri'=> url(RulesPluginUI::path($rules_config->name)),
      );
      backdrop_set_message(t('The @plugin <a href="!uri">%label (%name)</a> fails the integrity check and cannot be executed.', $variables), 'error');
    }

  }
  backdrop_set_message(t('Integrity of %count configurations checked in %duration seconds. %count_failed broken configurations found.', array(
    '%count' => count($rules_configs),
    '%count_failed' => $count,
    '%duration' => round(microtime(TRUE) - $start, 2),
  )));
}

/**
 * Form submit callback: Rebuild the Rules' cache.
 */
function rules_admin_settings_cache_rebuild_submit($form, &$form_state) {
  $start = microtime(TRUE);
  rules_clear_cache();
  // Manually trigger cache rebuilding of all caches.
  rules_get_cache();
  _rules_rebuild_component_cache();
  RulesEventSet::rebuildEventCache();
  backdrop_set_message(t('Rules cache rebuilt in %duration seconds.', array(
    '%duration' => round(microtime(TRUE) - $start, 2),
  )));
}

/**
 * Add reaction rules form.
 */
function rules_admin_add_reaction_rule($form, &$form_state, $base_path) {
  RulesPluginUI::formDefaults($form, $form_state);

  $rules_config = isset($form_state['rules_config']) ? $form_state['rules_config'] : rules_reaction_rule();
  $rules_config->form($form, $form_state, array('show settings' => TRUE, 'button' => TRUE));

  $form['settings']['#collapsible'] = FALSE;
  $form['settings']['#type'] = 'container';
  $form['settings']['label']['#default_value'] = '';

  // Hide the rule elements stuff for now.
  foreach (array('elements', 'conditions', 'add', 'events') as $key) {
    $form[$key]['#access'] = FALSE;
  }
  foreach (array('active', 'weight') as $key) {
    $form['settings'][$key]['#access'] = FALSE;
  }
  // Incorporate the form to add the first event.
  $form['settings'] += rules_ui_add_event(array(), $form_state, $rules_config, $base_path);
  $form['settings']['event']['#tree'] = FALSE;
  $form['settings']['event_settings']['#tree'] = FALSE;
  unset($form['settings']['help']);

  unset($form['settings']['submit']);
  $form['submit']['#value'] = t('Save');

  $form_state += array('rules_config' => $rules_config);
  $form['#validate'][] = 'rules_ui_add_reaction_rule_validate';
  $form['#validate'][] = 'rules_ui_edit_element_validate';
  $form['#submit'][] = 'rules_ui_add_reaction_rule_submit';
  return $form;
}

/**
 * Form validation callback.
 */
function rules_ui_add_reaction_rule_validate(&$form, &$form_state) {
  rules_ui_add_event_validate($form['settings'], $form_state);
}

/**
 * Form submit callback.
 */
function rules_ui_add_reaction_rule_submit(&$form, &$form_state) {
  rules_ui_add_event_apply($form['settings'], $form_state);
  rules_ui_edit_element_submit($form, $form_state);
}

/**
 * Add component form.
 */
function rules_admin_add_component($form, &$form_state, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  RulesPluginUI::formDefaults($form, $form_state);

  $form['plugin_name'] = array(
    '#type' => 'select',
    '#title' => t('Component plugin'),
    '#options' => rules_admin_component_options(),
    '#description' => t('Choose which kind of component to create. Each component type is described in <a href="@url">the online documentation</a>.',
      array('@url' => rules_external_help('component-types'))),
    '#weight' => -2,
    '#default_value' => isset($form_state['values']['plugin_name']) ? $form_state['values']['plugin_name'] : '',
  );

  if (!isset($form_state['rules_config'])) {
    $form['continue'] = array(
      '#type' => 'submit',
      '#name' => 'continue',
      '#submit' => array('rules_admin_add_component_create_submit'),
      '#value' => t('Continue'),
    );
  }
  else {
    $form['plugin_name']['#disabled'] = TRUE;
    $form_state['rules_config']->form($form, $form_state, array('show settings' => TRUE, 'button' => TRUE, 'init' => TRUE));
    $form['settings']['#collapsible'] = FALSE;
    $form['settings']['#type'] = 'container';
    $form['settings']['label']['#default_value'] = '';
    $form['settings']['#weight'] = -1;

    // Hide the rule elements stuff for now.
    foreach (array('elements', 'negate') as $key) {
      $form[$key]['#access'] = FALSE;
    }
    foreach (array('active', 'weight') as $key) {
      $form['settings'][$key]['#access'] = FALSE;
    }
  }
  return $form;
}

function rules_admin_component_options() {
  $cache = rules_get_cache();
  return rules_extract_property(rules_filter_array($cache['plugin_info'], 'component', TRUE), 'label');
}

/**
 * Submit callback that creates the new component object initially.
 */
function rules_admin_add_component_create_submit($form, &$form_state) {
  $form_state['rules_config'] = rules_plugin_factory($form_state['values']['plugin_name']);
  $form_state['rebuild'] = TRUE;
}

/**
 * Validation callback for adding a component.
 */
function rules_admin_add_component_validate($form, &$form_state) {
  if (isset($form_state['rules_config'])) {
    $form_state['rules_config']->form_validate($form, $form_state);
  }
}

/**
 * Final submit callback for adding a component.
 */
function rules_admin_add_component_submit($form, &$form_state) {
  $rules_config = $form_state['rules_config'];
  $rules_config->form_submit($form, $form_state);
  backdrop_set_message(t('Your changes have been saved.'));
  $form_state['redirect'] = RulesPluginUI::path($rules_config->name);
}
