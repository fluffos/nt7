#include <weapon.h>
#include <ansi.h> 
inherit SWORD;

void create()
{
        set_name(HIC"精灵长剑"NOR, ({ "spirit sword", "sword" })); 
        set("long", "精灵的宝物，其中包含着精灵之王"+HIY"夜"+HIG"辰"NOR+"的力量。\n");
        set("no_get",1);
        set("no_give",1);
        set("no_steal",1);
        set("no_sell",1);
        set("no_put",1);
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("value", 0);
                set("material", "iron");
                set("wield_msg", HIC"$N右手结印，垂目默念咒语。一点光芒在$N掌中逐渐亮起，$n"NOR+HIC"渐渐成形。\n"NOR);
                set("unwield_msg", "$n"+HIC"从$N手中一跃而起，化为一片明亮的光芒。\n"NOR); 
        }
        init_sword(300);
        setup();
}

void owner_is_killed()
{
        write(HIY"只觉金光一闪，有什么东西不见了。\n"NOR);
       destruct(this_object());
}
/*
int query_autoload()
{
        write(HIG"一阵清风拂过身侧，仿佛在呢喃什么咒语。\n"NOR);
       return 1;
}
*/ 
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int may, dam;
        may = random(5);
        if(may >3)
        { 
        dam = random(10)+10;
        victim->receive_wound("qi",dam);
        return HIC "精灵长剑发出一道闪光，正好击中了$n。\n" NOR;
        }
}