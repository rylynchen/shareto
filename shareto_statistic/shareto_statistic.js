(function ($) {
  Drupal.behaviors.sharetoStatistic = {
    attach: function (context, settings) {
      $('.shareto', context).once(function () {
        $('.shareto_icon', this).click(Drupal.behaviors.sharetoStatistic.record);
      });
    },

    record: function () {
      $.ajax({
        url:location.protocol + '//' + location.host + Drupal.settings.basePath + 'shareto/statistic/ajax/record',
        dataType: 'jsonp',
        data: {callback: '?', nid:Drupal.settings.shareto_statistic.nid, url:Drupal.settings.shareto_statistic.url}
      });
    }
  };
})(jQuery);