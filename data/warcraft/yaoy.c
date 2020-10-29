// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m拉土车[33m[2;37;0m[2;37;0m", ({"yaoys"}));        
        set("gender", "女性");                
        set("long", "我的坐骑[2;37;0m
它是菜由的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaoy");
        set("owner_name", "菜由");
        set_temp("owner", "yaoy");
        set_temp("owner_name", "菜由");
        ::setup();
}
