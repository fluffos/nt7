// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("香菜[2;37;0m[2;37;0m", ({"xiangcai"}));        
        set("gender", "女性");                
        set("long", "香菜[2;37;0m
它是花太香的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "rymud");
        set("owner_name", "花太香");
        set_temp("owner", "rymud");
        set_temp("owner_name", "花太香");
        ::setup();
}
