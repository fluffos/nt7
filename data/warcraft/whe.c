// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("五丫麒麟[2;37;0m[2;37;0m", ({"wacai"}));        
        set("gender", "女性");                
        set("long", "五丫麒麟[2;37;0m
它是吴吴雅的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "whe");
        set("owner_name", "吴吴雅");
        set_temp("owner", "whe");
        set_temp("owner_name", "吴吴雅");
        ::setup();
}
