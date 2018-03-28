var balls = [];
var state = 0;
var down = 0;
var ID;
var drad = 1;
var direction;
var rad;
var x;
var y;
var dn = 0;
var dx=5;
var dy=5;
var context;

document.getElementById("clear").onclick = function(){
  balls = [];
  cancelAnimationFrame(ID);
  context.fillStyle = "#000000";
  context.fillRect(0, 0, myCanvas.width, myCanvas.height);
};

myCanvas.onmousemove = function(event){
  if(dn){
    balls.push({
      x: event.clientX,
      y: event.clientY,
      r: 0,
      d: 1,
      c: 0
    });
    cancelAnimationFrame(ID);
    ID = requestAnimationFrame(place);
  }
}

myCanvas.onmousedown = function(event){
  dn = 1;
  balls.push({
    x: event.clientX,
    y: event.clientY,
    r: 0,
    d: 1,
    c: 0
  });
  cancelAnimationFrame(ID);
  ID = requestAnimationFrame(place);
  // console.log(mos.toString;
  // console.log(mos.x);
  // balls.push({xVal: x, yVal: y, rVal: 20});
}

myCanvas.onmouseup = function(){
  dn = 0;
  console.log("up");
};

function init()
{
  console.log("start");
  context= myCanvas.getContext('2d');
  canvas = document.getElementById("myCanvas");
  canvas.width = document.body.clientWidth;
  canvas.height = 300;
  context.fillStyle = "#000000";
  context.fillRect(0, 0, myCanvas.width, myCanvas.height);
}

function place()
{
      // console.log(balls[0].x);
    context.fillStyle = "#000000";
    // context.fillRect(0, 0, 1300, 600);
  
    context.fillRect(0, 0, myCanvas.width, myCanvas.height);
  
    for(var i = 0; i < balls.length; i++){
      rad = balls[i].r;
      direction = balls[i].d;
      if(rad < 50 && direction == 1){
        // balls[i].c = 244;
        rad += drad;
      }
      else{      
        direction = 0;
      }
      if(rad > 0 && direction == 0){
        // balls[i].c = 360;
        rad -= drad;
      }
      else{
        direction = 1;
      }
      balls[i].r = rad;
      balls[i].d = direction;
      
      context.fillStyle='hsl(' + balls[i].c++ + ', 100%, 50%)';
      context.beginPath();
      context.arc(balls[i].x,balls[i].y,rad,0,Math.PI*2,true);
      context.fill();
    }
  
  ID = requestAnimationFrame(place);
}