<?php

/**
 * @file
 * This file contains the functions that are required to execute
 * `drush kw-update`.
 */

/**
 * Implements drush_COMMAND_init() for `drush kw-update`.
 */
function drush_kw_update_init() {
  kraftwagen_context_init_kraftwagen_root();
}

/**
 * Implements drush_COMMAND() for `drush kw-update`.
 */
function drush_kraftwagen_kw_update() {

  // Find out where the Kraftwagen root is.
  $root = kraftwagen_context_get_option('root-path');

  // Determine config directory.
  if (!($dir_cnf = kraftwagen_context_get_option('cnf-dir'))) {
    return drush_set_error(dt('No cnf dir name set.'));
  }
  if (!($file_environment = kraftwagen_context_get_option('environment-file'))) {
    return drush_set_error(dt('No environment file set.'));
  }
  
  if (!file_exists($root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment)) {
    return drush_set_error(dt('No environment file found at !path.', array('!path' => $root . DIRECTORY_SEPARATOR . $dir_cnf . DIRECTORY_SEPARATOR . $file_environment)));
  }

  $environment = kraftwagen_context_get_option('environment');

  kraftwagen_commands_sequence_run('update-commands', array(
    '*environment*' => $environment,
  ), FALSE);
}
