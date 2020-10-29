// xdong.c 石洞
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIB"石洞"NOR);
        set("long", @LONG
此处为一小山洞，中间透入一线天光，宛如天窗一般。这里陶碗、
土灶、石床、厨具等一应俱全。
LONG );
	set("exits",([
		"out" : __DIR__"shishan1",
	]));
/*
        set("objects",([
                CLASS_D("mingjiao") + "/xie" : 1,
	]));
*/
	setup();
}
