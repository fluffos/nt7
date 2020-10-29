// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白玉麒麟[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "女性");                
        set("long", "神兽之王[2;37;0m
它是梅剑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "minihs");
        set("owner_name", "梅剑");
        set_temp("owner", "minihs");
        set_temp("owner_name", "梅剑");
        ::setup();
}
