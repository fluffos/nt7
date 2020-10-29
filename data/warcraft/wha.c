// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大丫麒麟[2;37;0m[2;37;0m", ({"wharide"}));        
        set("gender", "女性");                
        set("long", "大丫麒麟[2;37;0m
它是吴大丫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wha");
        set("owner_name", "吴大丫");
        set_temp("owner", "wha");
        set_temp("owner_name", "吴大丫");
        ::setup();
}
