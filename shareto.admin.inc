<?php

/**
 * @file
 * Administration page for the ShareTo Share Button
 */

/**
 * Menu callback: displays the ShareTo Share Button module settings page.
 *
 * @ingroup forms
 */
function shareto_page_admin_settings() {
	$script = '';

  $locations = array();
  $entity_info = entity_get_info('node');
  $view_modes = $entity_info['view modes'];
  foreach ($view_modes as $name => $info) {
    $locations[$name] = $info['label'];
  }

	$form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display Settings'),
    '#description' => t('These are settings for nodes: the button will be created dynamically for each node using its URL. <br />On the othesr hand, if you only need a block with a fixed URL like your homepage, go to the <a href="@blocks">blocks</a> page to enable and configure the <em>Shareto Button</em> block.', array('@blocks' => url('admin/build/block'))),
  );

	$form['display']['shareto_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display the button on these content types:'),
    '#options' => node_type_get_names(),
    '#default_value' => variable_get('shareto_node_types', array()),
  );

  $form['display']['shareto_node_location'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Display the button in these view modes:'),
    '#options' => $locations + array('link' => t('Node links')),
    '#default_value' => variable_get('shareto_node_location', array('full')),
  );

  $form['display']['shareto_weight'] = array(
     '#type' => 'weight',
     '#title' => t('Weight'),
     '#delta' => 50,
     '#default_value' => variable_get('shareto_weight', '-10'),
     '#description' => t('Heavier items will sink. The default weight -10 will show the button at the top of the node content.'),
  );
  $available_sizes = array(
  	'4'	=> t('Tiny'),
    '3' => t('Small'),
    '2' => t('Medium'),
    '1' => t('Large'),
  );
  $available_styles = array(
    '0' => t('Standard'),
    '1' => t('Mini'),
  );
  $default = array(
		'iconstyle' => 0,
    'count' => 0,
    'size' => 1,  // standard
    'css' => 'margin: 0 1em 1em 1em;float:right',
  );

  $button_settings = variable_get('shareto_button_settings', $default);

  $form['shareto_button_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Button Settings'),
    '#tree' => TRUE, // All the options in this fieldset will be grouped in 1 single variable.
  );
  $form['shareto_button_settings']['iconstyle'] = array(
    '#type' => 'radios',
    '#title' => t('Style'),
    '#options' => $available_styles,
    '#default_value' => $button_settings['iconstyle'],
	  );
  $form['shareto_button_settings']['count'] = array(
    '#type' => 'radios',
    '#title' => t('Include count?'),
    '#options' => array(t('No'), t('Yes')),
    '#default_value' => $button_settings['count'],
  );
  $form['shareto_button_settings']['size'] = array(
    '#type' => 'radios',
    '#title' => t('Size'),
    '#options' => $available_sizes,
    '#default_value' => $button_settings['size'],
  );
  $form['shareto_button_settings']['css'] = array(
    '#type' => 'textfield',
    '#title' => t('Optional wrapper with CSS'),
    '#maxlength' => 256,
    '#default_value' => $button_settings['css'],
    '#description' => t('To help with the layout and placement of the button, it will be rendered by default inside a wrapper: <br />	&lt;div class="wb_sharebutton-wrapper"&gt;	&lt;/div&gt;<br/>You can enter CSS rules to style this wrapper. By default <em>margin: 0 1em 1em 1em;float:right</em><br />To disable totally the wrapper, input the word <em>nowrapper</em>'),
  );
  return system_settings_form($form);
}

function shareto_block_admin_settings() {
	$form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display Settings'),
    '#description' => t('These are settings for the block. To use the block, go to the <a href="@blocks">blocks</a> page to enable and configure the <em>Shareto Button</em> block.', array('@blocks' => url('admin/structure/block'))),
  );

  $available_sizes = array(
  	'4'	=> t('Tiny'),
    '3' => t('Small'),
    '2' => t('Medium'),
    '1' => t('Large'),
  );
  $available_styles = array(
    '0' => t('Standard'),
    '1' => t('Mini'),
  );

  $default = array(
		'iconstyle_block' => 0,
    'count_block' => 0,
    'size_block' => 1,  // standard
    'css_block' => 'margin: 0 1em 1em 1em;float:right',
  );

  $button_settings = variable_get('shareto_block_button_settings', $default);

  $form['shareto_block_button_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Button Settings'),
    '#tree' => TRUE, // All the options in this fieldset will be grouped in 1 single variable.
  );
  $form['shareto_block_button_settings']['iconstyle_block'] = array(
    '#type' => 'radios',
    '#title' => t('Style'),
    '#options' => $available_styles,
    '#default_value' => $button_settings['iconstyle_block'],
	  );
  $form['shareto_block_button_settings']['count_block'] = array(
    '#type' => 'radios',
    '#title' => t('Include count?'),
    '#options' => array(t('No'), t('Yes')),
    '#default_value' => $button_settings['count_block'],
  );
  $form['shareto_block_button_settings']['size_block'] = array(
    '#type' => 'radios',
    '#title' => t('Size'),
    '#options' => $available_sizes,
    '#default_value' => $button_settings['size_block'],
  );
  $form['shareto_block_button_settings']['css_block'] = array(
    '#type' => 'textfield',
    '#title' => t('Optional wrapper with CSS'),
    '#maxlength' => 256,
    '#default_value' => $button_settings['css_block'],
    '#description' => t('To help with the layout and placement of the button, it will be rendered by default inside a wrapper: <br />	&lt;div class="wb_sharebutton-wrapper"&gt;	&lt;/div&gt;<br/>You can enter CSS rules to style this wrapper. By default <em>margin: 0 1em 1em 1em;float:right</em><br />To disable totally the wrapper, input the word <em>nowrapper</em>'),
  );
  return system_settings_form($form);
}

/*
 * Trim and polish text input fields
*/
function shareto_page_admin_settings_validate($form, &$form_state) {
  $form_state['values']['shareto_button_settings']['css'] = shareto_trim($form_state['values']['shareto_button_settings']['css'], ';');
}

/**
 * Helper function to trim whitespace and make sure to remove
 * the last character if it is a delimiter.
 *
 * @param $list
 *   A string representing a list of items
 * @param $delimiter
 *   A string that contains a delimiter.
 * @return
 *   A whitespace-trimmed string
 *
*/
function shareto_trim($list, $delimiter) {
	$list = trim(check_plain($list));
  if (!empty($list)) {
    if (drupal_substr($list, -1) === $delimiter) {
      $list = drupal_substr($list, 0, -1);
    }
  }
	return $list;
}

function shareto_icon_admin_settings() {
  $settings = shareto_icon_settings();
  $form['default_settings'] = array(
    '#type' => 'value',
    '#value' => $settings,
  );
  $form['custom'] = array(
    '#type' => 'checkbox',
    '#title' => t('启用自定义'),
    '#default_value' => isset($settings['custom']) ? $settings['custom'] : NULL,
  );
  $form['prev'] = array(
    '#type' => 'fieldset',
    '#title' => t('前缀'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array(
        'input[name="custom"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['prev']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('启用前缀'),
    '#default_value' => isset($settings['prev_enabled']) ? $settings['prev_enabled'] : NULL,
  );
  $form['prev']['label'] = array(
    '#type' => 'textfield',
    '#title' => t('前缀文本'),
    '#default_value' => isset($settings['prev_label']) ? $settings['prev_label'] : '',
    '#states' => array(
      'visible' => array(
        'input[name="prev[enabled]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['more'] = array(
    '#type' => 'fieldset',
    '#title' => t('更多'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array(
        'input[name="custom"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['more']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('启用更多'),
    '#default_value' => isset($settings['more_enabled']) ? $settings['more_enabled'] : NULL,
  );
  $form['show'] = array(
    '#type' => 'fieldset',
    '#title' => t('显示'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array(
        'input[name="custom"]' => array('checked' => TRUE),
      ),
    ),
  );
  $icons = _shareto_icons();
  if (isset($settings['show'])) {
    foreach ($settings['show'] as $val) {
      if (isset($val['key']) && isset($icons[$val['key']])) {
        $icon = $icons[$val['key']];
        $form['show'][$val['key']] = array(
          'name' => array(
            '#markup' => $icon,
          ),
          'weight' => array(
            '#type' => 'weight',
            '#default_value' => $val['weight'],
            '#delta' => 10,
            '#title_display' => 'invisible',
          ),
          'status' => array(
            '#type' => 'checkbox',
            '#default_value' => $val['status'],
          ),
        );
      }
    }
  }
  foreach ($icons as $key => $name) {
    if (!isset($form['show'][$key])) {
      $form['show'][$key] = array(
        'name' => array(
          '#markup' => $name,
        ),
        'weight' => array(
          '#type' => 'weight',
          '#default_value' => 1000,
          '#delta' => 10,
          '#title_display' => 'invisible',
        ),
        'status' => array(
          '#type' => 'checkbox',
        ),
      );
    }
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('提交')
  );
  $form['#submit'][] = 'shareto_icon_admin_settings_submit';
  return $form;
}

function _shareto_icons() {
  $icons = array();
  foreach (shareto_icons_settings() as $val) {
    if (isset($val['key']) && isset($val['name'])) {
      $icons[$val['key']] = $val['name'];
    }
  }
  return $icons;
}

/**
 * Form or_front_group_settings_form submit handler.
 */
function shareto_icon_admin_settings_submit($form, &$form_state) {
  $settings = $form_state['values']['default_settings'];
  $settings['custom'] = $form_state['values']['custom'];
  $settings['prev_enabled'] = $form_state['values']['prev']['enabled'];
  $settings['prev_label'] = $form_state['values']['prev']['label'];
  $settings['more_enabled'] = $form_state['values']['more']['enabled'];
  $settings['show'] = array();
  $show = $form_state['values']['show'];
  foreach ($show as $key => $value) {
    $show[$key]['key'] = $key;
  }
  usort($show, '_shareto_sort_show');
  foreach ($show as $key => $val) {
    $settings['show'][$key] = array(
      'key' => $val['key'],
      'weight' => $val['weight'],
      'status' => $val['status'],
    );
  }
  variable_set('shareto_icon_settings', serialize($settings));
  drupal_set_message(t('设置成功'));
}

/**
 * Theme form or_front_group_settings_form.
 */
function theme_shareto_icon_admin_settings($variables) {
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form['show']) as $id) {
    $form['show'][$id]['weight']['#attributes']['class'] = array('item-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['show'][$id]['name']),
        drupal_render($form['show'][$id]['weight']),
        drupal_render($form['show'][$id]['status']),
      ),
      'class' => array('draggable'),
    );
  }
  $header = array(t('名称'), t('重量'), t('显示'));
  $table_id = 'show-table';
  $table_output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));
  $form['show']['table'] = array('#markup' => $table_output);
  $output = drupal_render_children($form);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'item-weight');
  return $output;
}

function _shareto_sort_show($a, $b) {
  return $a['weight'] - $b['weight'];
}

function shareto_icons_admin_settings($form, &$form_state) {
  $form['#attributes']['class'][] = 'shareto_icons_admin_settings';
  $settings = shareto_icons_settings();
  $isRebuild = isset($form_state['num']);
  $form_state['num'] = $isRebuild ? $form_state['num'] : (count($settings) > 0 ? count($settings) : 1);
  $real_num = isset($form_state['storage']['remove_ids']) ? $form_state['num'] - count($form_state['storage']['remove_ids']) : $form_state['num'];
  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Icons'),
    '#prefix' => '<div id="fieldset_wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );
  $form['fieldset']['icon'] = array(
    '#prefix' => '<div id="fieldset_icons_wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );
  for ($i = 0; $i < $form_state['num']; $i++) {
    // pass the remove item
    if (isset($form_state['storage']['remove_ids']) && in_array($i, $form_state['storage']['remove_ids'])) {
      continue;
    }
    $form['fieldset']['icon'][$i] = array(
      '#prefix' => '<div class="container-inline icon">',
      '#suffix' => '</div><div class="clearfix"></div>',
      '#tree' => TRUE,
    );
    $form['fieldset']['icon'][$i]['key'] = array(
      '#type' => 'textfield',
      '#title' => t('Icon %num key', array('%num' => $i)),
      '#size' => 20,
    );
    $form['fieldset']['icon'][$i]['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Icon %num name', array('%num' => $i)),
      '#size' => 20,
    );
    if (!$isRebuild && isset($settings[$i])) {
      $form['fieldset']['icon'][$i]['key']['#default_value'] = $settings[$i]['key'];
      $form['fieldset']['icon'][$i]['name']['#default_value'] = $settings[$i]['name'];
    }
    if ($real_num > 1) {
      $form['fieldset']['icon'][$i]['remove'] = array(
        '#type' => 'submit',
        '#name' => 'icons_fieldset_icon_remove'.$i,
        '#value' => t('Remove'),
        '#submit' => array('shareto_icons_admin_settings_remove_submit'),
        '#ajax' => array(
          'callback' => 'shareto_icons_admin_settings_ajax_callback',
          'wrapper' => 'fieldset_icons_wrapper',
          'progress' => array(
            'type' => 'throbber',
            'message' => '',
          ), 
        ),
      );
    }
  }
  $form['fieldset']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => array('shareto_icons_admin_settings_add_submit'),
    '#validate' => array(),
    '#ajax' => array(
      'callback' => 'shareto_icons_admin_settings_ajax_callback',
      'wrapper' => 'fieldset_icons_wrapper',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ), 
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['#submit'][] = 'shareto_icons_admin_settings_submit';
  $form['#attached']['css'][] = drupal_get_path('module', 'shareto').'/shareto.css';
  return $form;
}

/**
 * Submit handler for the "Add" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function shareto_icons_admin_settings_add_submit($form, &$form_state) {
  $form_state['num']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the favourite in it.
 */
function shareto_icons_admin_settings_ajax_callback($form, $form_state) {
  return $form['fieldset']['icon'];
}

/**
 * Submit handler for the "Remove" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function shareto_icons_admin_settings_remove_submit($form, &$form_state) {
  if ($form_state['num'] > 1) {
    $form_state['storage']['remove_ids'][] = $form_state['triggering_element']['#parents'][2];
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for demo_add_more_form.
 */
function shareto_icons_admin_settings_submit($form, &$form_state) {
  $settings = array();
  foreach ($form_state['values']['fieldset']['icon'] as $item) {
    $settings[] = array(
      'key' => $item['key'],
      'name' => $item['name'],
    );
  }
  variable_set('shareto_icons_settings', serialize($settings));
  drupal_set_message(t('已保存'));
}