// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蜜蜂[2;37;0m[2;37;0m", ({"budai"}));        
        set("gender", "男性");                
        set("long", "嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡嗡[2;37;0m
它是涛华的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dupenga");
        set("owner_name", "涛华");
        set_temp("owner", "dupenga");
        set_temp("owner_name", "涛华");
        ::setup();
}
