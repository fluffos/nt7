#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "峭壁");
        set("long", @LONG
自古有云：蜀道难，难于上青天，呜呼。无怪大诗人李白如此写。
路到了这里真可谓惊险无比，一边是滔滔的江水，一边是如刀切般的
峭壁。你正爬在一个很危险的峭壁上，你还是快走吧，别一不小心掉
了下去。
LONG );
        set("exits", ([
                  "eastdown" : __DIR__"shudao7",
                  "westup" : __DIR__"shudao9",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15060);
	set("coor/y", -1830);
	set("coor/z", -50);
	setup();
        replace_program(ROOM);
}