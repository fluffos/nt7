// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m渡鸦[2;37;0m[2;37;0m", ({"duya"}));        
        set("gender", "女性");                
        set("long", "赤红色的狂鸦[2;37;0m
它是辉夜的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "huiye");
        set("owner_name", "辉夜");
        set_temp("owner", "huiye");
        set_temp("owner_name", "辉夜");
        ::setup();
}
