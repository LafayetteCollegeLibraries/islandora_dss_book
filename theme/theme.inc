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

  $dc_array = $variables['dc_array'];

  /**
   * Work-around for displaying PDF datastream content
   * Refactor for Objects belonging to a specific namespace (?)
   *
   */

  global $base_url;
  if(in_array('islandora:newspaper', $islandora_object->getParents())) {

    islandora_dss_pdf_preprocess_islandora_pdf($variables);

    // Work-around
    drupal_add_js("PDFView.open('" . $base_url . "/islandora/object/" . $islandora_object->id . "/datastream/OBJ/view' );
jQuery(document).ready(function() { PDFView.open('" . $base_url . "/islandora/object/" . $islandora_object->id . "/datastream/OBJ/view' )  });",
		  array('type' => 'inline', 'scope' => 'footer', 'weight' => 5));

    $meta_ie_render_engine = array('#type' => 'html_tag',
				   '#tag' => 'meta',
				   '#attributes' => array('property' =>  'og:image',
							  'content' => $base_url . '/' . current_path() . '/datastream/TN/view',
							  )
				   );
 
    // Add header meta tag for IE to head
    drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');

  } else {

    // Determine if OpenSeadragon is the viewer...
    if(preg_match('/openseadragon/', $variables['viewer'])) {

      module_load_include('inc', 'islandora_paged_content', 'includes/utilities');
      $init_pages = islandora_paged_content_get_pages($islandora_object);

      if(!empty($init_pages)) {

	$init_page = array_shift($init_pages);

	$meta_ie_render_engine = array('#type' => 'html_tag',
				       '#tag' => 'meta',
				       '#attributes' => array('property' =>  'og:image',
							      'content' => $base_url . '/islandora/object/' . $init_page['pid'] . '/datastream/JPG/view')
				       );
      } else {

	$meta_ie_render_engine = array('#type' => 'html_tag',
				       '#tag' => 'meta',
				       '#attributes' => array('property' =>  'og:image',
							      'content' => $base_url . '/' . current_path() . '/datastream/JPG/view')
				       );
      }
 
      // Add header meta tag for IE to head
      drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');

      // If these are East Asia Image Collection postcards, modify the text for the links...
      $prev_content = t('Previous');
      $next_content = t('Next');

      $viewer_page_controls = array();
      
      $variables['viewer_page_controls'] = drupal_render($viewer_page_controls);
    }
  }
  }
