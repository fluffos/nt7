// Room: /d/guiyun/road3.c
// Last Modified by Lonely on Jul. 9 2001

inherit ROOM;

int go_north();
int go_south();
int do_go(string arg);

void create()
{
        set("short", "湖滨小路");
        set("long", @LONG
一条湖滨的小路，往南面看远处似乎有一家小酒馆。往北面看远处
似乎有一座庄园。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "guiyun");

        set("exits", ([
                "south": __DIR__"road2",
                "north": __DIR__"road4",
        ]) );

        set("coor/x", 290);
        set("coor/y", -850);
        set("coor/z", 0);
        setup();
}

void init()
{
        object me=this_player();

        if( !query_temp("guiyun_road", me) )
                set_temp("guiyun_road", random(4)+2, me);
        add_action("go_north","north");
        add_action("go_south","south");
        add_action("do_go","go");
}

int go_north()
{
        object me=this_player();
        int road;
        
        road=query_temp("guiyun_road", me);
        if (road > 1) {
                road--;
                set_temp("guiyun_road", road, me);
                me->move(__FILE__);
        }
        else {
                me->move(__DIR__"road4");
                delete_temp("guiyun_road", me);
        }
        return 1;
}

int go_south()
{
        object me=this_player();
        int road;
        
        road=query_temp("guiyun_road", me);
        if (road > 1)
        {
                road--;
                set_temp("guiyun_road", road, me);
                me->move(__FILE__);
        }
        else {
                me->move(__DIR__"road2");
                delete_temp("guiyun_road", me);
        }
        return 1;
}

int do_go(string arg)
{
        object me=this_player();
        int road;
        
        if (arg != "north" && arg !="south") return 0;
        road=query_temp("guiyun_road", me);
        if (road > 1)
        {
                road--;
                set_temp("guiyun_road", road, me);
                me->move(__FILE__);
        }
        else {
                if (arg == "north")
                        me->move(__DIR__"road4");
                else
                        me->move(__DIR__"road2");
                delete_temp("guiyun_road", me);
        }
        return 1;
}