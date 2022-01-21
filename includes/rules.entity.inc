<?php
/**
 * @file
 * Provides Rules integration for entities provided via the CRUD API.
 *
 * Rules automatically provides us with actions for CRUD and a suiting entity
 * data type. For events the controller automatically invokes Rules events once
 * Rules is active, so we just have to provide the appropriate info.
 */

/**
 * Default controller for generating Rules integration.
 */
class RulesEntityEventController {

  protected $type, $info;

  public function __construct($type) {
    $this->type = $type;
    $this->info = entity_get_info($type);
  }

  public function eventInfo() {
    $info = $this->info;
    $type = $this->type;

    $label = $info['label'];
    $defaults = array(
      'module' => isset($info['module']) ? $info['module'] : 'entity',
      'group' => $label,
      'access callback' => 'rules_entity_integration_event_access',
    );

    $items[$type . '_insert'] = $defaults + array(
      'label' => t('After saving a new @entity', array('@entity' => backdrop_strtolower($label))),
      'variables' => rules_entity_events_variables($type, t('created @entity', array('@entity' => backdrop_strtolower($label)))),
    );
    $items[$type . '_update'] = $defaults + array(
      'label' => t('After updating an existing @entity', array('@entity' => backdrop_strtolower($label))),
      'variables' => rules_entity_events_variables($type, t('updated @entity', array('@entity' => backdrop_strtolower($label))), TRUE),
    );
    $items[$type . '_presave'] = $defaults + array(
      'label' => t('Before saving a @entity', array('@entity' => backdrop_strtolower($label))),
      'variables' => rules_entity_events_variables($type, t('saved @entity', array('@entity' => backdrop_strtolower($label))), TRUE),
    );
    $items[$type . '_delete'] = $defaults + array(
      'label' => t('After deleting a @entity', array('@entity' => backdrop_strtolower($label))),
      'variables' => rules_entity_events_variables($type, t('deleted @entity', array('@entity' => backdrop_strtolower($label)))),
    );
    if (count($info['view modes'])) {
      $items[$type . '_view'] = $defaults + array(
        'label' => t('@entity is viewed', array('@entity' => $label)),
        'variables' => rules_entity_events_variables($type, t('viewed @entity', array('@entity' => backdrop_strtolower($label)))) + array(
          'view_mode' => array(
            'type' => 'text',
            'label' => t('view mode'),
            'options list' => 'rules_get_entity_view_modes',
             // Add the entity-type for the options list callback.
            'options list entity type' => $type,
          ),
        ),
      );
    }
    // Specify that on presave the entity is saved anyway.
    $items[$type . '_presave']['variables'][$type]['skip save'] = TRUE;
    return $items;
  }

}
