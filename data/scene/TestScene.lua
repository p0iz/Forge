-- A test script for creating a scene

-- Setup lighting
Loader.addDirectionalLight({ 0.0, 1.0, 1.0 }, { 0.0, 0.0, 1.0, 1.0 });
Loader.addPointLight({ 10.0, 10.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 }); 

-- Load meshes
Loader.loadMesh("paddle");
Loader.loadMesh("ball");
Loader.loadMesh("tile");
Loader.loadMesh("border");

-- Load materials apply them to meshes
Loader.loadMaterial("Tile");
Loader.loadMaterial("Paddle");

--[[
Mesh.setMaterial("ball", "Tile");
Mesh.setMaterial("tile", "Tile");
Mesh.setMaterial("border", "Tile");
Mesh.setMaterial("paddle", "Paddle");

-- Create scene nodes and attach meshes
borderNode = Loader.createSceneNode("BorderNode", nil, { 0.0, 6.1, 0.0 });
SceneNode.attachMesh(borderNode, "border");

paddleNode = Loader.createSceneNode("PaddleNode");
SceneNode.attachMesh(paddleNode, "paddle");

ballNode = Loader.createSceneNode("BallNode", nil, { 0.0, 5.0, 0.0 });
SceneNode.attachMesh(ballNode, "ball");

tileNode = Loader.createSceneNode("Tile1Node", nil, { 5.0, 10.0, 0.0 });
SceneNode.attachMesh(tileNode, "tile");

tileNode = Loader.createSceneNode("Tile2Node", nil, { 6.0, 10.0, 0.0 });
SceneNode.attachMesh(tileNode, "tile");

-- create camera
camera = Loader.createCamera("MainCamera");
Camera.translate(camera, { 0.0, 5.0, -10.0 });
Camera.setDirection({ 0.0, 5.0, 0.0 });

]]--

