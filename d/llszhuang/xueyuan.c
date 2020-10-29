#include <combat.h>
#include <ansi.h>
inherit ROOM;
string *all_dirs = ({"north","south","east","west","southwest","northeast","southeast","northwest"});
void create()
{
        set("short", "雪原");
        set("long",
"这里是一片无垠的雪地，天地之间一片苍茫，两行足迹远远地延伸出\n"
"去，似乎永无尽头。此时狂风大作，风中隐隐传来厉啸和“咯咯”的笑声。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "north" : __FILE__,
          "south" : __FILE__,
          "east" : __FILE__,
          "west" : __FILE__,
          "southeast" : __FILE__,
          "southwest" : __FILE__,
          "northeast" : __FILE__,
        "northwest" : __FILE__,
        ]));

        set("objects", ([
                //      __DIR__"npc/roc" : 1,
                ])
        );
        setup();
}

int valid_leave(object ob,string dir)
{
        object roc;

        switch(random(15))
        {
                case 1:
                case 2:
                case 3:
                        message_vision(RED"\n狂风飞雪之中，似乎有什么东西自你上一掠而过！"NOR,ob);
                        roc = new("/d/llszhuang/npc/roc");
                        roc->move(environment(ob));
                        COMBAT_D->do_attack(roc,ob,query_temp("weapon", roc),TYPE_QUICK);
                      message_vision(YEL"幽冥大鹏振羽长啸，身形转眼消失在云层中。\n\n"NOR,ob);
                        destruct(roc);
                        return 1;
                default:
                        if( dir == all_dirs[random(4)] )
                                addn_temp("doom_trigger", 1, ob);
                        if( dir == all_dirs[4+random(4)] )
                                addn_temp("doom_trigger", -1, ob);

                        if( query_temp("doom_trigger", ob) == 3 )
                        {
                     message("channel:chat", YEL"【江湖故事】江湖传言："+ob->name()+"在某一天突然闯入了柳绿山庄。\n"NOR,users());
                                ob->move(__DIR__"gate");
                                delete_temp("doom_trigger", ob);
                                return notify_fail("你终于找到了出口，来到了绿柳山庄的正门。\n");
                        }


                        if( query_temp("doom_trigger", ob) == -3 )
                        {
                                write("你终于找到了来时的路，渡过了小河，循原路回。\n");
                                ob->move(__DIR__"dukou");
                                delete_temp("doom_trigger", ob);
                              return notify_fail("你终于找到了来时的路，渡过了小河，循原路回到了渡口。\n");
                        }

                        return 1;
        }

}
