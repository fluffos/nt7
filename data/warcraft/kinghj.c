// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m白玉麒麟[2;37;0m[2;37;0m", ({"kinghjshou"}));        
        set("gender", "男性");                
        set("long", "四大神兽[2;37;0m
它是古月的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kinghj");
        set("owner_name", "古月");
        set_temp("owner", "kinghj");
        set_temp("owner_name", "古月");
        ::setup();
}
