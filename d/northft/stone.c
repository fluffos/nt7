// stone.c

protected int open, count;

void create()
{
	count = 3 + random(3);
}

int query_open() { return open; }

void do_push(object who)
{
	object room1, room2;

	if(!objectp(who) || open)
		return;

	if(!objectp(room1 = find_object(__DIR__"ftn11"))
	&& !objectp(room1 = load_object(__DIR__"ftn11")) )
		return;
	if(!objectp(room2 = find_object(__DIR__"ftn12"))
	&& !objectp(room2 = load_object(__DIR__"ftn12")) )
		return;

	if(--count <= 0)
	{
		count = 3 + random(3);
		open = 1;

set("exits/east", __DIR__"ftn12", 		room1);
set("exits/west", __DIR__"ftn11", 		room2);
		tell_object(room1, "大石头“轰隆”一声滚到了一旁。\n");	
		tell_object(room2, "大石头“轰隆”一声滚到了一旁。\n");

		if(find_call_out("do_close") >= 0)
			remove_call_out("do_close");
		call_out( "do_close", 300);
	}

	else
		tell_object(who, "大石头纹丝没动。\n");
}

protected void do_close()
{
	object room1, room2;

	if(!objectp(room1 = find_object(__DIR__"ftn11"))
	&& !objectp(room1 = load_object(__DIR__"ftn11")) )
		return;
	if(!objectp(room2 = find_object(__DIR__"ftn12"))
	&& !objectp(room2 = load_object(__DIR__"ftn12")) )
		return;

delete("exits/east", 	room1);
delete("exits/west", 	room2);

	tell_object(room1, "大石头“轰隆”一声滚到了路中间挡住了去路。\n");	
	tell_object(room2, "大石头“轰隆”一声滚到了路中间挡住了去路。\n");

	open = 0;
}
