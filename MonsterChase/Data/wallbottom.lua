
Version = "Alpha"

Player =
{
	--basic info
	name = "text",
	controller = "Controller",
	position = {0.0, -225.0, 0.0},
	rotation = 0.0,	

	--collider info
	Collider = 
	{
		isCollider = true,
		size = {900.0, 20.0, 0.0}
	},

	--rigidbody info
	Rigidbody = 
	{
		isRigidbody = true,
		mass = 1000.0,
		drag = 1000.0,
		velocity = {0.0, 0.0, 0.0}
	},

	--renderer info
	Renderer = 
	{
		isRenderer = false,
		sprite_path = "Data\\text.dds"
	}
}