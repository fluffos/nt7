// Room: /d/suzhou/caixingjing.c
// Last Modified by Lonely on May. 15 2001

inherit ROOM;

void create()
{
        set("short", "采香径");
        set("long",@long
这里名为采香径，又称“一箭径”，此溪乃吴王夫差陪西施游山之
必经之水道，也是越伐吴时，范蠡携西施，驾小舟出逃之处。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "northeast" : __DIR__"shuiwa",
                "northwest" : __DIR__"shuiwa1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1120);
	set("coor/y", -1160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}