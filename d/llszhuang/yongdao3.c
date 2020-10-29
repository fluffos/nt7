inherit ROOM;
#include <ansi.h>
int do_pick(string arg);
void create()
{
       set("short", "柳绿山庄");
        set("long",
"这是庄院的石阶，石阶呈现出一种奇异的死灰色。石阶旁边是一座假\n"
"山，假山石缝里面插着一把钢拐，直至没柄。钢拐旁边斜倚着一具骷髅，\n"
"骷髅上的白发是银灰色的。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"dynamic/jiuqu1",
          "southeast" : __DIR__"yongdao2",
        ]));

        set("item_desc", ([
                "钢拐": "这是一把精光闪闪的钢拐，虽已历经多年风雨，上面却毫无锈?踈n",
        ]) );

        set("have_weapon",1);
        setup();
}
int init()
{
        add_action("do_pick","pick");
}

int do_pick(string arg)
{
        object me,killer;
        int i;

        me = this_player();

        if( !arg || arg != "钢拐" )
                return 0;
        if( query("have_weapon") != 1 )
                return notify_fail("钢拐已经被拔走了。\n");

        i=query("neili", me);
        if( random(i)<2000 )
        {
                i -= 200;
                if( i<1 ) i = 1;
                set("neili", i, me);
                return notify_fail("你使出吃奶的力气狠命摇晃着钢拐，可钢拐纹丝不
动。\n");
        }
        addn("neili", -1000, me);
        message_vision("$N运足内力，把钢拐从假山石缝中拔了出来。\n可是...\n"+BLU
"忽然一阵阴风吹起...还..我..命..来...\n"NOR,me);
        set("have_weapon",0);
        killer = new(__DIR__"npc/wraith");
        killer->move(this_object());
        killer->set_leader(me);
        killer->kill_ob(me);
        me->fight_ob(killer);
        return 1;
}
