
#define CTL_MINE	__DIR__"iron_mine"

#include <mine_def.h>

inherit ROOM;

void create()
{
	set("short", "矿区");
	set("long", @LONG
这里是一片巨大的矿区，放眼一望四处是巨大的岩石，很多
岩石上还留有被人敲砸过的痕迹，地上还散落着一些碎石头。
LONG
	);

	setup();
}

int cmd_dig_function(object me, string arg)
{
	if(!me || (environment(me) != this_object()))
		return 0;

	if( query("qi", me) <= 20 )
		return notify_fail("你已经累的没有一点力气了。\n");

	message_vision("$N抡起手中的十字镐狠狠的砸了下去。\n", me);
	me->start_busy(10);
	call_out("finish_dig", 3+random(3), me);
	return 1;
}

protected void finish_dig(object me)
{
	object stone;

	if(!me || (environment(me) != this_object()))
		return 0;

	me->stop_busy();

	if( query("qi", me) <= 20 )
	{
		tell_object(me, "你已经累的没有一点力气了。\n");
		return;
	}

addn("qi", -20, 	me);

	if(!random(10) || !objectp(stone = new(MINE_STONE)))
	{
		tell_object(me, "结果什么也没能砸下来。\n");
		return;
	}

	if(random(10))
		CTL_MINE->setup_stone(stone);

	if(!stone->move(this_object()))
	{
		destruct(stone);
		return;
	}
	message_vision(sprintf("$N敲下了一块%s。\n", stone->name()), me);
}
