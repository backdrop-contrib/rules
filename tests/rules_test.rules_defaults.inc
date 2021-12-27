<?php
/**
 * @file
 * Includes Rules integration provided by the Rules Test module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rules_test_default_rules_configuration() {
  $rule = rules_reaction_rule();
  $rule->label = 'example default rule';
  // Add rules tags.
  $rule->tags = array('Admin', 'Tag2');
  $rule->active = FALSE;
  $rule->event('node_update')
    ->condition(rules_condition('data_is', array('data:select' => 'node:status', 'value' => TRUE))->negate())
    ->condition('data_is', array('data:select' => 'node:type', 'value' => 'page'))
    ->action('backdrop_message', array('message' => 'A node has been updated.'));

  $configs['rules_test_default_1'] = $rule;

  $action_set = rules_action_set(array('node' => array('type' => 'node', 'label' => 'Content')));
  $action_set->action('node_publish');
  $configs['rules_test_action_set'] = $action_set;

  // An action set used to test merging term parents.
  $configs['rules_retrieve_term_parents'] = rules_import('{ "rules_retrieve_term_parents" : {
    "LABEL" : "Retrieve term parents",
    "PLUGIN" : "action set",
    "REQUIRES" : [ "rules" ],
    "USES VARIABLES" : {
      "terms" : { "label" : "Terms", "type" : "list\u003ctaxonomy_term\u003e" },
      "term_parents" : {
        "label" : "Term parents",
        "type" : "list\u003ctaxonomy_term\u003e",
        "parameter" : false
      }
    },
    "ACTION SET" : [
      { "LOOP" : {
          "USING" : { "list" : [ "terms" ] },
          "ITEM" : { "current_term" : "Current term" },
          "DO" : [
            { "LOOP" : {
                "USING" : { "list" : [ "current-term:parent" ] },
                "ITEM" : { "current_parent" : "Current parent" },
                "DO" : [
                  { "list_add" : {
                      "list" : [ "term-parents" ],
                      "item" : [ "current-parent" ],
                      "unique" : 1
                    }
                  }
                ]
              }
            }
          ]
        }
      }
    ],
    "PROVIDES VARIABLES" : [ "term_parents" ]
  }
}');

  return $configs;
}
