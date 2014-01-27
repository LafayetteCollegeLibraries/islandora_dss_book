<?php
/**
 * @file
 * Template for Islandora Book Objects
 * @author griffinj@lafayette.edu
 *
 */
?>
<?php if (isset($viewer)): ?>

    <?php if (isset($viewer_page_controls)): ?>

	<?php print $viewer_page_controls; ?>
    <?php endif; ?>
  <div id="book-viewer">
    <?php print $viewer; ?>
  </div>
<?php endif; ?>

  <fieldset class="islandora-book-metadata">
  <legend><span class="fieldset-legend"><?php print t('Extended details'); ?></span></legend>
    <div class="fieldset-wrapper">
      <dl class="islandora-inline-metadata islandora-book-fields">
        <?php $row_field = 0; ?>

        <?php if (isset($mods_object)): ?>

          <?php foreach ($mods_object as $key => $value): ?>

            <dt class="<?php print $value['class']; ?><?php print $row_field == 0 ? ' first' : ''; ?>">
              <?php print $value['label']; ?>
            </dt>
            <dd class="<?php print $value['class']; ?><?php print $row_field == 0 ? ' first' : ''; ?>">

              <?php if( array_key_exists('date_value', $value)): ?>

		<?php print array_key_exists('facet', $value) ? l($value['date_value'], "islandora/search/eastasia." . $value['facet'] . "%3A" . $value['facet_value']) : $value['date_value']; ?>
	      <?php else: ?>

                <?php

		    // print array_key_exists('facet', $value) ? l($value['value'], "islandora/search/eastasia." . $value['facet'] . "%3A" . $value['facet_value']) : $value['value'];
		    if(array_key_exists('facet', $value)) {

		      print l($value['value'], "islandora/search/eastasia." . $value['facet'] . "%3A" . $value['facet_value']);
		    } elseif(array_key_exists('href', $value)) {

                      print l($value['value'], $value['href']);
		    } else {

		      print $value['value'];
		    }
		?>
	      <?php endif; ?>
            </dd>
          <?php $row_field++; ?>
        <?php endforeach; ?>
        <?php endif; ?>

      </dl>
    </div>
  </fieldset>
