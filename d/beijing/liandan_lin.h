void init()
{
        add_action("do_cai","cai");
}

int do_cai(string arg)
{
        object me=this_player();
//      object ob;
//      object ob1;
        if( query_temp("caiyao", me)<1 )
                return notify_fail("别在这浪费时间了，快走吧。\n");

        if (!arg || arg != "yao")
                return notify_fail("你要采什么。\n");

        if ( me->is_busy() )
                return notify_fail("慢慢找，先别急。\n");
       
        if( query("jing", me)<40 )
                return notify_fail("你太累了，休息下吧。\n");

        if( query("qi", me)<40 )
                return notify_fail("你太累了，休息下吧。\n");

        if( query_temp("caiyao", me) == 2 )
                return notify_fail("东西到手，快去交了吧。\n"); 

        message_vision("$N趴在地上，瞪大了眼睛在草丛中找寻着药草，生怕漏掉了目标。\n",me); 

        me->start_call_out((: call_other, __FILE__, "cai", me :), 3); 
        me->start_busy(4); 
        return 1;
}
 
int cai(object me)
{ 
        object ob;
        object ob1;        
        if (random(10)<7)
        {
        me->receive_damage("jing",10+random(20));
        me->receive_damage("qi",10+random(20));   
        message_vision(CYN"一翻摸索后，草丛中似乎没有$N要找的东西，$N失望的叹了口气。\n"NOR,me);
        }

        if (random(20) ==1 && ! present("du she", environment(me))) 
        {         
        tell_room(environment(me),HIR"草丛中一阵晃动，突然钻出一条毒蛇。\n"NOR );
        ob=new("/d/beijing/npc/liandan_dushe");
        ob->move(environment(me));
        }

   else if(random(20)==1 && ! present("du langzhong", environment(me))) 
        {         
        tell_room(environment(me),HIR"林子后面突然跳出一个凶神恶刹的男子，手提一把短刀向你扑来！\n"NOR );
        ob=new("/d/beijing/npc/liandan_langzhong");
        ob->move(environment(me));
        }
   else
        { 
        ob1 = new("/d/beijing/npc/dan/caoyao");
        ob1->move(me);
        me->receive_damage("jing",10+random(20));
        me->receive_damage("qi",10+random(20));
        addn_temp("caiyao", 1, me);
        message_vision(HIG"$N找了半天，终于发现其中一株草苗与其它的草略有不同，
小心翼翼地掘了出来。\n"NOR,me); 
        }
        me->stop_busy();
        return 1;
       
}