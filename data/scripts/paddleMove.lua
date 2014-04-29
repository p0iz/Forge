
function update()
	if Input.isKeyDown(Input.Key.A) then
		print('Move paddle left')
	elseif Input.isKeyDown(Input.Key.D) then
		print('Move paddle right')
		Renderer.stop()
	end
end
