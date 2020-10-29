// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m寰宇天晶[2;37;0m[2;37;0m", ({"lianga"}));        
        set("gender", "男性");                
        set("long", "停权[2;37;0m
它是笑沧海的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xyab");
        set("owner_name", "笑沧海");
        set_temp("owner", "xyab");
        set_temp("owner_name", "笑沧海");
        ::setup();
}
