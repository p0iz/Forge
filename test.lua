
-- Asset file loaders
Assets.setLoaderPath 'build/debug/src/Forge/AssetPlugins'
Assets.addLoader 'ObjLoader'
Assets.addLoader 'ImageLoader'

-- Lights!
Scene.addDirectionalLight({1, -1, -1}, {0.0, 1.0, 0.0, 1.0})
Scene.addPointLight({10, 10, 10}, {0.0, 0.0, 1.0, 1.0})

-- Create camera and camera node
Scene.createCamera('main', 45, 1, 1000)
Scene.createCamera('left', 45, 1, 1000)
Scene.createCamera('right', 45, 1, 1000)
Scene.createObject 'cameraMain'
Scene.createObject 'cameraLeft'
Scene.createObject 'cameraRight'
Scene.translate(Scene.objects.cameraMain, 0, 5, -30)
Scene.translate(Scene.objects.cameraLeft, -10, 5, -40)
Scene.translate(Scene.objects.cameraRight, 10, 5, -40)
Scene.attach(Scene.objects.cameraMain, Scene.cameras.main)
Scene.attach(Scene.objects.cameraLeft, Scene.cameras.left)
Scene.attach(Scene.objects.cameraRight, Scene.cameras.right)

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

while current - start < 1.0
do
  current = os.clock()
end

Scene.createObject 'test'
mesh = Assets.load 'data/meshes/paddle.obj'
Components.mesh(Scene.objects.test, mesh)

start = os.clock()
while current - start < 3.0
do
  current = os.clock()
  Scene.translate(Scene.objects.test, 0.0001 * (current - start), 0, 0)
end

alley = Assets.load 'data/meshes/alleyway_1.obj'

-- Add alley to scene
Scene.createObject 'Alley'
Components.mesh(Scene.objects.Alley, alley)

start = os.clock()
while current - start < 5.0
do
  Scene.translate(Scene.objects.cameraMain, 0.000001, 0, 0.00001)
  current = os.clock()
end

start = os.clock()
while current - start < 2.0
do
  Scene.translate(Scene.objects.cameraMain, 0.000001, 0, 0.00001)
  current = os.clock()
end

-- Main loop
while not Input.keyDown(Input.Key.A)
do
  
end
