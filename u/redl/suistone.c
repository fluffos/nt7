// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 
string look_stone(object me);

void create()
{
        set("short", "随风石");
        set("long", 
"这里是化乐天最高峰，山巅平台边上的一块巨石(stone)，临渊\n"
"是悬崖万丈深不见底。极目四望，数千里方圆海天无际，浮云聚散如\n"
"梦似幻。你站在这里怀有种临风踏云飘飘欲仙的感觉，不禁生出想"CYN"随"NOR"\n"
"风而去的念头。\n"
);
        set("outdoors", "chengdu");
        set("exits",([ /* sizeof() == 1 */
                "southdown" : __DIR__"suiroad3",
        ]));

                set("no_fight", 1); 
                set("no_magic", 1); 
                set("no_rideto", 1);
                set("no_flyto", 1);
        
        set("item_desc", ([
                "石": (: look_stone :),
                "巨石": (: look_stone :),
                "stone": (: look_stone :),
        ]) );

        setup();
}

string look_stone(object me)
{
        return 
HIW + "   《雨蝉》\n" + NOR + 
WHT + "  穷秋迷天赐，\n" +  NOR + 
HIW + "  二百八对辞。\n" +  NOR + 
WHT + "  夜半雨鸣蝉，\n" +  NOR + 
HIW + "  颠倒颠醉思。\n\n" +  NOR + 
HIK + "         sui...\n" +  NOR;
}

void init()
{
        add_action("do_sui", ({"sui", "jump"}));
}


int do_sui()
{
        object me = this_player();
        
        if(me->is_busy()) return 1;
        me->start_busy(20);
        
/*semote goodbye
表情 goodbye 之详细叙述如下：
────────────────────────────────────────
1.无对象无附加文字    ：微风拂过细细的杨柳，在夕阳的映衬之下，离别是那样的伤感而美丽，泪水在你眼眶之中，迟迟不肯落下……
2.无对象有附加文字    ：微风拂过细细的杨柳，在夕阳的映衬之下，离别是那样的伤感而美丽，泪水在你眼眶之中，迟迟不肯落下……
3.对象为自己无附加文字：你站在万丈悬崖的边上，举目望去，云雾缭绕，恍若仙境，
喃喃低语道：“来过，活过，爱过，也不枉此生了”。说罢，纵身跃入那云雾之中……
4.对象为自己有附加文字：你站在万丈悬崖的边上，举目望去，云雾缭绕，恍若仙境，
喃喃低语道：“事物，也不枉此生了”。说罢，纵身跃入那云雾之中……
5.对象为某人无附加文字：你望着某人低声说道：“要走了吗？..还回来吗？...会记得我吗？...我...我...我会想你的....永远会！！”
6.对象为某人有附加文字：你望着某人低声说道：“要走了吗？..还回来吗？...会事物吗？...我...我...我会事物的....永远会！！”
7.表情注解            ：无注解
8.使用次数            ：20 次
────────────────────────────────────────*/
 
                set_temp("can_redlsuistone", 1, me);
                message_vision(YEL "$N埋头，踢了踢脚下的巨石。\n" NOR, me);
                call_out("do_sui2", 2, me); 
                return 1;
}

void do_sui2(object me)
{
                switch(query_temp("can_redlsuistone", me))
                {
                        case 1:
                                addn_temp("can_redlsuistone", 1, me);
                                me->command("goodbye " + query("couple/couple_id", me));
                                call_out("do_sui2", 3, me); 
                break;
                        case 2:
                                addn_temp("can_redlsuistone", 1, me);
                                me->command("goodbye " + query("id", me));
                                call_out("do_sui2", 4, me); 
                break;
                        case 3:
                                delete_temp("can_redlsuistone", me);
                                message_vision(YEL "$N的影子越来越远，随着清风徐徐往深渊飘去...\n" NOR, me);
                                call_out("do_sui3", 3, me); 
                break;
        }
}

void do_sui3(object me)
{
        me->move(__DIR__"inwind");
}


