// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
        set("short", "仙人洞");
        set("long", @LONG
这个洞高七尺，里面光线暗淡，你看不清是否洞里有任何器物，
只有洞口堆着半尺来高的山羊粪。
LONG );
        set("exits", ([
                "down" : "/d/xingxiu/xrdong",
        ]));
        set("cost", 2);
        
        setup();
}
void init()
{
        add_action("do_use", "use");
        add_action("do_zuan", "zuan");
}

int do_use(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(

"你点燃了火折，发现西面石壁上有一道裂缝，似乎可以钻(zuan)出去。\n");
        set_temp("marks/钻", 1, this_player());
             return 1;
       }
}

int do_zuan(string arg)
{
        object me = this_player();
        
        if( query_temp("marks/钻", me)){

        message("vision", me->name() +
"滋溜一下不知从什么地方钻出去了。\n",
                    environment(me), ({me}) );
            me->move("/d/xingxiu/icecave1");
            message("vision", me->name() + "从石缝里钻了出来。\n",
                    environment(me), ({me}) );
            delete_temp("marks/钻", this_player());
        return 1;
        }
        else {
            write("你想往哪儿钻?!\n");
            return 1;
        }
}
