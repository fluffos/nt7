#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIM "【天外桃源】" NOR);
        set("long", HIM @LONG

                天     外     桃      源
    天空的尽头是一处桃源胜地，宇宙似乎没有终点，你始终能发现
不一样的天地，四周紫气氤氲，白云缭绕，难道是传说中的仙境？琴
音又再响起，但似乎听得更加清晰了，隐约间，你面前出现了一位熟
悉的青年，他随意拨弄着古琴，阵阵天籁之音令你心旷神怡。你只想
永远留在此处，不再理会人间的纷争与情仇。
LONG NOR );

        set("sleep_room", 1);
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/tianshen2": 1,
        ]));
        set("no_clean_up", 1);
        set("no_roar", 1);
        set("no_flyto", 1);    // 不能骑马或MISS到这里，已经在horse.c做限制
        set("no_rideto", 1);   // 不能骑马或MISS到这里，已经在horse.c做限制
        set("no_obsend", 1);
        set("no_paimai", 1);
        set("sky", 1);
        
        setup();
}

void init()
{
        object me = this_player();
        
        tell_object(me, HIG "\n恭喜你，已经完成所有二转任务，与天神对话即可完成二转！\n" NOR);
}
