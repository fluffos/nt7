// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m拉土车[2;37;0m[2;37;0m", ({"aways"}));        
        set("gender", "男性");                
        set("long", "菜菜子的坐骑[2;37;0m
它是菜菜子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "away");
        set("owner_name", "菜菜子");
        set_temp("owner", "away");
        set_temp("owner_name", "菜菜子");
        ::setup();
}
