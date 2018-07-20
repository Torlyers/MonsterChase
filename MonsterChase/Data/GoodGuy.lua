
Version = "Alpha"

Player =
{
	--basic info
	name = "GoodGuy",
	controller = "Controller",
	position = {300.0, -100.0, 0.0},
	rotation = 0.0,	

	--collider info
	Collider = 
	{
		isCollider = true,
		size = {88.0, 164.0, 0.0}
	},

	--rigidbody info
	Rigidbody = 
	{
		isRigidbody = true,
		mass = 1.0,
		drag = 0.0,
		velocity = {-40.0, 1.0, 0.0}
	},

	--renderer info
	Renderer = 
	{
		isRenderer = true,
		sprite_path = "Data\\bg.dds"
	}
}