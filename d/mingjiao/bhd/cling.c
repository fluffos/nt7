// chongling.c 丛林
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIG"丛林"NOR);
        set("long", @LONG
向北一直走出二十余里，就是一大片丛林了。原来此岛方圆极广，
延伸至北，不知尽头。丛林老树参天，阴森森的遮天蔽日，林内有什
么古怪，却是不得而知。遇有好事之人肯定要进入一探的。
LONG );
	set("outdoors","冰火岛");
	set("exits",([
		"south" : __DIR__"shishan",
                "north" : __DIR__"cling1",
	]));
	setup();
}
