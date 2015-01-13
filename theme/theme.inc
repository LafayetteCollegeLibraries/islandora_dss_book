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
  $meta_element_open_graph_type = array('#type' => 'html_tag',
					'#tag' => 'meta',
					'#attributes' => array('property' =>  'og:type',
							       'content' => 'article'),
					);

  $meta_element_open_graph_url = array('#type' => 'html_tag',
				       '#tag' => 'meta',
				       '#attributes' => array('property' =>  'og:url',
							      'content' => $base_url . '/' . drupal_get_path_alias()),
				       );
  $meta_element_open_graph_author = array('#type' => 'html_tag',
					  '#tag' => 'meta',
					  '#attributes' => array('property' =>  'og:author',
								 'content' => 'https://www.facebook.com/LafayetteCollegeLibrary',
								 )
					  );
  $meta_element_open_graph_title = array('#type' => 'html_tag',
					 '#tag' => 'meta',
					 '#attributes' => array('property' =>  'og:title',
								'content' => $islandora_object->label,
								)
					 );

  /**
   * Iterate through each array for the generation of <meta> Elements
   * @todo Refactor for a Drupal-based UI
   *
   */
  $meta_elements = array(
			 'meta_element_open_graph_type' => array('#type' => 'html_tag',
			       '#tag' => 'meta',
								 '#attributes' => array('property' =>  'og:type',
						      'content' => 'article'),
			       ),
			 'meta_element_open_graph_url' => array('#type' => 'html_tag',
			       '#tag' => 'meta',
			       '#attributes' => array('property' =>  'og:url',
						      'content' => $base_url . '/' . drupal_get_path_alias()),
			       ),
			 'meta_element_open_graph_author' => array('#type' => 'html_tag',
			       '#tag' => 'meta',
			       '#attributes' => array('property' =>  'og:author',
						      'content' => 'https://www.facebook.com/LafayetteCollegeLibrary',
						      )
			       ),
			 'meta_element_open_graph_title' => array('#type' => 'html_tag',
			       '#tag' => 'meta',
			       '#attributes' => array('property' =>  'og:title',
						      'content' => $islandora_object->label,
						      )
			       )
			 );

  // Additionally, iterate through each Dublin Core element, and insert the HTML-encoded metadata

  foreach($variables['dc_array'] as $dc_key => $dc_element) {

    if( !empty($dc_element['value']) ) {

      $key = 'meta_element_'  . preg_replace('/\:/', '_', $dc_key);
      $segments = explode(':', $dc_key);
      $name = array_pop($segments);
      
      $meta_elements[$key] = array('#type' => 'html_tag',
				   '#tag' => 'meta',
				   '#attributes' => array('name' => 'DC.' . $name,
							  'content' => $dc_element['value'])
				   );
    }
  }
  
  /**
   * For the Object members of the Lafayette Newspaper and Lafayette Magazine Collections
   *
   */
  if(in_array('islandora:newspaper', $islandora_object->getParents()) or
     in_array('islandora:alumni', $islandora_object->getParents())) {

    islandora_dss_pdf_preprocess_islandora_pdf($variables);

    // Work-around
    drupal_add_js("
jQuery(document).ready(function() { setTimeout(function() {

PDFView.open('/islandora/object/" . $islandora_object->id . "/datastream/OBJ/view')

}, 200); });

",
		  array('type' => 'inline', 'scope' => 'footer', 'weight' => 5));

    /**
     * Passing the selector for the PDF.js markup
     *
     */
    drupal_add_js(array('islandoraDssBook' => array('selector' => '.islandora-pdf-content-wrapper',
						    'grippieSelector' => '.islandora-pdf-content')), 'setting');

    
    $meta_elements['meta_element_open_graph_image'] = array('#type' => 'html_tag',
							    '#tag' => 'meta',
							    '#attributes' => array('property' =>  'og:image',
										   'content' => $base_url . '/' . current_path() . '/datastream/TN/view',
										   ),
							    );
    $meta_elements['meta_element_open_graph_site_name'] = array('#type' => 'html_tag',
								'#tag' => 'meta',
								'#attributes' => array('property' =>  'og:site_name',
										       'content' => in_array('islandora:newspaper', $islandora_object->getParents()) ?
										       'Lafayette Newspaper Collection' : 'Lafayette Magazine Collection',
										       )
								);

    //
    dpm($variables);

  } else {

    // Determine if OpenSeadragon is the viewer...
    if(array_key_exists('viewer', $variables) and preg_match('/openseadragon/', $variables['viewer'])) {

      module_load_include('inc', 'islandora_paged_content', 'includes/utilities');
      $init_pages = islandora_paged_content_get_pages($islandora_object);

      if(!empty($init_pages)) {

	$init_page = array_shift($init_pages);

	$meta_element_open_graph_image = array('#type' => 'html_tag',
					       '#tag' => 'meta',
					       '#attributes' => array('property' =>  'og:image',
								      'content' => $base_url . '/islandora/object/' . $init_page['pid'] . '/datastream/JPG/view')
					       );
      } else {

	 $meta_element_open_graph_image = array('#type' => 'html_tag',
						'#tag' => 'meta',
						'#attributes' => array('property' =>  'og:image',
								       'content' => $base_url . '/' . current_path() . '/datastream/JPG/view')
						);
      }

      $collection = 'East Asia Image Collection';

      $meta_elements['meta_element_open_graph_image'] = $meta_element_open_graph_image;

      $meta_elements['meta_element_open_graph_description'] = array('#type' => 'html_tag',
								    '#tag' => 'meta',
								    '#attributes' => array('property' =>  'og:description',
											   'content' => $collection,
											   )
								    );
 
      // If these are East Asia Image Collection postcards, modify the text for the links...
      $prev_content = t('Previous');
      $next_content = t('Next');

      $viewer_page_controls = array();
      
      $variables['viewer_page_controls'] = drupal_render($viewer_page_controls);
    }
  }
  
  foreach($meta_elements as $key => $meta_element) {

    drupal_add_html_head($meta_element, $key);
  }

  /**
   * Adding support for the integration of the Drupal "grippie"
   *
   */

  drupal_add_css( drupal_get_path('module', 'islandora_dss_book') . '/css/islandora_dss_book.css' );
  drupal_add_js( drupal_get_path('module', 'islandora_dss_book') . '/js/build/islandora_dss_book.js' );

  }
