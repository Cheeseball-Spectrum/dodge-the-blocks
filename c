<!DOCTYPE html>
<html>
<head>
    <title>Dodge The Blocks</title>
    <style>
        body {
            margin: 0;
            overflow: hidden;
            background: #111;
            font-family: Arial;
            color: white;
            text-align: center;
        }

        canvas {
            background: #222;
            display: block;
            margin: 0 auto;
        }

        #score {
            position: absolute;
            top: 10px;
            left: 50%;
            transform: translateX(-50%);
            font-size: 20px;
        }

        #gameOver {
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
            font-size: 30px;
            display: none;
        }

        button {
            padding: 10px 20px;
            margin-top: 10px;
            cursor: pointer;
        }
    </style>
</head>
<body>

<div id="score">Score: 0</div>
<div id="gameOver">
    Game Over<br>
    <button onclick="restart()">Restart</button>
</div>

<canvas id="gameCanvas" width="400" height="600"></canvas>

<script>
const canvas = document.getElementById("gameCanvas");
const ctx = canvas.getContext("2d");

let player = {
    x: 180,
    y: 550,
    width: 40,
    height: 40,
    speed: 6
};

let obstacles = [];
let score = 0;
let gameRunning = true;
let obstacleSpeed = 3;

document.addEventListener("keydown", movePlayer);

function movePlayer(e) {
    if (e.key === "ArrowLeft" && player.x > 0) {
        player.x -= player.speed;
    }
    if (e.key === "ArrowRight" && player.x < canvas.width - player.width) {
        player.x += player.speed;
    }
}

function spawnObstacle() {
    let width = 40;
    let x = Math.random() * (canvas.width - width);
    obstacles.push({
        x: x,
        y: -40,
        width: width,
        height: 40
    });
}

function update() {
    if (!gameRunning) return;

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Draw player
    ctx.fillStyle = "blue";
    ctx.fillRect(player.x, player.y, player.width, player.height);

    // Spawn obstacles
    if (Math.random() < 0.02) {
        spawnObstacle();
    }

    // Move obstacles
    ctx.fillStyle = "red";
    obstacles.forEach((obs, index) => {
        obs.y += obstacleSpeed;
        ctx.fillRect(obs.x, obs.y, obs.width, obs.height);

        // Collision
        if (
            player.x < obs.x + obs.width &&
            player.x + player.width > obs.x &&
            player.y < obs.y + obs.height &&
            player.y + player.height > obs.y
        ) {
            endGame();
        }

        // Remove off-screen
        if (obs.y > canvas.height) {
            obstacles.splice(index, 1);
        }
    });

    score++;
    obstacleSpeed += 0.0005;
    document.getElementById("score").innerText = "Score: " + score;

    requestAnimationFrame(update);
}

function endGame() {
    gameRunning = false;
    document.getElementById("gameOver").style.display = "block";
}

function restart() {
    obstacles = [];
    score = 0;
    obstacleSpeed = 3;
    player.x = 180;
    gameRunning = true;
    document.getElementById("gameOver").style.display = "none";
    update();
}

update();
</script>

</body>
</html>
