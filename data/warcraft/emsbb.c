// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "一只麒麟[2;37;0m
它是服侍主人的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emsbb");
        set("owner_name", "服侍主人");
        set_temp("owner", "emsbb");
        set_temp("owner_name", "服侍主人");
        ::setup();
}
