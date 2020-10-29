//Cracked by Kafei
//桃花岛经书，literate 100lv後可以请教别人至200lv，但是比learn慢很多。
//可以向player请教。(literate > 200 ，桃花弟子)
//maco 1999/5/9

#include <ansi.h>
inherit ITEM;
string* names = ({
        "《国策》",
        "《楚辞》",
        "《诗经》",
        "《周髀算经》",
});

string* longs = ({
        "这是一册厚重的古书，文字极多，却很少注解。\n",
        "这是一册破旧的古书，有些字迹已经模糊不清，难以理解。\n",
        "这是一册薄皮古书，写满了蝇头小字，不易看得清楚。\n",
});
void create()
{
        set_name(names[random(sizeof(names))], ({"book","jing","book"}));
        set_weight(300);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "册");
                set("value", 4000);
                set("no_sell",1);
             set("long",longs[random(sizeof(longs))]);
        }
}
void init()
{
        add_action("do_qingjiao", "qingjiao");
}

int do_qingjiao(string arg)
{
        object me, ob;
        int jing_cost,grade;

        me = this_player();
        jing_cost=150/query("int", me)+1;
        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");
        if( me->is_fighting() )
                return notify_fail("先把这场架打完吧。\n");
        if( !arg )
                return notify_fail("你想请教谁？\n");
        if(!objectp(ob = present(arg, environment(this_player()))))
                return notify_fail("这里没有这个人。\n");
        if (me == ob)
                return notify_fail("自己请教自己？\n");
        if( !ob->is_character() || ob->is_corpse() )
                return notify_fail("看清楚一点，那并不是活物。\n");
        if( !living(ob) )
                return notify_fail("嗯....你得先把" + ob->name() + "弄醒再说。\n");
        if( query("potential", me)<2 )
                return notify_fail("你的潜能不足，无法领会任何东西。\n");

        if(me->query_skill("literate",1) < 100 )
                return notify_fail("凭你现在的学识，还无法理解经书上的知识。\n");
        if(ob->query_skill("literate",1) < 200 )
                return notify_fail("以"+ ob->name() +"的学识，还不足以指导你。\n");
        if(me->query_skill("literate",1) > 300 )
                return notify_fail("你的学识已经相当精深，理解这本书无甚困难之处。\n");
        
        if( query("family/family_name", me) != "桃花岛" || 
        query("family/family_name", ob) != "桃花岛" )
        {
        printf("你向%s请教经书上的疑难之处，然而对方似乎不想为你解释。\n", ob->name());
        }
        else if (me->query_skill("literate") >= ob->query_skill("literate"))
        {
        printf("%s的学问已经无法再指导你什麽了。\n", ob->name());
        }

         else if( query("jing", me)>jing_cost )
        {
                printf("你向%s请教经书上的疑难之处，用心思考其中涵义。\n", ob->name());
                if ((int)me->query_skill("literate",1) < 200) {
                addn("potential", -2, me);
                me->improve_skill("literate",(random(10)+query("int", me)*2/3));}
                
                else {
                addn("potential", -2, me);
                me->improve_skill("literate",(random(10)+query("int", me)/3));
                        }
                }
        
        else
        {
                jing_cost=query("jing", me);
                write("你现在太累了，没有办法专心研读经书。\n");
        }
        me->receive_damage("jing", jing_cost );
        return 1;
}