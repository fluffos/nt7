inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
这里是一片茂密的树林(wood)，翠绿色的树阴遮盖着天空，偶尔
还从林子深处传来几声不知什么野兽的嘶叫。旁边立着一张木牌(pai
)。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "east"      : __DIR__"shulin",
                "southwest" : __DIR__"caomeide",
        ]));
        set("quarrys", ([
                "tu"         : 100000,
                "ji"         : 80000,
                "pao"        : 50000,
                "caihuashe"  : 50000,
                "dushe"      : 20000,
                "hu"         : 5000,
                "bao"        : 2000,
                "laohu"      : 2000,
        ]));
        
        set("item_desc", ([
                "pai"  : "保护树林  适量砍伐\n",
                "wood" :"一片可砍伐的树林。\n",
        ]));        
                
         set("coor/x", -50000);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
         replace_program(ROOM);
}

void init()
{
        add_action("do_cut","cut");
}

int do_cut(string arg)
{
        object me = this_player();
        object ob;
 
        if (! arg || arg != "wood")
                return notify_fail("你要砍什么？\n");
                
        if (present("chai dao", me))
                return notify_fail("没有柴刀怎么砍柴？\n");
                
        if (query_temp("times") == 0)
                return notify_fail("请适量砍伐！\n");
 
        if( query("qi", me)<20 )
                return notify_fail("你的气太虚弱，不能砍柴！\n");
 
        ob = new("/d/baituo/obj/chai");
        ob->move(environment(me));
        addn("qi", -20, me);
        addn_temp("times", -1);
        message_vision("$N砍了一捆柴，累得够呛。\n", me);
        return 1;
}
