
Version = "Alpha"

Player =
{
	--basic info
	name = "text",
	controller = "Controller",
	position = {0.0, -1000.0, 0.0},
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
		sprite_path = "Data\\gameover.dds"
	}
}