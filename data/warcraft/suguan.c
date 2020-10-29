// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是杨肃观的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "suguan");
        set("owner_name", "杨肃观");
        set_temp("owner", "suguan");
        set_temp("owner_name", "杨肃观");
        ::setup();
}
