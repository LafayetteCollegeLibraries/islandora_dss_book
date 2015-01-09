<?php
/**
 * @file
 * Template for Islandora Book Objects
 * @author griffinj@lafayette.edu
 *
 */
?>

<div itemscope itemtype="http://schema.org/Book">

<?php if (isset($pdf_viewer)): ?>
    <div class="islandora-pdf-object islandora">
       <div class="islandora-pdf-content-wrapper clearfix">

       <div class="islandora-pdf-content">

	  <?php print $pdf_viewer; ?>
       </div>
    </div>

<?php else: ?>

<?php if (isset($viewer)): ?>

    <?php if (isset($viewer_page_controls)): ?>

	<?php print $viewer_page_controls; ?>
    <?php endif; ?>

  <div id="book-viewer">

    <div id="book-viewer-pages-overlay"></div>

    <?php print $viewer; ?>
  </div>
<?php endif; ?>

<?php endif; ?>

  <fieldset class="islandora-book-metadata">
  <h3 class="islandora-image-details">Item Details</h3>
    <div class="fieldset-wrapper">
      <dl class="islandora-inline-metadata islandora-book-fields">
        <?php $row_field = 0; ?>

        <?php if (isset($mods_object)): ?>

          <?php foreach ($mods_object as $key => $value): ?>

	    <?php if ($value['label'] or $value['value']): ?>

            <dt class="<?php
print $value['class'];
print $row_field == 0 ? ' first' : '';
if($value['label'] != ''):

  print ' islandora-inline-metadata-displayed';
endif;
?>">

              <?php print $value['label']; ?>
            </dt>

            <dd class="<?php print $value['class']; ?><?php print $row_field == 0 ? ' first' : ''; ?>" itemprop="<?php print array_key_exists('itemprop', $value) ? $value['itemprop'] : ''; ?>" ><!-- This should be refactored into a theme hook -->

              <?php if(array_key_exists('date_value', $value)): ?>

	        <?php print $value['facet_href']; ?>
	      <?php else: ?>

                <?php

		    if(array_key_exists('facet', $value)) {

		      print $value['facet_href'];
		    } elseif(array_key_exists('href', $value)) {

                      print l($value['value'], $value['href']);
                    } else {

		      print $value['value'];
		    }
		?>
	      <?php endif; ?>
            </dd>

	    <?php endif; ?>
          <?php $row_field++; ?>
        <?php endforeach; ?>
        <?php endif; ?>
      </dl>
    </div>
  </fieldset>

</div><!-- Resolves the scope for the item -->
