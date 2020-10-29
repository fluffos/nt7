/* /std/room/danger_road.c
*
*  走夜路有可能遇到强盗,此为一个标准被劫的 road ,
*  每一条路上视此路的长短和偏僻程度可放置几个这个
*  被劫的路,简单继承此物件即可 "inherit DANGER_ROAD",
*  不要继承 ROOM , 其他就不用管了.
*  注意:如果您的房间里用到了init() 函数,请在结尾处
*  加上 ::init().
*
*  by 发现号(Find) 10/98.
*/

#define TOU_MU                __DIR__"npc/qiangdao_t"
#define LOU_LOU                __DIR__"npc/qiangdao"

inherit ROOM;

void init()
{
        string day_night;
        int time,n;
        object obj,obj_1,obj_2,me = this_player();
        mapping exits;
        string *dir = ({});

        if(is_day() || !userp(me) || !living(me))
                return;
return;
        if( query_temp("init_qiangdao", me) )
                return;

        if ( sscanf( NATURE_D->day_or_night(),"%s %d",day_night,time) )
        {
                if( day_night == "night"
                && time > 60
                && !present("qiang dao",this_object())
                && !present("qiangdao leader",this_object())
                && !me->is_fighting()
                && random(100) < 15 )
                {
                        obj = new(TOU_MU);        // 头目出场
                        obj->set_attribute(me);

                        n = 1+random(3);

                        if(n-1)
                        {
                                obj_1 = new(LOU_LOU);        //强盗甲出场
                                obj_1->set_leader(obj);
                                set("my_leader", obj, obj_1);
                                addn("tonghuo/", ({obj_1}), obj);
                                obj_1->set_attribute(me);

                                if(n-2)
                                {
                                        obj_2 = new(LOU_LOU);        // 强盗乙出场
                                        obj_2->set_leader(obj);
                                        set("my_leader", obj, obj_2);
                                        addn("tonghuo/", ({obj_2}), obj);
                                        obj_2->set_attribute(me);
                                }
                        }

                        if(!me || !environment(me))
                        {
                                destruct(obj);
                                if(obj_1) destruct(obj_1);
                                if(obj_2) destruct(obj_2);
                                return;
                        }

                        set_temp("init_qiangdao", 1, me);
                        exits=query("exits", environment(me));
                        if(mapp(exits))
                                dir = keys(exits);
                        obj->set_leader(me);

                        obj->move(environment(me));

                        message_vision("\n突然旁边窜出"+chinese_number(n)+"条蒙面大汉朝着$N走了过来。\n",me);
                        message_vision("\n$N恶狠狠的对着$n喊道：打劫！拿出"+
                                chinese_number((query("age", me)/10)*10)+
                                "两银子算完事，要不让你活不到天亮!\n\n",obj,me);
                        obj->ask_money();
                        if(sizeof(dir))
                                GUARD_CMD->main(obj,dir[0]);

                        if(obj_1)
                        {
                                obj_1->move(environment(me));
                                if(sizeof(dir) > 1)
                                        GUARD_CMD->main(obj_1,dir[1]);
                        }
                        if(obj_2)
                        {
                                obj_2->move(environment(me));
                                if(sizeof(dir) > 2)
                                        GUARD_CMD->main(obj_2,dir[2]);
                        }
                        return;
                }
        }
}