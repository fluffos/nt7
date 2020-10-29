// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("贤哥麒麟[2;37;0m[2;37;0m", ({"wzxride"}));        
        set("gender", "男性");                
        set("long", "贤哥麒麟[2;37;0m
它是胃中闲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wzx");
        set("owner_name", "胃中闲");
        set_temp("owner", "wzx");
        set_temp("owner_name", "胃中闲");
        ::setup();
}
