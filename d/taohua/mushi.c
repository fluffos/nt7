inherit ROOM;

void create()
{
  
        set("short", "墓室");
        set("long", @LONG
这是一间宽敞的墓室。墓室顶上有一颗特别大的明珠闪闪
发光。中央放着一副玉棺，周围则堆放了无数的奇珍异玩。有
张供桌摆在玉前,桌上放着盘子(panzi).墓室对面挂这幅青年少
妇的画像。画像上的少妇巧笑嫣然，和惨白的玉棺及碧油油的
珠光形成了一幅奇诡的画面。
LONG);
        set("exits", ([
                "up" : __DIR__"mudao",
        ]));

        if (random(1000) > 998)
                set("objects", ([
                        "/clone/money/gold" : 10,
                        "/clone/fam/item/haoyue" : 1,
                        "/clone/fam/etc/lv5b" : 1,
                ]));
        else
        if (random(100) > 98)
                set("objects", ([
                        "/clone/money/gold" : 5,
                        "/clone/fam/etc/lv5a" : 1,
                ]));
        else
        if (random(100) > 97)
                set("objects", ([
                        "/clone/money/gold" : 5,
                        "/clone/fam/etc/lv5d" : 1,
                ]));
        else
        if (random(10) > 8)
                set("objects", ([
                        "/clone/money/gold" : 1,
                ]));

        set("item_desc", ([
                "panzi" : @TEXT
    你仔细看了一下盘子，这是一个玉盘，里面放着数颗晶莹的
    明珠。这些明珠似乎可以拿出来(pick zhu)。
TEXT
        ]) );

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_pick","pick");
        set_temp("taohua/墓室", 0, me);
}
void reset()
{
        ::reset();
        set("pick_available" , 6);
}
int do_pick(string arg)
{
        object *obs;
        object me,obj,killer;
        int count;

        me = this_player();
        if( !arg || arg!="zhu" )
                return notify_fail("你要拿什么? \n");
                
        if (me->is_busy()) return notify_fail("你正在忙着呢！\n");

        if ( query("pick_available") )
        {
                message_vision("$N从盘子里拿出来一颗明珠。\n",this_player() );
                obj = new ("/d/taohua/obj/mingzhu");
                obj->move(me);
                addn("pick_available", -1);
                me->start_busy(3);
                if( query_temp("taohua/墓室", me))return 1;
                killer = new ("/d/taohua/npc/shoumu") ;
                obs = all_inventory(this_object());        
                count = 0;
                foreach(object ob in obs) {
                        if(ob && ob->id("shou mu"))
                                count++;
                }
                if (count < 6)
                {
                        message_vision("\n突然墓室中打开了一道暗门，从里面走出一个守墓家奴。\n"
                                       "对$N喝道：贼子敢尔！连夫人的东西你也敢动！\n", me);
   
                        killer->move(environment(me));
                        killer->kill_ob(me);
                        set_temp("taohua/墓室", 1, me);
                }
       }
       return 1;
}

