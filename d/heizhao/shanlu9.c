// Room: /heizhao/shanlu9.c
// Date: Dec. 8 1999 by Lonely

inherit ROOM;

int do_find(string arg);
void create()
{
        set("short", "山路");
        set("long", @LONG
又行了一阵，正觉唇干口渴，忽听远处传来隐隐水声，你当即
加快脚步。空山寂寂，那水声在山谷间激荡回响，轰轰汹汹，愈走
水声愈大，待得走上岭顶，只见一道白龙似的大瀑布从对面双峰之
间奔腾而下，声势甚是惊人。从岭上望下去，瀑布旁有一间草屋。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                //"northdown" : __DIR__"pubu",
                "northdown" : __DIR__"yideng1",
                "eastdown"  : __DIR__"shanlu8",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1290);
        set("coor/z", 30);
        setup();
}

void init()
{
        add_action("do_find", "find");
        add_action("do_find", "zhao");
}

int do_find(string arg)
{
        object me;
        object *inv;
        int i;
        me=this_player();

        if( arg == "way" && query("family/master_id", me) == "yidengdashi" )
        {
                        
                inv=all_inventory(me);
                for(i=0; i<sizeof(inv); i++) {
                        if (userp(inv[i]))
                                return notify_fail("你负重太大了，没法找路爬山。\n");
                }
                tell_object(me, "你左右看看没人注意你，偷偷摸摸拨开树丛溜了进去。\n");
                tell_object(me, "你从一条没人知道的小路上了山，来到了一灯大师所在的地方。\n");
                me->move(__DIR__"yideng9");
                return 1;
        }
        return 0;
}

