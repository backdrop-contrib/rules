/**
 * @file
 * Adds the collapsible functionality to the rules debug log.
 */

// Registers the rules namespace.
Backdrop.rules = Backdrop.rules || {};

(function($) {
  Backdrop.behaviors.rules_debug_log = {
    attach: function(context) {
      $('.rules-debug-open').click(function () {
        var icon = $(this).children('span.ui-icon');
        if ($(this).next().is(':hidden')) {
          Backdrop.rules.changeDebugIcon(icon, true);
        }
        else {
          Backdrop.rules.changeDebugIcon(icon, false);
        }
        $(this).next().toggle();
      }).next().hide();

      $('.rules-debug-open-main').click(function () {
        var icon = $(this).children('span.ui-icon');
        if ($(this).parent().next().is(':hidden')) {
          Backdrop.rules.changeDebugIcon(icon, true);
          $(this).parent().children('.rules-debug-open-all').text(Backdrop.t('-Close all-'));
        }
        else {
          Backdrop.rules.changeDebugIcon(icon, false);
          $(this).parent().children('.rules-debug-open-all').text(Backdrop.t('-Open all-'));
        }
        $(this).parent().next().toggle();
      }).parent().next().hide();

      $('.rules-debug-open-all').click(function() {
        if ($('.rules-debug-open-main').parent().next().is(':hidden')) {
          $('.rules-debug-open').next().show();
          Backdrop.rules.changeDebugIcon($('.rules-debug-open').children('span.ui-icon'), true);
          $('.rules-debug-open-main').parent().next().show();
          Backdrop.rules.changeDebugIcon($(this).prev().children('span.ui-icon'), true);
          $(this).text(Backdrop.t('-Close all-'));
        }
        else {
          $('.rules-debug-open-main').parent().next().hide();
          Backdrop.rules.changeDebugIcon($('.rules-debug-open-main').children('span.ui-icon'), false);
          $(this).text(Backdrop.t('-Open all-'));
          $('.rules-debug-open').next().hide();
          Backdrop.rules.changeDebugIcon($(this).prev().children('span.ui-icon'), false);
        }
      });
    }
  };

  /**
   * Changes the icon of a collapsible div.
   */
  Backdrop.rules.changeDebugIcon = function(item, open) {
    if (open == true) {
      item.removeClass('ui-icon-triangle-1-e');
      item.addClass('ui-icon-triangle-1-s');
    }
    else {
      item.removeClass('ui-icon-triangle-1-s');
      item.addClass('ui-icon-triangle-1-e');
    }
  }
})(jQuery);
