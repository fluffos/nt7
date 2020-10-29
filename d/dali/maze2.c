// Code of ShenZhou
// Room: /d/dali/maze2.c
// AceP

inherit ROOM;

int do_findout(string);
int do_out();

void create()
{
        set("short", "迷宫树林");
        set("long", @LONG
这是迷宫中的一个路口，但见四下黑森森的都是树木，脚下小路
东盘西曲，密林中难辨方向，举步踏到的尽是矮树杂草，荆棘钩刺到
小腿，划得你鲜血淋淋。一个小木桩上钉了五个木牌，分别指向五条
小路，并标明『金，木，水，火，土』。北边树木稀少些，看来可以
是走出去(out)的方向。
LONG );
        set("exits", ([
                "金" : __FILE__,
                "木" : __FILE__,
                "水" : __FILE__,
                "火" : __FILE__,
                "土" : __FILE__,
                ]));

        set("invalid_startroom", 1);
        set("cost", 3);
        set("outdoors", "dali");
        set("coor/x", -38000);
        set("coor/y", -71020);
        set("coor/z", 0);
        setup();
}

void init()
{
        object me;
        me=this_player();

        if (me->query_skill("dodge",1)<100 && random(10)==1) {
                message_vision("$N一个不小心，在树丛上一拌，“咕嘟”一下摔进了荆棘丛。\n", me);
                addn("qi", -100, me);
                addn("eff_qi", -100, me);
                message_vision("$N挣扎了半天，从荆棘丛里爬了出来，浑身扎满了刺，痛苦难当。\n", me);
        }
        add_action("do_findout", "findout");
        add_action("do_out", "out");
}

int valid_leave(object me, string dir)
{
        int mazepath;
        string walked,mpath;

        mazepath=query_temp("mazepath", me);

        mpath=sprintf("%d",mazepath);
        tell_object(me, "密码："+mpath+"\n");

        walked=sprintf("%d%d%d%d%d",(query_temp("mark/maze金", me)-1),(query_temp("mark/maze木", me)-1),(query_temp("mark/maze水", me)-1),(query_temp("mark/maze火", me)-1),(query_temp("mark/maze土", me)-1));
        tell_object(me, "走过："+walked+"\n");

        addn("qi", -10, me);

        if (walked==mpath) {
                tell_object(me,"你苦思冥想，精掐细算，终于找到了破此迷宫之道。只三转两转，便走了出去。\n");
                set("exits/"+dir, "/d/dali/yingroom1.c");
                remove_call_out("closing");
                call_out("closing",1,dir);
                return 1;
        }
                
        if (dir=="金")
                addn_temp("mark/maze金", 1, me);
        if (dir=="木")
                addn_temp("mark/maze木", 1, me);
        if (dir=="水")
                addn_temp("mark/maze水", 1, me);
        if (dir=="火")
                addn_temp("mark/maze火", 1, me);
        if (dir=="土")
                addn_temp("mark/maze土", 1, me);
        return ::valid_leave(me, dir);
}

void closing(string dir)
{
        set("exits/"+dir, __FILE__);
        return;
}

int do_findout(string arg)
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
                me->move("/d/dali/yideng9.c");
                return 1;
        }
        return 0;
}

int do_out()
{
        object me;
        me=this_player();

        tell_object(me, "你苦思冥想，左转右看了许久，觉得没有什么办法找到路，只好从原路退了回去。\n");
        set_temp("mark/maze金", 1, me);
        set_temp("mark/maze木", 1, me);
        set_temp("mark/maze水", 1, me);
        set_temp("mark/maze火", 1, me);
        set_temp("mark/maze土", 1, me);
        delete_temp("mazepath", me);
        me->move("/d/dali/maze1.c");
        return 1;
}