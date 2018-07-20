
Version = "Alpha"

Player =
{
	--basic info
	name = "pat",
	controller = "Controller",
	position = {-360, -20.0, 0.0},
	rotation = 0.0,	

	--collider info
	Collider = 
	{
		isCollider = true,
		size = {8.0, 40.0, 0.0}
	},

	--rigidbody info
	Rigidbody = 
	{
		isRigidbody = true,
		mass = 1.0,
		drag = 10.0,
		velocity = {0.0, 0.0, 0.0}
	},

	--renderer info
	Renderer = 
	{
		isRenderer = true,
		sprite_path = "Data\\pat.dds"
	}
}