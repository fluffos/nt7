// beehive.c 蜂箱
// by April     01.08.26
// update by April 01.10.30


#include <ansi.h>

inherit COMBINED_ITEM;

int auto_check(object me, object ob);

void create()
{
        set_name(HIW "玉蜂箱" NOR, ({ "feng xiang", "beehive", "box", "xiang" }) );
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "个");
                set("long", HIW "这是古墓派木制的玉蜂箱。里面嗡嗡的，不知道有多少玉蜂。\n" NOR);
                set("base_unit", "个");
                set("value", 1000);
                set("material", "wood");
                set("no_sell", 1);
                set("no_give",0);
                set("no_get",1);
                set("base_weight",5000);
        }

        set("no_refresh", 1);

        set_amount(1);
        setup();
}

void init()
{
        object me = this_player();
        if( query("id", me) != "sunpopo"){
                set("no_drop",  "这么有用的东西怎么能扔了呢。\n");
                set("no_steal", "这个东西你偷不到。\n");
        }

        add_action("do_open", "open");
        add_action("do_close", "close");
        add_action("do_fang", "fang");
        add_action("do_give","give");
        add_action("do_cai", "cai");
        add_action("do_dest", "dest");

}

int do_fang(string arg)
{
        object me, ob;
        me = this_player();
        ob = this_object();

        if(!arg || (arg != "feng xiang" && arg != "beehive" && arg != "box" && arg != "xiang"))
                return 0;
        if( query("down", ob))return notify_fail("你糊涂了？\n");
        if( !ob) return notify_fail("你并没有拿着蜂箱啊？\n");
        if(strsrch(query("short", environment(me)), "树林") == -1)
                return notify_fail("你找不到合适的地方放蜂箱！ \n");
        if( query("owner", ob) != me)return notify_fail("这你的蜂箱吗？\n");
        if(present("feng xiang", environment(me))) return notify_fail("这里已经有别人在放养玉蜂了。\n");
        if( query("lastplace", ob) == environment(me))return notify_fail("玉蜂刚在这里采过蜜！\n");

        ob = present("feng xiang", me);

        if(me->is_busy())
                return notify_fail("你正忙着呢! \n");

        message_vision(HIB"$N在树林中找了一块儿空地，轻轻地把蜂箱放在地上。\n"NOR,me);

        set("down", 1, ob);
        ob->move(environment(me));
        remove_call_out("auto_check"); 
        call_out("auto_check", 5+random(5),me,ob);
        return 1;
}

int do_open(string arg){
        object me = this_player();
        object ob = this_object();
        string descrp;

        if(!arg || (arg != "feng xiang" && arg != "beehive" && arg != "box" && arg != "xiang"))
                return 0;
        if( query("open", ob))return notify_fail("你糊涂了？\n");
        if( query("owner", ob) != me)return notify_fail("这你的蜂箱吗？\n");
        if(me->is_busy()) return notify_fail("你正忙着呢！ \n");
        if( !query("down", ob))return notify_fail("你得先把玉蜂箱放下！\n");
        if( query("open", ob))return notify_fail("玉蜂箱门开着呢！\n");
//      if(query("bee_out")) return notify_fail("你的玉蜂群忙着呢！\n");

        remove_call_out("auto_check");
        call_out("auto_check", 5+random(5),me,ob);

        message_vision(HIG"$N轻轻地打开玉蜂箱的门，玉蜂陆陆续续地飞出来，采蜜去了。\n"NOR,me);

        set("open", 1, ob);
        set("lastplace", environment(me), ob);
        set("mi", 1, ob);

        return 1;
}

int do_close(string arg){
        object me = this_player();
        object ob = this_object();
        string descrp;

        if(!arg || (arg != "feng xiang" && arg != "beehive" && arg != "box" && arg != "xiang"))
                return 0;
        if( !query("open", ob))return notify_fail("你糊涂了？\n");
        if( query("owner", ob) != me)return notify_fail("这是你的蜂箱吗？\n");
        if(me->is_busy()) return notify_fail("你正忙着呢！ \n");
        if( !query("down", ob))return notify_fail("你得先把玉蜂箱放下！\n");
        if( !query("open", ob))return notify_fail("玉蜂箱门关着呢！\n");
        if( query("qi", me)<100)return notify_fail("你已经精疲力竭，无法召唤玉蜂回来了！\n");

        message_vision(HIG"$N口中念念有词，一会儿玉蜂陆陆续续地都飞了回来，$N轻轻关上玉蜂箱门,把蜂箱背在身上。\n"NOR,me);

        set("open", 0, ob);
        set("down", 0, ob);
        ob->move(me);

        me->receive_damage("qi", 10+random(10));

        remove_call_out("auto_check");

        return 1;
}


int auto_check(object me,object ob)
{
        int lvl;
        if (! me)
        {
                destruct(this_object());
                return 1;
        }
        lvl = me->query_skill("qufeng", 1);

        if( environment(ob) != environment(me) ){
                set("escaped", 1, ob);
                destruct(this_object());
                message_vision(HIR"工作时你怎么跑了？玉蜂都没人管啦！。\n"NOR,me);
                return 0;
        }
        if( query("mi", ob)<40 )
                addn("mi", 10, ob);
        if( query("mi", ob)>25 && random(2) == 0 || 
            query("mi", ob) >= 40 )
        {
                message_vision(HIW"玉蜂团团打转，看样子蜂箱的蜜已经采满了,你应该回去了。\n"NOR,me);
                return 1;

        }
        else if (random(15) == 0)
        {
                if (random(3) == 0)
                {
                        message_vision("$N看见一些玉蜂在一个地方奇怪地舞着，也许有什么药材可以采(cai yao)吧。\n",me);
                        set("yaocai_h", 1, environment(me));
                }
                else
                {
                        message_vision("$N看见一些玉蜂在一个地方奇怪地舞着，也许有什么药材可以采(cai yao)吧。\n",me);
                        set("yaocai", 1, environment(me));
                }

        }
        else if( query("mi", ob)%2 == 0 && random(2) == 0 )
        {
                message_vision(HIY"$N嘴里不断发出嗡嗡声，指导玉蜂更有效率的采蜜。\n"NOR, me);
                me->start_busy(random(3));
                addn("qi", -(2+random(3)), me);
                if (lvl < 600)
                me->improve_skill("qufeng",lvl/3+random(lvl/2));
                me->improve_skill("force",lvl/5+random(lvl/3));

        }

        call_out("auto_check",5,me,ob);
        return 1;
}

int do_give(string arg)
{
        string target, item;
        object obj, who,ping, me=this_player();
        string msg;
//        int    exp,qn,gj,i,j;
        int    qn,gj,i,j;
        mixed exp;
        object *inv;


    if(!arg) return notify_fail("你要给谁什么东西？\n");

    if( sscanf(arg, "%s to %s", item, target)==2
        || sscanf(arg, "%s %s", target, item)==2 );
    else return notify_fail("你要给谁什么东西？\n");

        if ( item != "beehive" && item !="box" && item != "xiang" ) return 0;
        if ( target != "sun" && target !="nanny" ) return 0;
        if ( !objectp(obj = present(item, me)) ) return notify_fail("你身上没有这样东西。\n");
        if (me->is_busy()) return notify_fail("你正忙着呢。\n");
    if (!objectp(who = present(target, environment(me))) || !living(who))
        return notify_fail("这里没有这个人。\n");
        if ( userp(who) ) return notify_fail("对方不接受这样东西。\n");
        if( query("race", who) != "人类" )
                return notify_fail("别找碴儿！怎么把玉蜂箱交给畜生？\n");
        if( who == me) return notify_fail("自己给自己？！\n");

        message_vision("$N给$n一个"+HIW"玉蜂箱。\n"NOR, me, who);

        if( query("owner", obj) == me )
        {
                if(query("escaped")) {
                        message_vision(CYN"$N不好意思地搔了搔头。\n"NOR, me, who);
                        message_vision(CYN"$N红着脸对孙婆婆说道，这次工作没干好。\n"NOR, me, who);
                        message_vision(CYN"$n轻轻拍了拍$N的头。\n"NOR, me, who);
                        message_vision(CYN"$n和蔼地对$N说道：没关系，下次注意就好。\n"NOR, me, who);
                        if( query_temp("gm_xunfeng", me) ) delete_temp("gm_xunfeng", me);
                }
                else if( query("mi", obj)<25 )
                {
                        message_vision(CYN"$n说道：蜂蜜没有采满啊，没关系，下次注意就好。\n"NOR,me,who);
                        if( query_temp("gm_xunfeng", me) ) delete_temp("gm_xunfeng", me);
                }
                else
                {
                        message_vision(CYN"$n轻轻拍了拍$N的头。\n"NOR, me, who);
                        message_vision(CYN"$n和蔼地对$N说道：辛苦$N啦，下去休息一下吧。\n"NOR, me, who);
                        exp = 140+random(40);
                        qn = 40 + random(40);
                        gj = 5 + random(5);
                        if( query("potential", me)>me->query_potential_limit() )
                                qn = 1 + random(2);
                        msg=sprintf(HIW"这次养蜂任务共得到:%d经验、%d潜能和%d门派功绩。\n"NOR,exp,qn, gj);
                        tell_object(me,msg);
                        if( query_temp("gm_xunfeng", me) ) delete_temp("gm_xunfeng", me);
                        addn("combat_exp", exp, me);
                        addn("potential", qn, me);
                        addn("family/gongji", gj, me);

                        if (random(1)==0)
                        {
                                inv = all_inventory(me);
                                j=0;
                                for(i=0; i<sizeof(inv); i++)
                                        if( query("name", inv[i]) == CYN"青瓷瓶"NOR )
                                        j += 1;
                                if (j > 4)
                                tell_object(me,"孙婆婆对你说：你已经有好多青瓷瓶了，我就不给你了。\n");
                                else if (random(5)==0)
                                {
                                        ping = new("/d/gumu/npc/obj/qingci-ping");
                                        set("liquid/remaining", 10, ping);
                                        set("liquid/name", "玉蜂王浆", ping);
                                        ping->move(me);
                                        tell_object(me,"孙婆婆给你一瓶玉蜂王浆。\n");

                                }
                                else
                                {
                                        ping = new("/d/gumu/npc/obj/qingci-ping");
                                        set("liquid/remaining", 10, ping);
                                        ping->move(me);
                                        tell_object(me,"孙婆婆给你一瓶玉蜂蜜。\n");

                                }
                        }
                }

        }
        else
        {
                message_vision(CYN"$n对$N微微笑了笑。\n"NOR, me, who);
                message_vision(CYN"$n说道：多谢啦！\n"NOR, me, who);
        }

        destruct(obj);

        return 1;
}

int do_cai(string arg)
{
        object me = this_player();
        object here = environment(me);
        int i;
        object yaocai;

        if ( !arg && arg != "yao" ) return 0;
        if( !query("yaocai", here) && !query("yaocai_h", here))return 0;

        if( query("yaocai", here)){
                set("yaocai", 0, here);
                switch (random(5)){
                case 0 : yaocai = new("/clone/herb/chantui");
                        break;
                case 1 : yaocai = new("/clone/herb/muxiang");
                        break;
                case 2 : yaocai = new("/clone/herb/shengma");
                        break;
                case 3 : yaocai = new("/clone/herb/chaihu");
                        break;
                case 4 : yaocai = new("/clone/herb/shanju");
                        break;
                }
                yaocai->move(me);
                message_vision("$N拨开杂草发现了"+query("name", yaocai)+"。\n",me);
        }
        if( query("yaocai_h", here)){
                set("yaocai_h", 0, here);
                switch (random(3)){
                case 0 : yaocai = new("/clone/herb/renshen");
                        break;
                case 1 : yaocai = new("/clone/herb/heshouwu");
                        break;
                case 2 : yaocai = new("/clone/herb/tufuling");
                        break;
                }
                yaocai->move(me);
                message_vision("$N拨开杂草发现了"+query("name", yaocai)+"。\n",me);
        }
        return 1;
}
int do_dest(string arg){
         object obj;
         object me = this_player();

         if (arg != "box" && arg != "xiang" )
                return notify_fail("你只能摧毁蜂箱。\n");
         obj = present(arg, environment(me));
         if (!obj)  return notify_fail("你只能摧毁自己的蜂箱。\n");
         if( query("owner", obj) != me || !obj )
                return notify_fail("你只能摧毁自己的蜂箱。\n");
         if (obj)
         {
                   message_vision(HIG"$N发现这个蜂箱已经废弃了，一脚把它踢了个粉碎。\n"NOR,me);
                   destruct(obj);
         }
         else return notify_fail("没有这样东西。。。。\n");
         return 1;
}