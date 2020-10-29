// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"meccepet"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是阿兰千月的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "mecce");
        set("owner_name", "阿兰千月");
        set_temp("owner", "mecce");
        set_temp("owner_name", "阿兰千月");
        ::setup();
}
