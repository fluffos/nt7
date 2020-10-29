// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"drink_shui_dai"}));        
        set("gender", "女性");                
        set("long", "玄武[2;37;0m
它是静二的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jingb");
        set("owner_name", "静二");
        set_temp("owner", "jingb");
        set_temp("owner_name", "静二");
        ::setup();
}
