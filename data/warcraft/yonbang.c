// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("帮用[2;37;0m[2;37;0m", ({"bangyon"}));        
        set("gender", "女性");                
        set("long", "帮用[2;37;0m
它是用帮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yonbang");
        set("owner_name", "用帮");
        set_temp("owner", "yonbang");
        set_temp("owner_name", "用帮");
        ::setup();
}
