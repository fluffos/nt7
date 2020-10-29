// xiongdong.c 熊洞
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIB"熊洞"NOR);
        set("long", @LONG
此处为一熊洞，洞内极是宽敞，有八九丈深，中间透入一线天光，
宛似天窗一般。此洞以前有几条白熊在此居处，但后来张翠山夫妇杀
熊而住在此处，故此陶碗、土灶、石床、粗具等一应俱全。
LONG );
	set("exits",([
		"out" : __DIR__"shishan",
	]));
        set("objects",([
                  "/d/mingjiao/obj/luopan" :  1,
	]));
        set("no_fight", 1);
        set("sleep_room", 1);
	setup();
}
