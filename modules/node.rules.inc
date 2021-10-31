<?php

/**
 * @file rules integration for the node module
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_category_info() on behalf of the node module.
 */
function rules_node_category_info() {
  return array(
    'node' => array(
      'label' => t('Node'),
      'equals group' => t('Node'),
    ),
  );
}

/**
 * Implements hook_rules_file_info() on behalf of the node module.
 */
function rules_node_file_info() {
  return array('modules/node.eval');
}

/**
 * Implements hook_rules_event_info() on behalf of the node module.
 */
function rules_node_event_info() {
  $items = array(
    'node_insert' => array(
      'label' => t('After saving new content'),
      'category' => 'node',
      'variables' => rules_events_node_variables(t('created content')),
      'access callback' => 'rules_node_integration_access',
      'class' => 'RulesNodeEventHandler',
    ),
    'node_update' => array(
      'label' => t('After updating existing content'),
      'category' => 'node',
      'variables' => rules_events_node_variables(t('updated content'), TRUE),
      'access callback' => 'rules_node_integration_access',
      'class' => 'RulesNodeEventHandler',
    ),
    'node_presave' => array(
      'label' => t('Before saving content'),
      'category' => 'node',
      'variables' => rules_events_node_variables(t('saved content'), TRUE),
      'access callback' => 'rules_node_integration_access',
      'class' => 'RulesNodeEventHandler',
    ),
    'node_view' => array(
      'label' => t('Content is viewed'),
      'category' => 'node',
      'help' => t("Note that if backdrop's page cache is enabled, this event won't be generated for pages served from cache."),
      'variables' => rules_events_node_variables(t('viewed content')) + array(
        'view_mode' => array(
          'type' => 'text',
          'label' => t('view mode'),
          'options list' => 'rules_get_entity_view_modes',
          // Add the entity-type for the options list callback.
          'options list entity type' => 'node',
        ),
      ),
      'access callback' => 'rules_node_integration_access',
      'class' => 'RulesNodeEventHandler',
    ),
    'node_delete' => array(
      'label' => t('After deleting content'),
      'category' => 'node',
      'variables' => rules_events_node_variables(t('deleted content')),
      'access callback' => 'rules_node_integration_access',
      'class' => 'RulesNodeEventHandler',
    ),
  );
  // Specify that on presave the node is saved anyway.
  $items['node_presave']['variables']['node']['skip save'] = TRUE;
  return $items;
}

/**
 * Returns some parameter suitable for using it with a node
 */
function rules_events_node_variables($node_label, $update = FALSE) {
  $args = array(
    'node' => array('type' => 'node', 'label' => $node_label),
  );
  if ($update) {
    $args += array(
      'node_unchanged' => array(
        'type' => 'node',
        'label' => t('unchanged content'),
        'handler' => 'rules_events_entity_unchanged',
      ),
    );
  }
  return $args;
}

/**
 * Implements hook_rules_action_info() on behalf of the node module.
 */
function rules_node_action_info() {
  $defaults = array(
    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Content'),
        'save' => TRUE,
      ),
    ),
    'category' => 'node',
    'access callback' => 'rules_node_admin_access',
    'group' => t('Content'),
  );
  $items['node_publish'] = $defaults + array(
    'label' => t('Publish content'),
    'base' => 'rules_action_node_publish',
  );
  $items['node_unpublish'] = $defaults + array(
    'label' => t('Unpublish content'),
    'base' => 'rules_action_node_unpublish',
  );
  $items['node_make_sticky'] = $defaults + array(
    'label' => t('Make content sticky'),
    'base' => 'rules_action_node_make_sticky',
  );
  $items['node_make_unsticky'] = $defaults + array(
    'label' => t('Make content unsticky'),
    'base' => 'rules_action_node_make_unsticky',
  );
  $items['node_promote'] = $defaults + array(
    'label' => t('Promote content'),
    'base' => 'rules_action_node_promote',
  );
  $items['node_unpromote'] = $defaults + array(
    'label' => t('Unpromote content'),
    'base' => 'rules_action_node_unpromote',
  );

  return $items;
}

/**
 * Node integration access callback.
 */
function rules_node_integration_access($type, $name) {
  if ($type == 'event' || $type == 'condition') {
    return entity_plus_access('view', 'node');
  }
}

/**
 * Node integration admin access callback.
 */
function rules_node_admin_access() {
  return user_access('administer nodes');
}


/**
 * Event handler support node bundle event settings.
 */
class RulesNodeEventHandler extends RulesEventHandlerEntityBundle {

  /**
   * Returns the label to use for the bundle property.
   *
   * @return string
   */
  protected function getBundlePropertyLabel() {
    return t('type');
  }
}

/**
 * @}
 */
