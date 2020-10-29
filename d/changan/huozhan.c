inherit ROOM;

void create ()
{
        set ("short", "货栈");
        set("long", @LONG
这是一家生意兴隆货栈。货栈门口车来车往，几个活计在忙忙碌
碌地工作着，地上放着一些刚刚运来的货物。屋里面整齐的排列着几
排货架，货架上堆着各式各样的杂货，有一个掌柜模样的人坐在柜台
后面笑容可鞠地招呼着客人。货栈的墙上贴着一张破旧的告示(gaosh
i)。
LONG );
        set("item_desc", (["gaoshi" : "现在正紧缺人手，急需雇佣一批短工来干活。
work        开始工作。
", ]));
        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao1",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/liang" : 1,
        ]));
        set("no_fight", 0);
        set("coor/x", -10750);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_work", "work");
}

int do_work(string arg)
{
        object ob;
        object me;
        me = this_player();
        if( !query_temp("working_in_huozhan", me) )
        {
                if( query("qi", me)<25 || 
                    query("jing", me)<25 )
                        return notify_fail("你可是累坏了，干不动了。\n");

                message_vision("$N从车上卸下一袋袋的大米，又"
                               "垒在墙边，累的腰酸腿疼！\n",me);
                me->receive_damage("qi", 20);
                me->receive_damage("jing", 20);
                ob = new("/clone/money/coin");
                ob->set_amount(10);
                ob->move(me);
                message_vision("梁老板笑眯眯地对$N说：辛苦啦，这是你的工钱。\n",me);
                set_temp("working_in_huozhan", 1, me);
                remove_call_out ("reset_work");
                call_out ("reset_work", 2 + random(3), me);
        } else
        {
                message_vision("梁老板赶紧把$N扶起来：先歇一会儿。\n",me);
        }
        return 1;
}

void reset_work(object me)
{
        delete_temp("working_in_huozhan", me);
}