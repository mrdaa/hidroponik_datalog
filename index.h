const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Hidroponik DataLog</title>
  <style>
    /* Data Table Styling */
    #dataTable {
      font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
      border-collapse: collapse;
      width: 100%;
    }

    #dataTable td,
    #dataTable th {
      border: 1px solid #ddd;
      padding: 8px;
    }

    #dataTable tr:nth-child(even) {
      background-color: #f2f2f2;
    }

    #dataTable tr:hover {
      background-color: #ddd;
    }

    #dataTable th {
      padding-top: 12px;
      padding-bottom: 12px;
      text-align: center;
      background-color: #4CAF50;
      color: white;
    }
  </style>
</head>

<body>
  <div style="text-align: center;">
    <h2><b>Hidroponik Datalog</b></h2>
  </div>
  <div>
    <table id="dataTable">
      <tr>
        <th>Time</th>
        <th>Temperatur (&deg;C)</th>
        <th>Humidity (%)</th>
        <th>TDS Level (ppm)</th>
      <th>Water Level (%)</th>
      </tr>
    </table>
  </div>

  <script>
    var Tvalues = [];
    var Hvalues = [];
    var timeStamp = [];
    var Tdsvalues = [];
    var Wlvalues = [];
    // var R1values = [];
    // var R2values = [];

    setInterval(function () {
      getData();
    }, 1000);

    function getData() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          var time = new Date().toLocaleTimeString();
          var txt = this.responseText;
          var obj = JSON.parse(txt);
          Tvalues.push(obj.Temperature);
          Hvalues.push(obj.Humidity);
          Tdsvalues.push(obj.Tds);
          Wlvalues.push(obj.WL);
          timeStamp.push(time);

          //Update Data Table
          var table = document.getElementById("dataTable");
          var row = table.insertRow(1); //Add after headings
          var cell1 = row.insertCell(0);
          var cell2 = row.insertCell(1);
          var cell3 = row.insertCell(2);
          var cell4 = row.insertCell(3);
          var cell5 = row.insertCell(4);

          cell1.innerHTML = time;
          cell2.innerHTML = obj.Temperature;
          cell3.innerHTML = obj.Humidity;
          cell4.innerHTML = obj.Tds;
          cell5.innerHTML = obj.WL;

        }
      };
      xhttp.open("GET", "readSensor", true);
      xhttp.send();
    }

  </script>

</body>

</html>

)=====";
