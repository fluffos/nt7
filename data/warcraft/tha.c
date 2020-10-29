// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m日月镜[2;37;0m[2;37;0m", ({"qwe"}));        
        set("gender", "男性");                
        set("long", "shit[2;37;0m
它是桃开花的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "tha");
        set("owner_name", "桃开花");
        set_temp("owner", "tha");
        set_temp("owner_name", "桃开花");
        ::setup();
}
