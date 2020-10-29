// Code of ShenZhou
// xuesang.c  
// By Haowen 1/14/98

#include <ansi.h>

inherit ITEM;


void create()
{
        set_name("雪桑",({"xue sang","sang"}));
        set_weight(900000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一棵天山特有的生长在雪峰的雪桑树。
传说有一种雪蚕最喜欢生长在这雪桑之上，经常有人来寻找(xunzhao)?\n");
                set("unit", "棵");
                set("value", 8);
                set("no_get", 1);
                set("leaves",20);
       }
       
        setup();
}

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "xunzhao");
        add_action("do_feed", "fed");
        add_action("do_look", "look");
        add_action("do_look", "l");
}

int do_search()
{
object obj=this_object(),me=this_player();

if( query_temp("find_can", me) )
        return notify_fail("雪蚕已经在雪桑上了，你还找什么呀？\n");

if( random(query("kar", me))>15 )
        {
        tell_object(me,HIG"你仔细的翻动雪桑叶，到处寻找起来。\n" NOR);
        if(random(10)>5)
                {
                tell_object(me,HIR"你忽然眼前一亮，一条晶莹雪白的雪蚕(can)正卧在一片雪桑叶上！\n"NOR);
                set_temp("find_can", 1, me);
                }
        addn("neili", -10, me);
        return 1;
        }
else    {
        addn("neili", -10, me);
        return notify_fail("你找了半天什么也没找到！\n");
        }
}

int do_feed(string arg)
{
object ob,obj=this_object(),me=this_player();
string what;

//message_vision(arg);
if (!arg || sscanf(arg,"%s",what)!=1)
        return notify_fail("你要喂什么？\n");

if (what!="can")
        return notify_fail("这里的雪桑叶只有天山雪蚕爱吃！\n");

if( !query_temp("find_can", me) )
        return notify_fail("这雪桑上什么也没有，你要喂什么？\n");

if( query_temp("get_si", me) )
        return notify_fail("雪蚕刚吐过丝，恐怕现在不会再吐了！\n");

if( query("leaves", obj)>1 )
        {
        tell_object(me,HIY "你摘了一片雪桑叶喂给雪蚕吃。雪蚕仔细的吃了起来。\n" NOR);
        set("leaves",query("leaves",  obj)-1, obj);
                if (random(10)>5)
                        {
                        tell_object(me,HIY "雪蚕吃完了桑叶，头一昂，吐出一根蚕丝，你赶紧用手接住。\n" NOR);
                        set_temp("get_si", 1, me);
                        ob=new("/d/xingxiu/obj/xuecan-si");
                        ob->move(me);
                        }
        return 1;}
else 
        {
        call_out("grow",200,obj);
        return notify_fail("雪桑上的叶子都摘完了，等慢慢长出来再来喂吧！\n");
        }
}

int do_look(string arg)
{
        object ob,me=this_player();
        string what;
        ob=this_object();
 
        if( !arg || arg == "" || sscanf(arg,"%s",what)!=1) return 0;

        
        if(what=="sang" || what=="xue sang")
                {        
                if( query_temp("find_can", me) )
                        tell_object(me,query("long", ob)+"现在上面有一只雪蚕(can)！好象正在等你喂(fed)它。\n");
                else tell_object(me,query("long", ob));
                return 1;
                }

return 0;

}

int grow(object ob)
{
        message_vision(HIG "雪桑上的桑叶又长出来了！\n");
        set("leaves", 20, ob);
}