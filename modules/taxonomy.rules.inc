<?php
/**
 * @file
 * Rules integration for the taxonomy_term module.
 *
 * @addtogroup rules
 *
 * @{
 */

/**
 * Implements hook_rules_file_info() on behalf of the taxonomy module.
 *
 * @see rules_core_modules()
 */
function rules_taxonomy_file_info() {
  return array('modules/taxonomy.eval');
}

/**
 * Implements hook_rules_event_info().
 */
function rules_taxonomy_event_info() {
  $defaults_term = array(
    'group' => t('Taxonomy'),
    'access callback' => 'rules_taxonomy_term_integration_access',
    'module' => 'taxonomy',
    'class' => 'RulesTaxonomyEventHandler',
  );
  $defaults_vocab = array(
    'group' => t('Vocabulary'),
    'access callback' => 'rules_taxonomy_vocabulary_integration_access',
    'module' => 'taxonomy',
  );
  return array(
    'taxonomy_term_insert' => $defaults_term + array(
      'label' => t('After saving a new term'),
      'variables' => array(
        'term' => array('type' => 'taxonomy_term', 'label' => t('created term')),
      ),
    ),
    'taxonomy_term_update' => $defaults_term + array(
      'label' => t('After updating an existing term'),
      'variables' => array(
        'term' => array('type' => 'taxonomy_term', 'label' => t('updated term')),
        'term_unchanged' => array(
          'type' => 'taxonomy_term',
          'label' => t('unchanged term'),
          'handler' => 'rules_events_entity_unchanged',
        ),
      ),
    ),
    'taxonomy_term_presave' => $defaults_term + array(
      'label' => t('Before saving a taxonomy term'),
      'variables' => array(
        'term' => array(
          'type' => 'taxonomy_term',
          'label' => t('saved term'),
          'skip save' => TRUE,
        ),
        'term_unchanged' => array(
          'type' => 'taxonomy_term',
          'label' => t('unchanged term'),
          'handler' => 'rules_events_entity_unchanged',
        ),
      ),
    ),
    'taxonomy_term_delete' => $defaults_term + array(
      'label' => t('After deleting a term'),
      'variables' => array(
        'term' => array('type' => 'taxonomy_term', 'label' => t('deleted term')),
      ),
    ),
    'taxonomy_vocabulary_insert' => $defaults_vocab + array(
      'label' => t('After saving a new vocabulary'),
      'variables' => array(
        'vocabulary' => array('type' => 'taxonomy_vocabulary', 'label' => t('created vocabulary')),
      ),
    ),
    'taxonomy_vocabulary_update' => $defaults_vocab + array(
      'label' => t('After updating an existing vocabulary'),
      'variables' => array(
        'vocabulary' => array(
          'type' => 'taxonomy_vocabulary',
          'label' => t('updated vocabulary'),
        ),
        'vocabulary_unchanged' => array(
          'type' => 'taxonomy_vocabulary',
          'label' => t('unchanged vocabulary'),
          'handler' => 'rules_events_entity_unchanged',
        ),
      ),
    ),
    'taxonomy_vocabulary_presave' => $defaults_vocab + array(
      'label' => t('Before saving a vocabulary'),
      'variables' => array(
        'vocabulary' => array(
          'type' => 'taxonomy_vocabulary',
          'label' => t('saved vocabulary'),
          'skip save' => TRUE,
        ),
        'vocabulary_unchanged' => array(
          'type' => 'taxonomy_vocabulary',
          'label' => t('unchanged vocabulary'),
          'handler' => 'rules_events_entity_unchanged',
        ),
      ),
    ),
    'taxonomy_vocabulary_delete' => $defaults_vocab + array(
      'label' => t('After deleting a vocabulary'),
      'variables' => array(
        'vocabulary' => array(
          'type' => 'taxonomy_vocabulary',
          'label' => t('deleted vocabulary'),
        ),
      ),
    ),
  );
}

/**
 * Taxonomy term integration access callback.
 */
function rules_taxonomy_term_integration_access($type, $name) {
  if ($type == 'event' || $type == 'condition') {
    return entity_plus_access('view', 'taxonomy_term');
  }
}

/**
 * Taxonomy vocabulary integration access callback.
 */
function rules_taxonomy_vocabulary_integration_access($type, $name) {
  if ($type == 'event' || $type == 'condition') {
    //@todo This will always return FALSE, but it was the same in D7?.
    return entity_plus_access('view', 'taxonomy_vocabulary');
  }
}

/**
 * Event handler support taxonomy bundle event settings.
 */
class RulesTaxonomyEventHandler extends RulesEventHandlerEntityBundle {

  /**
   * Returns the label to use for the bundle property.
   *
   * @return string
   *   The label to use for the bundle property.
   */
  protected function getBundlePropertyLabel() {
    return t('vocabulary');
  }

}

/**
 * Implements hook_rules_category_info() on behalf of the node module.
 */
function rules_taxonomy_category_info() {
  return array(
    'vocabulary' => array(
      'label' => t('Vocabulary'),
      'equals group' => t('Vocabulary'),
    ),
  );
}

/**
 * Implements hook_rules_action_info() on behalf of the taxonomy module.
 *
 * @see rules_core_modules()
 */
function rules_taxonomy_action_info() {
  $return['vocabulary_fetch'] = array(
    'label' => t('Fetch vocabulary by machine name'),
    'parameter' => array(
      'id' => array('type' => 'token', 'label' => t('Machine name')),
    ),
    'provides' => array(
      'vocabulary_fetched' => array('type' => 'taxonomy_vocabulary', 'label' => t('Fetched vocabulary')),
    ),
    'category' => 'vocabulary',
    'group' => t('Vocabulary'),
    'base' => 'rules_action_vocabulary_fetch',
    'callbacks' => array(
      'access' => 'rules_action_vocabulary_createfetch_access',
    ),
  );

  $return['vocabulary_create'] = array(
    'label' => t('Create a new vocabularity'),
    'parameter' => array(
      'machine_name' => array(
        'type' => 'token',
        'label' => t('Vocabulary machine name'),
        'description' => 'A unique machine-readable name. Can only contain lowercase letters, numbers, and underscores.',
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('Name'),
        'description' => t('The name of the vocabulary'),
      ),
      'description' => array(
        'type' => 'text',
        'label' => t('Description'),
      ),
    ),
    'provides' => array(
      'vocabulary_created' => array(
        'type' => 'taxonomy_vocabulary',
        'label' => t('Created vocabulary'),
        'save' => TRUE,
      ),
    ),
    'group' => t('Vocabulary'),
    'base' => 'rules_action_vocabulary_create',
    'callbacks' => array(
      'access' => 'rules_action_vocabulary_createfetch_access',
    ),
  );

  $return['vocabulary_save'] = array(
    'label' => t('Save vocabulary'),
    'parameter' => array(
      'data' => array(
        'type' => 'taxonomy_vocabulary',
        'label' => t('Taxonomy Vocabulary'),
        'description' => t('Specifies the vocabulary, which should be saved permanently.'),
        'restriction' => 'selector',
        'wrapped' => TRUE,
      ),
      'immediate' => array(
        'type' => 'boolean',
        'label' => t('Force saving immediately'),
        'description' => t('Usually saving is postponed till the end of the evaluation, so that multiple saves can be fold into one. If this set, saving is forced to happen immediately.'),
        'default value' => FALSE,
        'optional' => TRUE,
        'restriction' => 'input',
      ),
    ),
    'group' => t('Vocabulary'),
    'base' => 'rules_action_vocabulary_save',
    'callbacks' => array(
      'access' => 'rules_action_vocabulary_createfetch_access',
    ),
  );

  $return['vocabulary_delete'] = array(
    'label' => t('Delete vocabulary'),
    'parameter' => array(
      'data' => array(
        'type' => 'taxonomy_vocabulary',
        'label' => t('Vocabulary'),
        'description' => t('Specifies the vocabulary, which should be deleted permanently.'),
        'restriction' => 'selector',
        'wrapped' => TRUE,
      ),
    ),
    'group' => t('Vocabulary'),
    'base' => 'rules_action_vocabulary_delete',
    'callbacks' => array(
      'access' => 'rules_action_vocabulary_createfetch_access',
  ),
);

  return $return;

}

/**
 * Custom access callback for data create and fetch action.
 */
function rules_action_vocabulary_createfetch_access(RulesAbstractPlugin $element) {
  $op = $element->getElementName();
  if ($op == 'vocabulary_create' || $op == 'vocabulary_save' || $op == 'vocabulary_delete') {
    return user_access('administer taxonomy');
  }
  return TRUE;
}

/**
 * @} End of "addtogroup rules"
 */
