// room: mishi.c

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_press();
int valid_leave();
string look_hua();
string look_liang();

void create()
{
        set("short","密室");
        set("long", @LONG
这是一间黑黢黢的小房间，墙上的砖头(zhuan) 已经掉渣子了，房
梁(liang) 也已经朽烂不堪。墙脚处有一个铁箱子，上面积满了尘土。
左首处悬挂着一幅画(hua)，角落处斜放着几捆干柴。
LONG );
        set("exits", ([
                "out" : __DIR__"midao",
        ]));
        set("item_desc", ([
                "hua"     : (: look_hua :),
                "liang"   : (: look_liang :),
                "zhuan": "砖头烂得一塌糊涂。\n",
                //"liang": "房梁是上好的楠木做的，可惜年代太久，已经腐烂得不成样子了。\n",
        ]) );
        set("objects", ([
                __DIR__"obj/tiexiang" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 1820);
        set("coor/y", -6312);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

string look_hua()
{
        object me = this_player();

        if( query("score", me)<1000 )
                return HIR "\n一幅陈旧的画卷，画中乃是达摩老祖，没有什么不同。\n" NOR;

        if( query("score", me)<3000 )
                return HIR "\n一幅陈旧的画卷，画中达摩老祖左手握个剑诀，慈祥安和。\n" NOR;

        set_temp("marks/辟1", 1, me);
        return HIR "\n一幅陈旧的画卷，画中达摩老祖左手握个剑诀，正指向房梁(liang)处。\n" NOR;
}

string look_liang()
{
        object me = this_player();

        if( !query_temp("marks/辟1", me) )
                return "你要看什么？\n";

        if (query("move"))
                return WHT "一根楠木做的房梁，上面有崭新的刮痕，似乎不久前才有人动过。\n" NOR;

        set_temp("marks/辟2", 1, me);
        return WHT "一根楠木做的房梁，可惜年代太久，已经腐烂得不成样子了。\n" NOR;
}

int do_jump(string arg)
{
        object me, ob;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg=="liang")
        {
            if( query_temp("marks/跳1", me)){
                if (me->query_dex()<20)
                    write("你试图跳上房梁，无奈身法不够敏捷，只好做罢。\n");
                else {
                    write("你纵身跃上了房梁。\n");
                    message("vision",
                             me->name() + "一纵身跃上了房梁。\n",
                             environment(me), ({me}) );
                    set("move", 1);
                    me->move(__DIR__"liang");
                    message("vision",
                             me->name() + "从下面跃了上来。\n",
                             environment(me), ({me}) );
                }
                return 1;
           }

           if( query_temp("marks/辟2", me) )
           {
                if (me->query_dex() < 40)
                        write(HIC "你试图跳上房梁，无奈身法不够敏捷，只好做罢。\n" NOR);
                else
                {
                        foreach (ob in deep_inventory(me)) if (ob->is_character())
                        {
                                ob->move(environment(me));
                                message_vision("\n$N将" + ob->name() + "从背上放了下来"
                                               "，躺在地上。\n\n" NOR, me);
                        }

                        message("vision", HIY "只见" + me->name() + HIY "一纵身跃上了房"
                                          "梁。\n" NOR, environment(me), me);
                        set("move", 1);
                        write(HIY "\n你纵身轻轻一跃，跳上了房梁。\n\n" NOR);
                        me->move(__DIR__"liang");
                        message("vision", HIY "只见" + me->name() + HIY "从下面的柴房跃"
                                          "了上来。\n" NOR, environment(me), me);
                }
                return 1;
            }
        }
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/辟1", me);
        delete_temp("marks/辟2", me);
        delete_temp("marks/跳1", me);
        return ::valid_leave(me, dir);
}