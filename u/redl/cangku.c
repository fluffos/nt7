// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create()
{
                int i = random(4) + 3;
                object ob;
        set("short", "仓库");
        set("long", 
"这里是化乐天里的仓库，各种奇珍异宝车载斗量堆满了整间屋子，灿\n"
"烂耀眼的珠宝和移山倒海的装备法宝扔了一地，不过都还没有放进来。角\n"
"落里有个猫舍，你忍不住想用手去掏一掏(" + CYN + "tao" + NOR + ")。\n"
);
//         set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
                "west"   : __DIR__"houdian",
                "down" : __DIR__"dijiao",
        ]));

        set("objects", ([
                "/u/redl/obj/chutou3" : 3,
                "/u/redl/obj/chutou4" : 3,
                      "/clone/wizard/dan" : 2, 
                      "/u/redl/obj/fanghuamu" : 3, 
                      "/u/redl/obj/mbox" : 2, 

        ]));

                set("no_rideto", 1);
                set("no_flyto", 1);
        
        setup();
        
        ob = new("/clone/money/thousand-gold");
        ob->move(this_object());
        ob->set_amount(10000);
        while (i--) {EQUIPMENT_D->create_dynamic("", 60, 600)->move(this_object());}
}


void init()
{
        object me = this_player();
        if ( query("id", me) != "redl" && query("couple/couple_id", me) != "redl" )
        {
                add_action("do_noget", ({"get", "drop", "eat", "smell"}));
        }
        add_action("do_tao", "tao");
}


int do_noget()
{
        tell_object(this_player(), NOR"你看看就行了啊，可别动歪脑筋！\n"NOR);
        return 1;
}

int do_tao()
{

        object ob, me = this_player();
        if ( me->is_busy() ) {
                        tell_object(me, "你还是忙完手头上的事情再说吧。\n");
                        return 1;
                }
        message_vision(YEL "$N将手伸进去猫舍里去掏了掏...\n" NOR, me);
        if ( query("id", me) != "redl" && query("couple/couple_id", me) != "redl" ) 
                {
                        message_vision(YEL "只听见喵呜，$N" NOR YEL "惨叫一声把手缩回来，可怜已是被" HIK "小懒猫" NOR YEL "抓得面目全非了。\n" NOR, me, ob);
                        me->start_busy(5);
                        }
        else 
                {
                                                ob = new(__DIR__"npc/lcat");
                        message_vision(YEL "只听见喵呜一声，$N" NOR YEL "从猫舍里轻轻拎出来一只可爱的$n" NOR YEL "。\n" NOR, me, ob);
                                                ob->move(this_object());
                        ob->command("cat " + query("id", me));
                }

        return 1;
}

void do_start_hslj(string arg)
{
//      int type;
        object cat;
        DEBUG_CHANNEL("TIME_D调用比武 " +(arg?arg:0)+ "成功。\n");
        if (!arg) {
                switch(random(4)) {
                        case 0:
                                message_system(NOR + HIW + "每月６、２１日，晚２０点华山绝顶开放[１号比武场]，限制２０级到１００级之间，奖品有勋章和泥潭币，参与即有好礼。\n"NOR);
                                break;
                        case 1:
                                message_system(NOR + HIW + "每月６、２１日，晚２２点华山绝顶开放[２号比武场]，限制１０１级到２００级之间，奖品有勋章和泥潭币，参与即有好礼。\n"NOR);
                                break;
                        case 2:
                                message_system(NOR + HIW + "每月７日，晚２０点华山绝顶开放[３号比武场]，限制２０１级之上，奖品有勋章和泥潭币，参与即有好礼。\n"NOR);
                                break;
                        case 3:
                                message_system(NOR + HIW + "每月７日，晚２２点华山绝顶开放[华山论剑比武场]，不限武器装备，奖品有勋章和泥潭币，参与即有好礼。\n"NOR);
                                break;
                }
                return;
        }
        
        cat = new(__DIR__"npc/lcat");
                cat->move(this_object());
        cat->do_start_hslj(arg);
}

void callout_hslj(string arg) 
{
        int delay;
        if (!arg || sscanf(arg, "%s %d", arg, delay) != 2) return;
        call_out("do_start_hslj", delay, arg);       
}