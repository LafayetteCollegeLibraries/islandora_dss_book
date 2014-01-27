<?php

  /**
   * @file Theming hook implementations and other elements of functionality
   * @author griffinj@lafayette.edu
   *
   */

/*
 * Implements hook_preprocess_HOOK()
 * Deprecates the "front" and "back" tabs for postcards
 * @see islandora_book_preprocess_islandora_book_book
 *
 */
function islandora_dss_book_preprocess_islandora_book_book(array &$variables) {

  // Determine if OpenSeadragon is the viewer...
  if(preg_match('/openseadragon/', $variables['viewer'])) {

    // If these are East Asia Image Collection postcards, modify the text for the links...
    if(false) {
      
      $prev_content = t('Front');
      $next_content = t('Back');
    } else {

      $prev_content = t('Previous');
      $next_content = t('Next');
    }

    $viewer_page_controls = array('islandora-openseadragon-prev' => array('#type' => 'markup',
									  '#markup' => '<div id="islandora-openseadragon-prev" class="islandora-openseadragon-page-control">' . $prev_content . '</div>',
									  '#prefix' => '<div class="islandora-openseadragon-page-controls">',
									  ),
				  'islandora-openseadragon-next' => array('#type' => 'markup',
									  '#markup' => '<div id="islandora-openseadragon-next" class="islandora-openseadragon-page-control">' . $next_content . '</div>',
									  ),
				  'islandora-openseadragon-page-state' => array('#type' => 'markup',
										'#markup' => '<div id="islandora-openseadragon-page-state" class="islandora-openseadragon-page-control"></div>',
										'#suffix' => '</div>'),
				  );

    $variables['viewer_page_controls'] = drupal_render($viewer_page_controls);
  }
  }
