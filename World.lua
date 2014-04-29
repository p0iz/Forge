-- Scene file

world = GameObject
{ -- Actual object
  Transform(0,0,0), -- Component
  Mesh("data/meshes/alleyway_1.obj"), -- Another component
  Script("data/scripts/sunlight.lua") -- Yet another component
}

print "World loaded."

paddle = GameObject
{
  transform = Transform(0,5,0),
  mesh = Mesh("data/meshes/paddle.obj"),
  script = Script("data/scripts/paddleMove.lua"),
  -- child nodes are nested game objects
  {
    GameObject
    {
      Transform(0,0,-10)
    }
  }
}

print "Paddle loaded."

--[[
light = GameObject
{
  Transform(-10,10,-5),
  Light(Light.point, 1, 1, 1, 1)
}

camera = GameObject
{
  Transform(0,5, 10)
  Camera(45.0f, 10, 1000)
}

mainView = Renderer.createViewport("main", 0,0, 1,1)
mainView:bindCamera(camera)

]]--

Renderer.start()

--[[ Inter-component usage

paddle.script:use(t, 'transform')
paddle.mesh:use(material)

]]--

--[[ Game object constructor inits components
GameObject(Components...)
  for each component in Components
    component.init(self) -- Sets up the component and stores a reference to the object
  end
]]--


--[[ main loop

update input
update scripts
update view

read input state

for each s in Script
  s.update(delta)
end

for each m in Mesh
  m.draw()
end

]]--
