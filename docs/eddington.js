// Define Eddington function
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

// Parse user input into integer array
function textParse(text)
{
  return text.split(/\r*\n|,/).map(ride => parseInt(ride))
}

// Process file and compute E
function getFile()
{
  
  file = document.getElementById('file-input').files[0]
  reader = new FileReader()
  
  
  reader.onload = function() 
  {
    rides = textParse(this.result)
    document.getElementById('E').innerHTML = eddington(rides)    
  }

  reader.readAsText(file)

}

// Create event listener for file-input element
window.onload = function() 
{
  document.getElementById('file-input').addEventListener('change', getFile)
}

// Process textarea element and compute E
function submitText() 
{
   rides = textParse(document.getElementById('text-input').value)
   document.getElementById('E').innerHTML = eddington(rides)
}
