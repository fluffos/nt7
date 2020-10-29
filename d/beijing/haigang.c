#include <ansi.h>

inherit BUILD_ROOM;

void create()
{
        set("short", "东海之滨");
        set("long", @LONG
这里是大海之滨，浪花拍打着礁石，发出阵阵响声，海面上一群
群海鸥『欧欧。。』地叫着，不时有鱼儿跃出海面，溅起层层的浪花。
边上有艘大船(chuan)， 船上坐着几个渔夫打扮的人，乘船可渡过大
海到达海的另一端。西面一直走就是燕京了，东面是一望无际的大海。
极目眺望不禁让人心胸开扩，神舒意畅，的确是一个好居处。
LONG );
        set("exits", ([
                "west" : "/d/beijing/road10",
                "north" : "/d/tulong/tulong/haian",
        ]));
        set("item_desc", ([
                "chuan" : "一艘大帆船，造得很结实，看来可以出远海的。\n",
        ]));
        set("objects", ([
                "/d/beijing/npc/flowerg":1,
                "/d/shenlong/npc/chuanfu" : 1,
                "/d/shenlong/npc/xiucai" : 1,
        ]));
        set("max_room", 5);
        set("outdoors", "beijing");
        set("navigate",1);
        set("opposite","/d/shenlong/haitan");
	set("coor/x", -2760);
	set("coor/y", 7550);
	set("coor/z", 0);
	setup();
}

/*
// 路径改在杭州钱塘江畔
void init()
{
        object dao, room, ren, ding;
        object me = this_player();
        room = get_object("/d/tulong/tulong/huichang");
        ding = present("chang jinpeng", room);

        if (objectp(ding)) 
        dao = present("tulong blade", ding);
        if (! dao)
        {
                ding = present("ding", room);
                if (objectp(ding)) 
                dao = present("tulong blade", ding);
        }

        if (objectp(dao))
        {
                room = get_object("/d/tulong/tulong/daobian");
                ren = present("bai guishou",room);
                tell_object(me, HIC "你看见沙滩上停泊满了海船，所有的海船全部标记着天鹰教的标记。\n"NOR);
                tell_object(me, CYN "白龟寿对你说道：我天鹰教得到屠龙宝刀，这位武林同道可愿意参加扬刀立威大会？\n"NOR);
                message("vision", HIR"\n【倚天屠龙】" NOR+WHT "白龟寿仰天一声长笑。\n" NOR, all_interactive());
                message("vision", HIR"\n【倚天屠龙】" NOR+WHT "白龟寿：我天鹰教得到屠龙宝刀，今在王盘山岛举行扬刀立威大会。\n" NOR, all_interactive());
                remove_call_out("mes");
                call_out("mes",1,this_player());
                set_temp("to_wang", 1, this_player());
                add_action("do_accept", ({ "accept", "jieshou" }));
        }
        add_action("do_enter", "enter");
}

void mes(object me)
{
      if (!me) return;
        message_vision(HIR "你愿意参加(accept/jieshou)王盘山岛扬刀立威大会吗？\n"NOR, me);
}

int do_accept()
{
        object me = this_player();
        if( query_temp("to_wang", me) )
        {
                tell_object(me, HIR "你决定去参加扬刀立威大会。\n" NOR);
                remove_call_out("moveto");
                call_out("moveto",10,me);
        }
        return 1;
}

int moveto(object me)
{
        me->move("/d/tulong/tulong/boat");
        message_vision(HIC "\n$N坐上了天鹰教的大船，听到舵子手喊道：“开船了！”，大船慢慢的向大海驶进。\n"NOR, me);
        remove_call_out("arrive1");
        call_out("arrive1",10,me);
        return 1;
}

int arrive1(object me)
{
        message_vision(HIB "\n天鹰教的大船在大海上慢慢的漂着......$N不禁感到睡意朦胧。\n"NOR, me);
        remove_call_out("arrive2");
        call_out("arrive2",10,me);
        return 1;
}

int arrive2(object me)
{
        message_vision(HIY "\n$N突然听到一声惊喝：“到了，下船吧”！$N顿时提起精神，跟着天鹰教教众下了船。\n"NOR, me);
        me->move("/d/tulong/tulong/daobian");
        tell_object(me, HIR "\n你突然想到：最好先砸了其他人的船(break boat)，让他们无路可逃。\n" NOR);
        return 1;
}


int do_enter ( string arg )
{
        object ob ;
        string dir;
        if (! arg || arg != "chuan")
        {
                tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
        message_vision("船夫升起帆，船就向东方航行。\n", ob);
        ob->move("/d/mingjiao/lsd/dahai") ;
        tell_object(ob, BLU "你在海上航行了三天三夜.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "大船终于抵达了南海岸边。你走下船来。\n" ) ;
        ob->move("/d/mingjiao/lsd/anbian") ;
}

*/
void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;

        me = this_player();

        if (! arg || arg != "haigang")
                return notify_fail("你要到海港么，请输入 enter haigang。\n");

        me->move("/d/shenlong/japangames/japan0");

        return 1;
                
}

