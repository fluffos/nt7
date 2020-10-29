// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("日日日[2;37;0m[2;37;0m", ({"goldrrr"}));        
        set("gender", "男性");                
        set("long", "日日日[2;37;0m
它是金揉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldrr");
        set("owner_name", "金揉");
        set_temp("owner", "goldrr");
        set_temp("owner_name", "金揉");
        ::setup();
}
