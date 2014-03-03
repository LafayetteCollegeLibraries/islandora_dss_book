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

  $islandora_object = $variables['object'];

  dpm($variables);

  $dc_array = $variables['dc_array'];

  // Refactor
  $is_newspaper = false;
  if(array_key_exists('dc:type', $dc_array)) {

    if($dc_array['dc:type']['value'] == 'Student newspaper' && isset($islandora_object->PDF)) {

      $is_newspaper = true;
    }
  }

  if($is_newspaper) {

    drupal_load('module', 'islandora_dss_pdf');
    islandora_dss_pdf_preprocess_islandora_pdf($variables);

    // Work-around
    drupal_add_js("
PDFView.open( '/islandora/object/" . $islandora_object->id . "/datastream/OBJ/view' );
jQuery(document).ready(function() { PDFView.open( '/islandora/object/" . $islandora_object->id . "/datastream/OBJ/view' )  });",
		  array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
		  );

  } else {

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

      $viewer_page_controls = array();
      /*
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
      */

    $variables['viewer_page_controls'] = drupal_render($viewer_page_controls);
  }
  }
  }
