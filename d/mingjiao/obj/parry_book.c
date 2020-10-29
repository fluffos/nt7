// parry_book.c

inherit ITEM;
inherit F_UNIQUE;
void create()
{
        set_name("羊皮", ({ "yang pi", "pi" }));
        set_weight(600);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "张");
                set("unique", 1);
                set("long", "这是一张羊皮，上面写着密密麻麻的文字，好象很难看(read)懂。\n");
                set("value", 2000);
                set("material", "paper");
                set("no_drop", "这样东西不能离开你。\n");
                set("treasure",1);
        }
}
void init()
{
        add_action("do_du", "read");
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
//        object ob;
//        mapping skill;
        int qklevel,neili_lost,lit, med;
        lit = me->query_skill("literate", 1);
        med = me->query_skill("medicine", 1);
        qklevel = me->query_skill("qiankun-danuoyi", 1);
        if (!(arg=="yang pi" ||arg=="pi"))
        return 0;

        if( query("family/master_name", me) != "张无忌" )
             return notify_fail("只有教主亲传弟子才可以修习乾坤大挪移神功！\n");
        if( !query_temp("marks/挪移", me) )
             return notify_fail("没有教主允许任何人都不可以擅自修习乾坤大挪移神功！\n");
        if( query("pigging", where) )
             return notify_fail("你还是专心拱猪吧！\n");
        if(me->is_busy())
             return notify_fail("你现在正忙着呢。\n");
        if(me->is_fighting())
             return notify_fail("你无法在战斗中专心下来研读新知！\n");
        if(!id(arg))
             return notify_fail("你要读什么？\n");
        if(!lit)
             return notify_fail("你是个文盲，先学点文化(literate)吧。\n");
        if(me->query_int() < (qklevel/10)+20)
             return notify_fail("你的头脑不够用，恐怕不能修习乾坤大挪移神功。\n");
        if( query("combat_exp", me)<350000 )
             return notify_fail("你的实战经验不足，不能修习乾坤大挪移神功。\n");
        if( query("max_neili", me)<1200 )
             return notify_fail("你的内力不足，不能修习乾坤大挪移神功。\n");
        if(me->query_skill("force") < 200)
             return notify_fail("你的内功等级不足，不能修习乾坤大挪移神功。\n");
        if(!me->query_skill("shenghuo-shengong",1) &&
           !me->query_skill("jiuyang-shengong",1) &&
           !me->query_skill("jiuyin-zhengong",1))
             return notify_fail("你发觉你的内功路子和乾坤大挪移走的路子不同，再练下去没有多大的好处。\n");
        if( query("jing", me)<30 )
             return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");
        if(me->query_skill("qiankun-danuoyi",1) > (me->query_skill("force",1)+10))
             return notify_fail("由于你的内功的火侯不够，不能再进行更高一层的提高。\n");
        if( query("neili", me)<neili_lost )
            return notify_fail("你内力不够，无法钻研这么高深的武功。\n");
        if( query("combat_exp", me)<qklevel*qklevel*qklevel/10 )
             return notify_fail("你的实战经验不足，再怎么读也没用。\n");
        if(qklevel > 400)
             return notify_fail("你练乾坤大挪移第七层心法时，发觉一共有一十九句心法没能练成，结果没能再长了。\n");
        if(qklevel > 60 && qklevel > lit+50)
             return notify_fail("你的读书写字等级不够，认不完羊皮上的字。\n");
//        if(qklevel > 60 && qklevel > med+40)
//             return notify_fail("你的本草术理等级不够，理解不完羊皮上的字的意思。\n");

        switch(random(3)) {
          case 0: message("vision", me->name() + "半边脸孔胀得血红，半边脸颊却发铁青。\n", environment(me), me); break;
          case 1: message("vision", me->name() + "脸上忽然变红，额头汗如雨下，如堕碳火。\n", environment(me), me); break;
          case 2: message("vision", me->name() + "脸上忽然变青，身子微颤，如堕寒冰。\n", environment(me), me); break;
          }

        if(qklevel > 190){
                neili_lost = 30;
                me->receive_damage("jing", 55);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第七层心法，似乎有点心得。\n");
                return 1;
                }
        if(qklevel > 180){
                neili_lost = 25;
                me->receive_damage("jing", 50);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第六层心法，似乎有点心得。\n");
                return 1;
                }
        if(qklevel > 150){
                neili_lost = 20;
                me->receive_damage("jing", 45);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第五层心法，似乎有点心得。\n");
                return 1;
                }
        if(qklevel > 120){
                neili_lost = 15;
                me->receive_damage("jing", 40);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第四层心法，似乎有点心得。\n");
                return 1;
                }
        if(qklevel > 90){
                neili_lost = 10;
                me->receive_damage("jing", 35);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第三层心法，似乎有点心得。\n");
                return 1;
                }
        if(qklevel > 60){
                neili_lost = 6;
                me->receive_damage("jing", 30);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第二层心法，似乎有点心得。\n");
                return 1;
                }
        else{
                neili_lost = 5;
                me->receive_damage("jing", 25);
                set("neili",query("neili",  me)-neili_lost, me);
                me->improve_skill("qiankun-danuoyi", lit/3+1);
                write("你正在研习乾坤大挪移的第一层心法，似乎有点心得。\n");
                return 1;
                }
}