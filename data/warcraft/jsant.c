// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("羽毛[2;37;0m[2;37;0m", ({"yumao"}));        
        set("gender", "男性");                
        set("long", "羽毛[2;37;0m
它是欧阳羽的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jsant");
        set("owner_name", "欧阳羽");
        set_temp("owner", "jsant");
        set_temp("owner_name", "欧阳羽");
        ::setup();
}
