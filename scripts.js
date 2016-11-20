var deviceID = "340036001951353338363036"; //change these to your device's
var accessToken = "7aae8e0b7bd849a669f4efc2907b31b0442cf7c3"; //eventually these values will be obtained from a user form

//using publish() isn't the best...

function subscribe() //look for Particle.publish() events
{
  document.getElementById('electronData').innerHTML = "Waiting for result...";

  var eventSource = new EventSource("https://api.particle.io/v1/devices/" + deviceID + "/events/?access_token=" + accessToken);
  eventSource.addEventListener("trackerData", function(e) {
            var parsedData = JSON.parse(e.data);
            document.getElementById('electronData').innerHTML = parsedData.data;
        }, false);
}
