var VERSION = '1.5';

// https://github.com/smallstoneapps/gcolor.js/blob/master/lib/gcolor.js
function GColorFromHex(hex) {
  var hexNum = parseInt(hex, 16);
  var a = 192;
  var r = (((hexNum >> 16) & 0xFF) >> 6) << 4;
  var g = (((hexNum >>  8) & 0xFF) >> 6) << 2;
  var b = (((hexNum >>  0) & 0xFF) >> 6) << 0;
  return a + r + g + b;
}

/******************************** PebbleKit JS ********************************/

Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready! Version: ' + VERSION);
});

Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL('https://dl.dropboxusercontent.com/u/10824180/pebble%20config%20pages/isotime-config-testing.html?version=' + VERSION);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var json = JSON.parse(decodeURIComponent(e.response));

  // Convert colors
  var background = GColorFromHex(json.isotime_background);
  var sides = GColorFromHex(json.isotime_sides);
  var face = GColorFromHex(json.isotime_face);

  var options = {
    'AppKeyColorBackground': background,
    'AppKeyColorSides': sides,
    'AppKeyColorFace': face,
    'AppKeyAnimations': (json.isotime_animations === 'true') ? 1 : 0,
    'AppKeyBluetooth': (json.isotime_bluetooth === 'true') ? 1 : 0,

  };

  Pebble.sendAppMessage(options, function() {
    console.log('Settings update successful!');
  }, function(e) {
    console.log('Settings update failed: ' + JSON.stringify(e) + " for update " + JSON.stringify(options));
  });
});
