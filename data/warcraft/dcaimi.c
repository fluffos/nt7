// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("选无神[2;37;0m[2;37;0m", ({"xwushen"}));        
        set("gender", "男性");                
        set("long", "最佳护卫[2;37;0m
它是大猜谜的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "dcaimi");
        set("owner_name", "大猜谜");
        set_temp("owner", "dcaimi");
        set_temp("owner_name", "大猜谜");
        ::setup();
}
