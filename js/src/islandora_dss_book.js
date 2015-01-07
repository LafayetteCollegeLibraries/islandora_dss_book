/**
 * Drupal functionality for Objects rendered using the islandora_dss_book
 * @author griffinj@lafayette.edu
 *
 */

var Drupal = Drupal || {};

/**
 * Class for the Islandora Book Object
 *
 */
var IslandoraBookObject = function(element, drupal, $) {

    this.element = element;
    this.Drupal = drupal || Drupal;
    this.$ = $ || jQuery;

    this.theme(this.$, this.Drupal);
};

/**
 * Class for the Islandora Book Objects containing a Document in the PDF for the OBJ Datastream
 *
 */
function IslandoraBookObjectPdf(element, $) {

    IslandoraBookObject.call(this, element, $);
};

IslandoraBookObjectPdf.prototype = Object.create(IslandoraBookObject.prototype);
IslandoraBookObjectPdf.prototype.constructor = IslandoraBookObjectPdf;

var Grippie = function() {};

Grippie.jQuery = jQuery || {};
Grippie.performDrag = function performDrag(e) {
    
    var $ = Grippie.jQuery;
    var $element = $(document).data('islandoraDssBook').element;

    $element.height(Math.max(32, Grippie.staticOffset + e.pageY) + 'px');
    return false;
};

Grippie.endDrag = function endDrag(e) {

    var $ = Grippie.jQuery;
    var $element = $(document).data('islandoraDssBook').element;

    $(document).unbind('mousemove', Grippie.performDrag).unbind('mouseup', Grippie.endDrag);
    $element.css('opacity', 1);
};

Grippie.startDrag = function startDrag(e) {

    var $ = Grippie.jQuery;
    var data = $(document).data('islandoraDssBook') || {};

    if(!data.hasOwnProperty('grippieSelector')) {

	throw "No jQuery selector passed for retrieving the element being resized by the grippie widget.";
    }

    var $element = $(this).siblings(data.grippieSelector);
    data.element = $element;

    $(document).data('islandoraDssBook', data);
	
    Grippie.staticOffset = $element.height() - e.pageY;
    $element.css('opacity', 0.25);
    $(document).mousemove(Grippie.performDrag).mouseup(Grippie.endDrag);
    return false;
};

/**
 * The theme() Method (for theming the Object)
 *
 */
IslandoraBookObjectPdf.prototype.theme = function($, drupal) {

    var $ = $ || jQuery;
    var staticOffset = null;

    var grippie = $('<div class="grippie"></div>').mousedown(Grippie.startDrag);
    grippie.appendTo(this.element);
};
	
(function($, Drupal) {

    Drupal.behaviors.islandoraDssBook = {

	attach: function(context, settings) {

	    var books = $(settings.islandoraDssBook.selector).each(function(index, element) {

		    return new IslandoraBookObjectPdf(element, $, Drupal);
		});
	    
	    // Set (or update) the state of the widget for the Document
	    var data = $(document).data( 'islandoraDssBook', data ) || {};
	    data.books = books;
	    data.grippieSelector = settings.islandoraDssBook.grippieSelector;
	    $(document).data( 'islandoraDssBook', data );
	}
    };
})(jQuery, Drupal);
