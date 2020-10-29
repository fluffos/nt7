// /u/hotjc/dzt.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "打造台" NOR, ({ "dazao tai", "tai" }) );
        set_weight(3000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
          set("long", HIG @LONG
这是一个签名、强化、绿化、升级装备的打造台。
镶嵌物品              enchase
附魔属性              enchant
防具升级              forge
装备打孔              notch
宝石合并              combine
洗 装 备              melt
装备强化              qianghua
装备绿化              dosuit
LONG NOR );
                set("value", 2000);
                set("unit", "片");
                set("no_get", 1);
                set("auto_load", 1);
        }
        setup();
}