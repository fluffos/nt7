// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是喝个咖啡的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nnx");
        set("owner_name", "喝个咖啡");
        set_temp("owner", "nnx");
        set_temp("owner_name", "喝个咖啡");
        ::setup();
}
