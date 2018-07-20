
Version = "Alpha"

Player =
{
	--basic info
	name = "bg",
	controller = "Controller",
	position = {0.0, -225.0, 0.0},
	rotation = 0.0,	

	--collider info
	Collider = 
	{
		isCollider = false,
		size = {0.0, 0.0, 0.0}
	},

	--rigidbody info
	Rigidbody = 
	{
		isRigidbody = false,
		mass = 1.0,
		drag = 0.0,
		velocity = {0.0, 0.0, 0.0}
	},

	--renderer info
	Renderer = 
	{
		isRenderer = true,
		sprite_path = "Data\\bg.dds"
	}
}