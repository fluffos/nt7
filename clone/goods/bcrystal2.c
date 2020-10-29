// Written by Lonely@chinamud.cn
// crystal.c 水晶
// 应该有三个黑水合并一个黑水的设计

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("超级黑水晶", ({ "black crystal2", "crystal" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIC "一块黑色的水晶，可以抽取(extract)动态装备的属性，用来镶嵌或强化自造装备。\n" NOR);
                set("value", 50000);
                set("can_extract", 1);
                set("unit", "块");
                set("autoload", 1);
        }
        setup();
}

int do_extract(object obj)
{
        object ob;
        mapping prop;
        string *ks, key, type;
        int value;

        ob = this_object();

        if( !obj ) return notify_fail("没有这个物品。\n");

        if( query("enchase", ob) )
                return notify_fail("超级黑水晶已经抽取过一个属性了。\n");

        if( !query("enchase", obj) || !(prop=query("enchase/apply_prop", obj)) )
                return notify_fail("这个物品上面没有可用来抽取的属性。\n");

        if( obj->is_item_make() )
                return notify_fail("黑色水晶只可抽取动态装备的属性。\n");

        if( this_player()->query_skill("enchanting", 1) < 200 &&
            !present("enchant scroll", this_player()) )
                return notify_fail("你的附魔技艺不够，也没有附魔卷轴，不敢贸然下手。\n");

        if( random(100) < 60 ) {
                destruct(ob);
                return notify_fail("抽取失败，超级黑水晶消失。\n");
        }
        ks = keys(prop);
        key = ks[random(sizeof(ks))];
        value = prop[key];

        delete("enchase/apply_prop/"+key, obj);
        if( sizeof(query("enchase/apply_prop", obj))<1 )
                delete("enchase/apply_prop", obj);

        if( query("skill_type", obj))type=query("skill_type", obj);
        else type=query("armor_type", obj);

        set("enchase/apply_prop/"+key, value, ob);
        set("enchase/type", type, ob);
        set("enchase/level",query("require/level",  obj), ob);

        set("set_data", 1, ob);
        if( this_player()->can_improve_skill("enchanting") )
                this_player()->improve_skill("enchanting", random(10) + 1);
        return 1;
}

string extra_long()
{
        int i, t;
        string *apply, str, msg, type;
        int value;

        str =  sprintf( YEL "\n物品属性 : 镶嵌物<水晶>，重量%d克，下线%s丢失\n" NOR,
                        this_object()->query_weight(),
                        (this_object()->query_autoload() || query("autoload")) ? "不" : "" );

        if( query("bindowner") )
                msg = sprintf( "已经绑定使用者(%s)", query("bindowner") );
        else
                msg = "暂未绑定使用者";

        if( intp(t = query("bindable")) && t > 0 ) {
                if( t == 1 )      msg += "<装备绑定>";
                else if( t == 2 ) msg += "<拾取帮定>";
                else if( t == 3 ) msg += "<直接绑定>";
        }

        str += sprintf( YEL "绑定状态 : %s\n\n" NOR, msg);

        if( query("enchase/apply_prop") ) {
                apply = keys(query("enchase/apply_prop"));
                for (i = 0; i<sizeof(apply); i++) {
                        value = query("enchase/apply_prop")[apply[i]];
                        str += HIK "拥有属性" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
                type = query("enchase/type");
                str += sprintf(HIK "可镶装备 : %s(%s)\n" NOR, to_chinese(type), type);
                str += sprintf(HIK "可镶等级 : %d\n" NOR, query("enchase/level"));
        }

        return str;
}

string query_name() { return "黑水"; }