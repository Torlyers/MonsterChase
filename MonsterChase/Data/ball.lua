
Version = "Alpha"

Player =
{
	--basic info
	name = "ball",
	controller = "Controller",
	position = {0.0, 0.0, 0.0},
	rotation = 0.0,	

	--collider info
	Collider = 
	{
		isCollider = true,
		size = {6.0, 6.0, 0.0}
	},

	--rigidbody info
	Rigidbody = 
	{
		isRigidbody = true,
		mass = 0.001,
		drag = 0.0,
		velocity = {0.0, 0.0, 0.0}
	},

	--renderer info
	Renderer = 
	{
		isRenderer = true,
		sprite_path = "Data\\ball.dds"
	}
}