// This program is a part of NITAN MudLIB 
// redl 2015/2
#include <ansi.h>
inherit ITEM;

#define EXPG 1000000

void create()
{
        set_name(NOR HIR"新年"HIY"礼盒"NOR,({"box"}));
        set("long", HIY "这是一只华丽的礼品盒子，不同等级的玩家可以获得不同的礼品。你可以让练功号（open box）打开它。\n" NOR HIK "(下线和扔掉会丢失，可以送人，赶快使用)\n" NOR); 
        set("unit", "些");
        set("base_unit", "个");
                //set("no_give","这样东西不能离开你。\n");
                set("no_sell", "这样东西不能离开你。\n");
                set("no_put", "这样东西不能放在那儿。\n");
                set("no_store", "这样东西不能放在那儿。\n");
                set("no_get", "这样东西不能离开那儿。\n");
                set("no_steal", "这样东西不能离开那儿。\n");
                set("no_beg", "这样东西不能离开那儿。\n");
                set("base_value", 0);
                set("base_weight",1);
}

int give_ob(object me, object ob)
{
        ob->move(me, 1);
        tell_object(me, NOR + query("name") + NOR + "爆炸，你获得了" + query("name", ob) + NOR + "。\n");
        return 1;
}
int drop_ob(object me, object ob)//不重要的，可能超重的东西扔地上
{
        ob->move(environment(me));
        tell_object(me, NOR + query("name") + NOR + "爆炸，你看见地上冒出了" + query("name", ob) + NOR + "。\n");
        return 1;
}

int do_open(string arg)
{
        object ob, me = this_player();
        int bon, lv = query("level", me);

        string file = "/temp/qroom/" + query("id", me) + ".c";
        
        if (!arg || arg!="box") return 0;
        if( me->is_busy() ||
                me->is_fighting()
                ) {
                write(NOR BUSY_MESSAGE NOR);
                return 1;
        }
        if( query("doing", me) ) {
                write(NOR "你现在正在忙于锻炼，不能开礼盒。\n" NOR);
                return 1; 
        }
        if( !query("no_fight", environment(me)) ) {
                write(NOR "你必须在安全的地方才能开礼盒。\n" NOR);
                return 1; 
        }
        if(sizeof(filter_array(all_inventory(environment(me)), (: playerp :))) < 5) {
                write(NOR "你必须到人多热闹的地方(比如聊天室)去开礼盒。\n" NOR);//炫耀+监督
                return 1; 
        }
        
        me->start_busy(3);
        message_vision(NOR + CYN + "$N" + NOR + CYN + "抬手打开一个" + query("name") + NOR + 
                CYN + "，其中冲出青色霞光一卷，$N" + NOR + CYN + "消失了。\n" + NOR, me);

        if (!sizeof(get_dir("/temp/qroom"))) mkdir("/temp/qroom"); 
        if (!(load_object(file)))  
                cp("/u/redl/teleport/qroom.c", file); 
        me->move(file); //移到独自空间，以免东西掉地上被捡取
        bon = (200-lv) * EXPG;
        if (bon<EXPG) bon = EXPG;
        GIFT_D->work_bonus(me, ([ "prompt":"被福地霞光冲刷洗涤之后", "exp" : bon, "pot" : bon / 5, "mar" : bon / 20 ]));
        give_ob(me, new("/kungfu/class/sky/obj/shenjiu"));
        give_ob(me, new("/kungfu/class/sky/obj/shenjiu"));
        ob = new("/clone/gift/jiuzhuan");
        ob->set_amount(300);
        drop_ob(me, ob);
        give_ob(me, new("/d/emei/obj/pantao"));
        give_ob(me, new("/d/emei/obj/pantao"));
        give_ob(me, new("/d/emei/obj/pantao"));
        give_ob(me, new("/d/emei/obj/pantao"));
        give_ob(me, new("/d/emei/obj/pantao"));
        give_ob(me, new("/u/redl/obj/fanghuamu"));
        give_ob(me, new("/clone/goods/moon_mf"));
        give_ob(me, new("/clone/goods/tianshi-charm"));
        destruct(this_object());
        return 1;
}

void init()
{
        add_action("do_open","open"); 
}

