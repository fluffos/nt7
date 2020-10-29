// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "白马[2;37;0m
它是冒险游戏的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "avg");
        set("owner_name", "冒险游戏");
        set_temp("owner", "avg");
        set_temp("owner_name", "冒险游戏");
        ::setup();
}
