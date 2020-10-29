//chufang.c                四川唐门—厨房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "厨房");
        set("long",
"这里是莲藕小筑中的厨房。屋子中摆着七、八张桌子，一些唐门弟子\n"
"围坐在桌旁一边开怀畅饮，一边谈论着江湖上的一些恩恩怨怨，你应该可\n"
"以向厨师点菜(serve)。\n"
);
        set("exits", ([
                        "east" : __DIR__"chaifang",
        ]));
        set("no_fight", 1);
        set("area", "tangmen");
        setup();
}
void init()
{
        add_action("do_serve","serve");
}

int do_serve()
{
        object ob, food, water;
        ob = this_player();
        food=new(__DIR__"obj/jiangnr");
        water=new(__DIR__"obj/donggt");

         if( (present("rou", ob)) && (present("tang", ob)) )
        {
                message_vision(HIC "\n厨师冲着你大叫着：“先吃完了再要。\n" NOR, ob);
                return 1;
        }
        else
        {
                if ( (present("rou", ob)) )
                {
                        message_vision(HIC "\n厨师将一碗冬瓜汤放在$N面前，嘴里嘟囔着：“有吃的还要！”。\n" NOR, ob);
                        water->move(ob);
                        return 1;
                };
                if ( (present("tang", ob)) )
                {
                        message_vision(HIC "\n厨师将一盘酱牛肉放在$N面前，嘴里嘟囔着：“有喝的还要！”。\n" NOR, ob);
                        food->move(ob);
                        return 1;
                }
                else
                {
                        message_vision(HIC "\n厨师将一盘酱牛肉、一碗冬瓜汤放在$N面前。\n" NOR, ob);
                        food->move(ob);
                        water->move(ob);
                        return 1;
                }

        }
}