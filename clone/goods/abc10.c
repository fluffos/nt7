// This program is a part of NT MudLIB
// ab_crystal.c 能力水晶

#include <ansi.h>

inherit ITEM;

int is_spe_crystal() { return 1; }
void create()
{
        set_name(HIY"超能力水晶"NOR, ({ "ability2 crystal", "ability2", "crystal" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIY "表面泛着金色光芒的超能力水晶，是一个储存着强化星级、改造品级\n"
                            HIY "及套装等级诸多能量的水晶，在干将处可实现不需任何其他材料就能\n"
                            HIY "让新签名的装备拥有同样的强化星级、改造品级及套装等级。\n" NOR);
                set("value", 50000);
                set("unit", "块");
        }
        set("qianghua_level", 10);
        set("set_data", 1);
        set("autoload", 1);
        setup();
}

string extra_long() 
{
        string str;

        if( !query("set_data") ) return "";
        str =  sprintf( HIM "\n能量存储\n" NOR); 
        str += sprintf(WHT "改造品级 : %d\n" NOR, query("reform_level")); 
        str += sprintf(WHT "强化星级 : %d\n" NOR, query("qianghua_level")); 
        str += sprintf(WHT "套装等级 : %d\n" NOR, query("upsuit_level")); 
        return str;
}
