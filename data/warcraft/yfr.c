// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宠物[2;37;0m[2;37;0m", ({"cwg"}));        
        set("gender", "女性");                
        set("long", "好牛逼[2;37;0m
它是云菲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yfr");
        set("owner_name", "云菲");
        set_temp("owner", "yfr");
        set_temp("owner_name", "云菲");
        ::setup();
}
