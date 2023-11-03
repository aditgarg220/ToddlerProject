let lion;
let obstacleX;
let obstacleWidth = 50;
let obstacleGap;
let isGameOver = false;
let points = 0;
let passedObstacle = false; // Track whether the lion has passed an obstacle
let positiveNoise;
let negativeNoise

function preload() {
  soundFormats('mp3','ogg');
  positiveNoise = loadSound('ding_noise.mp3');
  negativeNoise = loadSound('incorrect_sound.mp3');
}

function setup() {
  createCanvas(800, 400);
  lion = { x: width / 2, y: height / 2, size: 40 };
  generateRandomObstacle();

  
}

function draw() {
  background(135, 206, 235); // Set the background color to blue
 
  if (!isGameOver) {
   
  
    moveObstacles();
    checkCollision();

    lion.x = mouseX;
    lion.y = mouseY;

    text("Points: " + points, width / 2, height / 2);
    drawLion();
    drawObstacles();
    
  } else {
    // Game over screen
    textSize(32);
    textAlign(CENTER, CENTER);
    fill(255, 0, 0);
    text("Game Over", width / 2, height / 2);
    textSize(24);
    text("Points: " + points, width / 2, height / 2 + 40);
    text("Press Space to Restart", width / 2, height / 2 + 80);
  }
}

function keyPressed() {
  if (isGameOver && keyCode === 32) {
    // Restart the game when Space key is pressed
    isGameOver = false;
    points = 0;
    generateRandomObstacle();
  }
}

function drawLion() {
  fill(255); // Lion's face color (white)
  ellipse(lion.x, lion.y, lion.size, lion.size);

  fill(255, 204, 0); // Lion's mane color (yellowish-orange)
  ellipse(lion.x, lion.y - lion.size / 2, lion.size * 1.5, lion.size * 1.5);

  fill(0); // Lion's eyes and nose color (black)
  ellipse(lion.x - lion.size / 4, lion.y - lion.size / 4, lion.size / 6, lion.size / 6); // Left eye
  ellipse(lion.x + lion.size / 4, lion.y - lion.size / 4, lion.size / 6, lion.size / 6); // Right eye
  ellipse(lion.x, lion.y + lion.size / 6, lion.size / 8, lion.size / 8); // Nose
}


function generateRandomObstacle() {
  obstacleGap = random(200, 400); // Randomize the gap between obstacles
  obstacleX = width;
  passedObstacle = false; // Reset the flag when generating a new obstacle
}

function moveObstacles() {
  obstacleX -= 5;
  if (obstacleX < -obstacleWidth) {
    generateRandomObstacle(); // Generate a new set of random obstacles
    obstacleX = width;
  }
}

function drawObstacles() {
  fill('brown');
  // Draw the top obstacle
  rect(obstacleX, 0, obstacleWidth, height - obstacleGap);
  // Draw the bottom obstacle
  rect(obstacleX, height - obstacleGap + 120, obstacleWidth, height);
}

function checkCollision() {
  if (
    lion.x > obstacleX &&
    lion.x < obstacleX + obstacleWidth &&
    (lion.y - lion.size / 2 < height - obstacleGap || lion.y + lion.size / 2 > height - obstacleGap + 120)
  ) {
    gameOver();
  } else if (lion.x > obstacleX + obstacleWidth && !passedObstacle) {
    passedObstacle = true; // Mark that the lion has passed the obstacle
    points++; // Increment points when the lion passes through the obstacle
    positiveNoise.play();
  }
}

function gameOver() {
  isGameOver = true;
  negativeNoise.play(); // You can add code to play a sound here.
}

function playNegativeNoise() {
  // Add code to play a negative sound
  console.log("Negative noise played");
  
}