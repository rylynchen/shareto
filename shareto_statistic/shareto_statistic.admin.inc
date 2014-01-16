<?php

function shareto_statistic_admin_settings() {
	$form['shareto_statistic_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('开启统计'),
    '#default_value' => variable_get('shareto_statistic_enabled', NULL),
  );
  return system_settings_form($form);
}