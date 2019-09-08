function eddington(rides)
{
  n = rides.length
  E = 0
  above = 0
  H = new Array(n).fill(0)

  for ( i = 0; i < n; i++ ) {
    ride = rides[i]
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

function getFile()
{
  
  file = document.getElementById('rides').files[0]
  reader = new FileReader()
  
  
  reader.onload = function() 
  {
    rides = this.result.split(/\r*\n|,/).map(line => parseInt(line))
    document.getElementById('E').innerHTML = eddington(rides)    
  }

  reader.readAsText(file)

}

window.onload = function() 
{
  document.getElementById('rides').addEventListener('change', getFile)
}

function submitText() {
   textInput = document.getElementById('text-input').value
   rides = textInput.split(/\r*\n|,/).map(ride => parseInt(ride))
   document.getElementById('E').innerHTML = eddington(rides)
}
