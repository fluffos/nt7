// This program is a part of NITAN MudLIB 
// redl 2013/3
#include <ansi.h>
inherit ITEM;

#define EXPG 200000000

void create()
{
        set_name(NOR HIR"国庆"HIY"礼盒"NOR,({"box"}));
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
        int lv = query("level", me);
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
        
        if (lv >= 160) {
                GIFT_D->work_bonus(me, ([ "prompt":"被福地霞光冲刷洗涤之后", "exp" : EXPG / 9, "pot" : EXPG / 36 ]));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/wangzhe-zhixin"));
                give_ob(me, new("/clone/goods/wangzhe-zhixin"));
                give_ob(me, new("/clone/goods/wangzhe-zhixin"));
                give_ob(me, new("/d/dongtian/emei/lingpai3"));
                give_ob(me, new("/d/dongtian/guanwai/lingpai3"));
                give_ob(me, new("/d/dongtian/huanghe/lingpai3"));
                give_ob(me, new("/d/dongtian/huangshan/lingpai3"));
                give_ob(me, new("/d/dongtian/songshan/lingpai3"));
                give_ob(me, new("/d/dongtian/yueyang/lingpai3"));
        }
        else if (lv >= 80) {
                GIFT_D->work_bonus(me, ([ "prompt":"被福地霞光冲刷洗涤之后", "exp" : EXPG / 3, "pot" : EXPG / 12 ]));
                ob = new("/clone/medicine/yuqingwan");
                ob->set_amount(3);
                give_ob(me, ob);
                ob = new("/clone/money/thousand-gold");
                ob->set_amount(50);
                drop_ob(me, ob);
                give_ob(me, new("/clone/goods/qianghua_crystal"));
                give_ob(me, new("/clone/goods/qianghua_crystal"));
                give_ob(me, new("/clone/goods/qianghua_crystal"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/hongmeng-lingqi"));
                give_ob(me, new("/clone/goods/wangzhe-zhixin"));
                give_ob(me, new("/clone/goods/noname"));
                give_ob(me, new("/d/dongtian/emei/lingpai3"));
                give_ob(me, new("/d/dongtian/guanwai/lingpai3"));
                give_ob(me, new("/d/dongtian/huanghe/lingpai3"));
                give_ob(me, new("/d/dongtian/huangshan/lingpai3"));
                give_ob(me, new("/d/dongtian/songshan/lingpai3"));
                give_ob(me, new("/d/dongtian/yueyang/lingpai3"));
                give_ob(me, new("/d/dongtian/emei/lingpai3"));
                give_ob(me, new("/d/dongtian/guanwai/lingpai3"));
                give_ob(me, new("/d/dongtian/huanghe/lingpai3"));
                give_ob(me, new("/d/dongtian/huangshan/lingpai3"));
                give_ob(me, new("/d/dongtian/songshan/lingpai3"));
                give_ob(me, new("/d/dongtian/yueyang/lingpai3"));
        }
        else {
                GIFT_D->work_bonus(me, ([ "prompt":"被福地霞光冲刷洗涤之后", "exp" : EXPG, "pot" : EXPG / 4 ]));
                ob = new("/clone/medicine/yuqingwan");
                ob->set_amount(12);
                give_ob(me, ob);
                ob = new("/clone/gift/xuanhuang");
                ob->set_amount(200);
                drop_ob(me, ob);
                ob = new("/clone/money/thousand-gold");
                ob->set_amount(200);
                drop_ob(me, ob);
                give_ob(me, new("/clone/goods/noname"));
                give_ob(me, new("/clone/medal/yongshi_xunzhang"));
                give_ob(me, new("/clone/medal/vip_xunzhang"));
                give_ob(me, new("/clone/medal/diamond_xunzhang"));
                give_ob(me, new("/u/redl/obj/fanghuamu"));
                give_ob(me, new("/d/dongtian/obj/liudibi"));
                give_ob(me, new("/u/redl/obj/chutou3"));
                give_ob(me, new("/u/redl/obj/chutou3"));
                give_ob(me, new("/clone/goods/tianshi-charm"));
                give_ob(me, new("/clone/goods/tianshi-charm"));
        }
        give_ob(me, new("/u/redl/npc/obj/ntb2"));
        ob = new("/clone/gift/jiuzhuan");
        ob->set_amount(100);
        drop_ob(me, ob);
        destruct(this_object());
        return 1;
}

void init()
{
        add_action("do_open","open"); 
}

