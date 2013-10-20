var df = require('dateformat')
  , autonomy = require('ardrone-autonomy')
  , arDrone = require('ar-drone')
  , arDroneConstants = require('ar-drone/lib/constants')
  , mission  = autonomy.createMission()
  ;

function navdata_option_mask(c) {
  return 1 << c;
}

// From the SDK.
var navdata_options = (
    navdata_option_mask(arDroneConstants.options.DEMO)
  | navdata_option_mask(arDroneConstants.options.VISION_DETECT)
  | navdata_option_mask(arDroneConstants.options.MAGNETO)
  | navdata_option_mask(arDroneConstants.options.WIFI)
);

// Land on ctrl-c
var exiting = false;
process.on('SIGINT', function() {
    if (exiting) {
        process.exit(0);
    } else {
        console.log('Got SIGINT. Landing, press Control-C again to force exit.');
        exiting = true;
        mission.control().disable();
        mission.client().land(function() {
            process.exit(0);
        });
    }
});

// Connect and configure the drone
mission.client().config('general:navdata_demo', true);
mission.client().config('general:navdata_options', navdata_options);
mission.client().config('video:video_channel', 1);
mission.client().config('detect:detect_type', 12);

// Log mission for debugging purposes
mission.log("mission-" + df(new Date(), "yyyy-mm-dd_hh-MM-ss") + ".txt");

// Plan mission
mission.takeoff()
       .zero()         // Sets the current state as the reference
       .altitude(1)    // Climb to altitude = 1 meter
       .go({x:1, y:0}) // Forward to pickup zone
       .altitude(0.4)  // Go down to pickup altitude
       .forward(0.5)   // Forward to pick up
       .go({x:0, y:0}) // RTB
       .land();

// Execute mission
mission.run(function (err, result) {
    if (err) {
        console.trace("Oops, something bad happened: %s", err.message);
        mission.client().stop();
        mission.client().land();
    } else {
        console.log("We are done!");
        process.exit(0);
    }
});
