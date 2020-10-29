// This program is a part of NITAN MudLIB 
// redl 2013/7
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

#define BUNCH_NAME "菊花圣门"

void create()
{
        set_name(HIY "黄金甲" NOR, ({ "huangjin jia" }));
        set_weight(100);
                set("unit", "副");
                set("longx", NOR + "这是" + BUNCH_NAME + "特有的制服诱惑。\n" + NOR);
                set("value", 1);
                set("material", "gold");
                set("armor_prop/per", 10);
                set("armor_prop/str", 50);
                set("armor_prop/armor", 500);
                set("armor_prop/reduce_poison", 25);
                set("armor_prop/avoid_busy", 20);
                set("armor_prop/reduce_busy", 20);
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                        setup();
}        


void cimu_end(object target)
{
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target)) tell_object(target, HIR "你勉强睁开泪眼，看得见一些景象了。\n" NOR);
                delete_temp("block_msg/all", target);
        }
}


void cimu_start(object me)
{
                tell_object(me, query("name") + NOR + "上光芒一闪，显出两行金篆文：\n" + YEL + "  待到秋来九月八，我花开后百花杀\n  奶香冲天透泥潭，满城尽带黄金甲\n" + NOR + "你大叫一声捂住双眼，已经被晃瞎了...\n");
                message_vision("$N大叫一声捂住双眼，鲜血从两手的指缝间汩汩而出。\n",me);
                set_temp("block_msg/all", 1, me);
                me->start_busy(30);
                call_out("cimu_end", 30, me);
}


string long()
{
        object me = this_player();
        if (query("bunch/bunch_name", me) != BUNCH_NAME) call_out("cimu_start", 1, me);
        return query("longx");
}

int wear()
{
        object me = this_player();
        if (query("bunch/bunch_name", me) != BUNCH_NAME) {
                destruct(this_object());
                return -1;
        }
        if (query("id", me) != query("me_id")) {
                tell_object(me, NOR + "你不能佩戴这种特殊物品！\n" + NOR);//不许普通玩家非法穿戴变态属性的物品
                return -1;
        }
        if (::wear()) {
                //message_vision(YEL + "$N一把脱下衣服，拿出一件" + NOR + query("name") + NOR + YEL + "套在身上。\n" + NOR, me);
                return 1;
        }
}


int do_name(string arg)//授权
{
        object me;
        me = this_player();
        if (! wizardp(me)) return 0;
        if (! arg) return notify_fail("name id!\n");
        
                me = find_player(arg);
                if (!me || !objectp(me) || !playerp(me)) {
                        write("你目前没有发现这玩家在线。\n");
                        return 1;
                }        
        
                set("bindable", 3); 
                set("bind_owner",query("id",  me)); 
        set("me_id", arg);
                set("set_data", 1); 
                set("auto_load", 1); 
        delete("env/invisible_item", me);
        this_object()->move(me);
        tell_object(me, "你获得了特殊的帮会专用服装。\n");
        write("衣服被设为" + arg + "专用的！\n");
        return 1;
}

void init()
{
        add_action("do_name", "name");
}



        
        
