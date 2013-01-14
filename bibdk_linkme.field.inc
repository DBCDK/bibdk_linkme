<?php
/**
 * Implements hook_field_info().
 */
function bibdk_linkme_field_info() {
  return array(
    'bibdk_linkme_permalink' => array(
      'label' => t('Permalink.'),
      'description' => t('Linkme formatted permalink.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'bibdk_linkme_permalink_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function bibdk_linkme_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][] = array(
      'link' => bibdk_linkme_generate_permalink($id),
    );
  }
}


/**
 * Implements hook_field_formatter_info().
 */
function bibdk_linkme_field_formatter_info() {
  return array(
    'bibdk_linkme_permalink_default' => array(
      'label' => t('Default'),
      'field types' => array(
        'bibdk_linkme_permalink',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function bibdk_linkme_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    $form = drupal_get_form('bibdk_linkme_button_form_element', $item['link']);
    $element[$delta]['#markup'] = theme('bibdk_linkme_button', array('link_text' => t('Get permalink'), 'path' => $item['link'], 'query' => array(), 'link_attributes' => array(), 'link_form' => $form));
  }
  return $element;
}

function bibdk_linkme_button_form_element($form, &$form_state, $path){
 $form = array();
 $form['link'] = array(
    '#type' => 'textfield',
    '#default_value' => $path,
   //'#disabled' => true,
 );


  return $form;
}
