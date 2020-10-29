#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(HIG "「霸刀」" NOR, ({ "badao book", "badao", "book"}));
        set_weight(500);
        if (clonep())
               destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIG "\n这是一本用薄纸写成的书，封皮上写有「霸刀」二字。\n"
                            "你可以试着读读(read)看。\n\n" NOR, );
        }
        
        remove_call_out("check_environment");
        call_out("check_environment", 3);
}

// 检查这本书
// 1、书必须在玩家身上
// 2、玩家必须在碧水寒潭内，一旦离开碧水寒潭则消失
void check_environment()
{
        object pob, eob;

        remove_call_out("check_environment");
        call_out("check_environment", 3);
                
        pob = environment(this_object());
        
        if (! objectp(pob))
        {
                destruct(this_object());
                return;
        }
        /*
        if (! userp(pob))
        {
                destruct(this_object());
                return;
        }
        */
        
        // 掉在碧水寒潭不消失
        if( query("is_hantan", pob))return ;

        eob = environment(pob);
        
        if (! objectp(eob))
        {
                destruct(this_object());
                return;
        }
        
        if( !query("is_hantan", eob) )
        {
                tell_object(pob, HIG "你离开了碧水寒潭，《霸刀》叮~~地一声掉在地上，消失了！\n" NOR);
                destruct(this_object());
                return;
        }
        return;
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        string msg;
        
        if (! arg)
        {
                write("你要读什么？\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }

        if( query("no_fight", where )
            && query("doing", me) != "scheme" )
        {
                write("你无法在这里静下心来研读霸刀。\n");
                return 1;
        }

        if (query("reborn/times", me) < 3)
        {
                write("你还没有经历轮回转世呢，无法修炼霸刀。\n");
                return 1;
        }
        
        if( query("str", me)<38 )
        {
                write("你先天臂力不足，无法修炼霸刀。\n");
                return 1;
        }

        if( query("con", me)<38 )
        {
                write("你先天臂力不足，无法修炼霸刀。\n");
                return 1;
        }

        if( me->query_skill("sword",1) && query("reborn/times", me) < 3 )
        {
                write("你所学的杂学太多了，无法专心研习霸刀。\n");
                return 1;
        }

        if( me->query_skill("club",1) && query("reborn/times", me) < 3 )
        {
                write("你所学的杂学太多了，无法专心研习霸刀。\n");
                return 1;
        }
                
        if( me->query_skill("staff",1) && query("reborn/times", me) < 3 )
        {
                write("你所学的杂学太多了，无法专心研习霸刀。\n");
                return 1;
        }
                
        if( me->query_skill("whip",1) && query("reborn/times", me) < 3 )
        {
                write("你所学的杂学太多了，无法专心研习霸刀。\n");
                return 1;
        }
                
        if( me->query_skill("dagger",1) && query("reborn/times", me) < 3 )
        {
                write("你所学的杂学太多了，无法专心研习霸刀。\n");
                return 1;
        }
                
        if( me->query_skill("hammer",1) && query("reborn/times", me) < 3 )
        {
                write("你所学的杂学太多了，无法专心研习霸刀。\n");
                return 1;
        }
                                                          
        if( query("max_neili", me)<20000 )
        {
                write("你的内力修为不足。\n");
                return 1;
        }

        if ((int)me->query_skill("force", 1) < 500)
        {
                write("你的内功火候太浅。\n");
                return 1;
        }

        if ((int)me->query_skill("martial-cognize", 1) < 500)
        {
                write("你的武学修养不足。\n");
                return 1;
        }
                
        if ((int)me->query_skill("blade", 1) < 700)
        {
                write("你的基本刀法火候不够，无法学习霸刀。\n");
                return 1;
        }
                
        if (! me->query_skill("literate", 1))
        {
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }

        if (me->query_skill("sanscrit", 1) < 200)
        {
                write("你的梵文水平太低，无法看懂书里所记载的内容。\n");        
                return 1;
        }
        
        if (! id(arg))
        {
                write("这里没有这本书。\n");
                return 1;
        }

        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
        {
                write("你体内的阴阳真气无法与霸刀相兼容。\n");
                return 1;
        }
        
        if( me->query_skill("lunhui-sword",1) && query("reborn/times", me) < 4 )
        {
                write("你体内的六道轮回真气无法与霸刀相兼容。\n");
                return 1;
        }
                
        if( query("combat_exp", me)<30000000 )
        {
                write("你的实战经验不足，再怎么读也没用。\n");
                return 1;
        }

        if( query("jing", me)<100
            || query("qi", me)<100
            || query("neili", me)<200 )
        {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }
        
        msg = HIG "$N" HIG "翻看《霸刀》，仔细研究上面所记载的武学，霎那间若有所悟……\n" NOR;
        msg += HIG "$N" HIG "以手做刀，左劈右砍，忽而眉头金锁，忽而闭目沉思。\n" NOR;
        msg += HIG "$N" HIG "长叹一声，感慨万千，似乎明白了什么 ……\n" NOR; 
        message_vision(msg, me); 

        if (me->query_skill("badao", 1) < 180)
        {                        
                write(HIW "你对「" HIG "霸刀" HIW "」有了新的领悟。\n" NOR);
                // 第一次学习
                if (! me->query_skill("badao", 1))
                {
                        /*
                        // 轮回点
                        if( query("scborn/cur_lunhui_point", me)<7 && !query("thborn/ok", me) )
                        {
                                write("你轮回点不足，无法领悟霸刀。\n");
                                return 1;
                        }    
                        if( !query("thborn/ok", me) )
                        {
                                addn("scborn/cur_lunhui_point", -7, me);
                                write(HIG "\n恭喜你学会了霸刀，消耗轮回点 7 点，请勿将霸刀放弃为0级后再重新学习，否则需要重新消耗轮回点。\n" NOR);
                        }
                        */
                        me->set_skill("badao", 40 + random(21));
                        me->save();
                }
                else                                        
                        me->set_skill("badao", me->query_skill("badao", 1) + 40 + random(21));

                destruct(this_object());
        }
        else
        {
                write(HIR "你霸刀级别已经无法再通过研读秘籍来提升了。\n" NOR);
                return 1;
        }

        return 1;
}