//HTML code for webpage
//=====================
const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE HTML>
<html>
<head>
<title>ESP32 Web Server</title>
</head>
<!-------------------------------C S S-----------------------------
->
<style>
html{
font-family: 'Franklin Gothic Medium', 'Arial Narrow',
Arial, sans-serif;
display: inline-block;
text-align: center;
}
h1{
font-size: 3rem;
color: white;
}
body{
margin: 0;
background-color: white;
}
h2{
font-size: 2rem;
color: red;
}
h3{
font-size: 2rem;
color: green;
}
header{
background-position: center;
text-align: center;
padding: 40px 0;
overflow: hidden;
background-color: #0a1128;
}
.container{
display: flex;
justify-content: space-between;
align-items: center;
padding: 100px;
}
.card_grid{
max-width: 800px;
margin: 0 auto;
display: grid;
grid-gap: 25rem;
grid-template-columns: repeat(auto-fit,
minmax(230px,1fr));
}
.card{
background-color: white;
text-align: left;
box-shadow: 2px 2px 12px 1px rgb(140,140,140,.5);
width: 300px;
height: 250px;
}
.card_title{
font-size: 1.2rem;
font-weight: bold;
color: black;
text-align: center;
}
</style>
<!------------------------------H T M L--------------------------
--->
<body>
<header>
<h1>Parking Slot Tracker</h1>
<h2>Occupied</h2>
<h3>Free</h3>
</header>
<div class="container">
<div class="card_grid">
<span class="card" id="parkingA"><p
class="card_title">Parking A</p></span>
<span class="card" id="parkingB"><p
class="card_title">Parking B</p></span>
</div>
</div>
<!-----------------------------JavaScript-------------------------
-->
<script>
InitWebSocket()
function InitWebSocket()
{
websock = new WebSocket('ws://172.20.10.10:81/');
websock.onmessage = function(event)
{
const data = JSON.parse(event.data);
const parking1Status = data.p1;
const parking2Status = data.p2;
const parking1 =
document.getElementById('parkingA');
const parking2 =
document.getElementById('parkingB');
if(parking1Status == 'Occupied')
{
parking1.style.background ='#00ff44';
}
else if(parking1Status == 'Free')
{
parking1.style.background ='#ff0000';
}
if(parking2Status == 'Occupied')
{
parking2.style.background ='#00ff44';
}
else if(parking2Status == 'Free')
{
parking2.style.background ='#ff0000';
}
}
}
</script>
</body>
</html>
)=====";