
Version = "Alpha"

Player =
{
	name = "GoodGuy",
	class = "Player",
	controller = "Controller",
	init_position = {-300.0, -100.0, 0.0},
	rotation = 0.0,
	size = {88.0, 164.0, 0.0},

	PhysicsManager_settings = 
	{
		mass = 1.0,
		drag = 0.0,
		init_velocity = {50.0, 1.0, 0.0}
	},

	render_settings = 
	{
		sprite_path = "Data\\GoodGuy.dds",
		sprite = 
		{
			offset = {0.0, 0.0},
			extents = {-1.0, -1.0, 1.0, 1.0}
		},

		color = {255.0, 255.0, 255.0, 255.0}
	}

}