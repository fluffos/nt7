#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
这里是冰火岛祭坛内的一处密道，幽幽长长，深不见底不
知道通向何处。密道内灯光昏暗，阴风阵阵，不时传来诡异的
笑声，偶尔还触及一两根不知是人是兽的枯骨，让你全身直起
鸡皮疙瘩。情急之下只有四处寻路(xunlu)看看有没新的出路。
LONG);
        set("no_sleep_room",1);
        set("objects", ([
                "/clone/dream_npc/shenlongdao/xixue-bianfu" : 6+random(8),
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me = this_player();
        add_action("do_wang", "xunlu");
        me->start_busy(2 + random(3));

        if (random(2))
        {
                tell_object(me, HIC "你不小心踩到一副枯骨，竟然惊慌异常……\n" NOR);
        }
        else
        {
                tell_object(me, HIC "突然一群吸血蝙蝠飞过，你连忙应付 ……\n" NOR);
        }
}

int do_wang()
{
        object ob = this_player();

        message_vision(HIC "\n$N" HIC "四处乱窜，寻找新的出路，似乎发现远处射出一丝光亮。\n"NOR, ob);

        switch (random(4))
        {
        case 0 : set("exits/east", __DIR__"st1"); break;
        case 1 : set("exits/east", __DIR__"st2"); break;
        case 2 : set("exits/east", __DIR__"st1"); break;
        default: set("exits/east", __DIR__"st2");
        }
        switch (random(4))
        {
        case 0 : set("exits/west", __DIR__"st1"); break;
        case 1 : set("exits/west", __DIR__"st1"); break;
        case 2 : set("exits/west", __DIR__"st2"); break;
        default: set("exits/west", __DIR__"st2");
        }
        switch (random(4))
        {
        case 0 : set("exits/south", __DIR__"st2"); break;
        case 1 : set("exits/south", __DIR__"st2"); break;
        case 2 : set("exits/south", __DIR__"st1"); break;
        default: set("exits/south", __DIR__"st1");
        }
        switch (random(4))
        {
        case 0 : set("exits/north", __DIR__"jitaiqian"); break;
        case 1 : set("exits/north", __DIR__"st1"); break;
        case 2 : set("exits/north", __DIR__"st2"); break;
        default: set("exits/north", __DIR__"st1");
        }
        remove_call_out("close_out");
        call_out("close_out", 15);
        return 1;
}

void close_out()
{
        if (query("exits/east"))
                delete("exits/east");

        if (query("exits/west"))
                delete("exits/west");

        if (query("exits/south"))
                delete("exits/south");

        if (query("exits/north"))
                delete("exits/north");
}
