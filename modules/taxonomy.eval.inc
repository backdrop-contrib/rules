<?php

/**
 * @file
 * Contains rules integration for the taxonomy module needed during evaluation.
 *
 * @addtogroup rules
 *
 * @{
 */


 /**
 * Action: Fetch vocabulary.
 */
function rules_action_vocabulary_fetch($id) {
  $vocabulary = taxonomy_vocabulary_load($id);
  if (!$vocabulary) {
    throw new RulesEvaluationException('Unable to load vocabulary with machine name "@id"', array('@id' => $id));
  }
  return array('vocabulary_fetched' => $vocabulary);
}

/**
 * Action: Create vocabulary.
 */
function rules_action_vocabulary_create($machine_name, $name, $description = '') {
  try {
    $vocabulary = new TaxonomyVocabulary();
    $vocabulary->machine_name = $machine_name;
    $vocabulary->name = $name;
    $vocabulary->description = $description;
    return array('vocabulary_created' => $vocabulary);
  }
  catch (EntityMetadataWrapperException $e) {
    throw new RulesEvaluationException('Unable to create vocabulary": ' . $e->getMessage());
  }
}

/**
 * Action: Delete vocabulary.
 */
function rules_action_vocabulary_delete($wrapper, $settings, $state, $element) {
  try {
    $wrapper->delete();
  }
  catch (EntityMetadataWrapperException $e) {
    throw new RulesEvaluationException($e->getMessage(), array(), $element);
  }
}

/**
 * Action: Save vocabulary.
 */
function rules_action_vocabulary_save($wrapper, $immediate, $settings, $state, $element) {
  $state->saveChanges($settings['data:select'], $wrapper, $immediate);
}
