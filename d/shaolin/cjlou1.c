inherit ROOM;

void create()
{
        set("short", "藏经阁二楼");
        set("long", @LONG
千余年来少林寺执中原武林之牛耳，自达摩老祖以下，历代人材
辈出。其中有不少高僧遗著留存，汇集至今，终成名震天下的少林七
十二绝艺。少林精华，尽集于此。二楼四面开窗，确保通风。中间排
列着五排大书架。四周则陈列矮几，以供阅读。几位老僧手执经卷，
正在闭目凝思。房梁(fangliang)上满是灰尘。
LONG );
        set("exits", ([
                "down" : __DIR__"cjlou",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/hui-zhen" : 1,
                "/clone/book/wuji1" : 1,
                "/clone/book/wuji2" : 1,
                "/clone/book/wuji3" : 1,
        ]));
        set("item_desc", ([ /* sizeof() == 1 */ 
                "房梁" : "房梁离地面越有一丈多高。看看能不能跳(jump)上去。\n", 
        ])); 
        setup();

        if (random(5) == 0)
                "/clone/book/wuji4"->move(this_object());
}

void init()
{
        add_action("do_hit", "hit");
        add_action("do_jump", "jump");
}

int do_hit(string arg)
{
        object ob, me = this_player();
        
        if ( arg == "huizhen" || arg == "zunzhe" || arg == "huizhen zunzhe" ) {
                ob = present("huizhen zunzhe", environment(me));
                ob->kill_ob(me);
                me->fight_ob(ob);
                tell_object(me,"你突然天旋地转，冥冥中似乎有股力量在操纵你的命运!\n");
                me->unconcious();
        
                return 1;
        }

        return 0;
}

int do_jump(string arg)
{
        string dir;
        object me=this_player();

        if( !arg || arg=="" ) 
        {
                write("你想跳哪里去？\n");
                return 1;
        }

        if( arg=="fangliang" ) {
                           write("你深深地吸了一口气,猛然跃起......\n");
                if((int)me->query_skill("dodge",1)>=50)
                          {write("你一式「孤骛落日」，全身笔直，拔地而起，在半空中一转，已落到房梁上。\n");
                me->move(__DIR__"liang");
                return 1;}
                write("“啪”的一声你脑袋撞到了房梁,又跌回原处，摔了个四脚朝天。\n");
                addn("jing", -100, me);
                addn("qi", -100, me);
                addn("eff_qi", -100, me);
                me->improve_skill("dodge", random(30));
                me->unconcious();
                return 1;
        }
}

int valid_leave(object me, string dir)
{
        object *ob;
        int i;

        if (dir != "down" ||
            ! present("huizhen zunzhe", environment(me)))
                return ::valid_leave(me, dir);

        ob = deep_inventory(me);
        for (i = 0; i < sizeof(ob); i++)
                if (ob[i]->id("shaolin wuji")) 
                        return notify_fail("慧真说道：武功秘籍只许在藏经阁"
                                           "内研习，不得携带外出！\n");
        return ::valid_leave(me, dir);
}
