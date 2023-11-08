var eddington = function(rides) {
  var n = rides.length
  var E = 0
  var above = 0
  var H = new Array(n).fill(0)

  for ( i = 0; i < n; i++ ) {
    var ride = rides[i]
    if (ride > E) {
      above++
      if (ride < n) H[ride]++

      if (above > E) {
        E++
        above -= H[E]
      }
    }
  }

  return E
}

var parseText = function(text) {
  return text.split(/\r*\n|,/).map(ride => parseInt(ride))
}

var getFile = function() {
  var file = document.getElementById('file-input').files[0]
  var reader = new FileReader()

  reader.onload = function() {
    document.getElementById('E').innerHTML = eddington(parseText(this.result))
  }

  reader.readAsText(file)
}

var submitText = function() {
  var rides = parseText(document.getElementById('text-input').value)
  document.getElementById('E').innerHTML = eddington(rides)
}

var loadTab = function(evt, tab_content_id) {
  var tab_contents = document.getElementsByClassName("tab-content");
  for (var i = 0; i < tab_contents.length; i++) {
    tab_contents[i].style.display = "none";
  }
  document.getElementById(tab_content_id).style.display = "block";

  var tabs = document.getElementsByClassName("tab");
  for (var i = 0; i < tabs.length; i++) {
    tabs[i].className = tabs[i].className.replace(" active", "");
  }
  evt.currentTarget.className += " active";
}

window.onload = function() {
  document.getElementById('default-tab').click()
  document.getElementById('file-input').addEventListener('change', getFile)
}
