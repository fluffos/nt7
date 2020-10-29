#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "卧室" NOR);
        set("long", @LONG
这是村长家卧房，因门窗常闭着，光线很昏暗。卧室里别无他物，
只有中间放着一张收拾得舒舒服服的大床，看着就让人想睡觉（输入
指令 sleep）。
LONG);
        set("exits", ([
                "south" : __DIR__"cunzhangjia",
        ]));

        set("xinshoucun", 1);
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);

        set("no_pk", 1);
	setup();

        replace_program(ROOM);
}