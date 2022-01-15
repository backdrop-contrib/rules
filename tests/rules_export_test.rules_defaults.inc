<?php
/**
 * @file
 * Includes Rules integration provided by the export test module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rules_export_test_default_rules_configuration() {
  $configs['rules_export_test'] = rules_import(_rules_export_test_get_test_export());
  return $configs;
}
