function print_table(table)
  for k,v in pairs(Assets)
  do
    print(k, v)
    if type(v) == 'table' then
      print_table(v)
    end
  end
end

Assets.setLoaderPath 'src/Forge/AssetPlugins'
Assets.addLoader 'ObjLoader'
Assets.addLoader 'ImageLoader'
mesh = Assets.load 'data/meshes/alleyway_1.obj'

-- Create test mesh and scene node
Scene.createNode 'test'
Scene.attach(Scene.nodes.test, mesh)

-- Create camera and camera node
Scene.createCamera('main', 45, 1, 1000)
Scene.createCamera('left', 45, 1, 1000)
Scene.createCamera('right', 45, 1, 1000)
Scene.createNode 'cameraMain'
Scene.createNode 'cameraLeft'
Scene.createNode 'cameraRight'
Scene.translate(Scene.nodes.cameraMain, 0, 5, -30)
Scene.translate(Scene.nodes.cameraLeft, -10, 5, -40)
Scene.translate(Scene.nodes.cameraRight, 10, 5, -40)
Scene.attach(Scene.nodes.cameraMain, Scene.cameras.main)
Scene.attach(Scene.nodes.cameraLeft, Scene.cameras.left)
Scene.attach(Scene.nodes.cameraRight, Scene.cameras.right)

function print_table(table, indent)
  local indentation = indent or 0
  for k,v in pairs(table)
  do
    if indentation > 0 then
      for i=1,indentation do
        io.write('\t')
      end
    end
    print(k, v)
    if type(v) == 'table' then
      print_table(v, indentation + 1)
    end
  end
end

Renderer.createViewport('top', 0, 0.5, 1, 0.5)
Renderer.createViewport('bottomLeft', 0, 0, 0.5, 0.5)
Renderer.createViewport('bottomRight', 0.5, 0, 0.5, 0.5)

Renderer.bindCamera('top', Scene.cameras.main)
Renderer.bindCamera('bottomLeft', Scene.cameras.left)
Renderer.bindCamera('bottomRight', Scene.cameras.right)
Renderer.start()

--print('\nAsset table contents:\n')
--print_table(Assets)

--print('\n Scene table contents:\n')
--print_table(Scene)

--print('\n Renderer table contents:\n')
--print_table(Renderer)

start = os.clock()
current = os.clock()
while current - start < 5.0
do
  current = os.clock()
end

--[[ 

-- Acquire mesh assets and camera for rendering

-- Should be able to render meshes now!

]]--

--[[

Need the camera in renderer.

1. get camera properties (perspective matrix)
2. get camera node transform (view matrix) 

For each mesh
  3. Get mesh transform (world matrix)
  4. Get mesh material
  5. Apply matrices to material uniforms
  6. Draw mesh using material

RendererThread needs to know about assets and scene data

AssetsLibrary must provide C++ with asset data

SceneLibrary must provide C++ with scene data

]]--