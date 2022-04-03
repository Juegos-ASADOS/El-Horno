local scene = handler.root.people

if #scene.nodes > 1 then
   scene = scene.person
end

for i, n in pairs(scebe) do
  n.position{x, y, z}
  n.rotation{qw, qx, qy, qz}
  n.scale{x, y, z}
  n.entity{name, layer}
  n.components{mesh{meshFile}, rigidbody{mass, isTrigger, colshape}, particleSystem{name, particleFile}}
end
