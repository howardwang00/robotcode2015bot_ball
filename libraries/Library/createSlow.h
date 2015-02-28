void createSlow()
{
	create_connect();
	create_write_byte(144);
	create_write_byte(32);
	create_write_byte(0);
	create_write_byte(0);
}
