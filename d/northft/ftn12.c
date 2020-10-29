// Room: /d/northft/ftn12.c

inherit ROOM;

protected int open, count;
protected object mob;

protected object query_mob()
{
	if(!mob)
		mob = find_object(__DIR__"stone");
	if(!mob)
		mob = load_object(__DIR__"stone");

	return mob;
}

string query_long()
{
	object ob = query_mob();

	if(!ob || ob->query_open())
		return "这是一条窄窄的上山小路，两旁怪石嶙峋，中间的路倒是很
平坦，看样子是被人专门开掘出来的。\n";
	else
		return "这是一条窄窄的上山小路，两旁怪石嶙峋，中间的路倒是很
平坦，看样子是被人专门开掘出来的。路中央一块大石头挡住了
向西的去路。\n";
}

mapping query_desc()
{
	object ob = query_mob();

	if(ob && !ob->query_open())
		return ([
"石头" : "这是一块大青石头，不知道能不能推(push)开。\n",
"大石头" : "这是一块大青石头，不知道能不能推(push)开。\n",
]);

	else
		return 0;
}

void create()
{
	set("short", "山路");
	set("long",  (: query_long :));
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"ftn13",
]));

	set("item_desc", (: query_desc :));

	set("outdoors", "northft");
	setup();
}

void init()
{
	add_action("do_push", "push");
}

int do_push(string arg)
{
	object ob = query_mob(), me = this_player();

	if( !ob || ob->query_open() || ((arg != "石头") && (arg != "大石头")) )
		return 0;

	message_vision("$N双膀一较力，使劲推了一下大石头。\n", me);
	ob->do_push(me);

	return 1;
}
