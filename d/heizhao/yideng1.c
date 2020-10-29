//Cracked by Kafei
// yideng quest room 1
// acep

inherit ROOM;

void create()
{
        set("short", "无名山");
        set("long", @LONG
此处正是山岭的顶部，山峰穿云插天，山石滑溜，空山寂寂，只
见一道白龙似的大瀑布(waterfall)从对面双峰之间奔腾而下，声势甚
是惊人，水声在山谷间激荡回响，轰轰汹汹，从岭上望下去，瀑布旁
有一间草屋。
LONG );

        set("exits", ([
                "southup" : __DIR__"shanlu9",
                ]));

        set("objects", ([
                CLASS_D("dali") + "/fisher" : 1,
        ]));

        set("item_desc", ([
                "waterfall" : "
你目光随着瀑布向下流动，突然眼前金光闪烁，水底有物游动，
定睛望去，只见一对金娃娃钻在山石之中，两条尾巴却在外乱晃。\n",
                ]) );

        set("invalid_startroom", 1);
        set("outdoor", "taoyuan");
        set("no_magic", 1);
        set("cost", 1);
        set("coor/x", -38000);
        set("coor/y", -80000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_dive", "dive");
}

int do_dive(string arg)
{
        object me = this_player();

        if ( !arg || arg != "waterfall" )
                return notify_fail( "什么？\n");

        message_vision("$N纵身跳入了瀑布中。\n", me);
        if ( me->query_skill("dodge",1) <= 50 ) {
                message_vision("$N双足一入水，瀑布的急流便冲得他左摇右晃，难以站稳。一会儿便发出\n", me);
                message_vision("一声惨嚎，被山洪冲得无影无踪了。\n", me);
                set_temp("die_reason", "被山洪淹死了", me);
                me->receive_wound("qi",query("max_qi", me)+100);
        }

        if ( me->query_skill("dodge",1) > 50 &&
                me->query_skill("dodge",1) < 120 ) {
                message_vision("$N双足一入水，瀑布的急流便冲得左摇右晃，难以站稳。只好勉力提气\n", me);
                message_vision("，回身跳向岸边。\n", me);
                me->unconcious();
        }

        if ( me->query_skill("dodge",1) >= 120 ) {
                me->move(__DIR__"yideng2");
                message("vision", me->name()+"“噗咚”的一声跳了下来。\n",environment(me), ({me}) );
        }
        return 1;
}
