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
    // var Tvalues = [];
    // var Hvalues = [];
    // var timeStamp = [];
    // var Tdsvalues = [];
    // var Wlvalues = [];
    // var R1values = [];
    // var R2values = [];
   
    const ip = "";
    const url = ip+"/readsensor"

    setInterval(function () {
      getData();
    }, 1000);

    const pushTables = (data)=>{
          //Update Data Table
          const table = document.getElementById('dataTable').getElementsByTagName('tbody')[0];

          //buat row baru
          const newRow = table.insertRow();

          //buat cell baru
          const TimeCell = newRow.insertCell();
          const TempCell = newRow.insertCell();
          const HumCell = newRow.insertCell();
          const TDSCell = newRow.insertCell();
          const WLCell = newRow.insertCell();

         //membuat text element
         const time = document.createTextNode(data.time);
         const temp = document.createTextNode(data.temp);
         const hum = document.createTextNode(data.hum);
         const tds = document.createTextNode(data.tds);
         const wl = document.createTextNode(data.wl);

         //memasukan text kedalam cell
         TimeCell.appendChild(time);
         TempCell.appendChild(temp);
         HumCell.appendChild(hum);
         TDSCell.appendChild(tds);
         WLCell.appendChild(wl);
    }

    function getData() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          var txt = this.responseText;
          var obj = JSON.parse(txt);
          // Tvalues.push(obj.Temperature);
          // Hvalues.push(obj.Humidity);
          // Tdsvalues.push(obj.Tds);
          // Wlvalues.push(obj.WL);
          // timeStamp.push(time);

         pushTables({
           time:new Date().toLocaleTimeString(),
           temp:obj.Temperature || "--", //artinya jika obj.Temperature kosong nilai nya default jadi "--"
           hum:obj.Humidity || "--",
           tds:obj.Tds || "--",
           wl:obj.WL
         })

        }
      };
      xhttp.open("GET", "readSensor", true);
      xhttp.send();
    }
    
    const getDataVersiFetch = async ()=>{
       const res = await fetch(url).catch((err)=>console.log("terjadi error", err));
       const obj = await res.json();
        pushTables({
          time:new Date().toLocaleTimeString(),
          temp:obj.Temperature || "--", //artinya jika obj.Temperature kosong nilai nya default jadi "--"
          hum:obj.Humidity || "--",
          tds:obj.Tds || "--",
          wl:obj.WL
        })
    }

  </script>

</body>

</html>

)=====";
