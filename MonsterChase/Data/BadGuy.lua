
Version = "Alpha"

Player =
{
	name = "GoodGuy",
	class = "Player",
	Controller = "Controller",
	init_position = {0, -100.0, 0.0},
	rotation = 0.0,
	size = {320.0, 236.0, 0.0},

	PhysicsManager_settings = 
	{
		mass = 2.0,
		drag = 0.3,
		init_velocity = {0.0, 0.0, 0.0}
	},

	render_settings = 
	{
		sprite_path = "Data\\BadGuy.dds",
		sprite = 
		{
			offset = {0.0, 0.0},
			extents = {-1.0, -1.0, 1.0, 1.0}
		},

		color = {255.0, 255.0, 255.0, 255.0}
	}

}