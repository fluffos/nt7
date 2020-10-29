//Cracked by Roath
// /d/hangzhou/jiudian.c   牛家村酒店
// by maco 99/12/22

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{        set("short", "酒店");
        set("long", @LONG
这是座单门独户的小酒店，檐下摆着两张板桌，桌上罩着厚厚一
层灰尘，东首摆了个碗橱。小酒店的主人是个跛子，可以向他打酒(f
ill)。店中似乎也没什麽菜色，无非是些蚕豆、花生等下酒之物。
LONG );

         set("exits", ([ /* sizeof() == 2 */
                   "west" : __DIR__"village",  
                 ])
         );

         set("objects", ([
                CLASS_D("taohua") + "/qusan" : 1  
         ]));

         set("cost", 1);
         set("outdoors", "hangzhou");

         set("coor/x", 3890);
        set("coor/y", -1800);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_fill", "fill");
}
int do_fill(string arg)
{
        object ob, obj, me = this_player();

        if (!objectp(obj = present("qu san", environment(me))))
        {        write("掌柜的不在！\n");
                return 1;
        }

        if (!living(obj)){
                write("你还是等掌柜的醒过来再说吧。\n");
                return 1;
        }

        if( !arg || !(ob=present(arg,this_player())) || !query("liquid", ob)){
                write("你要把酒装在哪儿？\n");
                return 1;
        }

        switch (MONEY_D->player_pay(this_player(), 20)) {
        case 0: {
                write("穷光蛋，一边呆着去！\n");
                return 1;
                }
        case 2: {
                write("您的零钱不够了，银票又没人找得开。\n");
                return 1;
                }
        }

        if( query("liquid/remaining", ob) )
                message_vision("$N将"+ob->name()+"里剩下的"+query("liquid/name", ob)+
                "倒掉。\n", this_player());
        message_vision("$N给曲三二十文铜板。\n曲三给$N的"+ob->name()+"装满烧酒。\n", this_player());

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        set("liquid/type", "alcohol", ob);
        set("liquid/name", "烧酒", ob);
        set("liquid/remaining", query("max_liquid"), ob);
        set("liquid/drink_func", 0, ob);
        set("liquid/drunk_apply", 4, ob);
        return 1;
}