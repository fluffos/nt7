inherit ROOM;
void create()
{
        set("short", "七曲九回廊");
        set("long",
"这里是七、八十道长廊，相互接连，连绵不绝，直是无穷无尽。每个\n"
"长廊转弯处都有一盏宛如鬼火般摇晃不定的黄灯。廊边的潭水在灯光照射\n"
"下发出墨绿的异光。\n"
);
        set("no_magic", "1");

        setup();
}


int valid_leave(object me, string dir)
{
        object killer;

        if( random(query("kar", me))<20 && 
            ! objectp(present("figure", environment(me)))) 
        {
                killer = new(__DIR__"npc/killer");
                NPC_D->set_from_me(killer, me, 100);
                message_vision(killer->name() + "大声喝道：谁人敢擅闯柳绿山庄？！拿命来吧！\n", me);
                killer->move(environment(me));
                killer->set_leader(me);
                return notify_fail("只见突然从地板下窜出一人，拦住了你的去路。\n");
        }
        return ::valid_leave(me, dir);
}

