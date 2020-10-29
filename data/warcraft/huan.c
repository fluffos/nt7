// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星痕[2;37;0m[2;37;0m", ({"xinghen"}));        
        set("gender", "女性");                
        set("long", "星痕[2;37;0m
它是慕容幻的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "huan");
        set("owner_name", "慕容幻");
        set_temp("owner", "huan");
        set_temp("owner_name", "慕容幻");
        ::setup();
}
