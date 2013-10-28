-- Defines a technique
--[[
  All shaders used with Forge must at least
  accept the following vertex shader inputs
  for mesh material techniques:

  location 0: position,
  location 1: ST tex coord,
  location 2: normal,
  location 3: tangent,
  location 4: bitangent

  Legacy lighting sets the light values manually to
  Light* uniforms instead of a single block binding
]]--

technique = {
  description = "Simple color shader",
}

-- Conditional inclusion of legacy shaders
if Forge.openGL < 3.3 then  
  technique.shaders = {
    vertex = "data/shaders/SimpleTextureLegacy.vs",
    fragment = "data/shaders/SimpleColorLegacy.fs"
  }
else
  technique.shaders = {
    vertex = "data/shaders/SimpleTexture.vs",
    fragment = "data/shaders/SimpleColor.fs"
  }
end

