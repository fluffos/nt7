// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拖拖[2;37;0m[2;37;0m", ({"tuotuo"}));        
        set("gender", "女性");                
        set("long", "   [2;37;0m
它是冰冰贴的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lxddongwu");
        set("owner_name", "冰冰贴");
        set_temp("owner", "lxddongwu");
        set_temp("owner_name", "冰冰贴");
        ::setup();
}
