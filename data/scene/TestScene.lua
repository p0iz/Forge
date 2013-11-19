-- A test script for creating a scene

-- Setup lighting
Scene.addDirectionalLight({ 0.0, 1.0, 1.0 }, { 0.0, 0.0, 1.0, 1.0 });
Scene.addPointLight({ 10.0, 10.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });
Scene.addSpotLight(
	{ 10.0, 10.0, 1.0, 1.0 },
	{ 1.0, -1.0, -0.5 },
	16,
	20,
	25,
	{1.0, 0.0, 0.0, 1.0}
);

-- Load meshes
paddle = Assets.loadMesh("paddle");
ball = Assets.loadMesh("ball");
tile = Assets.loadMesh("tile");
border = Assets.loadMesh("border");

-- Load materials
tileMat = Assets.loadMaterial("Tile");
paddleMat = Assets.loadMaterial("Paddle");

ball:setMaterial(tileMat);
tile:setMaterial(tileMat);
border:setMaterial(tileMat);
paddle:setMaterial(paddleMat);

--[[
-- Create a scene graph from a single function call
Scene.graph{
  {
    name = "BorderNode",
    position = { 0.0, 6.1, 0.0 },
    attachables = { border },
  },
  {
    name = "PaddleNode",
    position = { 0.0, 5.0, 0.0 },
    attachables = { paddle },
  },
  {
    name = "BallNode",
    position = { 0.0, 5.0, 0.0 },
    attachables = { ball },
  },
  {
    name = "Tile1Node",
    position = { 5.0, 10.0, 0.0 },
    attachables = { tile },
  },
  {
    name = "Tile2Node",
    position = { 6.0, 10.0, 0.0 },
    attachables = { tile },
  }
};

-- create camera
camera = Scene.addCamera("MainCamera");
camera:translate({ 0.0, 5.0, -10.0 });
camera:setDirection({ 0.0, 5.0, 0.0 });
camera:setActive();

]]--

