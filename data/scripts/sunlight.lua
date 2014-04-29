sunlight = 0.0
speed = 0.1

function update()
	sunlight = sunlight + speed
	if sunlight > 360 then
		sunlight = 0
	end
end

